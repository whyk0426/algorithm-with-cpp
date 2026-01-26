#include <iostream>
#include <vector>
#include <stack>
#include <set>

struct Edge {
    int source;
    int target;
    double weight;
};

class Graph {
private:
    int n;
    std::vector<Edge> edge_list;

public:
    Graph(int N) : n(N) {}

    int nodes() const { return n; }
    const std::vector<Edge>& edges() const { return edge_list; }

    std::vector<Edge> edges(int node) const {
        std::vector<Edge> edges_from_node;
        for (const Edge& e : edge_list) {
            if (e.source == node)
                edges_from_node.emplace_back(e);
        }
        return edges_from_node;
    }

    void add_edge(const Edge& e) {
        if (e.source >= 1 && e.source <= n && e.target >= 1 && e.source <= n)
            edge_list.emplace_back(e);
        else
            std::cerr << "에러: 유효 범위를 벗어난 정점!" << std::endl;
    }
};

std::vector<int> DFS(const Graph& G, int start) {
    std::stack<int> stack;
    std::set<int> visited;
    std::vector<int> visit_order;

    stack.emplace(start);

    while (!stack.empty()) {
        int current_node = stack.top();
        stack.pop();

        if (visited.find(current_node) != visited.end()) continue;

        visited.emplace(current_node);
        visit_order.emplace_back(current_node);

        for (const Edge& e : G.edges(current_node)) {
            if (visited.find(e.target) != visited.end()) {
                stack.emplace(e.target);
            }
        }
    }
    return visit_order;
}


int main()
{
    std::cout << "Hello World!\n";
}