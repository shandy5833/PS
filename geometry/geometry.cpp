struct pt {
    ll x, y;
    pt() {
        x = 0;
        y = 0;
    }
    pt(ll p, ll q) { x = p, y = q; }
    pt operator+(pt t) { return {x + t.x, y + t.y}; }
    pt operator-(pt t) { return {x - t.x, y - t.y}; }
    ll operator*(pt t) { return x * t.x + y * t.y; }
    ll operator/(pt t) { return x * t.y - y * t.x; }
    bool operator==(const pt t) const { return x == t.x && y == t.y; }
    bool operator<(const pt t) const { return x == t.x ? y < t.y : x < t.x; }
    bool operator>(const pt t) const { return x == t.x ? y > t.y : x > t.x; }
    ll sz() { return x * x + y * y; }
    pt mul(ll m) { return {x * m, y * m}; }
};

ll ccw(pt a, pt b, pt c) {
    b = b - a, c = c - a;
    return b.x * c.y - c.x * b.y;
}

bool intersect(pt p1, pt p2, pt p3, pt p4) {
    ll a = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    ll b = ccw(p3, p4, p1) * ccw(p3, p4, p2);
    if (!a && !b) {
        if (p2 < p1) std::swap(p1, p2);
        if (p4 < p3) std::swap(p3, p4);
        return !(p2 < p3 || p4 < p1);
    }
    return a <= 0 && b <= 0;
}

ll dist(pt a, pt b) { return (b - a).sz(); }

void hull(std::vector<pt> &v) {
    std::sort(v.begin(), v.end());
    std::vector<pt> L, R;
    for (pt i : v) {
        while (L.size() >= 2 && ccw(i, L[L.size() - 1], L[L.size() - 2]) <= 0)
            L.pop_back();
        L.emplace_back(i);
        while (R.size() >= 2 && ccw(i, R[R.size() - 1], R[R.size() - 2]) >= 0)
            R.pop_back();
        R.emplace_back(i);
    }
    v.clear();
    for (ll i = 0; i < R.size() - 1; i++) v.emplace_back(R[i]);
    for (ll i = L.size() - 1; i > 0; i--) v.emplace_back(L[i]);
}

ll inside(pt p, std::vector<pt> &v) {
    ll n = v.size();
    if (n < 3 || ccw(v[0], v[1], p) < 0 || ccw(v[0], v[n - 1], p) > 0) return 0;

    ll l = 2, r = n - 1, m;
    while (l < r) {
        m = (l + r) / 2;
        if (ccw(v[0], v[m], p) < 0) r = m;
        else l = m + 1;
    }
    return ccw(v[l - 1], p, v[l]) < 0;
}
