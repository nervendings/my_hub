const int inf=500;
const int N=105;
int n,m,ans,num;
int dis[N][N],mapp[N][N],pre[N][N],path[N];
void floyd() {
  ans=inf;
  for(int k=1; k<=n; k++) {
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(i==j||k==i||k==j) {
          continue;
        }
        if(dis[i][j]+mapp[i][k]+mapp[k][j]<ans) {
          ans=dis[i][j]+mapp[i][k]+mapp[k][j];
          num=0;
          path[num++]=k;
          int temp=j;
          while(temp!=i) {
            path[num++]=temp;
            temp=pre[i][temp];
          }
          path[num++]=i;
        }
      }
    }
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(i==j||k==i||k==j) {
          continue;
        }
        if(dis[i][j]>dis[i][k]+dis[k][j]) {
          dis[i][j]=dis[i][k]+dis[k][j];
          pre[i][j]=pre[k][j];
        }
      }
    }
  }
}
int main() {
  cin>>n>>m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      pre[i][j]=i;
      if(i==j) {
        mapp[i][j]=dis[i][j]=0;
      } else {
        mapp[i][j]=dis[i][j]=inf;
      }
    }
  }
  int u,v,w;
  for(int i=1; i<=m; i++) {
    cin>>u>>v>>w;
    mapp[u][v]=mapp[v][u]=dis[u][v]=dis[v][u]=min(w,mapp[u][v]);
  }
  floyd();
  if(ans==inf) {
    printf("No solution.\n");
  } else {
    for(int i=num-1; i>=0; i--) {
      printf("%d",path[i]);
      if(i==0) {
        printf("\n");
      } else {
        printf(" ");
      }
    }
  }
  return 0;
}
