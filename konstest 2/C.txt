#include <deque>
#include <iostream>
#include <stack>
#include <vector>

int main() {
  int need;
  std::cin >> need;
  char let;
  int val;
  std::deque<int> d1;
  std::deque<int> d2;
  while (bool(need--)) {
    std::cin >> let;
    if (let == '-') {
      std::cout << d1.front() << '\n';
      d1.pop_front();
    } else if (let == '+') {
      std::cin >> val;
      d2.push_back(val);
    } else if (let == '*') {
      std::cin >> val;
      d1.push_back(val);
    }
    while (d1.size() > d2.size()) {
      d2.push_front(d1.back());
      d1.pop_back();
    }
    while (d1.size() < d2.size()) {
      d1.push_back(d2.front());
      d2.pop_front();
    }
  }
  return 0;
}