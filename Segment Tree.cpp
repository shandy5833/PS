vector<ll> tree;
ll n;

void Upd(ll p, ll val) { // update pth idx into val
    for (tree[p += n] = val; p > 1; p >>= 1)
        tree[p >> 1] = tree[p] + tree[p ^ 1];
}
ll Qry(ll l, ll r) { // query on range [l, r)
    ll ret = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret += tree[l++];
        if (r & 1) ret += tree[--r];
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    tree.resize(n << 2, 0);

    return 0;
}
