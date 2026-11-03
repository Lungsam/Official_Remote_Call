//Find
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

///Add
#if defined(KD_REMOTE_CALL)
			Set(HEADER_GC_REMOTE_CALL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCRemoteCall), STATIC_SIZE_PACKET));
#endif