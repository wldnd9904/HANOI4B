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
//절댓값 1 증가
int increment(int state) {
  return state>=0?state+1:state-1;
}
//부호
int sign(int state) {
  if(!state)return 0;
  else return state>0?1:-1;
}
int bfs(int discs, int begin, int end){
  if(begin==end)return 0;
  queue<int> q;
  memset(c, -1, sizeof(c));
  q.push(begin);
  c[begin]=0;
  while(!q.empty()){
    int here = q.front();
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

//양방향 탐색
int bis(int discs, int begin, int end){
  //기저 사례
  if(begin==end)return 0;
  queue<int> q;
  memset(c, 0, sizeof(c));
  //정방향 탐색은 양수, 역방향 탐색은 음수
  q.push(begin);
  c[begin]=1;
  q.push(end);
  c[end]=-1;
  while(!q.empty()){
    int here = q.front();
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
            if(sign(c[here])==sign(c[there])) continue;
            if(sign(c[here])*sign(c[there])==-1)return abs(c[here])+abs(c[there])-1;
            c[there] = increment(c[here]);
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
  for(int i=0;i<12;i++){
    begin=set(begin,i,0);
    end=set(end,i,3);
  }
  cout<<bis(12,begin,end)<<endl;
}