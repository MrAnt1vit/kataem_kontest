#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<bool> used;
std::vector<int> res;

void Dfs(int ver) {
  used[ver] = true;
  for (auto uuu : graph[ver]) {
    if (!used[uuu]) {
      Dfs(uuu);
    }
  }
  res.push_back(ver);
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
  }

  for (int ind = 0; ind < nnn; ind++) {
    if (!used[ind]) {
      Dfs(ind);
    }
  }

  std::reverse(res.begin(), res.end());
  std::vector<int> ind(nnn);
  for (int iii = 0; iii < nnn; iii++) {
    ind[res[iii]] = iii;
  }

  bool flag = false;
  for (int iii = 0; iii < nnn; iii++) {
    for (auto& jjj : graph[iii]) {
      if (ind[iii] >= ind[jjj]) {
        flag = true;
        break;
      }
    }
  }
  if (flag) {
    std::cout << "-1";
    return;
  }

  // std::cout << "YES\n";
  for (auto iii : res) {
    std::cout << iii + 1 << ' ';
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
