template <typename T> struct seg {
    ll n;
    T id;
    vector<T> t;
    T (*merge)(T, T);
    seg(ll N, T ID, T (*MERGE)(T, T)) : n(N), id(ID), merge(MERGE) {
        t.resize(N << 1, id);
    }
    void update(ll p, T val) {
        for (t[p += n] = val; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = merge(t[p ^ 1], t[p]);
            else t[p >> 1] = merge(t[p], t[p ^ 1]);
        }
    }
    T query(ll l, ll r) {
        T lret = id, rret = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lret = merge(lret, t[l++]);
            if (r & 1) rret = merge(t[--r], rret);
        }
        return merge(lret, rret);
    }
};
