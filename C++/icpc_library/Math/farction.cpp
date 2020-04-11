//@num是分子,den是分母,分母始终保持为正@
template<typename T>class farction{public:
  T num,den;
  farction(T num=0,T den=1) {
    if (den<0) {
      num=-num;
      den=-den;
    }
    T g=__gcd(abs(num),den);
    this->num=num/g;
    this->den=den/g;
  }
  farction operator +(const farction &o) const {
    return farction(num*o.den+den*o.num,den*o.den);
  }
  farction operator -(const farction &o) const {
    return farction(num*o.den-den*o.num,den*o.den);
  }
  farction operator *(const farction &o) const {
    return farction(num*o.num,den*o.den);
  }
  farction operator /(const farction &o) const {
    return farction(num*o.den,den*o.num);
  }
  bool operator <(const farction &o) const {
    return num*o.den<den*o.num;
  }
  bool operator >(const farction &o) const {
    return num*o.den>den*o.num;
  }
  bool operator ==(const farction &o) const {
    return num*o.den==den*o.num;
  }
};
