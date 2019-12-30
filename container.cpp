#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

template<class Container, class Transform>
Container map(const Container& c, Transform f) {
  Container r;
  r.reserve(c.size());
  transform(begin(c), end(c), back_inserter(r), f);
  return r;
}

template <typename T>
struct DoubleNum
{
  T operator()(T num){ return num * 2; }
};

template<class Container, class Predicate>
Container filter(const Container& c, Predicate f) {
  Container r;
  copy_if(begin(c), end(c), back_inserter(r), f);
  return r;
}

template <typename T2>
struct OddNumber
{
  bool operator()(T2 num){ return num % 2 != 0; }
};

#define MAX_NUMBER 10000000

int main() {
  // copy
  vector<int> in;
  vector<int> in2;
  for (auto i = 1; i <= MAX_NUMBER; ++i) {
    in.push_back(i);
    in2.push_back(i+MAX_NUMBER);
  }
  copy(in2.begin(), in2.end(), back_inserter(in));

  // map(lambda)
  {
    auto start = std::chrono::system_clock::now();
    auto out = map(in, [](int i) {return i * 2;});
    auto end = std::chrono::system_clock::now();
    cout << "map(lambda)" << endl;  
    cout << " first:" << out.front() << endl;  
    cout << " last :" << out.back() << endl;
    cout << " size :" << out.size() << endl;
    cout << " time :" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << endl;;
  }
  
  // map(functor)
  {
    auto start = std::chrono::system_clock::now();
    auto out = map(in, DoubleNum<int>());
    auto end = std::chrono::system_clock::now();
    cout << "map(functor)" << endl;  
    cout << " first:" << out.front() << endl;  
    cout << " last :" << out.back() << endl;
    cout << " size :" << out.size() << endl;
    cout << " time :" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << endl;;
  }

  // filter(lambda)
  {
    auto start = std::chrono::system_clock::now();
    auto out = filter(in, [](int i) {return i % 2 != 0;});
    auto end = std::chrono::system_clock::now();
    cout << "filter(lambda)" << endl;  
    cout << " first:" << out.front() << endl;
    cout << " last :" << out.back() << endl;
    cout << " size :" << out.size() << endl;
    cout << " time :" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << endl;;
  }

  // filter(functor)
  {
    auto start = std::chrono::system_clock::now();
    auto out = filter(in, OddNumber<int>());
    auto end = std::chrono::system_clock::now();
    cout << "filter(functor)" << endl;
    cout << " first:" << out.front() << endl;
    cout << " last :" << out.back() << endl;
    cout << " size :" << out.size() << endl;
    cout << " time :" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << endl;;
  }
  
  return 0;
}
