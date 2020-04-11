int rt[maxn];
class ptrie{public:
  int node[maxn*40][2],top;
  void init(){rt[0]=node[0][1]=node[0][0]=top=0;}
  int add(int pre,int val,int bit=31){
    int now=++top;
    if(bit<0) return now;
    int t=val>>bit&1;
    node[now][t]=add(node[pre][t],val,bit-1);
    node[now][t^1]=node[pre][t^1];
    return now;
  }
  int query(int now,int pre,int val,int bit=31,int ans=0){
    if(bit<0) return ans;
    int t=val>>bit&1;
    if(node[now][t^1]-node[pre][t^1]>0) return query(node[now][t^1],node[pre][t^1],val,bit-1,ans|(1<<bit));
    return query(node[now][t],node[pre][t],val,bit-1,ans);

  }
}tree;
