#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define vec std::vector

struct Section {
  long long left = -1;
  long long right = -1;
  // left <= right -> a[l...r]
  // right < left -> a[0...r] + a[l...n-1]

  bool Add(long long xx, long long yy) {
    if (left == -1 && right == -1) {
      left = xx;
      right = yy;
      return true;
    }

    if (xx <= yy) {
      std::swap(xx, left);
      std::swap(yy, right);
    }
    if (left <= right) {
      if (xx <= yy) {
        left = std::max(left, xx);
        right = std::min(right, yy);
      } else if (yy >= left) {
        right = std::min(right, yy);
      } else if (xx <= right) {
        left = std::max(left, xx);
      } else {
        return false;
      }
      return (left <= right);
    }

    right = std::min(right, yy);
    left = std::max(left, xx);
    return true;
  }
};

void Solve() {
  long long nn;
  std::cin >> nn;

  vec<long long> arr(2 * nn);
  long long sum = 0;
  for (long long ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
    arr[ii + nn] = arr[ii];
    sum += arr[ii];
  }

  vec<vec<long long>> bb(nn);
  vec<long long> pref(2 * nn + 1);
  pref[0] = 0;
  for (long long ii = 1; ii <= nn * 2; ii++) {
    pref[ii] = pref[ii - 1] + arr[ii - 1];
  }
  for (long long start = 0; start < nn; start++) {
    if (start + nn / 2 <= nn) {
      bb[start] = {pref[start + nn / 2] - pref[start], start,
                   start + nn / 2 - 1};
    } else {
      bb[start] = {pref[start + nn / 2] - pref[start], start,
                   start + nn / 2 - 1 - nn};
    }
  }

  std::sort(bb.rbegin(), bb.rend());
  Section inter;
  for (long long ii = 0; ii < nn; ii++) {
    if (!inter.Add(bb[ii][1], bb[ii][2])) {
      std::cout << sum - bb[ii][0] << ' ' << bb[ii][0];
      return;
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}