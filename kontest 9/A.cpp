#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> pred;
std::vector<int> size;

int Get(int v) {
  if (pred[v] == v) {
    return v;
  }
  return pred[v] = Get(pred[v]);
}

void Unite(int v, int u) {
  v = Get(v);
  u = Get(u);
  if (v == u) {
    return;
  }
  if (size[u] > size[v]) {
    std::swap(u, v);
  }
  pred[v] = u;
  size[u] += size[v];
}

bool Check(int v, int u) {
  v = Get(v);
  u = Get(u);
  return v == u;
}

void Solve() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  pred.resize(n);
  size.resize(n, 1);
  for (int i = 0; i < m; i++) {
    int x;
    std::cin >> x >> x;
  }
  for (int i = 0; i < n; i++) {
    pred[i] = i;
  }
  std::vector<std::vector<int>> ask(k, std::vector<int>(3));
  for (int i = 0; i < k; i++) {
    std::string st;
    std::cin >> st;
    int x;
    int y;
    std::cin >> x >> y;
    x--;
    y--;
    if (st == "ask") {
      ask[i] = {0, x, y};
    } else {
      ask[i] = {1, x, y};
    }
  }

  std::vector<bool> ans;
  std::reverse(ask.begin(), ask.end());
  for (int i = 0; i < k; i++) {
    if (ask[i][0] == 0) {
      ans.push_back(Check(ask[i][1], ask[i][2]));
    } else {
      Unite(ask[i][1], ask[i][2]);
    }
  }
  std::reverse(ans.begin(), ans.end());
  for (auto i : ans) {
    if (i) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
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