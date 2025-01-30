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

ll dist(pt a, pt b) { return (b - a).sz(); }

void hull(std::vector<pt> &v) {
    sort(v.begin(), v.end());
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
