#include <stdio.h>
#include "Cube.hpp"

//#define BINS 3257437
//#define BINS 3999971
// #define BINS 2999711
#define BINS 1932611

void rotate(int face, int direction, int cubies[9][6]);

bool initiated = false;

struct X{
    int hash, face, direction, parent; //parent 는 이전 상태임
} x[3257437]; // 역방향 탐색은 상태공간이 필요없음
int x_idx = 0;
int trial = 0;

struct Node{
    int idx;
    Node * next;
} node[BINS];
Node *head[BINS];

int hash(int cubies[9][6]){
    unsigned int ret = 0;

    /* 
    // 심플한 버전
    for (int i = 0 ; i < 9 ; ++i){
        for (int j = 0 ; j < 6 ; ++j)
            ret = ret * 31 + cubies[i][j];
    }    
    ret %= BINS;
    */
    // trick : 나눗셈 최소로 조금 더 빠르게
    for (int j = 0 ; j < 6 ; ++j){
        for (int i = 0 ; i < 4 ; ++i)
            ret = ret * 7 + cubies[i][j];
        for (int i = 5 ; i < 9 ; ++i)
            ret = ret * 7 + cubies[i][j];
        // hashing 에서 overflow 는 관심사항이 아니다.
    }
    ret %= BINS;
    return ret ;
}

// face, direction 은 직전 회전 위치 -> 되돌아가지 않기 위해
void bt(int cubies[9][6], int face, int direction, int parent, int lvl){
    int cur = x_idx++;
    // struct x 에 데이터 값을 저장하고,
    int h = hash(cubies);
    x[cur].hash = h;
    x[cur].face = face;
    x[cur].direction = direction;
    x[cur].parent = parent;
    //printf( "INIT: %d %d %d %d %d %d \n", cur, h, face, direction, parent, lvl);
    //cube_output(cubies);

    // node 에 linked list 형태로 데이터를 적재한다.
    node[cur].idx = cur;
    node[cur].next = head[h];
    head[h] = &node[cur];

    // linked list 끝단에 붙이는 것은 시간만 더 걸린다.  hash 값 충돌시 쌓는데 시간 소요( 충돌이 많을 시 더욱 치명적)
    /*
    if (!head[h]){ //  첫 입력
        node[idx].idx = cur;
        node[idx].next = 0;
        head[h] = &node[idx];
    }else{
        Node *p = head[h];
        while(p->next) {p = p->next;}
        node[idx].idx = cur;
        node[idx].next = 0;
        p->next = &node[idx];
    }
    */


    if (lvl == 5) return;
    for (int i = 0 ; i < 6; ++i){
        rotate(i, 0, cubies);
        if (!(i == face && direction == 1)) 
            bt(cubies, i, 0, cur, lvl + 1);
        rotate(i, 0, cubies);
        rotate(i, 0, cubies);
        if (!(i == face && direction == 0)) 
            bt(cubies, i, 1, cur, lvl + 1);
        rotate(i, 0, cubies);
    }
}

void init(){
    int cubies[9][6];
    for (int i = 0 ; i < 9 ; ++i)
        for (int j = 0 ; j < 6 ; ++j)
            cubies[i][j] = j;
    bt(cubies, -1, -1, -1, 0);
    printf("Initialize counting : %d \n", x_idx);
}

bool simulate(int cubies[9][6], int idx){
    int myCubies[9][6];
    for (int i = 0 ; i < 9 ; ++i) for (int j = 0 ; j < 6 ; ++j) myCubies[i][j] = cubies[i][j];
    // 하나씩 따라가 본다.
    while(idx){
        rotate(x[idx].face,!x[idx].direction, myCubies);
        idx = x[idx].parent;
        if (x[idx].hash != hash(myCubies)) return false;
    }
    
    // 모든 면이 돌아왔는지 확인한다.
    for (int i = 0 ; i < 9 ; ++i) for (int j = 0 ; j < 6 ; ++j) if (myCubies[i][j] != j) return false;
    return true;

}

void run(int cubies[9][6], int idx){
    while(idx){ // idx 0 은 정상 상태임 
        rotate(x[idx].face,!x[idx].direction, cubies);
        idx = x[idx].parent;
    }
}

bool try_bt(int cubies[9][6], int face, int direction, int lvl){
    int h = hash(cubies);
    trial++;

    if (head[h]){ // 답이 있는지 (일치하는 해시가 있는지)
        for (Node *p = head[h];p; p=p->next){

            if (simulate(cubies, p->idx)){
                printf("Solution found! "); // 답을 찾았다.
                run(cubies, p->idx); // 이제 큐브를 돌리자.
                return true;
            }
        }
    }

    if (lvl == 5) return false;
    bool founded = false;
    for (int i = 0 ; i < 6; ++i){
        rotate(i, 0, cubies);
        if ( !(i == face && direction == 1) ) 
            founded = try_bt(cubies, i, 0, lvl + 1);
        if (founded) return true;

        rotate(i, 0, cubies);
        rotate(i, 0, cubies);
        if ( !(i == face && direction == 0) ) 
            founded = try_bt(cubies, i, 1, lvl + 1);
        if (founded) return true;
        rotate(i, 0, cubies);
    }
    return false;
}

int cum_trial = 0;
void test(int cubies[9][6]){

    if (!initiated) { init(); initiated = true; }

    trial = 0;
    try_bt(cubies, -1, -1, 0);
    cum_trial += trial;

    printf("Trial: %d (cumulative %d) \n", trial, cum_trial);
}