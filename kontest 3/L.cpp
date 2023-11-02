#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

std::vector<int> left = {-1};
std::vector<int> right = {-1};
std::vector<int> arr;
std::vector<int> value = {-1};

void Build(int ver, int tl, int tr) {
  left.push_back(-1);
  right.push_back(-1);
  value.push_back(-1);
  if (tr - tl == 1) {
    value.back() = arr[tl];
    return;
  }
  int tm = (tl + tr) >> 1;
  int indl = left.size();
  Build(indl, tl, tm);
  int indr = right.size();
  Build(indr, tm, tr);
  left[ver] = indl;
  right[ver] = indr;
}

int Get(int var, int tl, int tr, int ind) {
  if (tr - tl == 1) {
    return value[var];
  }
  int tm = (tl + tr) >> 1;
  if (ind < tm) {
    return Get(left[var], tl, tm, ind);
  }
  return Get(right[var], tm, tr, ind);
}

void Add(int var, int tl, int tr, int pos, int val) {
  if (tr - tl == 1) {
    return;
  }
  int tm = (tl + tr) >> 1;
  if (pos < tm) {
    left.back() = left.size();
    right.back() = right[var];

    value.push_back(val);
    right.push_back(-1);
    left.push_back(-1);
    Add(left[var], tl, tm, pos, val);
  } else {
    left.back() = left[var];
    right.back() = right.size();

    value.push_back(val);
    right.push_back(-1);
    left.push_back(-1);
    Add(right[var], tm, tr, pos, val);
  }
}

void Solve() {
  int nn;
  std::cin >> nn;
  arr.resize(nn);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
  }
  Build(1, 0, nn);

  std::vector<int> root_id = {-1, 1};
  int mm;
  int xx;
  int yy;
  int zz;
  std::string com;
  std::cin >> mm;
  while (bool(mm--)) {
    std::cin >> com;
    if (com == "create") {
      std::cin >> xx >> yy >> zz;
      root_id.push_back(int(left.size()));
      left.push_back(-1);
      right.push_back(-1);
      value.push_back(zz);
      Add(root_id[xx], 0, nn, yy - 1, zz);
    } else {
      std::cin >> xx >> yy;
      std::cout << Get(root_id[xx], 0, nn, yy - 1) << '\n';
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
  return 0;
}