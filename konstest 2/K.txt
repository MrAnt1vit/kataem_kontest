#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define vec std::vector

struct Queue {
  std::queue<int> main;
  std::deque<int> help;

  void Push(int val) {
    main.push(val);

    while (!help.empty() && help.back() > val) {
      help.pop_back();
    }
    help.push_back(val);
  }

  void Pop() {
    if (help.front() == main.front()) {
      help.pop_front();
    }
    main.pop();
  }

  int Get() { return help.front(); }

  int Size() const { return int(main.size()); }

  void Clear() {
    while (!main.empty()) {
      main.pop();
    }
    help.clear();
  }
};

void Solve() {
  int nn;
  int mm;
  std::cin >> nn >> mm;
  vec<vec<int>> matrix(nn, vec<int>(nn));
  for (int ii = 0; ii < nn; ++ii) {
    for (int jj = 0; jj < nn; ++jj) {
      std::cin >> matrix[ii][jj];
    }
  }

  // объединяем по строчкам
  for (int ii = 0; ii < nn; ++ii) {
    Queue que;
    for (int jj = 0; jj < nn; ++jj) {
      que.Push(matrix[ii][jj]);
      if (jj >= mm - 1) {
        matrix[ii][jj - mm + 1] = que.Get();
        que.Pop();
      }
    }
  }

  // объединяем строчки в подматрицы
  for (int jj = 0; jj < nn - mm + 1; ++jj) {
    Queue que;
    for (int ii = 0; ii < nn; ++ii) {
      que.Push(matrix[ii][jj]);
      if (ii >= mm - 1) {
        matrix[ii - mm + 1][jj] = que.Get();
        que.Pop();
      }
    }
  }

  for (int ii = 0; ii < nn - mm + 1; ++ii) {
    for (int jj = 0; jj < nn - mm + 1; ++jj) {
      std::cout << matrix[ii][jj] << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}