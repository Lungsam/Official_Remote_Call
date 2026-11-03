//Find in void CHARACTER::Initialize()
	m_iSyncHackCount = 0;

///Add
#if defined(KD_REMOTE_CALL)
	m_dwRemoteCallNPCVID = 0;
	m_dwRemoteCallEnd = 0;
	m_dwRemoteCallCoolEnd = 0;
	m_pkRemoteCallEvent = nullptr;
	m_dwOnlyVisibleToPID = 0;
	m_bRemoteSafeboxRequest = false;
#endif

//Find in void CHARACTER::EncodeInsertPacket(LPENTITY entity)
	ch = (LPCHARACTER) entity;

///Add After
#if defined(KD_REMOTE_CALL)
	if (entity->IsType(ENTITY_CHARACTER))
	{
		if (!IsRemoteNpcVisibleTo(ch))
			return;
	}
#endif

//Find in void CHARACTER::Disconnect(const char * c_pszReason)
	marriage::CManager::instance().Logout(this);

///Add After
#if defined(KD_REMOTE_CALL)
	RemoteCall_Unsummon(false, false);
#endif

//Find in void CHARACTER::LoadSafebox(int iSize, DWORD dwGold, int iItemCount, TPlayerItem * pItems)
	p.bSize = iSize;

///Add After
#if defined(KD_REMOTE_CALL)
	p.bIsRemoteCalled = IsRemoteSafeboxRequest() ? true : false;
	SetRemoteSafeboxRequest(false);	
#endif

//Find in void CHARACTER::ChangeSafeboxSize(BYTE bSize)
	p.bSize = bSize;
	
///Add after
#if defined(KD_REMOTE_CALL)
	p.bIsRemoteCalled = IsRemoteSafeboxRequest() ? true : false;
	SetRemoteSafeboxRequest(false);
#endif


//Find in void CHARACTER::LoadMall(int iItemCount, TPlayerItem * pItems)
	p.bSize = 3 * SAFEBOX_PAGE_SIZE;

///Add After
#if defined(KD_REMOTE_CALL)
	p.bIsRemoteCalled = 0;
#endif




