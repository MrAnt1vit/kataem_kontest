#include <iostream>
// #include "string.h"
#include <algorithm>
#include <vector>

std::vector<int> ans;
std::vector<std::pair<int, int>> array;
int nn;

void MergeSort(int left, int right) {
  if (right - left == 1) {
    return;
  }
  int mid = (left + right) >> 1;

  MergeSort(left, mid);
  MergeSort(mid, right);

  std::vector<int> now(right - left);
  for (int ind = 0; ind < right - left; ind++) {
    now[ind] = array[left + ind].second;
  }

  int left_ind = left;
  int right_ind = mid;
  int count = 0;

  while (left_ind < mid && right_ind < right) {
    if (now[left_ind - left] < now[right_ind - left]) {
      array[left + count].second = now[left_ind - left];
      left_ind++;
    } else {
      ans[now[right_ind - left]] += mid - left_ind;
      array[left + count].second = now[right_ind - left];
      right_ind++;
    }
    count++;
  }
  while (left_ind < mid) {
    array[left + count].second = now[left_ind - left];
    left_ind++;
    count++;
  }
  while (right_ind < right) {
    array[left + count].second = now[right_ind - left];
    right_ind++;
    count++;
  }
}

void Solve() {
  std::cin >> nn;
  array.resize(nn);
  ans.resize(nn, 0);
  for (int index = 0; index < nn; ++index) {
    std::cin >> array[index].first;
    array[index].second = index;
  }
  std::sort(array.begin(), array.end());
  MergeSort(0, nn);

  for (int ind = 0; ind < nn; ind++) {
    std::cout << ans[ind] << ' ';
  }
}

int main() { Solve(); }