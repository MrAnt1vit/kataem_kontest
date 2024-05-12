#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const long long cMax = 9223372036854775807;

void Solve() {
  int nnn;
  int mmm;
  int kkk;
  std::cin >> nnn >> mmm >> kkk;
  std::vector<int> start(kkk);
  for (int i = 0; i < kkk; i++) {
    int xxx;
    std::cin >> xxx;
    start[i] = xxx - 1;
  }
  std::vector<std::vector<std::pair<int, int>>> graph(nnn);
  for (int i = 0; i < mmm; i++) {
    int xxx;
    int yyy;
    int zzz;
    std::cin >> xxx >> yyy >> zzz;
    if (xxx != yyy) {
      xxx--;
      yyy--;
      graph[xxx].emplace_back(yyy, zzz);
      graph[yyy].emplace_back(xxx, zzz);
    }
  }

  int begin;
  int end;
  std::cin >> begin >> end;
  begin--;
  end--;
  std::vector<long long> dist(nnn, cMax);
  std::set<std::pair<int, int>> queue;
  for (int i = 0; i < kkk; i++) {
    dist[start[i]] = 0;
    queue.insert(std::make_pair(0, start[i]));
  }
  while (!queue.empty()) {
    int ver = queue.begin()->second;
    queue.erase(queue.begin());
    for (size_t j = 0; j < graph[ver].size(); ++j) {
      int too = graph[ver][j].first;
      int len = graph[ver][j].second;
      if (dist[ver] + len < dist[too]) {
        queue.erase(std::make_pair(dist[too], too));
        dist[too] = dist[ver] + len;
        queue.insert(std::make_pair(dist[too], too));
      }
    }
  }

  if (dist[begin] == 0) {
    std::cout << -1;
    return;
  }
  std::vector<long long> dist1(nnn, cMax);
  dist1[begin] = 0;
  queue.insert(std::make_pair(0, begin));

  while (!queue.empty()) {
    int ver = queue.begin()->second;
    queue.erase(queue.begin());
    for (auto& j : graph[ver]) {
      int too = j.first;
      int len = j.second;
      if (dist1[ver] + len < std::min(dist[too], dist1[too])) {
        queue.erase(std::make_pair(dist1[too], too));
        dist1[too] = dist1[ver] + len;
        queue.insert(std::make_pair(dist1[too], too));
      }
    }
  }

  if (dist1[end] != cMax) {
    std::cout << dist1[end] << '\n';
  } else {
    std::cout << -1 << '\n';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int ttt = 1;
  //  std::cin >> ttt;
  while ((ttt--) != 0) {
    Solve();
  }
  return 0;
}
