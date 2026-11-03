//Find

};

ESex GET_SEX(LPCHARACTER ch);

///Before }; add

#if defined(KD_REMOTE_CALL)
	public:
		void	RemoteCall_Command(BYTE bSubCmd);
		bool	RemoteCall_Summon();
		void	RemoteCall_Unsummon(bool bFromEvent = false, bool bNotify = true);
		bool	RemoteCall_AddBuff(DWORD dwAffect, long lSec);
		void	RemoteCall_OnClickNPC(LPCHARACTER pkClicker);

		bool	IsRemoteCallNPC() const { return IsNPC() && GetRaceNum() == MOB_VNUM_REMOTE_CALL_NPC; }
		void	SetOnlyVisibleTo(DWORD dwPID) { m_dwOnlyVisibleToPID = dwPID; }
		bool	CanBeSeenBy(LPCHARACTER viewer) const;

		DWORD	GetRemoteCallNPCVID() const { return m_dwRemoteCallNPCVID; }
		DWORD	GetRemoteCallEnd() const { return m_dwRemoteCallEnd; }
		
		void	SetRemoteSafeboxRequest(bool status) { m_bRemoteSafeboxRequest = status; }
		bool	IsRemoteSafeboxRequest() const { return m_bRemoteSafeboxRequest; }

	private:
		DWORD	m_dwRemoteCallNPCVID;
		DWORD	m_dwRemoteCallEnd;
		DWORD	m_dwRemoteCallCoolEnd;
		LPEVENT	m_pkRemoteCallEvent;
		DWORD	m_dwOnlyVisibleToPID;
		bool	m_bRemoteSafeboxRequest;
#endif