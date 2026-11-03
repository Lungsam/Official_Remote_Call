# Find
	def AskSafeboxPassword(self):
		if self.wndSafebox.IsShow():
			return

		# SAFEBOX_PASSWORD
		self.dlgPassword.SetTitle(localeInfo.PASSWORD_TITLE)
		self.dlgPassword.SetSendMessage("/safebox_password ")
		# END_OF_SAFEBOX_PASSWORD

		self.dlgPassword.ShowDialog()

# Change
	if app.KD_REMOTE_CALL:
		def AskSafeboxPassword(self, is_remote_called):
			if self.wndSafebox.IsShow():
				return

			# SAFEBOX_PASSWORD
			if is_remote_called:
				self.dlgPassword.SetTitle(localeInfo.REMOTE_CALL_TITLE_REMOTE + localeInfo.PASSWORD_TITLE)
			else:
				self.dlgPassword.SetTitle(localeInfo.PASSWORD_TITLE)
			self.dlgPassword.SetSendMessage("/safebox_password ")
			# END_OF_SAFEBOX_PASSWORD

			self.dlgPassword.ShowDialog()
	else:
		def AskSafeboxPassword(self):
			if self.wndSafebox.IsShow():
				return

			# SAFEBOX_PASSWORD
			self.dlgPassword.SetTitle(localeInfo.PASSWORD_TITLE)
			self.dlgPassword.SetSendMessage("/safebox_password ")
			# END_OF_SAFEBOX_PASSWORD

			self.dlgPassword.ShowDialog()

# Find
	def OpenSafeboxWindow(self, size):
		self.dlgPassword.CloseDialog()
		self.wndSafebox.ShowWindow(size)

# Change
	if app.KD_REMOTE_CALL:
		def OpenSafeboxWindow(self, size, is_remote_called):
			self.dlgPassword.CloseDialog()
			self.wndSafebox.ShowWindow(size, is_remote_called)
	else:
		def OpenSafeboxWindow(self, size):
			self.dlgPassword.CloseDialog()
			self.wndSafebox.ShowWindow(size)

