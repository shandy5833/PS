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

double linedist(pt a, pt b, pt c) {
    pt t = b - a;
    // 선분일 때
    if (t * (c - a) <= 0) return sqrt(dist(a, c));
    if (t * (c - b) >= 0) return sqrt(dist(b, c));
    // 직선일 때
    return abs(t / (c - a)) / sqrt(t.sz());
}

std::vector<pt> hull(std::vector<pt> v) {
    int ix = std::min_element(v.begin(), v.end()) - v.begin();
    std::swap(v[0], v[ix]);
    std::vector<pt> st;
    std::sort(v.begin() + 1, v.end(), [&](pt &a, pt &b) {
        pt x = a - v[0], y = b - v[0];
        return x / y ? x / y > 0 : x.sz() < y.sz();
    });
    for (auto &p : v) {
        while (st.size() > 1 && ccw(st[st.size() - 2], st.back(), p) <= 0)
            st.pop_back();
        st.emplace_back(p);
    }
    return st;
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
