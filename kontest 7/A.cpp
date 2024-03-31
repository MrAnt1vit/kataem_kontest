#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

std::stack<int> sta;
std::vector<std::vector<int>> graph;
std::vector<int> color;
std::vector<int> res;
bool flag = false;

void Dfs(int ver) {
  if (flag) {
    return;
  }
  sta.push(ver);
  color[ver] = 1;
  for (auto uuu : graph[ver]) {
    if (color[uuu] == 0) {
      Dfs(uuu);
    } else if (color[uuu] == 1) {
      while (sta.top() != uuu) {
        res.push_back(sta.top());
        sta.pop();
      }

      res.push_back(uuu);
      std::reverse(res.begin(), res.end());
      std::cout << "YES\n";
      flag = true;
      for (auto ind : res) {
        std::cout << ind + 1 << ' ';
      }
    }
    if (flag) {
      return;
    }
  }
  sta.pop();
  color[ver] = 2;
}

void Solve() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  graph.resize(nnn);
  for (int ind = 0; ind < mmm; ind++) {
    int xxx;
    int yyy;
    std::cin >> xxx >> yyy;
    xxx--;
    yyy--;
    graph[xxx].push_back(yyy);
  }

  color.resize(nnn, 0);
  for (int ind = 0; ind < nnn; ind++) {
    if (color[ind] == 0) {
      Dfs(ind);
    }
  }

  if (!flag) {
    std::cout << "NO\n";
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
