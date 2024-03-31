#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> rev_graph;
int nnn;
int cur_comp = 1;
std::vector<bool> used;
std::vector<int> order;
std::vector<int> comp;

void Dfs(int ver) {
  used[ver] = true;
  for (auto uuu : graph[ver]) {
    if (!used[uuu]) {
      Dfs(uuu);
    }
  }
  order.push_back(ver);
}

void Dfs1(int ver) {
  used[ver] = true;
  comp[ver] = cur_comp;
  for (auto uuu : rev_graph[ver]) {
    if (!used[uuu]) {
      Dfs1(uuu);
    }
  }
}

void Solve() {
  int mmm;
  std::cin >> nnn >> mmm;
  graph.resize(nnn);
  rev_graph.resize(nnn);
  comp.resize(nnn);
  used.assign(nnn, false);
  for (int ind = 0; ind < mmm; ind++) {
    int xxx;
    int yyy;
    std::cin >> xxx >> yyy;
    xxx--;
    yyy--;
    rev_graph[yyy].push_back(xxx);
    graph[xxx].push_back(yyy);
  }
  for (int ind = 0; ind < nnn; ++ind) {
    if (!used[ind]) {
      Dfs(ind);
    }
  }
  std::reverse(order.begin(), order.end());
  used.assign(nnn, false);
  for (auto ind : order) {
    if (!used[ind]) {
      Dfs1(ind);
      ++cur_comp;
    }
  }
  std::cout << cur_comp - 1 << '\n';
  for (auto iter : comp) {
    std::cout << iter << ' ';
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
