#include <bits/stdc++.h>

using namespace std;


class SparseTable {
private:
    int N, P;
    std::vector<int> logs;
    std::vector<std::vector<long long>> sparse;
    std::vector<std::vector<int>> index;

    static long long cmp(long long &a, long long &b) {
        return std::min(a, b);
    }

public:
    SparseTable() = default;

    explicit SparseTable(std::vector<long long> &values) {
        init(values);
    }

    void init(std::vector<long long> &values) {
        N = (int) values.size();
        P = (int) std::__lg(N);
        logs.resize(N + 1);
        sparse.resize(P + 1, std::vector<long long>(N));
        index.resize(P + 1, std::vector<int>(N));

        for (int i = 2; i <= N; ++i)
            logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < N; ++i)
            sparse[0][i] = values[i], index[0][i] = i;
        for (int p = 1; p <= P; ++p)
            for (int i = 0; i + (1 << p) <= N; ++i) {
                long long rightValue = sparse[p - 1][i], leftValue = sparse[p - 1][i + (1 << (p - 1))];
                sparse[p][i] = cmp(rightValue, leftValue);
                if (rightValue == cmp(rightValue, leftValue))
                    index[p][i] = index[p - 1][i];
                else index[p][i] = index[p - 1][i + (1 << (p - 1))];
            }
    }


    long long FastQuery(int l, int r) {
        --l, --r;
        int p = logs[r - l + 1];
        return cmp(sparse[p][l], sparse[p][r - (1 << p) + 1]);
    }

    long long FastIndexQuery(int l, int r) {
        --l, --r;
        int p = logs[r - l + 1];
        long long rightValue = sparse[p][l], leftValue = sparse[p][r - (1 << p) + 1];
        return (rightValue == cmp(rightValue, leftValue) ? index[p][l] : index[p][r - (1 << p) + 1]);
    }
};

const int N = 2e5 + 3;
vector<int> adj[N], paths[N], e, h, ended, nPaths, doubleCount;
vector<long long> l;
int n, p, currentIndex = 0;
SparseTable sparse;


void visit(int node, int depth) {
    l[currentIndex] = depth;
    e[currentIndex] = node;
    h[node] = currentIndex;
    ++currentIndex;
}

void eulerTour(int node, int parent, int depth) {
    visit(node, depth);
    for (const int &u: adj[node]) {
        if (u == parent)continue;
        eulerTour(u, node, depth + 1);
        visit(node, depth);
    }
}

int lca(int u, int v) {
    int a = h[u] + 1, b = h[v] + 1;
    if (a > b) swap(a, b);
    return e[sparse.FastIndexQuery(a, b)];
}

int dfs(int node, int parent) {
    for (const int &u: adj[node]) {
        if (u == parent)continue;
        nPaths[node] += dfs(u, node);
    }
    int startedPaths = 0;
    for (const int &end: paths[node]) {
        int ancestor = lca(node, end);
        ++ended[ancestor], ++doubleCount[ancestor], ++startedPaths;
    }
    nPaths[node] += startedPaths;
    return nPaths[node] - ended[node];
}

void solve() {
    cin >> n >> p;
    e.resize(2 * n), l.resize(2 * n), h.resize(n + 1);
    nPaths.resize(n + 1), doubleCount.resize(n + 1), ended.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < p; ++i) {
        int a, b;
        cin >> a >> b;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    eulerTour(1, -1, 0);
    sparse.init(l);
    dfs(1, -1);
    for (int i = 1; i <= n; ++i)
        cout << nPaths[i] - doubleCount[i] / 2 << ' ';
    cout << '\n';
}


int main() {
    solve();
    return 0;
}