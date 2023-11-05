#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define vec std::vector

vec<int> arr;
const int kLog = 25;

int Merge(int x1, int x2, int y1, int y2) {
  if (x1 == y1) {
    if (arr[x2] <= arr[y2]) {
      return x2;
    }
    return y2;
  }

  if (x2 == y2) {
    if (arr[x1] <= arr[y1]) {
      return y1;
    }
    return x1;
  }

  if (x2 == y1) {
    return x2;
  }
  if (x1 == y2) {
    return y2;
  }

  if (arr[y1] <= arr[x1] && arr[x1] <= arr[y2]) {
    return x1;
  }
  if (arr[x1] <= arr[y1] && arr[y1] <= arr[x2]) {
    return y1;
  }
  if (arr[x2] <= arr[y1]) {
    return x2;
  }
  if (arr[y2] <= arr[x1]) {
    return y2;
  }
  return -1;
}

void Solve() {
  int nn;
  int query;
  std::cin >> nn >> query;
  arr.resize(nn);
  for (int ii = 0; ii < nn; ii++) {
    std::cin >> arr[ii];
  }

  int log = kLog;
  vec<vec<int>> sparse(log, vec<int>(nn));
  vec<vec<int>> sparse2(log, vec<int>(nn, 0));
  for (int ii = 0; ii < nn; ii++) {
    sparse[0][ii] = ii;
    if (ii == nn - 1) {
      break;
    }
    if (arr[ii] < arr[ii + 1]) {
      sparse[1][ii] = ii;
      sparse2[1][ii] = ii + 1;
    } else {
      sparse[1][ii] = ii + 1;
      sparse2[1][ii] = ii;
    }
  }

  for (int kk = 2; kk < log; kk++) {
    for (int ii = 0; ii + (1 << (kk - 1)) < nn; ii++) {
      if (arr[sparse[kk - 1][ii]] < arr[sparse[kk - 1][ii + (1 << (kk - 1))]]) {
        sparse[kk][ii] = sparse[kk - 1][ii];
      } else {
        sparse[kk][ii] = sparse[kk - 1][ii + (1 << (kk - 1))];
      }
      int x1 = sparse[kk - 1][ii];
      int x2 = sparse2[kk - 1][ii];
      int y1 = sparse[kk - 1][ii + (1 << (kk - 1))];
      int y2 = sparse2[kk - 1][ii + (1 << (kk - 1))];
      sparse2[kk][ii] = Merge(x1, x2, y1, y2);
    }
  }

  vec<int> pw(nn + 2);
  pw[0] = pw[1] = 0;
  for (int ii = 2; ii <= nn + 1; ii++) {
    pw[ii] = pw[ii >> 1] + 1;
  }

  while (bool(query--)) {
    int xx;
    int yy;
    std::cin >> xx >> yy;
    int sz = yy - xx + 1;
    int x1 = sparse[pw[sz]][xx - 1];
    int x2 = sparse2[pw[sz]][xx - 1];
    int y1 = sparse[pw[sz]][yy - (1 << pw[sz])];
    int y2 = sparse2[pw[sz]][yy - (1 << pw[sz])];
    std::cout << arr[Merge(x1, x2, y1, y2)] << '\n';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}