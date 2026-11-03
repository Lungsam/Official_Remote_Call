//Find
int affect_remove_all_collect(lua_State* L)
{
	...
}

///Add

#if defined(KD_REMOTE_CALL)
	// General Lua function to check if the character has a specific affect/buff active.
	// Can be used globally in any quest: affect.has(affect_type)
	// Dont Need defined
	ALUA(affect_has)
/* 	int affect_has(lua_State* L) */
	{
		const LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();

		if (!ch || !lua_isnumber(L, 1))
		{
			lua_pushboolean(L, 0);
			return 1;
		}

		const DWORD dwAffectType = static_cast<DWORD>(lua_tonumber(L, 1));
		lua_pushboolean(L, ch->FindAffect(dwAffectType) != nullptr);
		return 1;
	}
#endif


///Add In void RegisterAffectFunctionTable()

#if defined(KD_REMOTE_CALL)
			{ "has",	affect_has },
#endif
