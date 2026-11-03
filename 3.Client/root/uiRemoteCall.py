# * Author: Khaled / Lungsam
# * Date: 2026.11.03
import app
import chat
import chr
import item
import localeInfo
import net
import nonplayer
import player
import remoteCall
import ui
import uiCommon
import uiToolTip


class RemoteCallWindow(ui.ScriptWindow):
	BUFF_LOCA = {
		chr.AFFECT_REMOTE_CALL_BUFF_SAFEBOX : localeInfo.REMOTE_CALL_TOOLTIP_BUFF_SAFEBOX,
		chr.AFFECT_REMOTE_CALL_BUFF_GENERAL_SHOP : localeInfo.REMOTE_CALL_TOOLTIP_BUFF_GENERAL_SHOP,
	}

	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__Initialize()
		self.__LoadWindow()
		self.AddFlag("float")
		self.SetWindowName("RemoteCallWindow")
		self.SetPosition(0, 0)
		self.SetSize(23, 23)
		remoteCall.SetHandler(self)

	def __del__(self):
		ui.ScriptWindow.__del__(self)
		self.__Initialize()

	def __Initialize(self):
		self.__summon_button = None
		self.__tooltip = None
		self.__dialog = None
		self.__is_requesting = False
		self.__buff_dict = {}
		self.__cool_time_end = 0
		self.__summon_time_end = 0

	def __LoadWindow(self):
		self.__summon_button = ui.Button()
		self.__summon_button.SetParent(self)
		self.__summon_button.SetUpVisual("d:/ymir work/ui/pattern/btn_peddler_call_01.tga")
		self.__summon_button.SetOverVisual("d:/ymir work/ui/pattern/btn_peddler_call_02.tga")
		self.__summon_button.SetDownVisual("d:/ymir work/ui/pattern/btn_peddler_call_03.tga")
		self.__summon_button.SetShowToolTipEvent(ui.__mem_func__(self.__ShowToolTip))
		self.__summon_button.SetHideToolTipEvent(ui.__mem_func__(self.__HideToolTip))
		self.__summon_button.SetEvent(ui.__mem_func__(self.__PopUpDialog))
		self.__summon_button.Show()

		self.__tooltip = uiToolTip.ToolTip()
		self.__HideToolTip()

		self.__dialog = uiCommon.QuestionDialog()
		self.__dialog.AddFlag("not_move")
		self.__dialog.SetCancelEvent(ui.__mem_func__(self.CloseDialog))

	def __ShowToolTip(self):
		if self.__tooltip == None:
			return
		if self.__buff_dict == None:
			return

		if False == remoteCall.CanSummonOnMap():
			self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_TOOLTIP_INVALID_MAP)
			self.__tooltip.ResizeToolTip()
			self.__tooltip.Show()
			return

		buff_count = len(self.__buff_dict)

		if 0 == buff_count:
			self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_NO_BUFF_1)
			self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_NO_BUFF_2)
			self.__tooltip.ResizeToolTip()
			self.__tooltip.Show()
			return

		self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_TOOLTIP_SUMMON_NPC)
		self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_TOOLTIP_BUFF_COUNT % buff_count)

		now = app.GetGlobalTimeStamp()

		for affect_type, end_time in self.__buff_dict.items():
			buff_name = self.BUFF_LOCA.get(affect_type)
			if buff_name == None:
				return
			time_loca = end_time - now
			time_text = localeInfo.SecondToDHMWithLessThenOneMinute(time_loca)
			left_time_text = localeInfo.REMOTE_CALL_TOOLTIP_BUFF_LEFT_TIME % time_text
			self.__tooltip.AutoAppendTextLine(buff_name + " " + left_time_text)

		summon_left_time = self.__summon_time_end - now
		is_already_summon = summon_left_time > 0

		mob_name = nonplayer.GetMonsterName(remoteCall.MOB_VNUM_REMOTE_CALL_NPC)

		if is_already_summon:
			summon_left_time_text = localeInfo.SecondToDHMWithLessThenOneMinute(summon_left_time)
			self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_TOOLTIP_SUMMON_ING % (mob_name, summon_left_time_text))
		else:
			self.__tooltip.AutoAppendTextLine(localeInfo.REMOTE_CALL_TOOLTIP_SUMMON_AVAILABLE % mob_name)

		self.__tooltip.ResizeToolTip()
		self.__tooltip.Show()

	def __HideToolTip(self):
		if self.__tooltip != None:
			self.__tooltip.ClearToolTip()
			self.__tooltip.Hide()

	def AddAffect(self, affect_type, duration):
		if self.__buff_dict != None:
			self.__buff_dict[affect_type] = app.GetGlobalTimeStamp() + duration

	# Deprecated / No longer used
	def AddAffectMessage(self, affect_type, is_override):
		buff_name = self.BUFF_LOCA.get(affect_type)
		if buff_name == None:
			return

		if False == is_override:
			chat.AppendChat(chat.CHAT_TYPE_NOTICE, localeInfo.REMOTE_CALL_MESSAGE_BUFF_ACTIVATED % buff_name)
		else:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_BUFF_TIME_INCREASED % buff_name)

	def RemoveAffect(self, affect_type):
		if self.__buff_dict != None:
			self.__buff_dict.pop(affect_type, None)

	def __PopUpDialog(self):
		if self.__dialog == None:
			return
		if self.__buff_dict == None:
			return

		if chr.IsDead():
			return

		if False == remoteCall.CanSummonOnMap():
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_INVALID_PLACE)
			return

		now = app.GetGlobalTimeStamp()

		if self.__cool_time_end > now:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_SUMMON_COOLTIME)
			return

		if 0 == len(self.__buff_dict):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_NO_BUFF_2)
			return

		mob_name = nonplayer.GetMonsterName(remoteCall.MOB_VNUM_REMOTE_CALL_NPC)

		if self.__summon_time_end > now:
			self.__dialog.SetText(localeInfo.REMOTE_CALL_QUESTION_UMSUMMON_NPC % mob_name)
			self.__dialog.SetAcceptEvent(lambda arg = remoteCall.SCMD_UNSUMMON: self.__SendCommand(arg))
		else:
			self.__dialog.SetText(localeInfo.REMOTE_CALL_QUESTION_SUMMON_NPC % mob_name)
			self.__dialog.SetAcceptEvent(lambda arg = remoteCall.SCMD_SUMMON: self.__SendCommand(arg))

		self.__dialog.Open()
		#self.__dialog.Show()

	def CloseDialog(self):
		if self.__dialog != None:
			self.__dialog.Close()
			#self.__dialog.Hide()

	def __SendCommand(self, sub_cmd):
		if not self.__is_requesting:
			if not chr.IsDead():
				# net.SendCommandPacket(remoteCall.PLAYER_CMD_REMOTE_CALL, sub_cmd)
				net.SendChatPacket("/cmd_remote_call %d" % sub_cmd)
				self.__is_requesting = True
				self.CloseDialog()

	def CanUseItem(self, item, slot_window, slot_index):
		item_duration = player.GetItemMetinSocket(slot_window, slot_index, 0)
		if 0 == item_duration:
			item_duration = item.GetValue(3)

		affect_type = item.GetValue(0)
		end_time = self.__buff_dict.get(affect_type)

		if end_time == None:
			current_duration = 0
		else:
			current_duration = end_time - app.GetGlobalTimeStamp()

		new_duration = item_duration + current_duration

		if remoteCall.REMOTE_CALL_ITEM_MAX_DURATION_SEC < new_duration:
			return False
		return True

	def SummonSuccess(self, summon_end):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_SUMMON_SUCCESS % nonplayer.GetMonsterName(remoteCall.MOB_VNUM_REMOTE_CALL_NPC))
		self.__summon_time_end = summon_end
		self.__cool_time_end = 0
		self.__is_requesting = False

	def SummonFail(self):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_SUMMON_FAIL)
		self.__summon_time_end = 0
		self.__cool_time_end = 0
		self.__is_requesting = False

	def SummonEnd(self, cooltime_end):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_SUMMON_END % nonplayer.GetMonsterName(remoteCall.MOB_VNUM_REMOTE_CALL_NPC))
		self.__cool_time_end = cooltime_end
		self.__summon_time_end = 0
		self.__is_requesting = False

