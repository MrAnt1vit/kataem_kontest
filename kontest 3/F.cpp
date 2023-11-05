#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct MST {
  int sz;
  vec<vec<int>> vals;
  vec<int> left;
  vec<int> right;

  MST(int nn, vec<int>& arr) {
    sz = nn;
    vals.resize(4 * sz + 2);
    left.resize(4 * sz + 2);
    right.resize(4 * sz + 2);
    Build(1, 0, nn, arr);
  }

  void Build(int ver, int tl, int tr, vec<int>& arr) {
    if (tr - tl == 1) {
      vals[ver] = {arr[tl]};
      left[ver] = tl;
      right[ver] = tr;
      return;
    }
    int mid = (tl + tr) >> 1;
    Build(ver * 2, tl, mid, arr);
    Build(ver * 2 + 1, mid, tr, arr);
    vals[ver].resize(tr - tl);
    int tlind = 0;
    int trind = 0;
    vec<int> larr = vals[ver * 2];
    vec<int> rarr = vals[ver * 2 + 1];
    while (tlind < mid - tl && trind < tr - mid) {
      if (larr[tlind] <= rarr[trind]) {
        vals[ver][tlind + trind] = larr[tlind];
        tlind++;
      } else {
        vals[ver][tlind + trind] = rarr[trind];
        trind++;
      }
    }
    while (tlind < mid - tl) {
      vals[ver][tlind + trind] = larr[tlind];
      tlind++;
    }
    while (trind < tr - mid) {
      vals[ver][tlind + trind] = rarr[trind];
      trind++;
    }
    left[ver] = tl;
    right[ver] = tr;
  }

  int Get(int ver, int tl, int tr, int val) {
    if (left[ver] >= tr || right[ver] <= tl) {
      return 0;
    }
    if (tl <= left[ver] && right[ver] <= tr) {
      return int(std::upper_bound(vals[ver].begin(), vals[ver].end(), val) -
                 vals[ver].begin());
    }
    int ansl = Get(ver * 2, tl, tr, val);
    int ansr = Get(ver * 2 + 1, tl, tr, val);
    return ansl + ansr;
  }
};

void Solve() {
  int nn;
  int query;
  std::cin >> nn >> query;
  vec<int> arr(nn);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
  }
  MST tree(nn, arr);

  int xx;
  int yy;
  int kk;
  int ll;
  while (bool(query--)) {
    std::cin >> xx >> yy >> kk >> ll;
    int get1 = tree.Get(1, xx - 1, yy, kk - 1);
    int get2 = tree.Get(1, xx - 1, yy, ll);
    std::cout << get2 - get1 << '\n';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}