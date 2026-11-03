//Find
} EShopCoinType;

///Add
#if defined(KD_REMOTE_CALL)
enum ERemoteCallSubCmd
{
	REMOTE_CALL_SCMD_SUMMON,
	REMOTE_CALL_SCMD_UNSUMMON,
	REMOTE_CALL_SCMD_MAX,
};

enum ERemoteCall
{
	MOB_VNUM_REMOTE_CALL_NPC			= 20874,	// #--#  Npc
	REMOTE_CALL_CMD						= 54,		// #--# PLAYER_CMD_REMOTE_CALL (Not used)
	REMOTE_CALL_ITEM_MAX_DURATION_SEC	= 86400000,	// #--# 100Day Max
	REMOTE_CALL_SUMMON_SEC				= 180,		// #--# Duration of the NPC summon
	REMOTE_CALL_COOLTIME_SEC			= 10,		// #--# Cooltime after summon
	REMOTE_CALL_SPAWN_OFFSET			= 200,		// #--# Spawn distance offset next to the player
	REMOTE_CALL_MAX_DISTANCE			= 5000,		// #--# Max distance to summon the NPC
};
#endif