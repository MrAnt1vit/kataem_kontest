#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define vec std::vector

vec<vec<vec<int>>> matrix;
vec<vec<vec<vec<int>>>> to_go;

struct Queue {
  std::queue<vec<int>> main;
  std::deque<vec<int>> help;

  static int GetVal(vec<int>& coords) {
    return matrix[coords[0]][coords[1]][coords[2]];
  }

  void Push(vec<int>& now) {
    main.push(now);

    while (!help.empty() && GetVal(help.back()) < GetVal(now)) {
      help.pop_back();
    }
    help.push_back(now);
  }

  void Pop() {
    if (help.front() == main.front()) {
      help.pop_front();
    }
    main.pop();
  }

  vec<int> Get() { return help.front(); }

  int Size() const { return int(main.size()); }

  void Clear() {
    while (!main.empty()) {
      main.pop();
    }
    help.clear();
  }
};

int szx;
int szy;
int szz;
int xx;
int yy;
int zz;

void Input() {
  for (int ii = 0; ii < szx; ++ii) {
    for (int jj = 0; jj < szy; ++jj) {
      for (int kk = 0; kk < szz; ++kk) {
        std::cin >> matrix[ii][jj][kk];
        to_go[ii][jj][kk] = {ii, jj, kk};
      }
    }
  }
}

void Merge1() {
  // merge values to strings
  for (int ii = 0; ii < szx; ++ii) {
    for (int jj = 0; jj < szy; ++jj) {
      Queue que;
      for (int kk = szz - 1; kk >= 0; --kk) {
        que.Push(to_go[ii][jj][kk]);
        if (que.Size() > zz) {
          que.Pop();
        }
        to_go[ii][jj][kk] = que.Get();
      }
    }
  }
}

void Merge2() {
  // merge strings to matrix
  for (int ii = 0; ii < szx; ++ii) {
    for (int kk = 0; kk < szz; ++kk) {
      Queue que;
      for (int jj = szy - 1; jj >= 0; --jj) {
        que.Push(to_go[ii][jj][kk]);
        if (que.Size() > yy) {
          que.Pop();
        }
        to_go[ii][jj][kk] = que.Get();
      }
    }
  }
}

void Merge3() {
  // merge matrix to all
  for (int jj = 0; jj < szy; ++jj) {
    for (int kk = 0; kk < szz; ++kk) {
      Queue que;
      for (int ii = szx - 1; ii >= 0; --ii) {
        que.Push(to_go[ii][jj][kk]);
        if (que.Size() > xx) {
          que.Pop();
        }
        to_go[ii][jj][kk] = que.Get();
      }
    }
  }
}

void CountRes() {
  // count answer
  for (int ii = szx - 1; ii >= 0; --ii) {
    for (int jj = szy - 1; jj >= 0; --jj) {
      for (int kk = szz - 1; kk >= 0; --kk) {
        to_go[ii][jj][kk] = to_go[to_go[ii][jj][kk][0]]
                                 [to_go[ii][jj][kk][1]]
                                 [to_go[ii][jj][kk][2]];
      }
    }
  }
}

void Answer() {
  // read and answer :D
  int query;
  std::cin >> query;
  while (bool(query--)) {
    vec<int> now = {0, 0, 0};
    std::cin >> now[0] >> now[1] >> now[2];
    vec<int> res = to_go[now[0]][now[1]][now[2]];
    std::cout << res[0] << ' ' << res[1] << ' ' << res[2] << '\n';
  }
}

void Solve() {
  std::cin >> szx >> szy >> szz;
  std::cin >> xx >> yy >> zz;
  matrix.resize(szx, vec<vec<int>>(szy, vec<int>(szz)));
  to_go.resize(szx, vec<vec<vec<int>>>(szy, vec<vec<int>>(szz, vec<int>(3))));
  Input();
  Merge1();
  Merge2();
  Merge3();
  CountRes();
  Answer();
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}