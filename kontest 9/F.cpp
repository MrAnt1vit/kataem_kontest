#include <iostream>
#include <set>
#include <vector>

const int cLog = 20;
std::vector<int> pred;
std::vector<int> deep;
std::vector<std::vector<int>> jump;
std::vector<bool> is_real;

int Up(int v, int k) {
  for (int i = cLog; i >= 0; i--) {
    if (deep[v] - (1 << i) >= k) {
      v = jump[i][v];
    }
  }
  return v;
}

int LCA(int v, int u) {
  if (deep[v] > deep[u]) {
    v = Up(v, deep[u]);
  }
  if (deep[u] > deep[v]) {
    u = Up(u, deep[v]);
  }
  if (v == u) {
    return v;
  }
  for (int i = cLog; i >= 0; i--) {
    if (jump[i][v] != jump[i][u]) {
      v = jump[i][v];
      u = jump[i][u];
    }
  }
  return jump[0][v];
}

int Real(int v) {
  if (is_real[v]) {
    return v;
  }
  if (is_real[pred[v]]) {
    return pred[v];
  }
  return pred[v] = Real(pred[v]);
}

void Solve() {
  int q;
  int k = 0;
  std::cin >> q;
  deep.resize(1, 0);
  jump.resize(cLog + 1);
  pred.push_back(0);
  is_real.push_back(true);
  for (int i = 0; i <= cLog; i++) {
    jump[i].push_back(0);
  }
  while (q-- != 0) {
    char st;
    int x;
    int y;
    std::cin >> st;

    if (st == '+') {
      std::cin >> x;
      x--;
      k++;
      deep.push_back(deep[x] + 1);
      jump[0].push_back(x);
      is_real.push_back(true);
      pred.push_back(x);
      for (int i = 1; i <= cLog; i++) {
        jump[i].push_back(jump[i - 1][jump[i - 1][k]]);
      }
    } else if (st == '?') {
      std::cin >> x >> y;
      x--;
      y--;
      std::cout << Real(LCA(x, y)) + 1 << '\n';
    } else {
      std::cin >> x;
      x--;
      is_real[x] = false;
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