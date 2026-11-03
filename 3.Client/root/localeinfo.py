# Add
if app.KD_REMOTE_CALL:
	def SecondToDHMWithLessThenOneMinute(time):
		if time < 60:
			if IsARABIC():
				return "%.2f %s" % (time, SECOND)
			else:
				return "0" + MINUTE

		second = int(time % 60)
		minute = int((time / 60) % 60)
		hour = int((time / 60) / 60) % 24
		day = int(int((time / 60) / 60) / 24)

		text = ""

		if day > 0:
			text += str(day) + DAY
			if hour > 0 or minute > 0:
				text += " "

		if hour > 0:
			text += str(hour) + HOUR
			if minute > 0:
				text += " "

		if minute > 0:
			text += str(minute) + MINUTE

		return text