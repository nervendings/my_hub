#include<iostream>
#include<cstdio>
#include<cstring>
#include <vector>
#include <queue>
using namespace std;

const int N = 1000000 + 10, INF = 0x3f3f3f3f;

struct node {
  node *next[26];
  node *suff; //@指向后缀节点@
  bool flag;
} trie[N], *root;
int tot;
char ori[N];
node* node_init() {
  trie[tot].flag = false;
  trie[tot].suff = NULL;
  memset(trie[tot].next, 0, sizeof trie[tot].next);
  return trie + tot++;
}
void trie_insert(char *s) {
  node *p = root;
  for(int i = 0; s[i]; i++) {
    int j = s[i] - 'a';
    if(p->next[j] == NULL)
      p->next[j] = node_init();
    p = p->next[j];
  }
  p->flag = true;
}
void trie_graph() {
  //@trie[0]为虚拟节点，root为trie[1]，trie[0]的所有边均指向root，方便以后操作@
  for(int i = 0; i < 26; i++)
    trie[0].next[i] = root;
  root->suff = trie + 0;
  trie[0].suff = NULL;
  queue<node*> que;
  que.push(root);
  while(! que.empty()) {
    node *p = que.front();
    que.pop();
    for(int i = 0; i < 26; i++)
      if(p->next[i]) {
        //@查看父亲节点的后缀节点是否存在编号为i的边，若没有，就一直往上找，直到根节点@
        node *ptr = p->suff;
        while(ptr && ! ptr->next[i])
          ptr = ptr->suff;
        //@要么找到了，要么循环到了虚拟节点后，后缀节点被置为root@
        p->next[i]->suff = ptr->next[i];
        if(ptr->next[i]->flag)
          p->next[i]->flag = true;
        que.push(p->next[i]);
      }
  }
}
bool trie_query(char *s) {
  node *p = root;
  for(int i = 0; s[i]; i++) {
    int j = s[i] - 'a';
    while(true) {
      if(p->next[j] != NULL) {
        p = p->next[j];
        if(p->flag == true)
          return true;
        break;
      } else
        p = p->suff;
    }
  }
  return false;
}
int main() {
  int n;
  scanf("%d", &n);
  tot = 2;//@tot+0是虚拟节点，tot+1是根节点，故从2开始@
  root = trie + 1;
  memset(trie[root].next, 0, sizeof trie[root].next);
  for(int i = 1; i <= n; i++) {
    scanf("%s", ori);
    trie_insert(ori);
  }
  trie_graph();//@建trie图@
  scanf("%s", ori);
  puts(trie_query(ori) ? "YES" : "NO");
  return 0;
}
