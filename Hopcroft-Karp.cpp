const ll MAXN = 1010, MAXM = 1010;
ll dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
vector<ll> adj[MAXN];

bool B(ll x) {
    queue<ll> q;
    bool ret = 0;
    memset(dis, 0, sizeof(dis));
    for (ll i = 1; i <= x; i++)
        if (l[i] == -1 && !dis[i]) q.push(i), dis[i] = 1;
    while (q.size()) {
        ll cur = q.front();
        q.pop();
        for (auto &i : adj[cur]) {
            if (r[i] == -1) ret = 1;
            else if (!dis[r[i]]) dis[r[i]] = dis[cur] + 1, q.push(r[i]);
        }
    }
    return ret;
}

bool D(ll x) {
    if (vis[x]) return 0;
    vis[x] = 1;
    for (auto &i : adj[x]) {
        if (r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && D(r[i]))) {
            l[x] = i, r[i] = x;
            return 1;
        }
    }
    return 0;
}

ll M(ll x) {
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));
    ll ret = 0;
    while (B(x)) {
        memset(vis, 0, sizeof(vis));
        for (ll i = 1; i <= x; i++)
            if (l[i] == -1 && D(i)) ret++;
    }
    return ret;
}
