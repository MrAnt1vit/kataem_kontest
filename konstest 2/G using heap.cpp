#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const long long kMod = 1'073'741'824;

struct Heap {
  int size = 1;
  std::vector<long long> heap = {-1};

  void SiftUp(int now) {
    while (now != 1) {
      if (heap[now] > heap[now >> 1]) {
        std::swap(heap[now], heap[now >> 1]);
      } else {
        break;
      }
      now >>= 1;
    }
  }

  void Insert(long long val) {
    heap.push_back(val);
    size++;
    SiftUp(size - 1);
  }

  long long GetMax() { return heap[1]; }

  void SiftDown(int now) {
    while (now * 2 < size) {
      int to = now << 1;
      if (to != size - 1 && heap[to] < heap[to + 1]) {
        to++;
      }

      if (heap[now] < heap[to]) {
        std::swap(heap[now], heap[to]);
        now = to;
      } else {
        break;
      }
    }
  }

  void ExtractMax() {
    heap[1] = heap[size - 1];
    heap.pop_back();
    size--;
    SiftDown(1);
  }
};

void Solve() {
  int nn;
  int kk;
  std::cin >> nn >> kk;
  long long now;
  int xx;
  int yy;
  std::cin >> now >> xx >> yy;
  Heap set;
  for (int ind = 0; ind < nn; ind++) {
    now = (xx * now + yy) % kMod;
    set.Insert(now);
    if (set.size > kk + 1) {
      set.ExtractMax();
    }
  }

  std::vector<long long> res(kk);
  for (int ind = 1; ind <= kk; ind++) {
    res[ind - 1] = set.heap[ind];
  }
  std::sort(res.begin(), res.end());
  for (auto& el : res) {
    std::cout << el << ' ';
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}