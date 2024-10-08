ll mul(ll x, ll y, ll mod) { return (ll)((__int128)x * y % mod); }

ll ipow(ll x, ll y, ll p) {
    ll ret = 1, piv = x % p;
    while (y) {
        if (y & 1) ret = mul(ret, piv, p);
        piv = mul(piv, piv, p);
        y >>= 1;
    }
    return ret;
}

bool miller_rabin(ll x, ll a) {
    if (x % a == 0) return 0;
    ll d = x - 1;
    while (1) {
        ll tmp = ipow(a, d, x);
        if (d & 1) return (tmp != 1 && tmp != x - 1);
        else if (tmp == x - 1) return 0;
        d >>= 1;
    }
}

bool isprime(ll x) { // long long range
    for (auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (x == i) return 1;
        if (x > 40 && miller_rabin(x, i)) return 0;
    }
    if (x <= 40) return 0;
    return 1;
}

bool isprime(ll x) { // int range
    for (auto &i : {2, 7, 61}) {
        if (x == i) return 1;
        if (miller_rabin(x, i)) return 0;
    }
    return 1;
}
