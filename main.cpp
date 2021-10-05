#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

const int MAX_DISCS = 12;
//state:int 12개의 원반이 각각 몇 번째 기둥에 속해있는지
//state에서 index번째 디스크가 어디에 있는지 (0~3)
int get (int state, int index) {
  return (state>>(index*2)) & 3;
}
//state에서 index번째 디스크를 value번째 기둥으로 옮기기
int set (int state, int index, int value) {
  return (state & ~(3<<(index*2)))| (value<<(index*2));
}
int c[1<<(MAX_DISCS*2)];
//state를 출력
void prnt (int discs, int state) {
  for(int i=0;i<discs;i++){
    cout<<get(state,i)<<" ";
  }
  cout<<endl;
}

int bfs(int discs, int begin, int end){
  if(begin==end)return 0;
  queue<int> q;
  memset(c, -1, sizeof(c));
  q.push(begin);
  c[begin]=0;
  while(!q.empty()){
    int here = q.front();
    prnt(discs,here);
    q.pop();
    //각 기둥에서 가장 위에 있는 원반 계산
    int top[4] = {-1,-1,-1,-1};
    for(int i = discs-1; i >=0; --i){
      top[get(here,i)] = i; //가장 작은 애가 위에 있을테니까 비교는 필요없음
    }
    for(int i = 0; i<4; i++) {
      if(top[i]!=-1){
        for(int j=0; j<4; ++j) {
          if(i!=j&&(top[j]==-1||top[i]<top[j])){
            int there = set(here,top[i],j);
            if(c[there]!=-1) continue;
            c[there] = c[here]+1;
            if(there==end) return c[there];
            q.push(there);
          }
        }
      }
    }
  }

  return -1;
}

int main() {
  int begin=0,end = 0;
  for(int i=0;i<9;i++){
    begin=set(begin,i,0);
    end=set(end,i,3);
  }
  cout<<bfs(9,begin,end)<<endl;
}