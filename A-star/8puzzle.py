from astar import AstarState, AstarNodeState

class eightPuzzle(AstarState):
	#MANHATTAN HEURISTIC
	def heuristic(self, node, start, end):
		ans = 0
		for i in xrange(9):
			if node.array[i]==0:
				continue
			num = node.array[i]
			row = i/3
			col = i%3
			expi = (num-1)/3
			expj = (num-1)%3
			ans += abs(expi - row) + abs(expj - col)
		return ans

	#MISPLACED TILES HEURISTIC
	# def heuristic(self, node, start, end):
	# 	ans = 0
	# 	for i in xrange(9):
	# 		if node.array[i]==0:
	# 			continue
	# 		num = node.array[i]
	# 		row = i/3
	# 		col = i%3
	# 		expi = (num-1)/3
	# 		expj = (num-1)%3
	# 		if ((row != expi) or (col != expj)):
	# 			ans+=1
	# 	return ans

	#MISPLACED TILES HEURISTIC WITH ZERO TILE
	# def heuristic(self, node, start, end):
	# 	ans = 0
	# 	for i in xrange(9):
	# 		if node.array[i]==0:
	#			num = node.array[i]
	#			row = i/3
	#			col = i%3
	#			if((row!=2) or (col!=2)):
	#				ans+=1
	#			continue
	# 		num = node.array[i]
	#		row = i/3
	#		col = i%3
	#		expi = (num-1)/3
	#		expj = (num-1)%3
	#		if ((row != expi) or (col != expj)):
	#			ans+=1
	#	return ans


class puzzleState(AstarNodeState):
	def __init__(self, array):
		self.array = array
		self.g = 0
		self.h = 0
		self.parent = None

	def getAllNextStates(self):
		returnList = []
		pos = -1
		for i in range(len(self.array)):
			if self.array[i] == 0:
				pos = i
		if pos>=3:
			l = list(self.array)
			temp = l[pos]
			l[pos] = l[pos-3]
			l[pos-3] = temp
			p = puzzleState(tuple(l))
			returnList.append(p)
		if pos<6:
			l = list(self.array)
			temp = l[pos]
			l[pos] = l[pos+3]
			l[pos+3] = temp
			p = puzzleState(tuple(l))
			returnList.append(p)
		if pos%3!=2:
			l = list(self.array)
			temp = l[pos]
			l[pos] = l[pos+1]
			l[pos+1] = temp
			p = puzzleState(tuple(l))
			returnList.append(p)
		if pos%3!=0:
			l = list(self.array)
			temp = l[pos]
			l[pos] = l[pos-1]
			l[pos-1] = temp
			p = puzzleState(tuple(l))
			returnList.append(p)
		return returnList

	def move_cost(self, node):
		return 1

	def printState(self):
		for i in range(3):
			for j in range(3):
				print self.array[i*3 + j],
			print

	def equal(self, state):
		for i in range(9):
			if self.array[i] == state.array[i]:
				continue
			else:
				return False
		return True

def main():
	#start = (2,4,0,1,8,5,3,6,7)
	# start = (2,3,0,1,6,8,5,7,4)
	#start = (3,8,5,1,6,7,4,0,2)
	# start = (6,4,2,8,3,7,1,0,5)
	# start = (1,5,2,7,4,3,0,8,6)
	start = (4,2,3,1,5,7,6,0,8)
	end = (1,2,3,4,5,6,7,8,0)
	startState = puzzleState(start)
	endState = puzzleState(end)
	puzzle = eightPuzzle(startState)
	path = puzzle.search(startState, endState)
	# path = puzzle.bidirectional_search(startState, endState)
	for i in path:
		i.printState()
		print
	print "THe number of steps needed : ", len(path)-1

main()
