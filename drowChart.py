import matplotlib.pyplot as plt

count  = input();

a_star_nodes_count = []
dijkstra_nodes_count = []
distance = []

for counter in range(1, count):
    distance.append(input())
    dijkstra_nodes_count.append(input())
    a_star_nodes_count.append(input())

distance.sort()
a_star_nodes_count.sort()
dijkstra_nodes_count.sort()

a_star_line, dijkstra_line = plt.plot(distance, a_star_nodes_count, 'b', distance, dijkstra_nodes_count, 'r')


plt.xlabel('Distance, m')
plt.ylabel('Quantity of seen nodes')

plt.legend( (a_star_line, dijkstra_line), ('A*', 'Dijkstra'))

plt.grid()

plt.savefig('chart.png', format = 'png')