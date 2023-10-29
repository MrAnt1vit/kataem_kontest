#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct HeapMax {
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

  long long Get() { return heap[1]; }

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

  void Extract() {
    heap[1] = heap[size - 1];
    heap.pop_back();
    size--;
    SiftDown(1);
  }

  void Clear() {
    heap = {-1};
    size = 1;
  }
};

struct HeapMin {
  int size = 1;
  std::vector<long long> heap = {-1};

  void SiftUp(int now) {
    while (now != 1) {
      if (heap[now] < heap[now >> 1]) {
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

  long long Get() { return heap[1]; }

  void SiftDown(int now) {
    while (now * 2 < size) {
      int to = now << 1;
      if (to != size - 1 && heap[to] > heap[to + 1]) {
        to++;
      }

      if (heap[now] > heap[to]) {
        std::swap(heap[now], heap[to]);
        now = to;
      } else {
        break;
      }
    }
  }

  void Extract() {
    heap[1] = heap[size - 1];
    heap.pop_back();
    size--;
    SiftDown(1);
  }

  void Clear() {
    heap = {-1};
    size = 1;
  }
};

HeapMax heap_max_add;
HeapMax heap_max_del;
HeapMin heap_min_add;
HeapMin heap_min_del;
int sz = 0;

void Insert(int val) {
  heap_max_add.Insert(val);
  heap_min_add.Insert(val);
  sz++;
  std::cout << "ok\n";
}

void Update() {
  while (heap_min_add.size > 1 && heap_min_del.size > 1 &&
         heap_min_add.Get() == heap_min_del.Get()) {
    heap_min_add.Extract();
    heap_min_del.Extract();
  }

  while (heap_max_add.size > 1 && heap_max_del.size > 1 &&
         heap_max_add.Get() == heap_max_del.Get()) {
    heap_max_add.Extract();
    heap_max_del.Extract();
  }
}

void ExtractMin() {
  if (heap_min_add.size == 1) {
    std::cout << "error\n";
    return;
  }
  sz--;
  std::cout << heap_min_add.Get() << '\n';
  heap_max_del.Insert(heap_min_add.Get());
  heap_min_add.Extract();
}

void ExtractMax() {
  if (heap_max_add.size == 1) {
    std::cout << "error\n";
    return;
  }
  sz--;
  std::cout << heap_max_add.Get() << '\n';
  heap_min_del.Insert(heap_max_add.Get());
  heap_max_add.Extract();
}

void GetMin() {
  if (heap_min_add.size == 1) {
    std::cout << "error\n";
    return;
  }
  std::cout << heap_min_add.Get() << '\n';
}

void GetMax() {
  if (heap_max_add.size == 1) {
    std::cout << "error\n";
    return;
  }
  std::cout << heap_max_add.Get() << '\n';
}

void Clear() {
  heap_min_add.Clear();
  heap_max_add.Clear();
  heap_min_del.Clear();
  heap_max_del.Clear();
  sz = 0;
  std::cout << "ok\n";
}

void Solve() {
  int query;
  std::cin >> query;
  std::string str;
  int val;

  while (bool(query--)) {
    std::cin >> str;
    if (str == "insert") {
      std::cin >> val;
      Insert(val);
    } else if (str == "extract_min") {
      ExtractMin();
    } else if (str == "extract_max") {
      ExtractMax();
    } else if (str == "get_min") {
      GetMin();
    } else if (str == "get_max") {
      GetMax();
    } else if (str == "size") {
      std::cout << sz << '\n';
    } else if (str == "clear") {
      Clear();
    }
    Update();
  }
}

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  Solve();
}