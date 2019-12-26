#include <iostream>

class IProduct {
 public:
  virtual void PrintName() = 0;
  virtual ~IProduct() {}
};

class ProductA : public IProduct {
 public:
  void PrintName() { std::cout << "A" << std::endl; }
};

class ProductB : public IProduct {
 public:
  void PrintName() { std::cout << "B" << std::endl; }
};

IProduct *CreateProduct(std::string name) {
  if ("A" == name)
    return new ProductA();
  else if ("B" == name)
    return new ProductB();
  else
    return nullptr;
}

int main() {
  IProduct *p = CreateProduct("A");
  if (p)
    p->PrintName();
  else
    std::cout << "null" << std::endl;
  return 0;
}
