#define __STDC_LIMIT_MACROS
#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

typedef vector<vector<int64_t>> AdjMatrix;

struct TEdge {
    size_t from;
    size_t to;
    int64_t weigth;
};

struct TGraph {
    size_t v, e;
    vector<TEdge> edges;
    TGraph() {}
    TGraph(size_t n, size_t m) : v(n), e(m) {
        edges.reserve(m);
    }
};

bool operator < (TEdge p1, TEdge p2) {
    return p1.weigth > p2.weigth; 
}

void Dijkstra(AdjMatrix& gr, size_t givenNode, AdjMatrix& dist, size_t n) {
    dist[givenNode][givenNode] = 0;
    priority_queue<TEdge> pq;
    TEdge t = { givenNode, 0, 0 };
    pq.push(t);
    while (!pq.empty()) {
        TEdge s = pq.top();
        pq.pop();
        for (size_t i = 0; i < n; i++) {
            if (dist[givenNode][i] - dist[givenNode][s.from] > gr[s.from][i]) {
                dist[givenNode][i] = dist[givenNode][s.from] + gr[s.from][i];
                TEdge p = { i, 0, dist[givenNode][i] };
                pq.push(p);
            }
        }
    }
}

bool BellmanFord(TGraph& gr, size_t givenNode, AdjMatrix& dist) {
    dist[givenNode][givenNode] = 0;
    for (size_t k = 0; k < gr.v - 1; k++) {
        for (auto i : gr.edges)
            if (dist[givenNode][i.from] != INT64_MAX &&  dist[givenNode][i.to] > dist[givenNode][i.from] + i.weigth)
                dist[givenNode][i.to] = (dist[givenNode][i.from] + i.weigth);
    }
    for (auto i : gr.edges) 
        if (dist[givenNode][i.from] != INT64_MAX &&  dist[givenNode][i.to] > dist[givenNode][i.from] + i.weigth)
            return false;
    return true;
}

bool Johnson(TGraph& gr, AdjMatrix& dist) {
    TGraph gr2;
    gr2.v = gr.v + 1;
    gr2.e = gr.e + gr.v;
    gr2.edges = gr.edges;
    for (size_t i = 0; i < gr.v; i++)
        gr2.edges.push_back(TEdge{ gr.v, i, 0 });
    AdjMatrix dist2(1, vector<int64_t>(gr2.v, 0));
    if (!BellmanFord(gr2, 0, dist2)) {
        cout << "Negative cycle" << endl;
        return false;
    }
    AdjMatrix graph(gr.v, vector<int64_t>(gr.v, INT64_MAX));
    for (size_t i = 0; i < gr.v; i++)
        graph[i][i] = 0;
    for (auto i : gr.edges)
        graph[i.from][i.to] = i.weigth + dist2[0][i.from] - dist2[0][i.to];
    
    for (size_t i = 0; i < gr.v; i++)
        Dijkstra(graph, i, dist, gr.v);
    for (size_t i = 0; i < gr.v; i++)
        for (size_t j = 0; j < gr.v; j++)
            if (dist[i][j] != INT64_MAX)
                dist[i][j] = dist[i][j] + dist2[0][j] - dist2[0][i];
    return true;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    TGraph gr(n, m);
    AdjMatrix dist(n, vector<int64_t>(n, INT64_MAX));
    for (size_t i = 0; i < n; i++)
        dist[i][i] = 0;
    size_t i, j;
    int64_t w;
    for (size_t k = 0; k < m; k++) {
        cin >> i >> j >> w;
        gr.edges[i] = TEdge{ i - 1, j - 1, w };
    }
    if (Johnson(gr, dist)) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (dist[i][j] == INT64_MAX)
                    cout << "inf";
                else
                    cout << dist[i][j];
                if (j != n - 1)
                    cout << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}