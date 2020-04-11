//@可删堆@
//@保证remove元素被包含在x中,不能多删@
template<typename T>class re_heap{public:
  priority_queue<T> x,y;
  void push(T a){x.push(a);}
  void remove(T a){y.push(a);}
  T top(){
    while(y.size()&&x.top()==y.top())
    x.pop(),y.pop();return x.top();
  }
  int size(){return x.size()-y.size();}
  void pop(){
    while(y.size()&&x.top()==y.top())
    x.pop(),y.pop();
    x.pop();
  }
  T sectop(){
    T a=top();pop();
    T b=top();push(a);
    return b;
  }
};
re_heap<pii> heap;
