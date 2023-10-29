#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Heap {
  int size = 1;
  int size_heap_max = 1;
  int size_heap_min = 1;
  std::vector<long long> array = {-1};
  std::vector<int> heap_min = {-1};
  std::vector<int> ind_min = {-1};
  std::vector<int> heap_max = {-1};
  std::vector<int> ind_max = {-1};

  void SiftUpMin(int now) {
    while (now != 1) {
      if (array[heap_min[now]] < array[heap_min[now >> 1]]) {
        std::swap(heap_min[now], heap_min[now >> 1]);
        std::swap(ind_min[heap_min[now]], ind_min[heap_min[now >> 1]]);
      } else {
        break;
      }
      now >>= 1;
    }
  }

  void SiftDownMin(int now) {
    while (now * 2 < size_heap_min) {
      int to = now << 1;
      if (to != size_heap_min - 1 &&
          array[heap_min[to]] > array[heap_min[to + 1]]) {
        to++;
      }

      if (array[heap_min[now]] > array[heap_min[to]]) {
        std::swap(heap_min[now], heap_min[to]);
        std::swap(ind_min[heap_min[now]], ind_min[heap_min[to]]);
        now = to;
      } else {
        break;
      }
    }
  }

  long long GetMin() { return array[heap_min[1]]; }

  void ExtractMinKey(int now) {
    ind_min[heap_min[size_heap_min - 1]] = now;
    heap_min[now] = heap_min[size_heap_min - 1];

    heap_min.pop_back();
    size_heap_min--;
    SiftDownMin(now);
    SiftUpMin(now);
  }

  void ExtractMin() {
    ExtractMaxKey(ind_max[heap_min[1]]);

    ind_min[heap_min[size_heap_min - 1]] = 1;
    heap_min[1] = heap_min[size_heap_min - 1];

    heap_min.pop_back();
    size_heap_min--;
    SiftDownMin(1);
  }

  void SiftUpMax(int now) {
    while (now != 1) {
      if (array[heap_max[now]] > array[heap_max[now >> 1]]) {
        std::swap(heap_max[now], heap_max[now >> 1]);
        std::swap(ind_max[heap_max[now]], ind_max[heap_max[now >> 1]]);
      } else {
        break;
      }
      now >>= 1;
    }
  }

  void SiftDownMax(int now) {
    while (now * 2 < size_heap_max) {
      int to = now << 1;
      if (to != size_heap_max - 1 &&
          array[heap_max[to]] < array[heap_max[to + 1]]) {
        to++;
      }

      if (array[heap_max[now]] < array[heap_max[to]]) {
        std::swap(heap_max[now], heap_max[to]);
        std::swap(ind_max[heap_max[now]], ind_max[heap_max[to]]);
        now = to;
      } else {
        break;
      }
    }
  }

  long long GetMax() { return array[heap_max[1]]; }

  void ExtractMaxKey(int now) {
    ind_max[heap_max[size_heap_max - 1]] = now;
    heap_max[now] = heap_max[size_heap_max - 1];

    heap_max.pop_back();
    size_heap_max--;
    SiftDownMax(now);
    SiftUpMax(now);
  }

  void ExtractMax() {
    ExtractMinKey(ind_min[heap_max[1]]);

    ind_max[heap_max[size_heap_max - 1]] = 1;
    heap_max[1] = heap_max[size_heap_max - 1];

    heap_max.pop_back();
    size_heap_max--;
    SiftDownMax(1);
  }

  void Insert(int val) {
    array.push_back(val);
    heap_min.push_back(size);
    heap_max.push_back(size);
    ind_min.push_back(size_heap_min);
    ind_max.push_back(size_heap_max);
    size++;
    size_heap_min++;
    size_heap_max++;
    SiftUpMax(size_heap_max - 1);
    SiftUpMin(size_heap_min - 1);
  }

  void Clear() {
    array.clear();
    heap_min.clear();
    heap_max.clear();
    ind_min.clear();
    ind_max.clear();
    heap_max = heap_min = ind_min = ind_max = {-1};
    array = {-1LL};
    size = size_heap_min = size_heap_max = 1;
  }
};

void Solve() {
  int query;
  std::cin >> query;
  std::string str;
  int val;

  Heap minmax;
  while (bool(query--)) {
    std::cin >> str;
    if (str == "insert") {
      std::cin >> val;
      minmax.Insert(val);
      std::cout << "ok\n";
    } else if (str == "clear") {
      minmax.Clear();
      std::cout << "ok\n";
    } else if (str == "size") {
      std::cout << minmax.size_heap_min - 1 << '\n';
    } else {
      if (minmax.size_heap_min == 1) {
        std::cout << "error\n";
      } else if (str == "extract_min") {
        std::cout << minmax.GetMin() << '\n';
        minmax.ExtractMin();
      } else if (str == "extract_max") {
        std::cout << minmax.GetMax() << '\n';
        minmax.ExtractMax();
      } else if (str == "get_min") {
        std::cout << minmax.GetMin() << '\n';
      } else if (str == "get_max") {
        std::cout << minmax.GetMax() << '\n';
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