# Find
	def OpenSafeboxWindow(self, size):
		self.interface.OpenSafeboxWindow(size)

# Change
	if app.KD_REMOTE_CALL:
		def OpenSafeboxWindow(self, size, is_remote_called):
			self.interface.OpenSafeboxWindow(size, is_remote_called)
	else:
		def OpenSafeboxWindow(self, size):
			self.interface.OpenSafeboxWindow(size)


# Find
	def AskSafeboxPassword(self):
		self.interface.AskSafeboxPassword()

# Change
	if app.KD_REMOTE_CALL:
		def AskSafeboxPassword(self, is_remote_called = False):
			self.interface.AskSafeboxPassword(is_remote_called)
	else:
		def AskSafeboxPassword(self):
			self.interface.AskSafeboxPassword()