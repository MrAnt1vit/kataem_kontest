#include <iostream>
#include <stack>

void Solve() {
  std::string str;
  std::cin >> str;
  std::stack<char> up;

  for (auto& now : str) {
    if (now == '[' || now == '{' || now == '(') {
      up.push(now);
    } else {
      if (up.empty()) {
        std::cout << "NO";
        return;
      }
      if (now == ']' && up.top() == '[') {
        up.pop();
      } else if (now == '}' && up.top() == '{') {
        up.pop();
      } else if (now == ')' && up.top() == '(') {
        up.pop();
      } else {
        std::cout << "NO";
        return;
      }
    }
  }
  if (up.empty()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}

int main() {
  // ускорение ввода
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  int time = 1;
  // std::cin >> T;
  while (bool(time--)) {
    Solve();
  }
}