#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

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
  Queue que;
  int query;
  int val;
  std::cin >> query;
  while (bool(query--)) {
    std::string str;
    std::cin >> str;
    if (str == "enqueue") {
      std::cin >> val;
      que.Push(val);
      std::cout << "ok\n";
    } else if (str == "size") {
      std::cout << que.Size() << '\n';
    } else if (str == "clear") {
      que.Clear();
      std::cout << "ok\n";
    } else {
      if (que.Size() == 0) {
        std::cout << "error\n";
      } else if (str == "dequeue") {
        std::cout << que.main.front() << '\n';
        que.Pop();
      } else if (str == "front") {
        std::cout << que.main.front() << '\n';
      } else if (str == "min") {
        std::cout << que.Get() << '\n';
      }
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}