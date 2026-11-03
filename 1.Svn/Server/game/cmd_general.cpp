///Add new cmd

#if defined(KD_REMOTE_CALL)
ACMD(do_cmd_remote_call)
{
	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));
	if (!*arg1)
		return;

	int sub_cmd = 0;
	if (!str_to_number(sub_cmd, arg1))
		return;

	if (sub_cmd < 0 || sub_cmd >= REMOTE_CALL_SCMD_MAX)
		return;

	ch->RemoteCall_Command(sub_cmd);
}
#endif
