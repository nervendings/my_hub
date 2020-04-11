class splaytree{public:
#define nd node[now]
#define ndl node[node[now].son[0]]
#define ndr node[node[now].son[1]]
    struct splaynode{
        int son[2],fa,val,size;
        splaynode(){size=1,fa=son[0]=son[1]=0;}
    };
    int cnt,root;
    vector<splaynode> node;
    inline void pushup(int now){nd.size=ndl.size+ndr.size+1;}
    inline void pushdown(int now){}
    inline int wh(int now){return node[nd.fa].son[1]==now;}
    void rotate(int now){
        int fa=nd.fa,gf=node[fa].fa,c=wh(now);
        pushdown(fa);pushdown(now);
        if(gf) node[gf].son[wh(fa)]=now;
        nd.fa=gf;
        node[fa].son[c]=nd.son[c^1];
        node[node[fa].son[c]].fa=fa;nd.son[c^1]=fa;node[fa].fa=now;
        pushup(fa);pushup(now);
    }
    void splay(int now,int dst=0){
        for(;nd.fa!=dst;rotate(now))
            if(node[nd.fa].fa!=dst)rotate(wh(now)==wh(nd.fa)?nd.fa:now);
            if(!dst) root=now;
    }
    void insert(int pos){
        int now=root,fa=0,val=node[pos].val;
        while(now) fa=now,now=val<nd.val?nd.son[0]:nd.son[1];
        now=pos;
        node[fa].son[val>node[fa].val]=now;
        nd.fa=fa;
        splay(now);
    }
    void order(int now){
        int l=nd.son[0],r=nd.son[1];
        nd.son[0]=nd.son[1]=nd.fa=0;
        nd.size=1;
        if(l) order(l);
        insert(now);
        if(r) order(r);
    }
    void merge(int a,int b){
        if(a==b) return ;
        splay(a);splay(b);
        if(node[a].size>node[b].size) swap(a,b);
        pre[a]=b;root=b;
        order(a);
    }
    int kth(int now,int k){
        splay(now);int lsize=0;
        while(now){
            int lsum=lsize+ndl.size;
            if(k<=lsum) now=nd.son[0];
            else if(k==lsum+1) return now;
            else lsize=lsum+1,now=nd.son[1];
        }
        return -1;
    }
    splaytree(int n){
        node.resize(n+7,splaynode());
        rep(i,1,n) node[i].val=val[i];
        node[0].size=0;
        root=0,cnt=0;
    }
};
