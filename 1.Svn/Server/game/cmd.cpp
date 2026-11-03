//Find
ACMD (do_clear_affect);

///Add
#if defined(KD_REMOTE_CALL)
ACMD(do_cmd_remote_call);
#endif


//Find
{ "do_clear_affect",	do_clear_affect,			0,						POS_DEAD,		GM_LOW_WIZARD	},

///Add
#if defined(KD_REMOTE_CALL)
	{ "cmd_remote_call",	do_cmd_remote_call,			0,						POS_DEAD,		GM_PLAYER		},
#endif

