#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int cMax = 2009000999;

void Solve() {
  int nnn;
  int mmm;
  std::cin >> nnn >> mmm;
  std::vector<std::vector<std::pair<int, int>>> graph(nnn);
  for (int i = 0; i < mmm; i++) {
    int xxx;
    int yyy;
    int zzz;
    std::cin >> xxx >> yyy >> zzz;
    if (xxx != yyy) {
      graph[xxx].emplace_back(yyy, zzz);
      graph[yyy].emplace_back(xxx, zzz);
    }
  }
  int start;
  std::cin >> start;

  std::vector<int> dist(nnn, cMax);
  std::vector<int> pred(nnn, -1);
  dist[start] = 0;
  std::set<std::pair<int, int>> queue;
  queue.insert(std::make_pair(dist[start], start));
  while (!queue.empty()) {
    int ver = queue.begin()->second;
    queue.erase(queue.begin());
    for (size_t j = 0; j < graph[ver].size(); ++j) {
      int too = graph[ver][j].first;
      int len = graph[ver][j].second;
      if (dist[ver] + len < dist[too]) {
        queue.erase(std::make_pair(dist[too], too));
        dist[too] = dist[ver] + len;
        pred[too] = ver;
        queue.insert(std::make_pair(dist[too], too));
      }
    }
  }
  for (int i = 0; i < nnn; i++) {
    if (pred[i] == -1 && i != start) {
      std::cout << cMax << ' ';
    } else {
      std::cout << dist[i] << ' ';
    }
  }
  std::cout << '\n';
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int ttt = 1;
  std::cin >> ttt;
  while ((ttt--) != 0) {
    Solve();
  }
  return 0;
}
