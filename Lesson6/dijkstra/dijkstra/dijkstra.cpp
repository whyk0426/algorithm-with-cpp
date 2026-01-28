#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <set>

struct Edge {
    Node* source;
    Node* target;
    double weight;
};

struct Node {
    int x;
    int y;
    std::vector<Edge*> edges;

    Node(int _x, int _y) : x(_x), y(_y) {}

    bool operator == (const Node& other) {
        return (this->x == other.x) && (this->y == other.y);
    }
};

class Graph {
private:
    std::vector<Node*> nodes;

public:
    Graph() {};

    void add_node(Node* node) {
        nodes.emplace_back(node);
    }

    const std::vector<Node*>& get_nodes() const {
        return nodes;
    }
};

Graph dijkstra(const Graph& G, Node* start, Node* goal) {
    std::unordered_map<Node*, double> map;
    std::unordered_map<Node*, Node*> parent;


    for (Node* node : G.get_nodes()) {
            map[node] = std::numeric_limits<double>::max();
    }
    map[start] = 0.0;
    parent[start] = nullptr;

    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<std::pair<double, Node*>>> priority_q;

    priority_q.emplace(map[start], start);

    while (!priority_q.empty()) {
        double current_dist = priority_q.top().first;
        Node* current_node = priority_q.top().second;
        priority_q.pop();

        if (current_node == goal) break;

        if (current_dist > map[current_node]) continue;

        for (Edge* edge : current_node->edges) {
            Node* neighbor = edge->target;
            double dist = map[current_node] + edge->weight;

            if (dist < map[neighbor]) {
                map[neighbor] = dist;
                priority_q.emplace(dist, neighbor);
                parent[neighbor] = current_node;
            }            
        }
    }
    std::vector<Node*> path;
    Node* current = goal;

    while (current != nullptr) {
        path.emplace_back(current);
        current = parent[current];
    }
    Graph optimal_path;

    for (int i = path.size() - 1; i >= 0; i--) {
        optimal_path.add_node(path[i]);
    }
    return optimal_path;
}




int main()
{
    std::cout << "Hello World!\n";
}