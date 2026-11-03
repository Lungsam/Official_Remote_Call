//Find
PyObject * chrRaceToSex(PyObject * poSelf, PyObject * poArgs)
{
	..
}

///Add
#if defined(KD_REMOTE_CALL)
PyObject* chrIsDead(PyObject* poSelf, PyObject* poArgs)
{
	CInstanceBase* pkInst = CPythonCharacterManager::Instance().GetMainInstancePtr();
	const int iDead = (pkInst != nullptr && pkInst->IsDead()) ? true : false;
	return Py_BuildValue("i", iDead);
}
#endif

//Find
		{ "RaceToSex",					chrRaceToSex,							METH_VARARGS },

///Add
		{ "IsDead",						chrIsDead,								METH_VARARGS },
		

//Find
	PyModule_AddIntConstant(poModule, "NEW_AFFECT_DRAGON_SOUL_DECK1",		CInstanceBase::NEW_AFFECT_DRAGON_SOUL_DECK1);
	PyModule_AddIntConstant(poModule, "NEW_AFFECT_DRAGON_SOUL_DECK2",		CInstanceBase::NEW_AFFECT_DRAGON_SOUL_DECK2);

///Add
#if defined(KD_REMOTE_CALL)
	PyModule_AddIntConstant(poModule, "AFFECT_REMOTE_CALL_BUFF_SAFEBOX",	CInstanceBase::AFFECT_REMOTE_CALL_BUFF_SAFEBOX);
	PyModule_AddIntConstant(poModule, "AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP", CInstanceBase::AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP);
#endif