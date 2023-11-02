#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<int> sum;

  SegTree(int n, vec<int>& arr) {
    sz = n;
    sum.resize(4 * sz + 2, 0);
    Build(1, 0, n, arr);
  }

  void Build(int ver, int left, int right, vec<int>& arr) {
    if (right - left == 1) {
      if (bool(left & 1)) {
        sum[ver] = -arr[left];
      } else {
        sum[ver] = arr[left];
      }
      return;
    }
    int mid = (left + right) / 2;
    Build(ver * 2, left, mid, arr);
    Build(ver * 2 + 1, mid, right, arr);
    sum[ver] = sum[ver * 2] + sum[ver * 2 + 1];
  }

  void Update(int ver, int left, int right, int ind, int val) {
    if (right - left == 1) {
      if (bool(left & 1)) {
        sum[ver] = -val;
      } else {
        sum[ver] = val;
      }
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
    return Get(ver * 2, left, mid, tl, tr) +
           Get(ver * 2 + 1, mid, right, tl, tr);
  }
};

void Solve() {
  int nn;
  std::cin >> nn;
  vec<int> arr(nn);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
  }
  SegTree tree(nn, arr);
  int query;
  std::cin >> query;
  while (bool(query--)) {
    int xx;
    int yy;
    int zz;
    std::cin >> xx >> yy >> zz;
    if (xx == 0) {
      tree.Update(1, 0, nn, yy - 1, zz);
    } else {
      int val = tree.Get(1, 0, nn, yy - 1, zz);
      if (bool((yy - 1) & 1)) {
        val = -val;
      }
      std::cout << val << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  // std::cout << std::fixed << std::setprecision(kSZ);
  Solve();
}