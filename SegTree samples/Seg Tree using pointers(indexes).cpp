#include <algorithm>
#include <iostream>
#include <vector>

#define vec std::vector

// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352349/problem/A
// https://sirius2021.contest.codeforces.com/group/Xbf70KMJGz/contest/352532/problem/A

struct Node {
  long long sum;
  long long max;
  long long push;
  int left;
  int right;

  Node() : sum(0), push(0), max(0), left(-1), right(-1){}
  Node(int val, int v) : sum(val), push(0), max(val), left(-1), right(-1) {}

  Node operator+(Node& other) {
    Node res;
    res.sum = sum + other.sum;
    res.max = std::max(max, other.max);
    return res;
  }
};

struct SegTree {
  // 0-indexed
  // a[l...r] = [l, r)
  int sz;
  vec<Node> tree;

  SegTree(int n, vec<int>& arr) {
    sz = n;
    tree.push_back(Node());
    build(0, 0, sz, arr);
  }

  void build(int v, int l, int r, vec<int>& arr) {
    if (r - l == 1) {
      tree[v] = Node(arr[l], v);
      return;
    }
    int m = (l + r) >> 1; // (l + r) >> 1 == (l + r) / 2
    if (tree[v].left == -1) {
      tree.push_back(Node());
      tree[v].left = (int)tree.size() - 1;
    }
    build(tree[v].left, l, m, arr);
    if (tree[v].right == -1) {
      tree.push_back(Node());
      tree[v].right = (int)tree.size() - 1;
    }
    build(tree[v].right, m, r, arr);
    tree[v].sum = tree[tree[v].left].sum + tree[tree[v].right].sum;
    tree[v].max = std::max(tree[tree[v].left].max, tree[tree[v].right].max);
  }

  void push(int v, int l, int r) {
    if (tree[v].push == 0) return; // noting to push
    tree[v].sum += (r - l) * tree[v].push;
    tree[v].max += tree[v].push;
    if (r - l != 1) {
      tree[tree[v].left].push += tree[v].push;
      tree[tree[v].right].push += tree[v].push;
    }
    tree[v].push = 0;
  }

  void update(int ind, int val) { // set a[ind] = x;
    update_in_point(0, 0, sz, ind, val);
  }

  void update_in_point(int v, int l, int r, int ind, int val) {
    push(v, l, r);
    if (r - l == 1) {
      tree[v] = Node(val, v);
      return;
    }
    int m = (l + r) >> 1;
    if (ind < m) update_in_point(tree[v].left, l, m, ind, val);
    else update_in_point(tree[v].right, m, r, ind, val);
    tree[v].sum = tree[tree[v].left].sum + tree[tree[v].right].sum;
    tree[v].max = std::max(tree[tree[v].left].max, tree[tree[v].right].max);
  }

  void update(int l, int r, int val) { // a[l...r] += val;
    update_segment(0, 0, sz, l, r, val);
  }

  void update_segment(int v, int l, int r, int tl, int tr, int val) {
    push(v, l, r);
    if (l >= tr || r <= tl) return;
    if (tl <= l && r <= tr) {
      tree[v].push += val;
      push(v, l, r);
      return;
    }
    int m = (l + r) >> 1;
    update_segment(tree[v].left, l, m, tl, tr, val);
    update_segment(tree[v].right, m, r, tl, tr, val);
    tree[v].sum = tree[tree[v].left].sum + tree[tree[v].right].sum;
    tree[v].max = std::max(tree[tree[v].left].max, tree[tree[v].right].max);
  }

  Node get(int l, int r) {
    return get(0, 0, sz, l, r);
  }

  Node get(int v, int l, int r, int tl, int tr) {
    push(v, l, r);
    if (tl >= r || tr <= l) return Node(0, -1);
    if (tl <= l && r <= tr) return tree[v];
    int m = (l + r) >> 1;
    Node left = get(tree[v].left, l, m, tl, tr);
    Node right = get(tree[v].right, m, r, tl, tr);
    return left + right;
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
      std::cout << tree.get(l - 1, r).sum << '\n';
    } else if (com == "a") { // add segment
      int l, r, val;
      std::cin >> l >> r >> val;
      tree.update(l - 1, r, val);
    } else if (com == "m") { // get max
      int l, r;
      std::cin >> l >> r;
      std::cout << tree.get(l - 1, r).max << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}