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

Graph prim_MST(const Graph& G, Node* root) {
    std::unordered_map<Node*, double> map;
    std::unordered_map<Node*, Node*> parent;

    for (Node* node : G.get_nodes()) {
        if (node == root)
            map[node] = 0.0;
        else
            map[node] = std::numeric_limits<double>::max();
    }

    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<std::pair<double, Node*>>> priority_q;
    std::set<Node*> visited;
    
    priority_q.emplace(map[root], root);

    while (!priority_q.empty()) {
        Node* current_node = priority_q.top().second;
        priority_q.pop();

        if (visited.find(current_node) != visited.end()) continue;

        visited.emplace(current_node);

        for (Edge* edge : current_node->edges) {
            Node* neighbor = edge->target;

            if (visited.find(neighbor) != visited.end()) continue;
            
            if (edge->weight < map[neighbor]) {
                map[neighbor] = edge->weight;
                parent[neighbor] = current_node;
                priority_q.emplace(edge->weight, neighbor);
            }
        }
        
    }
    Graph MST;



    return MST;
}




int main()
{
    std::cout << "Hello World!\n";
}