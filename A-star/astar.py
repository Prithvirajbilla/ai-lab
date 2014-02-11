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
			# current.printState()
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
		# openset = set()
		openset = []
		closedset = set()
		current = start
		# openset.add(current)
		heapq.heappush(openset, current)
		count = 1
		while len(openset)!=0:
			# current = None
			# f_value = 10000000
			# for i in openset:
			# 	if((i.g + i.h) < f_value):
			# 		f_value = i.g + i.h
			# 		current = i
			current = heapq.heappop(openset)
			# print count
			# count+=1
			# current = min(openset, key=lambda o:o.g + o.h)
			# current.printState()
			# print
			# openset.remove(current)
			closedset.add(current)
			if current.equal(end):
				path = []
				while current.parent:
					path.append(current)
					current = current.parent
				path.append(current)
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
					heapq.heappush(openset, node)
					# openset.add(node)
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