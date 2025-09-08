# 5. Graph: Minimum Spanning Tree -- CO1, CO2, CO3
# Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes should represent the various departments/institutes and links should represent the distance between them.
# Find minimum spanning tree
# a) Using Kruskal’s algorithm.
# b) Using Prim’s algorithm.


# Graph Minimum Spanning Tree using Kruskal's and Prim's Algorithm
# Departments of a college as nodes, distances as weighted edges

class Graph:
    def __init__(self, vertices):
        self.V = vertices  # Number of vertices
        self.graph = []    # For Kruskal (Edge List)
        self.adj_matrix = [[0 for _ in range(vertices)] for _ in range(vertices)]  # For Prim

    def add_edge(self, u, v, w):
        """Adds edge for Kruskal and Prim"""
        self.graph.append([u, v, w])  # Kruskal representation
        self.adj_matrix[u][v] = w     # Prim representation
        self.adj_matrix[v][u] = w

    # ----------------------- Kruskal’s Algorithm -----------------------
    def find_parent(self, parent, i):
        """Find with path compression"""
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])

    def union(self, parent, rank, x, y):
        """Union by rank"""
        xroot = self.find_parent(parent, x)
        yroot = self.find_parent(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_mst(self):
        """Kruskal’s MST"""
        result = []  # Store MST edges
        i, e = 0, 0

        # Step 1: Sort all edges
        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1:
            u, v, w = self.graph[i]
            i = i + 1
            x = self.find_parent(parent, u)
            y = self.find_parent(parent, v)

            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        print("\nKruskal's MST:")
        total_cost = 0
        for u, v, weight in result:
            print(f"Department {u} -- {v}  weight = {weight}")
            total_cost += weight
        print("Total Cost of MST:", total_cost)

    # ----------------------- Prim’s Algorithm -----------------------
    def prim_mst(self):
        """Prim’s MST using adjacency matrix"""
        key = [float("inf")] * self.V
        parent = [-1] * self.V
        mst_set = [False] * self.V

        key[0] = 0  # Start from first vertex

        for _ in range(self.V):
            # Pick min key vertex not in MST
            u = min((k for k in range(self.V) if not mst_set[k]), key=lambda k: key[k])
            mst_set[u] = True

            # Update neighbors
            for v in range(self.V):
                if 0 < self.adj_matrix[u][v] < key[v] and not mst_set[v]:
                    key[v] = self.adj_matrix[u][v]
                    parent[v] = u

        print("\nPrim's MST:")
        total_cost = 0
        for i in range(1, self.V):
            print(f"Department {parent[i]} -- {i}  weight = {self.adj_matrix[i][parent[i]]}")
            total_cost += self.adj_matrix[i][parent[i]]
        print("Total Cost of MST:", total_cost)


# ----------------------- Driver Code -----------------------
if __name__ == "__main__":
    # Example: 5 departments (nodes)
    # 0: Admin, 1: CSE, 2: Mechanical, 3: Civil, 4: Library

    g = Graph(5)
    g.add_edge(0, 1, 2)  # Admin - CSE
    g.add_edge(0, 3, 6)  # Admin - Civil
    g.add_edge(1, 2, 3)  # CSE - Mech
    g.add_edge(1, 3, 8)  # CSE - Civil
    g.add_edge(1, 4, 5)  # CSE - Library
    g.add_edge(2, 4, 7)  # Mech - Library
    g.add_edge(3, 4, 9)  # Civil - Library

    g.kruskal_mst()
    g.prim_mst()



# Minimum Spanning Tree using Kruskal and Prim

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []  # store edges for Kruskal
        self.adj = [[0]*vertices for _ in range(vertices)]  # adjacency matrix for Prim

    def add_edge(self, u, v, w):
        self.edges.append((w, u, v))
        self.adj[u][v] = w
        self.adj[v][u] = w

    # ---------- Kruskal's Algorithm ----------
    def kruskal(self):
        parent = list(range(self.V))

        def find(i):
            while parent[i] != i:
                i = parent[i]
            return i

        mst = []
        self.edges.sort()
        for w, u, v in self.edges:
            pu, pv = find(u), find(v)
            if pu != pv:
                mst.append((u, v, w))
                parent[pu] = pv
        print("\nKruskal's MST:")
        cost = 0
        for u, v, w in mst:
            print(u, "--", v, "=", w)
            cost += w
        print("Total Cost:", cost)

    # ---------- Prim's Algorithm ----------
    def prim(self):
        selected = [False]*self.V
        key = [999999]*self.V
        parent = [-1]*self.V
        key[0] = 0

        for _ in range(self.V):
            u = min((i for i in range(self.V) if not selected[i]), key=lambda i: key[i])
            selected[u] = True
            for v in range(self.V):
                if self.adj[u][v] and not selected[v] and self.adj[u][v] < key[v]:
                    key[v] = self.adj[u][v]
                    parent[v] = u

        print("\nPrim's MST:")
        cost = 0
        for i in range(1, self.V):
            print(parent[i], "--", i, "=", self.adj[i][parent[i]])
            cost += self.adj[i][parent[i]]
        print("Total Cost:", cost)


# ----------- Driver Code -----------
g = Graph(5)  # 5 departments
g.add_edge(0, 1, 2)
g.add_edge(0, 3, 6)
g.add_edge(1, 2, 3)
g.add_edge(1, 3, 8)
g.add_edge(1, 4, 5)
g.add_edge(2, 4, 7)
g.add_edge(3, 4, 9)

g.kruskal()
g.prim()




