template<typename T>class random_xor{public:
  T s1,s2,s3,s4;
//   random_xor(){
//    srand(time(0)+rand());
//    s1=(T)rand()*rand()*rand()*rand();
//    s2=(T)rand()*rand()*rand()*rand();
//  }
//  T getint(){
//    T s3=s1,s4=s2;
//    s1=s4;s3^=s3<<23;
//    s2=s3^s4^(s3>>17)^(s4>>26);
//    return s2+s4;
//  }
  random_xor(){
    srand(time(0)+rand());
    s1=(T)rand()*rand()*rand()*rand();
    s2=(T)rand()*rand()*rand()*rand();
    s3=(T)rand()*rand()*rand()*rand();
    s4=(T)rand()*rand()*rand()*rand();
  }
  T getint() {
    T t=s1^(s1<<11);
    s1=s2;s2=s3;s3=s4;
    return s4=s4^(s4>>19)^t^(t>>8);
  }
  T get(T l,T r){return getint()%(r-l+1)+l;}
  T operator ()(T l,T r){return getint()%(r-l+1)+l;}
  T operator ()(){return getint();}
};
random_xor<unsigned __int128> a;
srand(time(0));
//mt19937::result_type seed=time(0);
auto randint=bind(uniform_int_distribution<int>(l,r),mt19937(time(0)));
auto randfloat=bind(uniform_real_distribution<double>(l,r),mt19937(time(0)));
