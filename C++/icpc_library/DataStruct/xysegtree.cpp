class sstree{public:
#define nd  node[nowx][nowy]
    struct segnode {int val;};
    int n,m,x1,x2,y1,y2,x,nowx;int ans;
    segnode node[maxn][maxn];
    void init(int nn,int mm) {
        n=nn,m=mm;
        memset(node ,0,sizeof node);
    }
    void update(int xx1,int xx2,int yy1,int yy2){
        x1=xx1,y1=yy1,x2=xx2,y2=yy2;
        updatex(1,n);
    }
    void updatey(int l,int r,int nowy=1){
        if(y1>r||y2<l) return ;
        if(y1<=l&&y2>=r){nd.val^=1;return ;}
        updatey(l,(l+r)>>1,nowy<<1); updatey(((l+r)>>1)+1,r,nowy<<1|1);
    }
    void updatex(int l,int r,int now=1){
        if(x1>r||x2<l) return ;
        if(x1<=l&&x2>=r) {nowx=now;updatey(1,m);return ;}
        updatex(l,(l+r)>>1,now<<1); updatex(((l+r)>>1)+1,r,now<<1|1);
    }
    int query(int xx,int yy){
        x1=xx,y1=yy;ans=0;
        queryx(1,n);
        return ans;
    }
    void queryy(int l,int r,int nowy=1){
        if(y1>r||y1<l) return ;
        ans^=nd.val;
        if(l==r) return ;
        queryy(l,(l+r)>>1,nowy<<1);queryy(((l+r)>>1)+1,r,nowy<<1|1);
    }
    void queryx(int l,int r,int now=1){
        if(x1>r||x1<l) return ;
    nowx=now;queryy(1,m);
        if(l==r) return ;
        queryx(l,(l+r)>>1,now<<1);queryx(((l+r)>>1)+1,r,now<<1|1);
    }
}tree;
