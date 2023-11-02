#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

struct SegTree {
  int sz;
  vec<int> sum;

  SegTree(int n) {
    sz = n;
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

const int kN = 42196;
const int kSZ = 7;

void Solve() {
  int nn;
  std::cin >> nn;
  SegTree tree(kN);
  std::map<int, int> mp;
  while (bool(nn--)) {
    std::string st;
    std::cin >> st;
    if (st == "CHEER") {
      int x;
      std::cin >> x;
      if (mp.find(x) == mp.end()) {
        std::cout << 0 << '\n';
      } else {
        if (mp.size() == 1) {
          std::cout << 1 << '\n';
        } else {
          std::cout << (double)(tree.Get(1, 0, kN, 0, mp[x])) /
                       (double)(mp.size() - 1)
                    << '\n';
        }
      }
    } else {
      int x;
      int y;
      std::cin >> x >> y;
      if (mp.find(x) != mp.end()) {
        tree.Update(1, 0, kN, mp[x], -1);
      }
      mp[x] = y;
      tree.Update(1, 0, kN, mp[x], 1);
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(kSZ);
  Solve();
}