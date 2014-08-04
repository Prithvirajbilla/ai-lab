import heapq

class AstarGraph(object):
	def __init__(self, graph):
		self.graph = graph

	def heuristic(self, node, start, end):
		raise NotImplementedError

	def search(self, start, end):
		openset = set()
		closedset = set()
		current = start
		openset.add(current)
		while openset:
			current = None
			f_value = 1000000
			for i in openset:
				if((i.g + i.h) < f_value):
					f_value = i.g + i.h
					current = i
			if current == end:
				path = []
				while current.parent:
					path.append(current)
					current = current.parent
				path.append(current)
				return path[::-1]
			openset.remove(current)
			closedset.add(current)
			for node in self.graph[current]:
				if node in closedset:
					continue
				if node in openset:
					new_g = current.g + current.move_cost(node)
					if node.g > new_g:
						node.g = new_g
						node.parent = current
				else:
					node.g = current.g + current.move_cost(node)
					node.h = self.heuristic(node, start, end)
					node.parent = current
					openset.add(node)
		return None


class AstarState(object):
	def __init__(self, state):
		self.state = state

	def heuristic(self, node, start, end):
		raise NotImplementedError

	def search(self, start, end):
		openset = set()
		closedset = set()
		current = start
		openset.add(start)
		count = 1
		while len(openset)!=0:
			count+=1
			current = min(openset, key=lambda o: o.g+o.h)
			closedset.add(current)
			openset.remove(current)
			if current.equal(end):
				path = []
				while current.parent:
					path.append(current)
					current = current.parent
				path.append(current)
				print count
				return path[::-1]
			for node in current.getAllNextStates():
				if node in closedset:
					continue
				if node in openset:
					new_g = current.g + current.move_cost(node)
					if node.g > new_g:
						node.g = new_g
						node.parent = current
				else:
					node.g = current.g + current.move_cost(node)
					node.h = self.heuristic(node, start, end)
					node.parent = current
					openset.add(node)
		return None

	def bidirectional_search(self, start, end):
		openset1 = set()
		openset2 = set()
		closedset1 = set()
		closedset2 = set()
		openset1.add(start)
		openset2.add(end)
		count = 1
		current1 = start
		current2 = end
		while (not current1.equal(current2)):
			count+=1
			current1 = min(openset1, key=lambda o: o.g+o.h)
			current2 = min(openset2, key=lambda o: o.g+o.h)
			closedset1.add(current1)
			closedset2.add(current2)
			openset1.remove(current1)
			openset2.remove(current2)
			if current1.equal(current2):
				path2 = []
				while current2.parent:
					path2.append(current2)
					current2 = current2.parent
				path2.append(current2)
				# path2 = path2[::-1]
				path1 = []
				while current1.parent:
					path1.append(current1)
					current1 = current1.parent
				path1.append(current1)
				path1 = path1[::-1]
				path = []
				path = path1 + path2
				print count
				return path
			for node1 in current1.getAllNextStates():
				if node1 in closedset1:
					continue
				if node1 in openset1:
					new_g = current1.g + current1.move_cost(node1)
					if node1.g > new_g:
						node1.g = new_g
						node1.parent = current1
				else:
					node1.g = current1.g + current1.move_cost(node1)
					node1.h = self.heuristic(node1, start, end)
					node1.parent = current1
					openset1.add(node1)
			for node2 in current2.getAllNextStates():
				if node2 in closedset2:
					continue
				if node2 in openset2:
					new_g = current2.g + current2.move_cost(node2)
					if node2.g > new_g:
						node2.g = new_g
						node2.parent = current2
				else:
					node2.g = current2.g + current2.move_cost(node2)
					node2.h = self.heuristic(node2, start, end)
					node2.parent = current2
					openset2.add(node2)
		return None

class AstarNodeState(object):
	def __init__(self):
		self.g = 0
		self.h = 0
		self.parent = None

	def move_cost(self, node):
		raise NotImplementedError

	def getAllNextStates(self):
		raise NotImplementedError

	def printState(self):
		raise NotImplementedError

	def equal(self, state):
 		raise NotImplementedError


class AstarNodeGraph(object):
	def __init__(self):
		self.g = 0
		self.h = 0
		self.parent = None

	def move_cost(self, node):
		raise NotImplementedError
