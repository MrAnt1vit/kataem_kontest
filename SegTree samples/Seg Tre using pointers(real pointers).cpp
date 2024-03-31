#include <algorithm>
#include <iostream>
#include <vector>

#define vec std::vector

// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352349/problem/A
// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352532/problem/A

struct SegTree {
  // 0-indexed
  // a[l...r] = [l, r)
  long long sum = 0;
  long long max = 0;
  long long push = 0;
  SegTree* left = nullptr;
  SegTree* right = nullptr;

  SegTree() {}
  SegTree(int n, vec<int>& a) {
    left = new SegTree();
    right = new SegTree();
    build(0, n, a);
  }

  void build(int l, int r, vec<int>& vals) {
    if (r - l == 1) {
      max = sum = vals[l];
      return;
    }
    left = new SegTree();
    right = new SegTree();
    int m = (l + r) >> 1;
    left->build(l, m, vals);
    right->build(m, r, vals);
    sum = left->sum + right->sum;
    max = std::max(left->max, right->max);
  }

  void push_ver(int l, int r) {
    if (push == 0) return; // noting to push
    sum += (r - l) * push;
    max += push;
    if (r - l != 1) {
      left->push += push;
      right->push += push;
    }
    push = 0;
  }

  void update_in_point(int l, int r, int ind, int val) { // set a[ind] = x;
    push_ver(l, r);
    if (r - l == 1) {
      sum = max = val;
      return;
    }
    int m = (l + r) >> 1;
    if (ind < m) left->update_in_point(l, m, ind, val);
    else right->update_in_point(m, r, ind, val);
    sum = left->sum + right->sum;
    max = std::max(left->max, right->max);
  }

  void update_segment(int l, int r, int tl, int tr, int val) { // a[l...r] += val;
    push_ver(l, r);
    if (l >= tr || r <= tl) return;
    if (tl <= l && r <= tr) {
      push += val;
      push_ver(l, r);
      return;
    }
    int m = (l + r) >> 1;
    left->update_segment(l, m, tl, tr, val);
    right->update_segment(m, r, tl, tr, val);
    sum = left->sum + right->sum;
    max = std::max(left->max, right->max);
  }

  long long get_sum(int l, int r, int tl, int tr) {
    push_ver(l, r);
    if (tl >= r || tr <= l) return 0;
    if (tl <= l && r <= tr) return sum;
    int m = (l + r) >> 1;
    long long lans = left->get_sum(l, m, tl, tr);
    long long rans = right->get_sum(m, r, tl, tr);
    return lans + rans;
  }

  long long get_max(int l, int r, int tl, int tr) {
    push_ver(l, r);
    if (tl >= r || tr <= l) return 0;
    if (tl <= l && r <= tr) return max;
    int m = (l + r) >> 1;
    long long lans = left->get_max(l, m, tl, tr);
    long long rans = right->get_max(m, r, tl, tr);
    return std::max(lans, rans);
  }
};

void Solve() {
  int n, m;
  std::cin >> n;
  std::vector<int> a(n, 0); // clear for 1st task
  for (int i = 0; i < n; i++) std::cin >> a[i];
  SegTree tree(n, a);
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::string com;
    std::cin >> com;
    if (com == "A") { // set point
      int ind, val;
      std::cin >> ind >> val;
      tree.update_in_point(0, n, ind - 1, val);
    } else if (com == "Q") { // get sum
      int l, r;
      std::cin >> l >> r;
      std::cout << tree.get_sum(0, n, l - 1, r) << '\n';
    } else if (com == "a") { // add segment
      int l, r, val;
      std::cin >> l >> r >> val;
      tree.update_segment(0, n, l - 1, r, val);
    } else if (com == "m") { // get max
      int l, r;
      std::cin >> l >> r;
      std::cout << tree.get_max(0, n, l - 1, r) << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}