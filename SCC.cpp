const ll MAXN = 101000;
ll fin[MAXN], vis[MAXN], sn[MAXN];
vector<vector<ll>> SCC;
ll n, m, u, v, id, SN;
vector<ll> adj[MAXN];
stack<ll> st;

ll DFS(ll x) {
    vis[x] = ++id;
    st.push(x);
    ll par = vis[x];
    for (auto i : adj[x]) {
        if (!vis[i]) par = min(par, DFS(i));
        else if (!fin[i]) par = min(par, vis[i]);
    }
    if (par == vis[x]) {
        vector<ll> scc;
        while (1) {
            ll cur = st.top();
            st.pop();
            scc.push_back(cur);
            fin[cur] = true;
            sn[cur] = SN + 1;
            if (cur == x) break;
        }
        sort(scc.begin(), scc.end());
        SCC.push_back(scc);
        SN++;
    }
    return par;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (ll i = 0; i < m; i++)
        cin >> u >> v, adj[u].push_back(v);
    for (ll i = 1; i <= n; i++)
        if (!vis[i]) D(i);

    return 0;
}
