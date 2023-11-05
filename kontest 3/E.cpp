#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<long long> sum;
  vec<int> real;

  SegTree(int nn, vec<int>& arr) {
    sz = nn;
    sum.resize(4 * sz + 2, 0);
    real.resize(4 * sz + 2, 0);
    Build(1, 0, nn, arr);
  }

  void Build(int ver, int left, int right, vec<int>& arr) {
    if (right - left == 1) {
      real[ver] = arr[left];
      return;
    }
    int mid = (left + right) >> 1;
    Build(ver * 2, left, mid, arr);
    Build(ver * 2 + 1, mid, right, arr);
    real[ver] = real[ver * 2] + real[ver * 2 + 1];
  }

  long long Get(int ver, int left, int right, int tl, int tr) {
    if (left >= tr || right <= tl) {
      return 0;
    }
    if (tl <= left && right <= tr) {
      return sum[ver];
    }
    int mid = (right + left) >> 1;
    long long ansl = Get(ver * 2, left, mid, tl, tr);
    long long ansr = Get(ver * 2 + 1, mid, right, tl, tr);
    return ansl + ansr;
  }

  void Update(int ver, int left, int right, int xx, int val) {
    if (right - left == 1) {
      sum[ver] += real[ver] * val;
      return;
    }
    int mid = (right + left) >> 1;
    if (xx < mid) {
      Update(ver * 2, left, mid, xx, val);
    } else {
      Update(ver * 2 + 1, mid, right, xx, val);
    }
    sum[ver] = sum[ver * 2] + sum[ver * 2 + 1];
  }
};

void Solve() {
  int nn;
  std::cin >> nn;
  vec<std::pair<char, int>> query(nn);
  std::map<int, int> coord;
  vec<int> arr;
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> query[ii].first >> query[ii].second;
    coord[query[ii].second] = 0;
  }
  int cnt = 0;
  for (auto& now : coord) {
    now.second = cnt;
    cnt++;
    arr.push_back(now.first);
  }

  SegTree tree(cnt, arr);

  for (auto& now : query) {
    if (now.first == '+') {
      tree.Update(1, 0, cnt, coord[now.second], 1);
    } else {
      std::cout << tree.Get(1, 0, cnt, 0, coord[now.second] + 1) << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}