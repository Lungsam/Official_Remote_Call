///Add
#if defined(KD_REMOTE_CALL)
#	include "PythonRemoteCall.h"
#endif

//Find
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;

///Add
#if defined(KD_REMOTE_CALL)
			case HEADER_GC_REMOTE_CALL:
				ret = RecvRemoteCallPacket();
				break;
#endif

//Find in bool CPythonNetworkStream::RecvAffectAddPacket()
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NEW_AddAffect", Py_BuildValue("(iiii)", rkElement.dwType, rkElement.wApplyOn, rkElement.lApplyValue, rkElement.lDuration));

///Add Before
#if defined(KD_REMOTE_CALL)
	CPythonRemoteCall::instance().OnAffectAdd(rkElement.dwType, rkElement.lDuration);
#endif

//Find in bool CPythonNetworkStream::RecvAffectRemovePacket()
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_NEW_RemoveAffect", Py_BuildValue("(ii)", kAffectRemove.dwType, kAffectRemove.wApplyOn));

///Add Before
#if defined(KD_REMOTE_CALL)
	CPythonRemoteCall::instance().OnAffectRemove(kAffectRemove.dwType);
#endif

///Add
#if defined(KD_REMOTE_CALL)
bool CPythonNetworkStream::RecvRemoteCallPacket()
{
	TPacketGCRemoteCall kPacket;
	if (!Recv(sizeof(kPacket), &kPacket)) 
		return false;
	switch (kPacket.bSubHeader)
	{
		case REMOTE_CALL_GC_SUBHEADER_SUCCESS:
			CPythonRemoteCall::Instance().OnSummonSuccess(kPacket.dwValue, kPacket.dwVID);
			break;

		case REMOTE_CALL_GC_SUBHEADER_FAIL: 
			CPythonRemoteCall::Instance().OnSummonFail(); 
			break;

		case REMOTE_CALL_GC_SUBHEADER_END: 
			CPythonRemoteCall::Instance().OnSummonEnd(kPacket.dwValue); 
			break;
	}
	return true;
}
#endif
