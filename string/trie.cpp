struct Trie {
    ll ed = 0;
    Trie *ch[26];
    Trie() { std::fill(ch, ch + 26, nullptr); }
    ~Trie() {
        for (ll i = 0; i < 26; i++)
            if (ch[i]) delete ch[i];
    }
    void insert(const char *s) {
        if (*s == 0) {
            ed = 1;
            return;
        }
        ll idx = *s - 'a';
        if (!ch[idx]) ch[idx] = new Trie();
        ch[idx]->insert(s + 1);
    }
};

// how to insert string s to trie t
// t->insert(s.c_str());
