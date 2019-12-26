#include <iostream>

class Singleton {
 private:
  Singleton() {}

 public:
  static Singleton *GetInstance() {
    if (!instance_) instance_ = new Singleton();
    return instance_;
  }

  void func() { std::cout << "wawawa..." << std::endl; }

 private:
  static Singleton *instance_;
};

Singleton *Singleton::instance_ = nullptr;

int main() {
  Singleton *p = Singleton::GetInstance();
  p->func();
  return 0;
}
