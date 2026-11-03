///Add
#if defined(KD_REMOTE_CALL)
	PyModule_AddIntConstant(poModule, "KD_REMOTE_CALL", true);
#else
	PyModule_AddIntConstant(poModule, "KD_REMOTE_CALL", false);
#endif
