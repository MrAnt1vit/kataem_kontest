#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> used;
std::vector<std::vector<int>> res;
bool flag = false;

void Dfs(int ver) {
  used[ver] = true;
  res.back().push_back(ver);
  for (auto uuu : graph[ver]) {
    if (!used[uuu]) {
      Dfs(uuu);
    }
  }
}

void Solve() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  graph.resize(nnn);
  used.resize(nnn, false);
  for (int ind = 0; ind < mmm; ind++) {
    int xxx;
    int yyy;
    std::cin >> xxx >> yyy;
    xxx--;
    yyy--;
    graph[xxx].push_back(yyy);
    graph[yyy].push_back(xxx);
  }

  for (int ind = 0; ind < nnn; ind++) {
    if (!used[ind]) {
      res.emplace_back();
      Dfs(ind);
    }
  }

  std::cout << res.size() << '\n';
  for (auto& ind : res) {
    std::cout << ind.size() << '\n';
    for (auto iii : ind) {
      std::cout << iii + 1 << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int ttt = 1;
  //  std::cin >> TT;
  while ((ttt--) != 0) {
    Solve();
  }
  return 0;
}
