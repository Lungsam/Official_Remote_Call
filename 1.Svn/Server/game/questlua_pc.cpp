///Add

#if defined(KD_REMOTE_CALL)
	ALUA(pc_remote_call_unsummon)
/* 	int pc_remote_call_unsummon(lua_State* L) */
	{
		const LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
			ch->RemoteCall_Unsummon(true);
		return 0;
	}
#endif

//Find
void RegisterPCFunctionTable()

///Add
#if defined(KD_REMOTE_CALL)
			{ "remote_call_unsummon",					pc_remote_call_unsummon					},
#endif