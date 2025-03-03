const ll MAXN = 101000;
ll fin[MAXN], vis[MAXN], sn[MAXN];
std::vector<std::vector<ll>> SCC;
std::vector<ll> adj[MAXN];
std::stack<ll> st;
ll n, m, id, SN;

ll dfs(ll x) {
    vis[x] = ++id;
    st.push(x);
    ll par = vis[x];
    for (auto i : adj[x]) {
        if (!vis[i]) par = std::min(par, dfs(i));
        else if (!fin[i]) par = std::min(par, vis[i]);
    }
    if (par == vis[x]) {
        std::vector<ll> scc;
        while (1) {
            ll cur = st.top();
            st.pop();
            scc.push_back(cur);
            fin[cur] = true;
            sn[cur] = SN + 1;
            if (cur == x) break;
        }
        std::sort(scc.begin(), scc.end());
        SCC.push_back(scc);
        SN++;
    }
    return par;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);

    std::cin >> n >> m;
    for (ll i = 0, u, v; i < m; i++) std::cin >> u >> v, adj[u].push_back(v);
    for (ll i = 1; i <= n; i++)
        if (!vis[i]) dfs(i);

    return 0;
}
