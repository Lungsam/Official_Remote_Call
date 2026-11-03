//_________________________________________________________________
// Author		: Khaled / Lungsam
// Created		: 2026.11.03
// Description	: Enasir - Remote Call
//_________________________________________________________________

#include "StdAfx.h"

#if defined(KD_REMOTE_CALL)
#include "InstanceBase.h"
#include "PythonRemoteCall.h"

#include "PythonCharacterManager.h"
#include "PythonBackground.h"

#include "../gamelib/ItemManager.h"

CPythonRemoteCall::CPythonRemoteCall()
	: m_poHandler(nullptr), m_dwSummonTimeEnd(0)
{
}

CPythonRemoteCall::~CPythonRemoteCall()
{
	Destroy();
}

void CPythonRemoteCall::Destroy()
{
	if (m_poHandler)
	{
		Py_DECREF(m_poHandler);
		m_poHandler = nullptr;
	}
	m_dwSummonTimeEnd = 0;
}

void CPythonRemoteCall::SetHandler(PyObject* poHandler)
{
	if (m_poHandler)
		Py_DECREF(m_poHandler);

	m_poHandler = poHandler;
	if (m_poHandler)
		Py_INCREF(m_poHandler);
}

bool CPythonRemoteCall::CanSummonOnMap() const
{
	static const std::unordered_set<std::string> s_setBlockedMaps =
	{
		// Sungzi
		"season1/metin2_map_sungzi_flame_hill_01",
		"season1/metin2_map_sungzi_flame_hill_02",
		"season1/metin2_map_sungzi_flame_hill_03",
		"season1/metin2_map_sungzi_desert_01",
		"season1/metin2_map_sungzi_desert_hill_01",
		"season1/metin2_map_sungzi_desert_hill_02",
		"season1/metin2_map_sungzi_desert_hill_03",
		"season2/metin2_map_empirewar03",

		// Dungeons
		"metin2_map_devilscatacomb",
		"metin2_map_mt_thunder",
		"metin2_map_n_flame_dungeon_01",
		"metin2_map_n_snow_dungeon_01",
		"metin2_map_deviltower1",
		"metin2_map_dawnmist_dungeon_01",
		"metin2_map_mt_th_dungeon_01",
		"metin2_12zi_stage",
		"metin2_map_n_flame_dragon",
		"metin2_map_defensewave",
		"metin2_map_mists_of_island",
		"metin2_map_miniboss_01",
		"metin2_map_miniboss_02",
		"metin2_map_labyrinth",
		"metin2_map_smhdungeon_01",
		"metin2_map_smhdungeon_02",
		"metin2_map_whitedragoncave_boss",

		// Boss crack / awaken
		"metin2_map_boss_crack_skipia",
		"metin2_map_boss_crack_flame",
		"metin2_map_boss_crack_snow",
		"metin2_map_boss_crack_dawnmist",
		"metin2_map_boss_awaken_skipia",
		"metin2_map_boss_awaken_flame",
		"metin2_map_boss_awaken_snow",
		"metin2_map_boss_awaken_dawnmist",

		// Elemental / Otherworld
		"metin2_map_elemental_01",
		"metin2_map_elemental_02",
		"metin2_map_elemental_03",
		"metin2_map_elemental_04",
		"metin2_map_otherworld_01",
		"metin2_map_otherworld_02",
		"metin2_map_otherworld_03",
		"metin2_map_otherworld_04",

		// SMH gates
		"metin2_map_smhgate_a1",
		"metin2_map_smhgate_b1",
		"metin2_map_smhgate_c1",
		"metin2_map_smhgate_threeway",
		"metin2_map_smhgate_desert",
		"metin2_map_smhgate_flame",
		"metin2_map_smhgate_snow",
		"metin2_map_smhgate_devils",
		"metin2_map_smhgate_dawnmist",
	};

	std::string strMap = CPythonBackground::Instance().GetWarpMapName();
	if (strMap.empty())
		return true;

	for (auto& c : strMap)
	{
		if (c == '\\')
			c = '/';
		else
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
	}

	return s_setBlockedMaps.find(strMap) == s_setBlockedMaps.end();
}

bool CPythonRemoteCall::IsRemoteBuffItem(DWORD dwItemVnum) const
{
	CItemData* pItemData = nullptr;
	if (!CItemManager::Instance().GetItemDataPointer(dwItemVnum, &pItemData))
		return false;

	switch (dwItemVnum)
	{
		case ITEM_VNUM_STOREKEEPER_ENASIR:
		case ITEM_VNUM_MERCHANT_ENASIR:
		case ITEM_VNUM_STOREKEEPER_ENASIR_T:
		case ITEM_VNUM_MERCHANT_ENASIR_T:
			return true;
		default:
			return false;
	}
}

