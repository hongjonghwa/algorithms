#include<stdio.h>

void report_qrc(char QRC[100][100]){
    for (int y = 0 ; y < 16 ; ++y){
        for (int x = 0 ; x < 100 ; ++x){
            if (QRC[y][x]) printf("#");
            else printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

void encode(char QRC[100][100], char SRC[100]){
    /*
    printf("ENC: ");
    for (int i = 0 ; i < 100 ; ++i) printf ("%c", SRC[i]);
    printf("\n");
    */

    bool b[500];
    for (int i = 0 ; i < 500 ; ++i) b[i] = false;
    for (int i = 0 ; i < 100 ; ++i){

        char s = SRC[i] - 'A';
        b[i*5] = s & 1;
        b[i*5+1] = s & 2;
        b[i*5+2] = s & 4;
        b[i*5+3] = s & 8;
        b[i*5+4] = s & 16;
    }

    /*
    printf("eBit: ");
    for (int i = 0 ; i < 10 ; ++i) printf ("%c", b[i] ? '1' : '0');
    printf("\n");
    */

    for (int y = 0 ; y < 4 ; ++y) for (int x = 0 ; x < 100 ; ++x) QRC[y][x] = 1;
    for (int y = 4 ; y < 100 ; ++y) for (int x = 0 ; x < 4 ; ++x) QRC[y][x] = 1;

    for (int i = 0 ; i < 500 ; ++i){
        if (b[i]){
            int dy = 6 + (i / 23) * 4, dx = 6 + (i % 23) * 4;
            for (int y = 0 ; y < 4 ; ++y) for (int x = 0 ; x < 4 ; ++x) QRC[dy+y][dx+x] = 1;
        }
    }

    //report_qrc(QRC);

}

void report_gray(char GRAY[100][100]){
    for (int y = 0 ; y < 100 ; ++y){
        for (int x = 0 ; x < 100 ; ++x){
            if (GRAY[y][x] == 0) printf(" ");
            else if (GRAY[y][x] == 1) printf(".");
            else if (GRAY[y][x] == 2) printf("|");
            else if (GRAY[y][x] == 3) printf("=");
            else if (GRAY[y][x] == 4) printf("#");
            //printf ("%d", GRAY[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void find_root(int &root_y, int &root_x, char GRAY[100][100]){
    root_y = -1, root_x = -1;
    for (int y = 0 ; y < 100 && root_y == -1; ++y){
        int count = 0;
        for (int x = 0 ; x < 100 && root_y == -1; ++x){
            if (GRAY[y][x] == 4) count++;
            else count = 0;
            if (count >= 10){
                bool f = true;
                for (int i = 1 ; i < 10 ; ++i){
                    if (GRAY[y+i][x-9] != 4){
                        //printf("#");
                        f = false;
                        break;
                    }
                }
                if (f){
                    root_y = y;
                    root_x = x-9;
                }
            }
        }
    }
}
bool is_set(int idx, int root_y, int root_x, bool odd_y, bool odd_x, char GRAY[100][100]){

    int dy = root_y + 3 + (idx / 23 ) * 2;
    int dx = root_x + 3 + (idx % 23 ) * 2;

    if (odd_y && odd_x){
        //printf("EE");
       if (GRAY[dy][dx] != 4) return false;
       if (GRAY[dy][dx-1] < 2) return false;
       if (GRAY[dy][dx+1] < 2) return false;
       if (GRAY[dy+1][dx] < 2) return false;
       if (GRAY[dy-1][dx] < 2) return false;
       if (GRAY[dy+1][dx+1] == 0) return false;
       if (GRAY[dy+1][dx-1] == 0) return false;
       if (GRAY[dy-1][dx+1] == 0) return false;
       if (GRAY[dy-1][dx-1] == 0) return false;
       return true;
    }

    if (odd_y){
        //printf("OY, dy %d, dx %d, \n", dy, dx);
       if (GRAY[dy][dx] != 4 || GRAY[dy][dx+1] != 4) return false;
       if (GRAY[dy-1][dx] < 2 || GRAY[dy-1][dx+1] < 2) return false;
       if (GRAY[dy+1][dx] < 2 || GRAY[dy+1][dx+1] < 2) return false;
       return true;
    }
    if (odd_x){
        //printf("Ox");
       if (GRAY[dy][dx] != 4 || GRAY[dy+1][dx] != 4) return false;
       if (GRAY[dy][dx-1] < 2 || GRAY[dy+1][dx-1] < 2) return false;
       if (GRAY[dy][dx+1] < 2 || GRAY[dy+1][dx+1] < 2) return false;
       return true;
    }

    // all even
    if (GRAY[dy][dx] != 4) return false;
    if (GRAY[dy][dx+1] != 4) return false;
    if (GRAY[dy+1][dx] != 4) return false;
    if (GRAY[dy+1][dx+1] != 4) return false;
    return true;
}
void decode(char GRAY[100][100], char DST[100]){
    //report_gray(GRAY);

    int root_y, root_x;
    find_root(root_y, root_x, GRAY);
    //printf(" ROOT : %d %d \n", root_y, root_x);

    bool odd_y = false, odd_x = false;
    for (int i = 1 ; i < 10 ; ++i)
        if (GRAY[root_y+1][root_x+i] != 4){
            odd_y = true;
            break;
        }
    for (int i = 1 ; i < 10 ; ++i)
        if (GRAY[root_y+i][root_x+1] != 4){
            odd_x = true;
            break;
        }

    /*
    printf("Odd: %d %d \n", odd_y, odd_x);
    printf("dBit: ");
    for (int i = 0 ; i < 10 ; ++i) printf ("%c", is_set(i, root_y, root_x, odd_y, odd_x, GRAY) ? '1' : '0');
    printf("\n");
    */

    for (int i = 0 ; i < 100 ; ++i){
        DST[i] = 'A';
        if ( is_set(i*5,  root_y, root_x, odd_y, odd_x, GRAY) ) DST[i]++;
        if ( is_set(i*5+1,  root_y, root_x, odd_y, odd_x, GRAY) ) DST[i] += 2;
        if ( is_set(i*5+2,  root_y, root_x, odd_y, odd_x, GRAY) ) DST[i] += 4;
        if ( is_set(i*5+3,  root_y, root_x, odd_y, odd_x, GRAY) ) DST[i] += 8;
        if ( is_set(i*5+4,  root_y, root_x, odd_y, odd_x, GRAY) ) DST[i] += 16;
        
    }

    /*
    printf("DEC: ");
    for (int i = 0 ; i < 100 ; ++i) printf ("%c", DST[i]);
    printf("\n");
    */

}
