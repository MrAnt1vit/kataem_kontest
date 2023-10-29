#include <deque>
#include <iostream>
#include <queue>
#include <vector>

int val;
int query;
std::queue<int> que;
std::deque<int> st;

void Enq() {
  std::cin >> val;
  while (!st.empty() && st.back() > val) {
    st.pop_back();
  }
  que.push(val);
  st.push_back(val);
  std::cout << "ok\n";
}

void Deq() {
  if (que.empty()) {
    std::cout << "error\n";
  } else {
    std::cout << que.front() << '\n';
    if (st.front() == que.front()) {
      st.pop_front();
    }
    que.pop();
  }
}

void Solve() {
  std::cin >> query;
  while (bool(query--)) {
    std::string str;
    std::cin >> str;
    if (str == "enqueue") {
      Enq();
    } else if (str == "dequeue") {
      Deq();
    } else if (str == "front") {
      if (que.empty()) {
        std::cout << "error\n";
      } else {
        std::cout << que.front() << '\n';
      }
    } else if (str == "size") {
      std::cout << que.size() << '\n';
    } else if (str == "clear") {
      while (!que.empty()) {
        que.pop();
      }
      st.clear();
      std::cout << "ok\n";
    } else {
      if (que.empty()) {
        std::cout << "error\n";
      } else {
        std::cout << st.front() << '\n';
      }
    }
  }
}

int main() {
  Solve();
  return 0;
}