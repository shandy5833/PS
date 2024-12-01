vector<ll> tree(n << 2, 0);
ll n;

void U(ll p, ll val) {
    for (tree[p += n] = val; p > 1; p >>= 1)
        tree[p >> 1] = tree[p] + tree[p ^ 1];
}
ll Q(ll l, ll r) {
    ll ret = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret += tree[l++];
        if (r & 1) ret += tree[--r];
    }
    return ret;
}
