package acm;
import java.math.BigInteger;
import java.util.Scanner;
public class Main{
  public static final int maxn=1000,maxm=200000;
  public static BigInteger gcd(BigInteger a,BigInteger b) {
    if(b.compareTo(BigInteger.ZERO)==0)return a;
    else return gcd(b, a.remainder(b));
  }
  public static void main(String[] argc){
    int[]a=new int[maxn];
    for(int i=2;i<maxn;i++) a[i]=i;
    for(int i=2;i<maxn;i++) if(a[i]!=0)
      for(int j=i*2;j<maxn;j=j+i) a[j]=0;
    Scanner cin=new Scanner(System.in);
    int casn=cin.nextInt();
    int[] prime=new int[10000];
    for(int ii=1;ii<=casn;++ii) {
      BigInteger x=cin.nextBigInteger();
      BigInteger res=BigInteger.ONE;
      BigInteger now=BigInteger.ONE;
      int i=1;
      while(true) {
        i++;
        if(a[i]==0) continue;
        if(res.multiply(BigInteger.valueOf(a[i])).compareTo(x)<=0) {
          res=res.multiply(BigInteger.valueOf(a[i]));
          now=now.multiply(BigInteger.valueOf(a[i]+1));
        }else break;
      }
      BigInteger g=gcd(res,now);
      res=res.divide(g);
      now=now.divide(g);
      System.out.println(res+"/"+now);
    }
  }
}
