//////////////////////////////////////////////////////////////////////////////
#include<bits/stdc++.h>
#define ll long long 
using namespace std;//head
namespace fastio{
bool isdecimal(char c){return (c >= 48 && c <= 57) || (c == 46);}
bool isdigit(char c){return c >= 48 && c <= 57;}
#define fabs(x) (x>0?x:-x)
const int maxsz=10000000;
struct fast_iostream{
  bool nega,ok = 1;
  char ch = get_nextchar();
  long double eps = 1e-8;
  int precious = 8;
  char get_nextchar(){
    static char buffer[maxsz], *p1 = buffer, *p2 = buffer;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, maxsz, stdin), p1 == p2) ? EOF : *p1++;
  }
  template <typename type> bool rn(type& _tmp){
    nega = 0;_tmp = 0;
    while (!isdigit(ch) && ch != EOF){nega = ch == '-';ch = get_nextchar();};
    if (ch == EOF) return ok = 0;
    do{_tmp = _tmp*10 + ch - 48;} while (isdigit(ch = get_nextchar()));
    if (nega) _tmp = -_tmp;
    return 1;
  }
  template <typename type>void rn_unsafe(type& _tmp){
    nega = 0;_tmp = 0;
    while (!isdigit(ch)){nega = ch == '-';ch = get_nextchar();};
    do{_tmp = _tmp*10 + ch - 48;} while (isdigit(ch = get_nextchar()));
    if (nega) _tmp = -_tmp;
  }
  template <typename type>type rn(){type v = type();rn_unsafe(v);return v;}
  template <typename type>bool run(type& _tmp){
    _tmp = 0;
    while (!isdigit(ch) && ch != EOF) ch = get_nextchar();
    if (ch == EOF) return ok = 0;
    do{_tmp = _tmp*10 + ch - 48;} while (isdigit(ch = get_nextchar()));
    return 1;
  }
  template <typename type>void run_unsafe(type& _tmp){
    _tmp = 0;
    while (!isdigit(ch)) ch = get_nextchar();
    do{_tmp = _tmp*10 + ch - 48;} while (isdigit(ch = get_nextchar()));
  }
  template <typename type>type run(){
    type v = type();run_unsafe(v);
    return v;
  }
  template <typename type>bool rd(type& _tmp){
    nega = 0;_tmp = 0;
    while (!isdigit(ch) && ch != EOF){
      nega = ch == '-';ch = get_nextchar();
    };
    if (ch == EOF) return ok = 0;
    do{_tmp = (_tmp * 10) + (ch - 48);} while (isdigit(ch = get_nextchar()));
    static int stk[80], top;
    if (ch == 46){
      top = 0;type _tmp2 = 0;
      while (isdigit(ch = get_nextchar())) stk[top++] = ch - 48;
      while (top--)_tmp2 = _tmp2 / 10 + stk[top];
      _tmp += _tmp2 / 10;
    }
    if (ch == 'e' || ch == 'E'){
      ch = get_nextchar();
      static bool _neg = 0;
      if (ch == '+') ch = get_nextchar();
      else if (ch == '-')_neg = 1, ch = get_nextchar();
      if (isdigit(ch))_tmp *= pow(10, run<ll>() * (_neg ? -1 : 1));
    }
    if (nega) _tmp = -_tmp;
    return 1;
  }
  template <typename type>type rd(){type v = type();rd(v);return v;}
  int get_str(char* s){
    char* c = s;
    while (ch == '\n' || ch == '\r' || ch == ' ') ch = get_nextchar();
    if (ch == EOF) return (ok = 0), *c = 0;
    do{*(c++) = ch;ch = get_nextchar();} while (ch != '\n' && ch != '\r' && ch != ' ' && ch != EOF);
    *(c++) = '\0';
    return static_cast<int>(c - s - 1);
  }
  char get_alpha(){
    while (!isalpha(ch)) ch = get_nextchar();
    const char ret = ch;ch = get_nextchar();
    return ret;
  }
  char get_nonblank(){
    while (isblank(ch)) ch = get_nextchar();
    const char ret = ch;ch = get_nextchar();
    return ret;
  }
  char get_char(){
    const char ret = ch;ch = get_nextchar();
    return ret;
  }
  template <typename type>void o(type p){
    static int stk[80], tp;
    if (p == 0){putchar(48);return;}
    if (p < 0){p = -p;putchar('-');}
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + 48);
  }
  template <typename type>void od(type v){
    static int stk[80], tp;
    tp = 0;
    if (fabs(v) < eps / 10){
      putchar(48);
      if (precious > 0){
        putchar(46);
        for (int i = 0; i < precious; ++i) putchar(48);
      }
      return;
    }
    else{
      if (v < 0){v = -v;putchar('-');}
      v += eps / 2;
      type p = floor(v) + eps / 10;
      while (fabs(p) > 1 - eps)stk[++tp] = fmod(p, 10), p /= 10;
      while (tp) putchar(stk[tp--] + 48);
    }
    if (precious == 0) return;
    putchar(46);v -= floor(v);
    for (int i = 0; i < precious; ++i){
      v *= 10;
      putchar((int)floor(v) + 48);
      v = fmod(v, 1);
    }
  }
  typedef void io_operator(fast_iostream& v);
  typedef char* charptr;
  template <typename type>fast_iostream& operator>>(type& x){
    if (numeric_limits<type>::is_signed) rn(x);
    else run(x);
    return *this;
  }
  template <typename type>fast_iostream& operator<<(const type& x);
  fast_iostream& operator<<(io_operator* v){v(*this);return *this;}
  operator bool() const {return ok;}
  void set_precious(int x){precious = x;eps = pow(10, -x);}
  #undef fabs(x)
};
template <>fast_iostream& fast_iostream::operator>>(char*& x){get_str(x);return *this;}
template <>fast_iostream& fast_iostream::operator>>(float& x){rd(x);return *this;}
template <>fast_iostream& fast_iostream::operator>>(double& x){rd(x);return *this;}
template <>fast_iostream& fast_iostream::operator>>(long double& x){rd(x);return *this;}
template <>void fast_iostream::o(char* p){printf(p);}
template <>void fast_iostream::o(char p){putchar(p);}
template <>void fast_iostream::o(float p){od(p);}
template <>void fast_iostream::o(double p){od(p);}
template <>void fast_iostream::o(long double p){od(p);}
template <typename type>fast_iostream& fast_iostream::operator<<(const type& x){o(x);return *this;}
}
