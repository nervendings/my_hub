template<typename T,const int Size> class heap_array{public:
  T heap[Size];
  int size;
  heap_array(){size=0;}
  inline int lson(int now){return now<<1;}
  inline int rson(int now){return now<<1|1;}
  inline int fa(int now){return now>>1;}
  void pushdown(int now){
    int l,r,tmp;
    while(lson(now)<=size){
      l=lson(now),r=rson(now);
      tmp=now;
      if(heap[tmp]>heap[l]) tmp=l;
      if(r<=size&&heap[tmp]>heap[r]) tmp=r;
      if(tmp!=now) {
        swap(heap[tmp],heap[now]);
        now=tmp;
      }
      else break;
    }
  }
  void pushup(int now){
    while(fa(now)){
      if(heap[fa(now)]>heap[now]){
        swap(heap[fa(now)],heap[now]);
        now=fa(now);
      }else break;
    }
  }
  void pop(){
    heap[1]=heap[size--];
    pushdown(1);
  }
  void push(T x){
    heap[++size]=x;
    pushup(size);
  }
  T top(){return heap[1];}
};
heap_array<int,100000> heap;
