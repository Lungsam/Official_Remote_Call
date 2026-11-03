# Find in class ChangePasswordDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__LoadDialog()

# Add
		if app.KD_REMOTE_CALL:
			self.__is_remote_called = False 

# Find
	def Open(self):
		self.oldPassword.SetText("")
		self.newPassword.SetText("")
		self.newPasswordCheck.SetText("")
		self.oldPassword.SetFocus()
		self.SetCenterPosition()
		self.SetTop()
		self.Show()

# Change
	if app.KD_REMOTE_CALL:
		def Open(self, is_remote_called = False):
			self.oldPasswordText.SetText("")
			self.newPasswordText.SetText("")
			self.newPasswordCheckText.SetText("")
			self.__is_remote_called = is_remote_called
			self.SetCenterPosition()
			self.SetTop()
			self.Show()
	else:
		def Open(self):
			self.oldPassword.SetText("")
			self.newPassword.SetText("")
			self.newPasswordCheck.SetText("")
			self.oldPassword.SetFocus()
			self.SetCenterPosition()
			self.SetTop()
			self.Show()

# Find In class SafeboxWindow(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.tooltipItem = None
		self.sellingSlotNumber = -1
		self.pageButtonList = []
		self.curPageIndex = 0
		self.isLoaded = 0
		self.xSafeBoxStart = 0
		self.ySafeBoxStart = 0

# Add
		if app.KD_REMOTE_CALL:
			self.__title_name = None
			self.__change_password_button = None

# Find
		self.GetChild("ChangePasswordButton").SetEvent(ui.__mem_func__(self.OnChangePassword))

# Change
		if app.KD_REMOTE_CALL:
			self.__title_name = self.GetChild("TitleName")
			self.__change_password_button = self.GetChild("ChangePasswordButton")
		else:
			self.GetChild("ChangePasswordButton").SetEvent(ui.__mem_func__(self.OnChangePassword))


# Find
	def ShowWindow(self, size):
		(self.xSafeBoxStart, self.ySafeBoxStart, z) = player.GetMainCharacterPosition()
		self.SetTableSize(size)
		self.Show()

# Change
	if app.KD_REMOTE_CALL:
		def ShowWindow(self, size, is_remote_called):
			if self.__title_name is None:
				return

			if self.__change_password_button is None:
				return
 
			(self.xSafeBoxStart, self.ySafeBoxStart, z) = player.GetMainCharacterPosition()
			self.SetTableSize(size)
			self.SetTop()
 
			if is_remote_called:
				self.__title_name.SetText(localeInfo.REMOTE_CALL_TITLE_REMOTE + uiScriptLocale.SAFE_TITLE)
			else:
				self.__title_name.SetText(uiScriptLocale.SAFE_TITLE)
 
			self.__change_password_button.SetEvent(lambda is_remote_called = is_remote_called: ui.__mem_func__(self.OnChangePassword)(is_remote_called))

			# if app.WJ_ENABLE_TRADABLE_ICON:
				# self.SetTop()

			self.Show()
			# if app.ENABLE_GROWTH_PET_SYSTEM:
				# player.SetOpenSafeBox(True)
	else:
		def ShowWindow(self, size):
			(self.xSafeBoxStart, self.ySafeBoxStart, z) = player.GetMainCharacterPosition()
			self.SetTableSize(size)
			self.Show()


# Find
	def OnChangePassword(self):
		self.dlgChangePassword.Open()

# Change
	if app.KD_REMOTE_CALL:
		def OnChangePassword(self, is_remote_called):
			self.dlgChangePassword.Open(is_remote_called)
	else:
		def OnChangePassword(self):
			self.dlgChangePassword.Open()