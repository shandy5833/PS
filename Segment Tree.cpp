const ll maxV = 1000000;

struct Seg {
    ll arr[maxV], tree[4 * maxV];
    void Init(ll N, ll s, ll e) {
        if (s == e) {
            tree[N] = arr[s];
            return;
        }
        ll mid = (s + e) / 2;
        Init(N * 2, s, mid);
        Init(N * 2 + 1, mid + 1, e);
        tree[N] = tree[N * 2] + tree[N * 2 + 1];
    }
    void Update(ll N, ll s, ll e, ll idx, ll val) {
        if (s == e) {
            if (s == idx) tree[N] = val;
            return;
        }
        ll mid = (s + e) / 2;
        if (idx <= mid)
            Update(N * 2, s, mid, idx, val);
        else
            Update(N * 2 + 1, mid + 1, e, idx, val);
        tree[N] = tree[N * 2] + tree[N * 2 + 1];
    }
    ll Query(ll N, ll s, ll e, ll l, ll r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[N];
        ll mid = (s + e) / 2;
        return Query(N * 2, s, mid, l, r) + Query(N * 2 + 1, mid + 1, e, l, r);
    }
};
