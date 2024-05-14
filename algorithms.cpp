#include "algorithms.h"

void Algorithms::dijkstra(int u)
{
    fill(Dis.begin(), Dis.begin() + (int)adj.size() + 2, double(1e9));
    Dis[u] = 0;
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    pq.push({Dis[u], u});
    while(pq.size()) {
        int u = pq.top().second;
        double dis = pq.top().first;
        if (dis > Dis[u]) continue;

        for (auto& e : adj[u]) {
            if (Dis[e.second] > Dis[u] + e.first) {
                Dis[e.second] = Dis[u] + e.first;
                pq.push({Dis[e.second], e.first});
            }
        }
    }
}

void Algorithms::initDijkstra()
{

}
