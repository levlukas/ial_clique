import os
import matplotlib.pyplot as plt
import networkx as nx

def draw_graph_with_colors(graph, node_colors):
    pos = nx.spring_layout(graph)
    plt.figure(figsize=(8, 8))
    nx.draw(graph, pos, with_labels=True, node_color=node_colors, node_size=800, font_size=10, font_color="black")
    plt.show()

def read_adjacency_matrix_from_file(filename):
    with open(filename, "r") as f:
        lines = f.readlines()
        num_vertices = int(lines[0].strip())
        matrix = [list(map(int, line.strip().split())) for line in lines[1:]]
    return num_vertices, matrix

def main(filename):
    num_vertices, adj_matrix = read_adjacency_matrix_from_file(filename)

    graph = nx.Graph()
    for i in range(num_vertices):
        for j in range(i + 1, num_vertices):
            if adj_matrix[i][j] == 1:
                graph.add_edge(i, j)

    node_colors = ["skyblue"] * num_vertices

    while True:
        draw_graph_with_colors(graph, node_colors)

        try:
            vertex_index = int(input(f"enter vertex from 0 to {num_vertices - 1}, or -1 to quit): "))
            if vertex_index == -1:
                break
            if vertex_index < 0 or vertex_index >= num_vertices:
                print(f"invlaid index, range from 0 to {num_vertices - 1}.")
                continue

            if node_colors[vertex_index] == "skyblue":
                node_colors[vertex_index] = "red"
            else:
                node_colors[vertex_index] = "skyblue"

        except ValueError:
            print("invlid input")

if __name__ == "__main__":
    for file in os.listdir():
        if file.endswith('.gh'):
            main(file)
