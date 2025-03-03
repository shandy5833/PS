// long double 써서 tle 나면 double로
using ld = long double;
typedef std::complex<ld> base;
void fft(std::vector<base> &a, bool invert) {
    ll n = a.size();
    std::vector<base> roots(n / 2);
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (ll i = 2; i <= n; i <<= 1) {
        std::vector<base> w(i / 2);
        for (ll j = 0; j < i / 2; ++j) {
            ld th = 2 * std::acos(-1.L) * j / i * (invert ? -1 : 1);
            w[j] = base(std::cos(th), std::sin(th));
        }
        for (ll j = 0; j < n; j += i) {
            for (ll k = 0; k < i / 2; ++k) {
                base u = a[j + k], v = a[j + k + i / 2] * w[k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
        }
    }
    if (invert)
        for (ll i = 0; i < n; i++) a[i] /= n;
}
void multiply(const std::vector<ll> &a, const std::vector<ll> &b,
              std::vector<ll> &res) {
    std::vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < std::max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    for (ll i = 0; i < n; i++)
        res[i] = ll(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}
