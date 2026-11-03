#Note:
# All In class InventoryWindow(ui.ScriptWindow):

# Add
if app.KD_REMOTE_CALL:
	import uiRemoteCall, remoteCall

# Find
	def __init__(self):
		ui.ScriptWindow.__init__(self)

 
# Add
		if app.KD_REMOTE_CALL:
			self.remote_call_window = None

# Find
	def __del__(self):
		ui.ScriptWindow.__del__(self)

# Add
		if app.KD_REMOTE_CALL:
			self.remote_call_window = None

# Find
	def Show(self):
		self.__LoadWindow()

		ui.ScriptWindow.Show(self)

		self.RefreshItemSlot()
		self.RefreshStatus()

# Add
		if app.KD_REMOTE_CALL:
			if self.remote_call_window:
				self.remote_call_window.Show()

# Find In def __LoadWindow(self):
		except:
			import exception
			exception.Abort("InventoryWindow.LoadWindow.BindObject")

# Add above
			if app.KD_REMOTE_CALL:
				self.remote_call_window = uiRemoteCall.RemoteCallWindow()
				inven_index = 3 if localeInfo.IsARABIC() else 0
				(x, y) = self.inventoryTab[inven_index].GetGlobalPosition()
				self.remote_call_window.SetPosition(x-30, y)

# Find
	def Destroy(self):
		self.ClearDictionary()

# Add
		if app.KD_REMOTE_CALL:
			self.remote_call_window = None

# Find
	def Hide(self):
		if constInfo.GET_ITEM_QUESTION_DIALOG_STATUS():
			self.OnCloseQuestionDialog()
			return

		if None != self.tooltipItem:
			self.tooltipItem.HideToolTip()

# Add
		if app.KD_REMOTE_CALL:
			if self.remote_call_window:
				self.remote_call_window.Hide()

# Find In def __UseItem(self, slotIndex)
		if item.IsFlag(item.ITEM_FLAG_CONFIRM_WHEN_USE):
			self.questionDialog = uiCommon.QuestionDialog()
			self.questionDialog.SetText(localeInfo.INVENTORY_REALLY_USE_ITEM2)
			self.questionDialog.SetAcceptEvent(ui.__mem_func__(self.__UseItemQuestionDialog_OnAccept))
			self.questionDialog.SetCancelEvent(ui.__mem_func__(self.__UseItemQuestionDialog_OnCancel))
			self.questionDialog.Open()
			self.questionDialog.slotIndex = slotIndex

			constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)
		else:
			self.__SendUseItemPacket(slotIndex, slotWindow)

# Add above
		if app.KD_REMOTE_CALL:
			if remoteCall.IsRemoteBuffItem(ItemVNum):
				if not self.remote_call_window.CanUseItem(item, slotWindow, slotIndex):			#--# leaked official 2018 root
				#if not self.remote_call_window.CanUseItem(item, player.INVENTORY, slotIndex):	#--# normal version
					chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.REMOTE_CALL_MESSAGE_CANNOT_ADD_MORE)
					return

				self.questionDialog = uiCommon.QuestionDialog()
				self.questionDialog.SetText(localeInfo.REMOTE_CALL_QUESTION_USE_ITEM % item.GetItemName())
				self.questionDialog.SetAcceptEvent(ui.__mem_func__(self.__UseItemQuestionDialog_OnAccept))
				self.questionDialog.SetCancelEvent(ui.__mem_func__(self.__UseItemQuestionDialog_OnCancel))
				self.questionDialog.Open()
				self.questionDialog.slotIndex = slotIndex
				# NOTE: If you are NOT using the leaked uiinventory from root 2018, disable this line:
				self.questionDialog.slotWindow = slotWindow	#--# leaked official 2018 root

				constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)
				return


# Find
	def OnMoveWindow(self, x, y):
		if self.wndBelt:
			self.wndBelt.AdjustPosition()

# Add
		if app.KD_REMOTE_CALL:
			if self.remote_call_window:
				inven_index = 3 if localeInfo.IsARABIC() else 0
				(tab_x, tab_y) = self.inventoryTab[inven_index].GetGlobalPosition()
				self.remote_call_window.SetPosition(tab_x - 30, tab_y)