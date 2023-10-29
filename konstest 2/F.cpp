#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Heap {
  int size = 1;
  int size_heap = 1;
  std::vector<long long> array = {-1};
  std::vector<int> heap = {-1};
  std::vector<int> ind = {-1};

  void SiftUp(int now) {
    while (now != 1) {
      if (array[heap[now]] < array[heap[now >> 1]]) {
        std::swap(heap[now], heap[now >> 1]);
        std::swap(ind[heap[now]], ind[heap[now >> 1]]);
      } else {
        break;
      }
      now >>= 1;
    }
  }

  void Insert(int val) {
    array.push_back(val);
    heap.push_back(size);
    ind.push_back(size_heap);
    size++;
    size_heap++;
    SiftUp(size_heap - 1);
  }

  long long GetMin() { return array[heap[1]]; }

  void SiftDown(int now) {
    while (now * 2 < size_heap) {
      int to = now << 1;
      if (to != size_heap - 1 && array[heap[to]] > array[heap[to + 1]]) {
        to++;
      }

      if (array[heap[now]] > array[heap[to]]) {
        std::swap(heap[now], heap[to]);
        std::swap(ind[heap[now]], ind[heap[to]]);
        now = to;
      } else {
        break;
      }
    }
  }

  void ExtractMin() {
    ind[heap[size_heap - 1]] = 1;
    heap[1] = heap[size_heap - 1];

    heap.pop_back();
    size_heap--;
    SiftDown(1);
  }

  void DecreaseKey(int key, int val) {
    array[key] -= val;
    int x = ind[key];
    SiftUp(x);
    SiftDown(x);
  }
};

void Solve() {
  int query;
  std::cin >> query;
  Heap heap;

  std::vector<int> cnt(query + 1, 0);
  int count = 0;
  for (int ind = 1; ind <= query; ind++) {
    std::string str;
    std::cin >> str;
    if (str == "insert") {
      int val;
      std::cin >> val;
      heap.Insert(val);
      count++;
    }
    if (str == "decreaseKey") {
      int num;
      int val;
      std::cin >> num >> val;
      heap.DecreaseKey(cnt[num], val);
    }
    if (str == "getMin") {
      std::cout << heap.GetMin() << '\n';
    }
    if (str == "extractMin") {
      heap.ExtractMin();
    }
    cnt[ind] = count;
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}