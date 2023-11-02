#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<int> sum;

  SegTree(int n) {
    sz = n;
    sum.resize(4 * n + 2, 0);
    // Build(1, 0, n, arr);
  }

  void Update(int ver, int left, int right, int ind, int val) {
    if (right - left == 1) {
      sum[ver] += val;
      return;
    }
    int mid = (left + right) >> 1;
    if (ind < mid) {
      Update(ver * 2, left, mid, ind, val);
    } else {
      Update(ver * 2 + 1, mid, right, ind, val);
    }
    sum[ver] = sum[ver * 2] + sum[ver * 2 + 1];
  }

  int Get(int ver, int left, int right, int tl, int tr) {
    if (right <= tl || tr <= left) {
      return 0;
    }
    if (tl <= left && right <= tr) {
      return sum[ver];
    }
    int mid = (left + right) >> 1;
    int ll = Get(ver * 2, left, mid, tl, tr);
    int rr = Get(ver * 2 + 1, mid, right, tl, tr);
    return ll + rr;
  }
};

bool Cmp(vec<int>& aa, vec<int>& bb) {
  if (aa[0] != bb[0]) {
    return aa[0] > bb[0];
  }
  return aa[1] < bb[1];
}

void Solve() {
  int nn;
  std::cin >> nn;
  vec<vec<int>> time(nn, vec<int>(3));
  std::map<int, int> ind;
  std::map<std::pair<int, int>, long long> rep;
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> time[ii][0] >> time[ii][1];
    ind[time[ii][0]] = 0;
    ind[time[ii][1]] = 0;
    time[ii][2] = ii;
    rep[{time[ii][0], time[ii][1]}]++;
  }
  int sz = 0;
  for (auto& ii : ind) {
    ii.second = sz;
    sz++;
  }
  SegTree tree(sz);
  std::sort(time.begin(), time.end(), Cmp);
  long long ans = 0;

  for (int ii = 0; ii < nn; ii++) {
    ans += tree.Get(1, 0, sz, ind[time[ii][0]], ind[time[ii][1]] + 1);
    tree.Update(1, 0, sz, ind[time[ii][1]], 1);
  }
  for (auto& ii : rep) {
    ans -= ii.second * (ii.second - 1) / 2;
  }
  std::cout << ans << '\n';
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  // std::cout << std::fixed << std::setprecision(kSZ);
  Solve();
}