import matplotlib.pyplot as plt
import networkx as nx

# Function to draw the graph
def draw_graph_with_colors(graph, node_colors):
    """Draw the graph with the specified node colors."""
    pos = nx.spring_layout(graph)  # Positions for all nodes
    plt.figure(figsize=(8, 8))
    nx.draw(graph, pos, with_labels=True, node_color=node_colors, node_size=800, font_size=10, font_color="black")
    plt.show()

# Read adjacency matrix from file
def read_adjacency_matrix_from_file(filename):
    """Reads an adjacency matrix from a file."""
    with open(filename, "r") as f:
        lines = f.readlines()
        num_vertices = int(lines[0].strip())
        matrix = [list(map(int, line.strip().split())) for line in lines[1:]]
    return num_vertices, matrix

# Main function
def main():
    # Load the adjacency matrix from the file
    filename = "..//graph.gh"  # Replace with your file path
    num_vertices, adj_matrix = read_adjacency_matrix_from_file(filename)

    # Create a graph from the adjacency matrix
    graph = nx.Graph()
    for i in range(num_vertices):
        for j in range(i + 1, num_vertices):
            if adj_matrix[i][j] == 1:
                graph.add_edge(i, j)

    # Initialize node colors (default blue)
    node_colors = ["skyblue"] * num_vertices

    while True:
        # Draw the graph
        draw_graph_with_colors(graph, node_colors)

        # Ask user for vertex index
        try:
            vertex_index = int(input(f"Enter a vertex index (0 to {num_vertices - 1}, or -1 to quit): "))
            if vertex_index == -1:
                print("Exiting program.")
                break
            if vertex_index < 0 or vertex_index >= num_vertices:
                print(f"Invalid index. Please enter a number between 0 and {num_vertices - 1}.")
                continue

            # Toggle the color of the selected vertex
            if node_colors[vertex_index] == "skyblue":
                node_colors[vertex_index] = "red"
            else:
                node_colors[vertex_index] = "skyblue"

        except ValueError:
            print("Invalid input. Please enter an integer.")

if __name__ == "__main__":
    main()
