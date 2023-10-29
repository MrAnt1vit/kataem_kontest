#include <iostream>
#include <stack>
#include <vector>

int main() {
  int nn;
  std::cin >> nn;
  std::vector<long long> arr(nn);
  std::vector<long long> left(nn);
  std::vector<long long> right(nn);
  for (int ii = 0; ii < nn; ++ii) {
    std::cin >> arr[ii];
  }

  std::stack<int> st;
  for (int ii = 0; ii < nn; ++ii) {
    while (!st.empty() && arr[st.top()] >= arr[ii]) {
      st.pop();
    }

    if (st.empty()) {
      left[ii] = 0;
    } else {
      left[ii] = st.top() + 1;
    }
    st.push(ii);
  }

  while (!st.empty()) {
    st.pop();
  }
  for (int ii = nn - 1; ii >= 0; --ii) {
    while (!st.empty() && arr[st.top()] >= arr[ii]) {
      st.pop();
    }

    if (st.empty()) {
      right[ii] = nn - 1;
    } else {
      right[ii] = st.top() - 1;
    }
    st.push(ii);
  }

  long long ans = 0;
  for (int ii = 0; ii < nn; ++ii) {
    ans = std::max(ans, arr[ii] * (right[ii] - left[ii] + 1));
  }

  std::cout << ans;
  return 0;
}