#include <iostream>
// #include "string.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

const long long kMod = 1'073'741'824;

void Solve() {
  int nn;
  int kk;
  std::cin >> nn >> kk;
  long long now;
  int xx;
  int yy;
  std::cin >> now >> xx >> yy;
  std::multiset<int> set;
  for (int ind = 0; ind < nn; ind++) {
    now = (xx * now + yy) % kMod;
    set.insert(int(-now));
    if (int(set.size()) > kk) {
      set.erase(set.begin());
    }
  }

  std::vector<int> res(kk);
  int* ind = &res[kk - 1];
  for (const auto& el : set) {
    *ind = -el;
    ind--;
  }
  for (auto& el : res) {
    std::cout << el << ' ';
  }
}

int main() { Solve(); }