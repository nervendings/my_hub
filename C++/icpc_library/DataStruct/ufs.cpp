#define same(a,b) (find(a)==find(b))
int pre[maxn],id[maxn];
int numid;
int fd(int a) {
    return pre[a]==a?a:pre[a]=find(pre[a]);
}
int find(int a){return fd(id[a])};
void unite(int a,int b){
    a=find(id[a]),b=find(id[b]);
    pre[b]=a;
}
void remove(int now){
    int pos=find(id[now]);
    id[now]=++numid;
    pre[numid]=numid;
}
