from astar import AstarState, AstarNodeState

totalno = 3

def validState(array):
	global totalno
	if array[0]<0 or array[1]<0 or array[0]>totalno or array[1]>totalno:
		return False
	elif array[0]==0:
		return True
	elif array[0]>=array[1]:
		return True
	else:
		return False

class mcPuzzle(AstarState):
	#ZERO HEURISTIC
	def heuristic(self, node, start, end):
		ans = 0
		return ans

	#NO. OF PEOPLE HEURISTIC
	# def heuristic(self, node, start, end):
	# 	ans = node.array[0] + node.array[1] - 1
	# 	return ans

	#NO. OF PEOPLE/CAPACITY HEURISTIC
	# def heuristic(self, node, start, end):
	# 	ans = (node.array[0] + node.array[1])/2
	# 	return ans

class puzzleState(AstarNodeState):
	def __init__(self, array):
		self.array = array
		self.g = 0
		self.h = 0
		self.parent = None

	def getAllNextStates(self):
		global totalno
		returnList = []
		l = list(self.array)
		
		l1 = list(l)
		l2 = list(l)
		# print "frrw"
		if l[2]==True:

			l1[0] = l[0] - 1
			l1[1] = l[1] - 1
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			# print l[0], l[1], l[2]
			# print l1[0], l1[1], l1[2]
			# print

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0]
			l1[1] = l[1] - 1
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0] - 1
			l1[1] = l[1]
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0] - 2
			l1[1] = l[1]
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0]
			l1[1] = l[1] - 2
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

		else:
			l1[0] = l[0] + 1
			l1[1] = l[1] + 1
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0]
			l1[1] = l[1] + 1
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0] + 1
			l1[1] = l[1]
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0] + 2
			l1[1] = l[1]
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

			l1[0] = l[0]
			l1[1] = l[1] + 2
			l1[2] = not(l[2])
			l2[0] = totalno - l1[0]
			l2[1] = totalno - l1[1]
			l2[2] = not(l1[2])

			if validState(l1) and validState(l2):
				p = puzzleState(tuple(l1))
				returnList.append(p)

		return returnList

	def move_cost(self, node):
		return 1

	def printState(self):
		for i in range(3):
			print self.array[i],
		print

	def equal(self, state):
		for i in range(3):
			if self.array[i] == state.array[i]:
				continue
			else:
				return False
		return True

def main():
	global totalno
	start = (totalno,totalno,True)
	end = (0,0,False)
	startState = puzzleState(start)
	endState = puzzleState(end)
	puzzle = mcPuzzle(startState)
	path = puzzle.search(startState, endState)
	# path = puzzle.bidirectional_search(startState, endState)
	for i in path:
		i.printState()
		print
	print "The number of steps needed : ", len(path)-1

main()
