#include <iostream>
#include <utility>

class IRequest {
 public:
  virtual void Request() = 0;
  virtual ~IRequest() {}
  void BeforeRequest() { std::cout << "before request" << std::endl; }
  void AfterRequest() { std::cout << "after request" << std::endl; }
};

class Client : public IRequest {
 public:
  void Request() { std::cout << "Client::request()" << std::endl; }
};

// 静态代理
class ClientProxy : public IRequest {
 public:
  // 大部分资料说Client应该在main中构造
  // 然而《图说设计模式》的作者认为应当保持操作的透明性，因此在ClientProxy中构造
  // 个人认为在哪里构造关系不大，视应用场景而定
  ClientProxy() { p = new Client(); }
  void Request() {
    BeforeRequest();
    p->Request();
    AfterRequest();
  }
  ~ClientProxy() { delete p; }

 private:
  Client* p;
};

// 虚拟代理：延迟加载
class ClientVirtualProxy : public IRequest {
 public:
  ClientVirtualProxy() { p = nullptr; }
  void Request() {
    if (!p) p = new Client();
    BeforeRequest();
    p->Request();
    AfterRequest();
  }
  ~ClientVirtualProxy() { delete p; }

 private:
  Client* p;
};

// 虚拟代理：COW
// 请参考 std::string

// 保护代理
// 控制被代理类中方法的访问权限

// 智能引用
template <typename T>
class simple_shared_ptr {
 public:
  simple_shared_ptr(T* p) { rb_ = new RefBlock({1, p}); }
  simple_shared_ptr(const simple_shared_ptr<T>& other) {
    rb_ = other.rb_;
    ++rb_->n;
  }
  simple_shared_ptr(simple_shared_ptr<T>&& other) {
    rb_ = std::__exchange(other.rb_, nullptr);
  }
  simple_shared_ptr<T>& operator=(const simple_shared_ptr<T>& other) {
    rb_ = other.rb_;
    ++rb_->n;
    return *this;
  }
  simple_shared_ptr<T>& operator=(simple_shared_ptr<T>&& other) {
    rb_ = std::__exchange(other.rb_, nullptr);
    return *this;
  }
  ~simple_shared_ptr() {
    --rb_->n;
    if (0 == rb_->n) {
      delete rb_->p;
      delete rb_;
    }
  }
  T* operator->() { return rb_->p; }
  T& operator*() { return *(rb_->p); }

 private:
  struct RefBlock {
    int n;
    T* p;
  } * rb_;
};

int main(int argc, char** argv) {
  ClientProxy cp;
  cp.Request();
  ClientVirtualProxy clp;
  clp.Request();

  simple_shared_ptr<int> c(new int(30));

  return 0;
}