bool CPythonRemoteCall::IsRemoteCallAffect(DWORD dwAffectType) const
{
	switch (dwAffectType)
	{
		case CInstanceBase::AFFECT_REMOTE_CALL_BUFF_SAFEBOX:
		case CInstanceBase::AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP:
			return true;
	}
	return false;
}

void CPythonRemoteCall::OnAffectAdd(DWORD dwAffectType, DWORD dwDuration)
{
	if (!IsRemoteCallAffect(dwAffectType))
		return;

	if (m_poHandler)
		PyCallClassMemberFunc(m_poHandler, "AddAffect", Py_BuildValue("(ii)", dwAffectType, dwDuration));
}

void CPythonRemoteCall::OnAffectRemove(DWORD dwAffectType)
{
	if (!IsRemoteCallAffect(dwAffectType))
		return;

	if (m_poHandler)
		PyCallClassMemberFunc(m_poHandler, "RemoveAffect", Py_BuildValue("(i)", dwAffectType));
}

void CPythonRemoteCall::OnSummonSuccess(DWORD dwSummonEnd, DWORD dwNpcVID)
{
	m_dwSummonTimeEnd = dwSummonEnd;

	CInstanceBase* pNpc = CPythonCharacterManager::Instance().GetInstancePtr(dwNpcVID);
	if (pNpc)
		pNpc->PushOnceMotion(CRaceMotionData::NAME_SPAWN);

	if (m_poHandler)
		PyCallClassMemberFunc(m_poHandler, "SummonSuccess", Py_BuildValue("(i)", dwSummonEnd));
}

void CPythonRemoteCall::OnSummonFail()
{
	m_dwSummonTimeEnd = 0;
	if (m_poHandler)
		PyCallClassMemberFunc(m_poHandler, "SummonFail", Py_BuildValue("()"));
}

void CPythonRemoteCall::OnSummonEnd(DWORD dwCoolTimeEnd)
{
	m_dwSummonTimeEnd = 0;
	if (m_poHandler)
		PyCallClassMemberFunc(m_poHandler, "SummonEnd", Py_BuildValue("(i)", dwCoolTimeEnd));
}

// --------------- Python binding ---------------

PyObject* remoteCallCanSummonOnMap(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonRemoteCall::Instance().CanSummonOnMap());
}

PyObject* remoteCallDestroy(PyObject* poSelf, PyObject* poArgs)
{
	CPythonRemoteCall::Instance().Destroy();
	return Py_BuildNone();
}

PyObject* remoteCallGetSummonTimeEnd(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonRemoteCall::Instance().GetSummonTimeEnd());
}

PyObject* remoteCallIsRemoteBuffItem(PyObject* poSelf, PyObject* poArgs)
{
	int iItemVnum;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVnum))
		return Py_BuildException();

	return Py_BuildValue("i", CPythonRemoteCall::Instance().IsRemoteBuffItem(iItemVnum));
}

PyObject* remoteCallSetHandler(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* poHandler;
	if (!PyTuple_GetObject(poArgs, 0, &poHandler))
		return Py_BuildException();

	CPythonRemoteCall::Instance().SetHandler(poHandler);
	return Py_BuildNone();
}

void initremoteCall()
{
	static PyMethodDef s_methods[] =
	{
		{ "CanSummonOnMap",		remoteCallCanSummonOnMap,		METH_VARARGS },
		{ "Destroy",			remoteCallDestroy,				METH_VARARGS },
		{ "GetSummonTimeEnd",	remoteCallGetSummonTimeEnd,		METH_VARARGS },
		{ "IsRemoteBuffItem",	remoteCallIsRemoteBuffItem,		METH_VARARGS },
		{ "SetHandler",			remoteCallSetHandler,			METH_VARARGS },
		{ nullptr,					nullptr,},
	};

	PyObject* poModule = Py_InitModule("remoteCall", s_methods);

	PyModule_AddIntConstant(poModule, "REMOTE_CALL_ITEM_MAX_DURATION_SEC",	CPythonRemoteCall::REMOTE_CALL_ITEM_MAX_DURATION_SEC);
	PyModule_AddIntConstant(poModule, "SCMD_SUMMON",						CPythonRemoteCall::REMOTE_CALL_SCMD_SUMMON);
	PyModule_AddIntConstant(poModule, "SCMD_UNSUMMON",						CPythonRemoteCall::REMOTE_CALL_SCMD_UNSUMMON);
	PyModule_AddIntConstant(poModule, "MOB_VNUM_REMOTE_CALL_NPC",			CPythonRemoteCall::MOB_VNUM_REMOTE_CALL_NPC);
	PyModule_AddIntConstant(poModule, "PLAYER_CMD_REMOTE_CALL",				CPythonRemoteCall::PLAYER_CMD_REMOTE_CALL);
}
#endif