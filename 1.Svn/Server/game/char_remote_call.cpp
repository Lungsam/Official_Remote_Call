//_________________________________________________________________
// Author		: Khaled / Lungsam
// Created		: 2026.11.03
// Description	: Enasir - Remote Call
//_________________________________________________________________

#include "stdafx.h"

#if defined(KD_REMOTE_CALL)
#include "constants.h"
#include "utils.h"
#include "config.h"
#include "char.h"
#include "char_manager.h"
#include "desc.h"
#include "packet.h"
#include "affect.h"
#include "event.h"
#include "shop_manager.h"
#include "threeway_war.h"

EVENTINFO(remote_call_end_info)
{
	DynamicCharacterPtr ch;
	remote_call_end_info() : ch() {}
};

EVENTFUNC(remote_call_end_event)
{
	remote_call_end_info* info = dynamic_cast<remote_call_end_info*>(event->info);
	if (!info)
		return 0;

	LPCHARACTER ch = info->ch;
	if (!ch)
		return 0;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(ch->GetRemoteCallNPCVID());

	const int iRemain = ch->GetRemoteCallEnd() - get_global_time();
	const bool bExpired = get_global_time() >= ch->GetRemoteCallEnd();
	const bool bFar = !npc
		|| npc->GetMapIndex() != ch->GetMapIndex()
		|| DISTANCE_APPROX(ch->GetX() - npc->GetX(), ch->GetY() - npc->GetY()) > REMOTE_CALL_MAX_DISTANCE;

	if (bExpired || bFar)
	{
		ch->RemoteCall_Unsummon(true);
		return 0;
	}

	return PASSES_PER_SEC(MINMAX(1, iRemain, 3));
}

static void SendRemoteCall(LPCHARACTER ch, BYTE bSub, DWORD dwValue, DWORD dwVID = 0)
{
	LPDESC d = ch->GetDesc();
	if (!d)
		return;

	TPacketGCRemoteCall p{};
	p.header = HEADER_GC_REMOTE_CALL;
	p.bSubHeader = bSub;
	p.dwValue = dwValue;
	p.dwVID = dwVID;
	d->Packet(&p, sizeof(p));
}

bool CHARACTER::IsRemoteNpcVisibleTo(LPCHARACTER viewer) const
{
	if (!m_dwOnlyVisibleToPID)
		return true;

	return viewer && viewer->GetPlayerID() == m_dwOnlyVisibleToPID;
}

bool CHARACTER::RemoteCall_Summon()
{
	if (!IsPC() || IsDead())
		return false;

	if (m_dwRemoteCallNPCVID)
		return false;

	const DWORD now = get_global_time();
	if (now < m_dwRemoteCallCoolEnd)
		return false;

	if (!FindAffect(AFFECT_REMOTE_CALL_BUFF_SAFEBOX) && !FindAffect(AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP))
		return false;

	if (GetMapIndex() >= 10000)
		return false;

	if (GetWarMap())
		return false;

	if (CThreeWayWar::instance().IsSungZiMapIndex(GetMapIndex()))
		return false;	

	long x = GetX() + REMOTE_CALL_SPAWN_OFFSET;
	long y = GetY();

	LPCHARACTER npc = CHARACTER_MANAGER::instance().SpawnMob(MOB_VNUM_REMOTE_CALL_NPC, GetMapIndex(), x, y, 0, false, -1, false);
	if (!npc)
		return false;

	npc->SetOnlyVisibleTo(GetPlayerID());

	if (!npc->Show(GetMapIndex(), x, y, 0, false))
	{
		x = GetX();
		if (!npc->Show(GetMapIndex(), x, y, 0, false))
		{
			M2_DESTROY_CHARACTER(npc);
			return false;
		}
	}

	m_dwRemoteCallNPCVID = npc->GetVID();
	m_dwRemoteCallEnd = now + REMOTE_CALL_SUMMON_SEC;

	remote_call_end_info* info = AllocEventInfo<remote_call_end_info>();
	info->ch = this;
	//m_pkRemoteCallEvent = event_create(remote_call_end_event, info, PASSES_PER_SEC(REMOTE_CALL_SUMMON_SEC));
	m_pkRemoteCallEvent = event_create(remote_call_end_event, info, PASSES_PER_SEC(3));

	SendRemoteCall(this, REMOTE_CALL_GC_SUBHEADER_SUCCESS, m_dwRemoteCallEnd, m_dwRemoteCallNPCVID);
	return true;
}

void CHARACTER::RemoteCall_Unsummon(bool bFromEvent, bool bNotify)
{
	if (bFromEvent)
		m_pkRemoteCallEvent = nullptr;
	else
		event_cancel(&m_pkRemoteCallEvent);

	if (!m_dwRemoteCallNPCVID)
		return;

	LPCHARACTER npc = CHARACTER_MANAGER::instance().Find(m_dwRemoteCallNPCVID);
	if (npc)
		M2_DESTROY_CHARACTER(npc);

	m_dwRemoteCallNPCVID = 0;
	m_dwRemoteCallEnd = 0;
	m_dwRemoteCallCoolEnd = get_global_time() + REMOTE_CALL_COOLTIME_SEC;

	if (bNotify)
		SendRemoteCall(this, REMOTE_CALL_GC_SUBHEADER_END, m_dwRemoteCallCoolEnd);
}

void CHARACTER::RemoteCall_Command(BYTE bSubCmd)
{
	switch (bSubCmd)
	{
		case REMOTE_CALL_SCMD_SUMMON:
			if (!RemoteCall_Summon())
				SendRemoteCall(this, REMOTE_CALL_GC_SUBHEADER_FAIL, 0);
			break;

		case REMOTE_CALL_SCMD_UNSUMMON:
			RemoteCall_Unsummon();
			break;

		default:
			return;
	}
}

bool CHARACTER::RemoteCall_AddBuff(DWORD dwAffect, long lSec)
{
	if (dwAffect != AFFECT_REMOTE_CALL_BUFF_SAFEBOX && dwAffect != AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP)
		return false;

	CAffect* pAff = FindAffect(dwAffect);
	const long lNew = lSec + (pAff ? pAff->lDuration : 0);

	if (lNew > REMOTE_CALL_ITEM_MAX_DURATION_SEC)
		return false;

	if (pAff)
		RemoveAffect(pAff);

	AddAffect(dwAffect, APPLY_NONE, 0, 0, lNew, 0, false);
	return true;
}
#endif

