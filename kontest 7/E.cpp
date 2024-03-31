#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Edge {
  int from;
  int to;
  int ind;
};

const int KMax = 2000000000;

std::vector<bool> used;
std::vector<int> upp;
std::vector<int> hhh;
std::vector<std::vector<int>> graph;
std::vector<Edge> edges;
std::vector<bool> is_br;
int ans = 0;

void Dfs(int ver, int pred) {
  used[ver] = true;
  upp[ver] = hhh[ver];
  for (int iii : graph[ver]) {
    auto edg = edges[iii];
    int too = ver ^ edg.from ^ edg.to;
    if (too == pred) {
      continue;
    }
    if (used[too]) {
      upp[ver] = std::min(upp[ver], hhh[too]);
    } else {
      hhh[too] = hhh[ver] + 1;
      Dfs(too, ver);
      upp[ver] = std::min(upp[ver], upp[too]);
      if (upp[too] == hhh[too]) {
        if (!is_br[edg.ind]) {
          is_br[edg.ind] = true;
          ans++;
        }
      }
    }
  }
}

void Solve() {
  int nnn;
  int mmm;
  int xxx;
  int yyy;
  std::cin >> nnn >> mmm;
  std::map<std::pair<int, int>, int> mpp;
  used.resize(nnn, false);
  upp.resize(nnn, KMax);
  hhh.resize(nnn, 0);
  graph.resize(nnn);
  edges.resize(mmm);
  is_br.resize(mmm, false);
  int cnt = 0;
  for (int ind = 0; ind < mmm; ind++) {
    std::cin >> xxx >> yyy;
    xxx--;
    yyy--;
    if (xxx > yyy) {
      std::swap(xxx, yyy);
    }

    if (xxx == yyy) {
      continue;
    }

    if (mpp.contains({xxx, yyy})) {
      ans--;
    }
    mpp[{xxx, yyy}]++;
    edges[ind].from = xxx;
    edges[ind].to = yyy;
    edges[ind].ind = ind;
    graph[xxx].push_back(ind);
    graph[yyy].push_back(ind);
  }

  for (int ind = 0; ind < nnn; ind++) {
    if (!used[ind]) {
      Dfs(ind, -1);
    }
  }
  ans -= cnt;

  std::cout << ans << '\n';
  for (int ind = 0; ind < mmm; ind++) {
    if (is_br[ind] && mpp[{edges[ind].from, edges[ind].to}] == 1 &&
        edges[ind].from != edges[ind].to) {
      std::cout << ind + 1 << ' ';
    }
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
