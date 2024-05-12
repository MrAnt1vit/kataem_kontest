#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int len, l, r, comp;

  bool operator<(const Edge& other) const { return len < other.len; }
};

std::vector<int> predx, szx;

int Get(int v) {
  if (predx[v] == v) {
    return v;
  }
  return predx[v] = Get(predx[v]);
}

void Uni(int a, int b) {
  a = Get(a);
  b = Get(b);
  if (szx[b] > szx[a]) {
    std::swap(a, b);
  }
  if (a != b) {
    predx[b] = a;
    szx[a] += szx[b];
  }
}

void Solve() {
  int nx;
  int mx;
  std::cin >> nx >> mx;
  std::vector<Edge> edges(mx);
  for (int i = 0; i < mx; i++) {
    int x;
    int y;
    int c;
    std::cin >> x >> y >> c;
    x--;
    y--;
    edges[i] = {c, x, y, 1};
  }

  predx.resize(nx);
  szx.resize(nx, 1);
  for (int i = 0; i < nx; i++) {
    predx[i] = i;
  }
  std::sort(edges.begin(), edges.end());

  int ans = 0;
  for (auto& now : edges) {
    int len = now.len;
    int x = now.l;
    int y = now.r;
    if (Get(x) == Get(y)) {
      continue;
    }
    ans += len;
    Uni(x, y);
  }
  std::cout << ans;
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int t = 1;
  while (t-- != 0) {
    Solve();
  }
  return 0;
}