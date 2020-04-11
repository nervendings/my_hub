struct fastout {
  const static int _O_Buffer_Size=10<<20;
  char _O_Buffer[_O_Buffer_Size],*_O_pos=_O_Buffer;
  ~fastout() { fwrite(_O_Buffer, 1,_O_pos-_O_Buffer, stdout); }
  template<class T> fastout &operator<<(T n) {
    static char _buf[10];
    char *_pos=_buf;
    do *_pos++='0'+n%10;
    while(n/=10);
    while(_pos!=_buf)*_O_pos++=*--_pos;
    return *this;
  }
  fastout &operator<<(char ch) {
    *_O_pos++ = ch;
    return *this;
  }
} fout;
