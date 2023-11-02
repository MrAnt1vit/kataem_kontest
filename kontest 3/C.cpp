#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<int> max;

  SegTree(int n, vec<int>& arr) {
    sz = n;
    max.resize(4 * n + 2);
    Build(1, 0, n, arr);
  }

  void Build(int ver, int left, int right, vec<int>& arr) {
    if (right - left == 1) {
      max[ver] = arr[left];
      return;
    }
    int mid = (left + right) / 2;
    Build(ver * 2, left, mid, arr);
    Build(ver * 2 + 1, mid, right, arr);
    max[ver] = std::max(max[ver * 2], max[ver * 2 + 1]);
  }

  void Update(int ver, int left, int right, int ind, int val) {
    if (right - left == 1) {
      max[ver] = val;
      return;
    }
    int mid = (left + right) >> 1;
    if (ind < mid) {
      Update(ver * 2, left, mid, ind, val);
    } else {
      Update(ver * 2 + 1, mid, right, ind, val);
    }
    max[ver] = std::max(max[ver * 2], max[ver * 2 + 1]);
  }

  int Get(int ver, int left, int right, int tl, int val) {
    if (right <= tl || max[ver] < val) {
      return -2;
    }
    if (right - left == 1) {
      return left;
    }
    int mid = (left + right) >> 1;
    int indl = Get(ver * 2, left, mid, tl, val);
    if (indl != -2) {
      return indl;
    }
    return Get(ver * 2 + 1, mid, right, tl, val);
  }
};

void Solve() {
  int nn;
  std::cin >> nn;
  int query;
  std::cin >> query;
  vec<int> arr(nn);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
  }
  SegTree tree(nn, arr);
  while (bool(query--)) {
    int xx;
    int yy;
    int zz;
    std::cin >> xx >> yy >> zz;
    if (xx == 0) {
      tree.Update(1, 0, nn, yy - 1, zz);
      arr[yy - 1] = zz;
    } else {
      int val = tree.Get(1, 0, nn, yy - 1, zz);
      std::cout << val + 1 << '\n';
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