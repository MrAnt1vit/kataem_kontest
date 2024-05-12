#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> up;
std::vector<int> h;
const int cLog = 30;

void Dfs(int v, int now) {
  h[v] = now;
  for (auto& u : graph[v]) {
    if (h[u] == -1) {
      Dfs(u, now + 1);
      up[0][u] = v;
    }
  }
}

int Up(int v, int height) {
  for (int i = cLog - 1; i >= 0; i--) {
    if (h[v] - (1 << i) >= height) {
      v = up[i][v];
    }
  }
  return v;
}

int Lca(int u, int v) {
  if (h[u] > h[v]) {
    u = Up(u, h[v]);
  }
  if (h[u] < h[v]) {
    v = Up(v, h[u]);
  }
  if (u == v) {
    return u;
  }
  for (int i = cLog - 1; i >= 0; i--) {
    if (up[i][u] != up[i][v]) {
      u = up[i][u];
      v = up[i][v];
    }
  }
  return up[0][u];
}

void Solve() {
  int n;
  std::cin >> n;
  graph.resize(n);
  up.resize(cLog, std::vector<int>(n, -1));
  int x;
  int y;
  for (int i = 0; i < n - 1; i++) {
    std::cin >> x >> y;
    x--;
    y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  h.resize(n, -1);
  Dfs(0, 0);
  for (int i = 1; i < cLog; i++) {
    for (int j = 0; j < n; j++) {
      if (up[i - 1][j] != -1) {
        up[i][j] = up[i - 1][up[i - 1][j]];
      }
    }
  }

  int m;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    x--;
    y--;
    int lca = Lca(x, y);
    std::cout << h[y] + h[x] - 2 * h[lca] << '\n';
  }
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