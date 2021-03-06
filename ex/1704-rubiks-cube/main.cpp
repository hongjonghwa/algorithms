#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include "Cube.hpp"

using namespace std;

void test(int cubies[9][6]);


//int cube[6][3][3]; // originial
int cubies[9][6];

void rotate(int face, int direction, int cubies[9][6]){
    switch(face){
        case 0:
            cube_F(direction==0 ? 1 : 3, cubies);
            break;
        case 1:
            cube_U(direction==0 ? 1 : 3, cubies);
            break;
        case 2:
            cube_R(direction==0 ? 1 : 3, cubies);
            break;
        case 3:
            cube_D(direction==0 ? 1 : 3, cubies);
            break;
        case 4:
            cube_L(direction==0 ? 1 : 3, cubies);
            break;
        case 5:
            cube_B(direction==0 ? 1 : 3, cubies);
            break;
    }
}

bool is_correct(int cubies[9][6]){
    for (int i = 0 ; i < 6 ; ++i)
        for (int j = 0 ; j < 9 ; ++j)
            if (cubies[j][i] != i)
                return false;
    return true;
}

void init_cube(){
    cube_init(cubies);
    for (int i = 0 ; i < 10 ; ++i){
        int f = rand() % 6;
        int d = rand() % 2;
        rotate (f, d, cubies);
    }
}

void test(){
    cube_init(cubies);
    
    for (int i = 0 ; i < 6 ; ++i)
        for (int j = 0 ; j < 2 ; ++j){
            for (int k = 0 ; k < 3 ; ++k ) {
                rotate(i,j, cubies);
                assert(cube_is_correct(cubies) == false);
            }
            rotate(i,j, cubies);
            assert(cube_is_correct(cubies) == true);
        }

    for (int i = 0 ; i < 9 ; ++i)
        for (int j = 0 ; j < 6 ; ++j)
            assert(cubies[i][j] == j);
}

int main(){
    srand(42);
    // test();

    for (int t = 0 ; t < 10 ; ++t){
        printf("[run round : %d] \n", t+1);
        init_cube();
        test(cubies);
        //cube_output(cubies);

        if (is_correct(cubies)) ; // printf("SUCCESS\n");
        else printf("FAILED\n");
        //if (t == 0) break;
    }
}
