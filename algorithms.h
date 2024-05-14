#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

#include <bits/stdc++.h>
#define pdi pair<double, int>

using namespace std;
class Algorithms
{
public:
    void dijkstra(int u);
    void initDijkstra();
private:
    vector<double> Dis;
    vector<vector<pdi>> adj;
};

#endif // ALGORITHMS_H_INCLUDED
