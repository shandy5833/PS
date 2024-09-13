const ll maxV = 1000000;

struct LazySeg {
    ll arr[maxV], tree[4 * maxV], lazy[4 * maxV];
    void Init(ll N, ll s, ll e) {
        lazy[N] = 0;
        if (s == e) {
            tree[N] = arr[s];
            return;
        }
        ll mid = (s + e) / 2;
        Init(N * 2, s, mid);
        Init(N * 2 + 1, mid + 1, e);
        tree[N] = tree[N * 2] + tree[N * 2 + 1];
    }
    void Lazy(ll N, ll s, ll e) {
        if (lazy[N]) {
            tree[N] += (e - s + 1) * lazy[N];
            if (s != e) {
                lazy[N * 2] += lazy[N];
                lazy[N * 2 + 1] += lazy[N];
            }
            lazy[N] = 0;
        }
    }
    void Update(ll N, ll s, ll e, ll l, ll r, ll val) {
        Lazy(N, s, e);
        if (e < l || r < s) return;
        if (l <= s && e <= r) {
            lazy[N] += val;
            Lazy(N, s, e);
            return;
        }
        ll mid = (s + e) / 2;
        Update(N * 2, s, mid, l, r, val);
        Update(N * 2 + 1, mid + 1, e, l, r, val);
        tree[N] = tree[N * 2] + tree[N * 2 + 1];
    }
    ll Query(ll N, ll s, ll e, ll l, ll r) {
        Lazy(N, s, e);
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) return tree[N];
        ll mid = (s + e) / 2;
        return Query(N * 2, s, mid, l, r) + Query(N * 2 + 1, mid + 1, e, l, r);
    }
};
