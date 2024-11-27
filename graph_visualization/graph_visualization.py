import networkx as nx
import matplotlib.pyplot as plt

def read_adjacency_matrix_from_file(filename):
    """Reads the adjacency matrix from a file."""
    with open(filename, 'r') as file:
        # Read the size of the matrix (first line)
        size = int(file.readline().strip())
        
        # Read the adjacency matrix (subsequent lines)
        matrix = []
        for line in file:
            row = list(map(int, line.split()))
            matrix.append(row)
        
        return size, matrix

def create_graph_from_matrix(adj_matrix):
    """Create an undirected graph from the adjacency matrix."""
    G = nx.Graph()
    num_vertices = len(adj_matrix)
    
    # Add nodes to the graph
    G.add_nodes_from(range(num_vertices))
    
    # Add edges based on the adjacency matrix
    for i in range(num_vertices):
        for j in range(i + 1, num_vertices):  # Check only upper triangle to avoid duplicate edges
            if adj_matrix[i][j] == 1:
                G.add_edge(i, j)
    
    return G

def display_graph(G):
    """Displays the graph using matplotlib."""
    # Use a spring layout for node positioning
    pos = nx.spring_layout(G)
    
    # Draw the graph
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_size=500, node_color="skyblue", font_size=12, font_weight="bold", edge_color="gray")
    plt.title("Graph Visualization")
    plt.show()


# Read the adjacency matrix from a file
filename = r'graph.ph'  # Replace with your file path
num_vertices, adj_matrix = read_adjacency_matrix_from_file(filename)

# Create the graph from the adjacency matrix
graph = create_graph_from_matrix(adj_matrix)

# Display the graph visually
display_graph(graph)
