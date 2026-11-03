//Find 
	int game_open_safebox(lua_State* L)
	{
		..
	}

///Change
	int game_open_safebox(lua_State* L)
	{
		CQuestManager& q = CQuestManager::instance();
		const LPCHARACTER ch = q.GetCurrentCharacterPtr();

#if defined(KD_REMOTE_CALL)
		if (!ch)
			return 0;

		// game.open_safebox(true) = bRemote، game.open_safebox() = normal
		const bool bRemote = (lua_gettop(L) >= 1 && lua_isboolean(L, 1)) ? (lua_toboolean(L, 1) != 0) : false;

		if (bRemote && !ch->FindAffect(AFFECT_REMOTE_CALL_BUFF_SAFEBOX))
			return 0;

		ch->SetSafeboxOpenPosition();
		ch->SetRemoteSafeboxRequest(bRemote);
		ch->ChatPacket(CHAT_TYPE_COMMAND, bRemote ? "ShowMeSafeboxPassword 1" : "ShowMeSafeboxPassword");
#else
		ch->SetSafeboxOpenPosition();
		ch->ChatPacket(CHAT_TYPE_COMMAND, "ShowMeSafeboxPassword");
#endif
		return 0;
	}