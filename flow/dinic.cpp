const int MAXN = 555;
struct edge {
    int to, cap, rev;
};
int level[MAXN];
int work[MAXN];
std::vector<edge> adj[MAXN];

void add_edge(int from, int to, int c) {
    adj[from].push_back({to, c, (int)adj[to].size()});
    adj[to].push_back({from, 0, (int)adj[from].size() - 1});
}

bool bfs(int src, int sink) {
    std::fill(level, level + MAXN, -1);
    std::fill(work, work + MAXN, 0);
    level[src] = 0;
    std::queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto &e : adj[now])
            if (e.cap > 0 && level[e.to] == -1)
                level[e.to] = level[now] + 1, q.push(e.to);
    }
    return level[sink] != -1;
}

int dfs(int now, int sink, int amount) {
    if (now == sink) return amount;
    for (int &i = work[now]; i < adj[now].size(); i++) {
        auto e = adj[now][i];
        if (e.cap > 0 && level[e.to] == level[now] + 1) {
            int df = dfs(e.to, sink, std::min(amount, e.cap));
            if (df > 0) {
                adj[now][i].cap -= df;
                adj[e.to][e.rev].cap += df;
                return df;
            }
        }
    }
    return 0;
}

int dinic(int src, int sink) {
    int max_flow = 0;
    while (bfs(src, sink))
        while (1) {
            int df = dfs(src, sink, INT_MAX);
            if (!df) break;
            max_flow += df;
        }
    return max_flow;
}
