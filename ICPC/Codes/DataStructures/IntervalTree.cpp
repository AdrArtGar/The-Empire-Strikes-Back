struct Interval {
  lli l, r, i;
};

struct ITree {
  ITree *ls, *rs;
  vector<Interval> cur;
  lli m;

  ITree(vector<Interval> &vec, lli l = LLONG_MAX, lli r = LLONG_MIN) : ls(0), rs(0) {
    if (l > r) { // not sorted yet
      sort(all(vec), [&](Interval a, Interval b) {
        return a.l < b.l;
      });
      for (auto it : vec) 
        l = min(l, it.l), r = max(r, it.r);
    }
    m = (l + r) >> 1;
    vector<Interval> lo, hi;
    for (auto it : vec) 
      (it.r < m ? lo : m < it.l ? hi : cur).pb(it);
    if (!lo.empty())
      ls = new ITree(lo, l, m);
    if (!hi.empty())
      rs = new ITree(hi, m + 1, r);
  }  

  template <class F>
  void near(lli l, lli r, F f) {
    if (!cur.empty() && !(r < cur.front().l)) {
      for (auto &it : cur)
        f(it);
    }
    if (ls && l <= m)
      ls->near(l, r, f);
    if (rs && m < r)
      rs->near(l, r, f);
  }

  template <class F>
  void overlapping(lli l, lli r, F f) {
    near(l, r, [&](Interval it) {
      if (l <= it.r && it.l <= r)
        f(it);
    });
  }

  template <class F>
  void contained(lli l, lli r, F f) {
    near(l, r, [&](Interval it) {
      if (l <= it.l && it.r <= r)
        f(it);
    });
  }
};