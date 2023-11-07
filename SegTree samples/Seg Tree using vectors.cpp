#include <algorithm>
#include <iostream>
#include <vector>

#define vec std::vector

// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352349/problem/A
// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352532/problem/A

struct SegTree {
  // 0-indexed
  // a[l...r] = [l, r)
  int sz;
  vec<long long> sum;
  vec<long long> max;
  vec<long long> push;

  SegTree(int n, vec<int>& arr) {
    sz = n;
    sum.resize(4 * sz + 2);
    max.resize(4 * sz + 2);
    push.resize(4 * sz + 2, 0);
    build(1, 0, sz, arr);
  }

  void build(int v, int l, int r, vec<int>& arr) {
    if (r - l == 1) {
      sum[v] = max[v] = arr[l];
      return;
    }
    int m = (l + r) >> 1; // (l + r) >> 1 == (l + r) / 2
    build(v * 2, l, m, arr);
    build(v * 2 + 1, m, r, arr);
    sum[v] = sum[v * 2] + sum[v * 2 + 1];
    max[v] = std::max(max[v * 2], max[v * 2 + 1]);
  }

  void Push(int v, int l, int r) {
    if (push[v] == 0) return; // noting to push
    sum[v] += (r - l) * push[v];
    max[v] += push[v];
    if (r - l != 1) {
      push[v * 2] += push[v];
      push[v * 2 + 1] += push[v];
    }
    push[v] = 0;
  }

  void update(int ind, int val) { // set a[ind] = x;
    update_in_point(1, 0, sz, ind, val);
  }

  void update_in_point(int v, int l, int r, int ind, int val) {
    Push(v, l, r);
    if (r - l == 1) {
      sum[v] = max[v] = val;
      return;
    }
    int m = (l + r) >> 1;
    if (ind < m) update_in_point(v * 2, l, m, ind, val);
    else update_in_point(v * 2 + 1, m, r, ind, val);
    sum[v] = sum[v * 2] + sum[v * 2 + 1];
    max[v] = std::max(max[v * 2], max[v * 2 + 1]);
  }

  void update(int l, int r, int val) { // a[l...r] += val;
    update_segment(1, 0, sz, l, r, val);
  }

  void update_segment(int v, int l, int r, int tl, int tr, int val) {
    Push(v, l, r);
    if (l >= tr || r <= tl) return;
    if (tl <= l && r <= tr) {
      push[v] += val;
      Push(v, l, r);
      return;
    }
    int m = (l + r) >> 1;
    update_segment(v * 2, l, m, tl, tr, val);
    update_segment(v * 2 + 1, m, r, tl, tr, val);
    sum[v] = sum[v * 2] + sum[v * 2 + 1];
    max[v] = std::max(max[v * 2], max[v * 2 + 1]);

  }

  long long get_sum(int l, int r) {
    return get_sum(1, 0, sz, l, r);
  }

  long long get_sum(int v, int l, int r, int tl, int tr) {
    Push(v, l, r);
    if (tl >= r || tr <= l) return 0;
    if (tl <= l && r <= tr) return sum[v];
    int m = (l + r) >> 1;
    long long left = get_sum(v * 2, l, m, tl, tr);
    long long right = get_sum(v * 2 + 1, m, r, tl, tr);
    return left + right;
  }

  long long get_max(int l, int r) {
    return get_max(1, 0, sz, l, r);
  }

  long long get_max(int v, int l, int r, int tl, int tr) {
    Push(v, l, r);
    if (tl >= r || tr <= l) return 0;
    if (tl <= l && r <= tr) return max[v];
    int m = (l + r) >> 1;
    long long left = get_max(v * 2, l, m, tl, tr);
    long long right = get_max(v * 2 + 1, m, r, tl, tr);
    return std::max(left, right);
  }
};

void Solve() {
  int n, m;
  std::cin >> n;
  std::vector<int> a(n, 0);
  for (int i = 0; i < n; i++) std::cin >> a[i]; // clear for 1st task
  SegTree tree(n, a);
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::string com;
    std::cin >> com;
    if (com == "A") { // set point
      int ind, val;
      std::cin >> ind >> val;
      tree.update(ind - 1, val);
    } else if (com == "Q") { // get sum
      int l, r;
      std::cin >> l >> r;
      std::cout << tree.get_sum(l - 1, r) << '\n';
    } else if (com == "a") { // add segment
      int l, r, val;
      std::cin >> l >> r >> val;
      tree.update(l - 1, r, val);
    } else if (com == "m") { // get max
      int l, r;
      std::cin >> l >> r;
      std::cout << tree.get_max(l - 1, r) << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}