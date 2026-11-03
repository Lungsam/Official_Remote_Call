//Find 
case USE_AFFECT:

///Add

#if defined(KD_REMOTE_CALL)
					if (item->GetValue(0) == AFFECT_REMOTE_CALL_BUFF_SAFEBOX || item->GetValue(0) == AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP)
					{
						const long lDur = item->GetValue(3);

						if (!RemoteCall_AddBuff(item->GetValue(0), lDur))
							return false;

						item->SetCount(item->GetCount() - 1);
						return true;
					}
#endif


// * example * 
				case USE_MOVE:
				case USE_TREASURE_BOX:
				case USE_MONEYBAG:
					break;

				case USE_AFFECT:
				{
#if defined(KD_REMOTE_CALL)
					if (item->GetValue(0) == AFFECT_REMOTE_CALL_BUFF_SAFEBOX || item->GetValue(0) == AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP)
					{
						const long lDur = item->GetValue(3);

						if (!RemoteCall_AddBuff(item->GetValue(0), lDur))
							return false;

						item->SetCount(item->GetCount() - 1);
						return true;
					}
#endif
					if (FindAffect(item->GetValue(0), aApplyInfo[item->GetValue(1)].bPointType))
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("??©ö? ??¡Æ?¡Æ? ¡Æ?¡¤? ??¨ö?¢¥?¢¥?."));
					}
					else
					{
						AddAffect(item->GetValue(0), aApplyInfo[item->GetValue(1)].bPointType, item->GetValue(2), 0, item->GetValue(3), 0, false);
						item->SetCount(item->GetCount() - 1);
					}
				}
				break;