#include <iostream>

using std::cout;
using std::endl;

class C {
 public:
  C() { cout << "constructor         " << this << endl; }

  C(const C &p) {
    cout << "copy constructor    " << &p << " -> " << this << endl;
  }

  C(const C &&p) {
    cout << "move constructor    " << &p << " -> " << this << endl;
  }

  ~C() { cout << "deconstructor       " << this << endl; }

  C &operator=(const C &p) {
    cout << "operator =          " << &p << " -> " << this << endl;
    return *this;
  }

  C &operator=(const C &&p) {
    cout << "move operator =     " << &p << " -> " << this << endl;
    return *this;
  }

  C return_local_obj() {
    C c;
    return c;
  }

  C &return_local_obj_ref() {
    C c;
    return c;  // never return a local variable reference !!
  }

  C &return_self_obj() { return *this; }

  void accept_obj_as_param(const C c) { this->value = c.value; }

  void accept_obj_ref_as_param(const C &c) { this->value = c.value; }

 private:
  int value;
};

int main() {
  cout << "1. constructor only" << endl;
  C a;

  cout << "2. copy constructor" << endl;
  C b = a;

  {
    cout << "3. move constructor" << endl;
    C c = std::move(a);
  }

  {
    cout << "4. assignment operator" << endl;
    b = a;
  }

  cout << "5. function test" << endl;

  {
    cout << "::accept_obj_as_param(C)" << endl;
    a.accept_obj_as_param(b);
  }

  {
    cout << "::accept_obj_ref_as_param(C&)" << endl;
    a.accept_obj_ref_as_param(b);
  }

  {
    cout << "::return_local_obj()" << endl;
    C c = a.return_local_obj();
    cout << "::return_local_obj() v2" << endl;
    c = a.return_local_obj();
  }

  {
    cout << "::return_local_obj_ref()" << endl;
    C c = a.return_local_obj_ref();
    cout << "::return_local_obj_ref() v2" << endl;
    c = a.return_local_obj_ref();
  }

  {
    cout << "::return_self_obj()" << endl;
    C c = a.return_self_obj();
    cout << "::return_self_obj() v2" << endl;
    c = a.return_self_obj();
  }

  cout << "end of program" << endl;

  return 0;
}
