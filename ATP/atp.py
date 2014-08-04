
class wff:
	def __init__(self, lhs, rhs, symbol):
		self.lhs = lhs
		self.rhs = rhs
		self.symbol = symbol

	def read(formula):
		if formula[0]=='(':
			#find matching bracket
			c = 1
			for i in enumerate(formula[1:]):
				if formula[i]=='(':
					c = c+1
				elif formula[i]==')':
					c = c-1
				if c==0:
					self.lhs =
		else:
			self.lhs = wff(None, None, formula[0])

