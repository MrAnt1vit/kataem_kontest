#include <iostream>
// #include "string.h"
#include <algorithm>
#include <vector>

std::vector<int> ans;
std::vector<std::pair<int, int>> array;

struct SegTree {
  int sz;
  std::vector<int> sum;

  explicit SegTree(int nn) {
    sz = nn;
    sum.resize(4 * nn + 2, 0);
  }

  void Update(int ver, int ind, int left, int right) {
    if (right - left == 1) {
      sum[ver]++;
      return;
    }
    int mid = (left + right) >> 1;
    if (ind < mid) {
      Update(ver * 2, ind, left, mid);
    } else {
      Update(ver * 2 + 1, ind, mid, right);
    }
    sum[ver]++;
  }

  void Update(int ind) { Update(1, ind, 0, sz); }

  int Get(int ver, int left, int right, int tl, int tr) {
    if (tl >= right || tr <= left) {
      return 0;
    }
    if (left >= tl && tr >= right) {
      return sum[ver];
    }
    int mid = (left + right) >> 1;
    return Get(ver * 2, left, mid, tl, tr) +
           Get(ver * 2 + 1, mid, right, tl, tr);
  }

  int Get(int tl, int tr) { return Get(1, 0, sz, tl, tr); }
};

void Solve() {
  int nn;
  std::cin >> nn;
  SegTree tree(nn);
  array.resize(nn);
  ans.resize(nn, 0);
  for (int index = 0; index < nn; ++index) {
    std::cin >> array[index].first;
    array[index].second = index;
  }
  std::sort(array.begin(), array.end());

  for (int ind = 0; ind < nn; ind++) {
    ans[array[ind].second] = tree.Get(array[ind].second + 1, nn);
    tree.Update(array[ind].second);
  }

  for (int ind = 0; ind < nn; ind++) {
    std::cout << ans[ind] << ' ';
  }
}

int main() { Solve(); }