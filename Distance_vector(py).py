def Bellman_Ford(G, V, E, edge):
    distance = [float('inf')] * V
    S = int(input("Enter source: ")) - 1  # Adjusted to 0-based indexing
    distance[S] = 0

    for i in range(V - 1):
        for k in range(E):
            u = edge[k][0]
            v = edge[k][1]
            weight = G[u][v]
            if distance[u] + weight < distance[v]:
                distance[v] = distance[u] + weight

    # Check for negative weight cycles
    for k in range(E):
        u = edge[k][0]
        v = edge[k][1]
        weight = G[u][v]
        if distance[u] + weight < distance[v]:
            print("\nGraph contains a negative weight cycle.")
            return

    print("\nShortest distances from source:")
    for i in range(V):
        print(f"To {i + 1}: {distance[i]}")

V = int(input("Enter no. of vertices: "))
edge = [[0] * 2 for _ in range(100)]
G = [[0] * 100 for _ in range(100)]
k = 0

print("Enter graph in matrix form:")
for i in range(V):
    for j in range(V):
        G[i][j] = int(input())
        if G[i][j] != 0:
            edge[k][0] = i
            edge[k][1] = j
            k += 1

Bellman_Ford(G, V, k, edge)
