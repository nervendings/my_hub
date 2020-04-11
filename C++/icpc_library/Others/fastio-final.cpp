namespace fastio{//@支持读取整数,字符串,输出整数@
bool isdigit(char c){return c>=48&&c<=57;}
const int maxsz=1e7;
class fast_iostream{public:
  char ch=get_char();
  bool endf=1,flag;
  char get_char(){
    static char buffer[maxsz],*a=buffer,*b=buffer;
    return b==a&&(b=(a=buffer)+fread(buffer,1,maxsz, stdin),b==a)?EOF:*a++;
  }
  template<typename type>bool get_int(type& tmp){
    flag=tmp=0;
    while(!isdigit(ch)&&ch!=EOF){flag=ch=='-';ch=get_char();};
    if(ch==EOF)return endf=0;
    do{tmp=ch-48+tmp*10;}while(isdigit(ch=get_char()));
    if(flag)tmp=-tmp;
    return 1;
  }
  int get_str(char* str){
    char* tmp=str;
    while(ch=='\r'||ch=='\n'||ch==' ')ch=get_char();
    if(ch==EOF)return(endf=0),*tmp=0;
    do{*(tmp++)=ch;ch=get_char();}while(ch!='\r'&&ch!='\n'&&ch!=' '&&ch!=EOF);
    *(tmp++)=0;
    return(int)(tmp-str-1);
  }
  fast_iostream& operator>>(char* tmp){get_str(tmp);return *this;}
  template<typename type>fast_iostream& operator>>(type& tmp){get_int(tmp);return *this;}
  operator bool() const {return endf;}
};
template<typename type>void put(type tmp){
  if (tmp==0){putchar(48);return;}
  static int top,stk[21];
  if (tmp<0){tmp=-tmp;putchar('-');}
  while(tmp)stk[++top]=tmp%10,tmp/=10;
  while(top)putchar(stk[top--]+48);
}
}fastio::fast_iostream io;
