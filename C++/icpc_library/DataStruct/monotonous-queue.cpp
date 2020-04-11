int main() {//luogu1440
  rep(i,1,n){
    if(que.empty()) ans[i]=0;
    else ans[i]=a[que.front()];
    if(!que.empty()&&i-que.front()>=m) que.pop_front();
    while(!que.empty()&&a[i]<a[que.back()]) que.pop_back();
    que.push_back(i);
  }//min(ai-m,...,ai-1)
}
int main(){//luogu2852 
  rep(i,1,n){
    while(!que.empty()&&h[i]<h[que.back()]) que.pop_back();
    que.push_back(i);
    while(!que.empty()&&i-que.front()>=m) que.pop_front();
    if(que.empty())ans[i]=0;
    else ans[i]=h[que.front()];
  }//min(ai-m+1,...,ai)
}
