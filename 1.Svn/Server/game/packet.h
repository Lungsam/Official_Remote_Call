//Find
	HEADER_CG_STATE_CHECKER					= 206,

///Add
#if defined(KD_REMOTE_CALL)
	HEADER_GC_REMOTE_CALL					= 235,
#endif

//Find in typedef struct packet_safebox_size
	BYTE bSize;

///Add
#if defined(KD_REMOTE_CALL)
	BYTE bIsRemoteCalled;
#endif

//Find
typedef struct command_shop_buy
{
	...
} TPacketCGShopBuy;

///Add
#if defined(KD_REMOTE_CALL)
// server -> client
enum ESubHeaderGCRemoteCall
{
	REMOTE_CALL_GC_SUBHEADER_SUCCESS,
	REMOTE_CALL_GC_SUBHEADER_FAIL,
	REMOTE_CALL_GC_SUBHEADER_END
};

typedef struct SPacketGCRemoteCall
{
	BYTE	header;
	BYTE	bSubHeader;
	DWORD	dwValue;
	DWORD	dwVID;
} TPacketGCRemoteCall;
#endif