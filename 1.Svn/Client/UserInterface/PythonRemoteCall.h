#pragma once

#if defined(KD_REMOTE_CALL)
class CPythonRemoteCall : public CSingleton<CPythonRemoteCall>
{
	public:
		enum ERemoteCallSubCmd
		{
			REMOTE_CALL_SCMD_SUMMON,
			REMOTE_CALL_SCMD_UNSUMMON,
			REMOTE_CALL_SCMD_MAX,

		};

		enum ERemoteCallItems
		{
			ITEM_VNUM_STOREKEEPER_ENASIR = 72368,
			ITEM_VNUM_MERCHANT_ENASIR = 72369,
			ITEM_VNUM_STOREKEEPER_ENASIR_T = 72370,
			ITEM_VNUM_MERCHANT_ENASIR_T = 72371,
		};

		enum ERemoteCall
		{
			REMOTE_CALL_ITEM_MAX_DURATION_SEC = 86400000,
			MOB_VNUM_REMOTE_CALL_NPC = 20874,
			PLAYER_CMD_REMOTE_CALL = 54,
		};

		CPythonRemoteCall();
		virtual ~CPythonRemoteCall();

		void Destroy();

		// remoteCall.SetHandler(RemoteCallWindow instance)
		void SetHandler(PyObject* poHandler);

		bool CanSummonOnMap() const;
		bool IsRemoteBuffItem(DWORD dwItemVnum) const;
		bool IsRemoteCallAffect(DWORD dwAffectType) const;

		DWORD GetSummonTimeEnd() const { return m_dwSummonTimeEnd; }

		void OnAffectAdd(DWORD dwAffectType, DWORD dwDuration);
		void OnAffectRemove(DWORD dwAffectType);
		void OnSummonSuccess(DWORD dwSummonEnd, DWORD dwNpcVID);
		void OnSummonFail();
		void OnSummonEnd(DWORD dwCoolTimeEnd);

	protected:
		PyObject*	m_poHandler;
		DWORD		m_dwSummonTimeEnd;
};
#endif