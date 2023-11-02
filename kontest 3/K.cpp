#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

const int kINF = 1'000'000'001;

struct Node {
  int left;
  int right;
  int cnt;
  int mn;
  int push = 0;
  Node operator+(const Node& other) const {
    if (mn < other.mn) {
      return {left, other.right, cnt, mn};
    }
    if (mn > other.mn) {
      return {left, other.right, other.cnt, other.mn};
    }
    return {left, other.right, cnt + other.cnt, mn};
  }
};

struct SegTree {
  std::vector<Node> tree;

  SegTree(int sz, std::vector<int>& coords) {
    tree.resize(4 * sz + 2);
    Build(1, 0, sz - 1, coords);
  }

  void Push(int ver) {
    if (tree[ver].push == 0) {
      return;
    }
    tree[2 * ver].push += tree[ver].push;
    tree[2 * ver + 1].push += tree[ver].push;
    tree[2 * ver].mn += tree[ver].push;
    tree[2 * ver + 1].mn += tree[ver].push;
    tree[ver].push = 0;
  }

  void Build(int ver, int left, int right, std::vector<int>& coords) {
    if (right - left == 1) {
      tree[ver] = {left, right, coords[right] - coords[left], 0};
      return;
    }
    int mid = (left + right) / 2;
    Build(ver * 2, left, mid, coords);
    Build(ver * 2 + 1, mid, right, coords);
    tree[ver] = tree[ver * 2] + tree[ver * 2 + 1];
  }

  void Update(int ver, int left, int right, int val) {
    if (tree[ver].left >= right || tree[ver].right <= left) {
      return;
    }
    if (tree[ver].right <= right && tree[ver].left >= left) {
      tree[ver].mn += val;
      tree[ver].push += val;
      return;
    }
    Push(ver);
    Update(ver * 2, left, right, val);
    Update(ver * 2 + 1, left, right, val);
    tree[ver] = tree[ver * 2] + tree[ver * 2 + 1];
  }

  Node Get(int ver, int left, int right) {
    if (tree[ver].right <= left || tree[ver].left >= right) {
      return {0, 0, 0, 0};
    }
    if (tree[ver].left >= left && tree[ver].right <= right) {
      return tree[ver];
    }
    return Get(ver * 2, left, right) + Get(ver * 2 + 1, left, right);
  }
};

void Solve() {
  std::map<int, int> mp;
  int nn;
  int x1;
  int x2;
  int y1;
  int y2;
  std::cin >> nn;
  std::vector<std::vector<int>> arr(2 * nn + 1);
  std::vector<int> coords(2 * nn + 2);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    arr[2 * ii] = {x1, y1, y2, 1};
    arr[2 * ii + 1] = {x2, y1, y2, -1};
    coords[2 * ii] = y1;
    coords[2 * ii + 1] = y2;
  }
  arr[2 * nn] = {-kINF, -kINF, 0, 0};
  coords[2 * nn] = -kINF;
  coords[2 * nn + 1] = kINF;
  std::sort(coords.begin(), coords.end());
  std::sort(arr.begin(), arr.end());
  int kk = int(unique(coords.begin(), coords.end()) - coords.begin());
  coords.resize(kk);
  for (int ii = 0; ii < kk; ii++) {
    mp[coords[ii]] = ii;
  }
  long long cnt = 0;
  SegTree tree(kk, coords);
  for (int ii = 1; ii <= 2 * nn; ii++) {
    Node now = tree.Get(1, 0, kk);
    cnt += (long long)(arr[ii][0] - arr[ii - 1][0]) *
           (coords[kk - 1] - coords[0] - now.cnt);
    tree.Update(1, mp[arr[ii][1]], mp[arr[ii][2]], arr[ii][3]);
  }
  std::cout << cnt;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
  return 0;
}