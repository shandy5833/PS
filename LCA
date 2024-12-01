const ll MAXN = 1000001;
ll par[20][MAXN], dep[MAXN];
vector<ll> adj[MAXN];
ll n;

void DFS(ll cur, ll prv, ll d) {
    dep[cur] = d;
    par[cur][0] = prv;
    for (ll i = 1; i < 20; i++)
        par[i][cur] = par[i - 1][par[i - 1][cur]];
    for (ll i : adj[cur])
        if (i != prv) DFS(i, cur, d + 1);
}
ll LCA(ll x, ll y) {
    if (dep[x] < dep[y]) swap(x, y);
    if (dep[x] != dep[y])
        for (ll i = 19; i >= 0; i--)
            if (dep[par[i][x]] >= dep[y]) x = par[i][x];
    if (x == y) return x;
    for (ll i = 19; i >= 0; i--)
        if (par[i][x] != par[i][y]) x = par[i][x], y = par[i][y];
    return par[0][x];
}

int main() {
    DFS(1, 0, 1);
}
