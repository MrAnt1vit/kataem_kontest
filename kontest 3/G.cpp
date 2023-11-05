#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<int> sum;

  SegTree(int nn) {
    sz = nn;
    sum.resize(4 * sz + 2, 0);
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

  long long Get(int ver, int left, int right, int tl, int tr) {
    if (right <= tl || left >= tr) {
      return 0;
    }
    if (tl <= left && right <= tr) {
      return sum[ver];
    }
    int mid = (left + right) >> 1;
    long long lft = Get(ver * 2, left, mid, tl, tr);
    long long rght = Get(ver * 2 + 1, mid, right, tl, tr);
    return lft + rght;
  }
};

struct Rect {
  int x1;
  int y1;
  int x2;
  int y2;

  Rect() : x1(0), y1(0), x2(0), y2(0) {}

  Rect(int xl, int yl, int xm, int ym) {
    x1 = std::min(xl, xm);
    y1 = std::min(yl, ym);
    x2 = std::max(xl, xm);
    y2 = std::max(yl, ym);
    x1--;
    y1--;
  }
};

struct BigSegTree {
  int sz;
  vec<SegTree> sums;

  BigSegTree(int nn) {
    sz = nn;
    sums.resize(4 * sz + 2, SegTree(nn));
  }

  void Update(int ver, int left, int right, int xx, int yy) {
    sums[ver].Update(1, 0, sz, yy, 1);
    if (right - left == 1) {
      return;
    }
    int mid = (left + right) >> 1;
    if (xx < mid) {
      Update(ver * 2, left, mid, xx, yy);
    } else {
      Update(ver * 2 + 1, mid, right, xx, yy);
    }
  }

  long long Get(int ver, int left, int right, Rect need) {
    if (right <= need.x1 || left >= need.x2) {
      return 0;
    }
    if (need.x1 <= left && right <= need.x2) {
      return sums[ver].Get(1, 0, sz, need.y1, need.y2);
    }
    int mid = (left + right) >> 1;
    long long lft = Get(ver * 2, left, mid, need);
    long long rght = Get(ver * 2 + 1, mid, right, need);
    return lft + rght;
  }
};

void Solve() {
  int nn;
  int query;
  std::cin >> nn >> query;
  BigSegTree tree(nn);
  std::string command;
  Rect now;
  int xx;
  int yy;
  while (bool(query--)) {
    std::cin >> command;
    if (command == "ADD") {
      std::cin >> xx >> yy;
      xx--;
      yy--;
      tree.Update(1, 0, nn, xx, yy);
    } else {
      std::cin >> now.x1 >> now.y1 >> now.x2 >> now.y2;
      now = Rect(now.x1, now.y1, now.x2, now.y2);
      std::cout << tree.Get(1, 0, nn, now) << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}