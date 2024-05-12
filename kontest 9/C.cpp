#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int len, l, r;

  bool operator<(const Edge& other) const { return len < other.len; }
};

std::vector<int> predx, szx, cost;
int ans = 0;

int Get(int v) {
  if (predx[v] == v) {
    return v;
  }
  return predx[v] = Get(predx[v]);
}

void Uni(int a, int b, int sz) {
  a = Get(a);
  b = Get(b);
  if (szx[b] > szx[a]) {
    std::swap(a, b);
  }

  if (a != b && sz - std::max(cost[a], cost[b]) < 0) {
    predx[b] = a;
    szx[a] += szx[b];
    ans = ans + sz - std::max(cost[a], cost[b]);
    cost[a] = std::min(cost[b], cost[a]);
  }
}

void Solve() {
  int nx;
  int len;
  std::cin >> nx;
  std::vector<Edge> edges;
  cost.resize(nx);
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < nx; j++) {
      std::cin >> len;
      if (i <= j) {
        continue;
      }
      edges.push_back({len, i, j});
    }
  }
  for (int i = 0; i < nx; i++) {
    std::cin >> cost[i];
    ans += cost[i];
  }

  predx.resize(nx);
  szx.resize(nx, 1);
  for (int i = 0; i < nx; i++) {
    predx[i] = i;
  }
  std::sort(edges.begin(), edges.end());

  for (auto& now : edges) {
    int sz = now.len;
    int x = now.l;
    int y = now.r;
    x = Get(x);
    y = Get(y);
    if (x == y) {
      continue;
    }
    Uni(x, y, sz);
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