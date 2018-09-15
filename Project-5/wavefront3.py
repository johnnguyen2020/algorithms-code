import csv
import sys

import cozmo

from cozmo.util import degrees, distance_inches, speed_mmps

class point:

    def __init__(self, ypos, xpos):
        self.x = xpos
        self.y = ypos

class map_object(point):

    def __init__(self):
        self.vector = []
        self.width = 0
        self.height = 0

    def in_map(self, point):
        try:
            if point.xpos < 0 or point.xpos >= self.w:
                return False
            if point.ypos < 0 or point.ypos >= self.h:
                return False
            return True

        # If this fails for any reason the point is not in the map
        except:
            return False

# Read in map from map.csv file
map = map_object()
with open("file.txt") as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
        int_row = [int(value) for value in row]
        map.vector.append(int_row)

# Set map size
map.w = len(map.vector[0])
map.h = len(map.vector)

for x in range(0, map.w):
    for y in range(0, map.h):
    
        if map.vector[y][x] == 8:
            start = point(y, x)

        if map.vector[y][x] == 9:
            goal = point(y, x)

def waveFront(map):

	fringe = [goal];
	visited = [];
	children = [];
	
	dist = 1
	
	while fringe.size:
		node = fringe[0]
			
		if node == start:
			return True
		
		# North
		if point(node.y-1, node.x) in visited:
			check = 0
		if node.y != 0 and check and map.vector[node.y-1][node.x] >= 0:
			map.vector[node.y-1][node.x] = dist
			fringe.append(point(node.y-1, node.x))
			
		# NorthEast
		if point(node.y-1, node.x+1) in visited:
			check = 0
		if node.y != 0 and node.x != map.w and check and map.vector[node.y-1][node.x+1] >= 0:
			map.vector[node.y-1][node.x+1] = dist
			fringe.append(point(node.y+1, node.x+1))
			
		# East
		if point(node.y, node.x+1) in visited:
			check = 0
		if node.x != map.w and check and map.vector[node.y][node.x+1] >= 0:
			map.vector[node.y][node.x+1] = dist
			fringe.append(point(node.y, node.x+1))
			
		# SouthEast
		if point(node.y+1, node.x+1) in visited:
			check = 0
		if node.y != map.h and x != map.w and check and map.vector[node.y+1][node.x+1] >= 0:
			map.vector[node.y+1][node.x+1] = dist
			fringe.append(point(node.y+1, node.x+1))
			
		# South
		if point(node.y+1, node.x) in visited:
			check = 0
		if node.y != map.h and check and map.vector[node.y+1][node.x] >= 0:
			map.vector[node.y+1][node.x] = dist
			fringe.append(point(node.y+1, node.x))
			
		# SouthWest
		if point(node.y+1, node.x-1) in visited:
			check = 0
		if node.y != map.h and x != 0 and check and map.vector[node.y+1][node.x-1] >= 0:
			map.vector[node.y+1][node.x-1] = dist
			fringe.append(point(node.y+1, node.x-1))
			
		# West
		if point(node.y, node.x-1) in visited:
			check = 0
		if node.x != 0 and check and map.vector[node.y][node.x-1] >= 0:
			map.vector[node.y][node.x-1] = dist
			fringe.append(point(node.y, node.x-1))
			
		# NorthWest
		if point(node.y-1, node.x-1) in visited:
			check = 0
		if node.y != 0 and node.x != 0 and check and map.vector[node.y-1][node.x-1] >= 0:
			map.vector[node.y-1][node.x-1] = dist
			fringe.append(point(node.y+1, node.x-1))
			
		visited.append(node)
		del fringe[0]
		dist = dist+1
		
def cozmo_program(robot: cozmo.robot.Robot, DEGREE):
    if DEGREE != 0 :
        robot.turn_in_place(DEGREEs(DEGREE)).wait_for_completed()
    robot.drive_straight(distance_inches(4), speed_mmps(50)).wait_for_completed()
		
#################### Traversing the map with cozmo ######################

node = start
nodes_to_check = []
values_to_check = []
degrees_to_turn = []
current_degree = 0

while node != goal:

	# North
	if node.y != 0 and map.vector[node.y-1][node.x] >= 0:
		nodes_to_check.append(point(node.y-1, node.x))
		values_to_check.append(map.vector[node.y-1][node.x])
		degrees_to_turn.append(0)

	# NorthEast
	if node.y != 0 and node.x != map.w and map.vector[node.y-1][node.x] >= 0:
		nodes_to_check.append(point(node.y-1, node.x+1))
		values_to_check.append(map.vector[node.y-1][node.x+1])
		degrees_to_turn.append(45)

	# East
	if node.x != map.w and map.vector[node.y][node.x+1] >= 0:
		nodes_to_check.append(point(node.y, node.x+1))
		values_to_check.append(map.vector[node.y][node.x+1])
		degrees_to_turn.append(90)

	# SouthEast
	if node.y != map.h and x != map.w and map.vector[node.y+1][node.x+1] >= 0:
		nodes_to_check.append(point(node.y+1, node.x+1))
		values_to_check.append(map.vector[node.y+1][node.x+1])
		degrees_to_turn.append(135)

	# South
	if node.y != map.h and map.vector[node.y+1][node.x] >= 0:
		nodes_to_check.append(point(node.y+1, node.x))
		values_to_check.append(map.vector[node.y+1][node.x])
		degrees_to_turn.append(180)

	# SouthWest
	if node.y != map.h and x != 0 and map.vector[node.y+1][node.x-1] >= 0:
		nodes_to_check.append(point(node.y+1, node.x-1))
		values_to_check.append(map.vector[node.y+1][node.x-1])
		degrees_to_turn.append(225)

	# West
	if node.x != 0 and map.vector[node.y][node.x-1] >= 0:
		nodes_to_check.append(point(node.y, node.x-1))
		values_to_check.append(map.vector[node.y][node.x-1])
		degrees_to_turn.append(270)

	# NorthWest
	if node.y != 0 and node.x != 0 and map.vector[node.y+1][node.x-1] >= 0:
		nodes_to_check.append(point(node.y+1, node.x-1))
		values_to_check.append(map.vector[node.y+1][node.x-1])
		degrees_to_turn.append(315)

	min_index = 0
	
	for x in range(1, values_to_check.size):
		if values_to_check[x] < min_value:
			min_index = x
	
	turn_dir = degrees_to_turn[min_index]
	degree_to_turn = turn_dir-current_degree
	if degree_to_turn > 180:
		degree_to_turn = degree_to_turn-360

	node = nodes_to_check[x]
	cozmo_program(degree_to_turn)
	
    
    
    
    			

