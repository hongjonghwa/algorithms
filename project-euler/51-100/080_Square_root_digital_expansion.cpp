#include<stdio.h>

int digit[105];
int limit[210];
int calc[210];
int digits_len = 0;

void dsp(int *a, int d){
    printf("num: ");
    for (int i = 1 ; i <=d ; ++i)
        printf("%d", a[i]);
    printf("\n");
}

int compare(int *a, int *b, int digit){
    for (int i = 0 ; i <= digit ; ++i){
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}


int sqrt(int n){
    limit[1] = n / 10;
    limit[2] = n % 10;

    for (int d = 1 ; d <= 101 ; ++d){
        for (int candidate = 9; candidate >= 0 ; --candidate){
            digit[d] = candidate;

            for (int i = 2*d ; i >= 0 ; --i) calc[i] = 0;

            for (int i = 1 ; i <= d ; ++i)
                for (int j = 1 ; j <= d ; ++j)
                    calc[i+j] += digit[i] * digit[j];

            for (int i = 2*d ; i > 0 ; --i){
                calc[i-1] += calc[i] / 10;
                calc[i] %= 10; 
            }

            int c = compare(calc, limit, 2*d);
            /*
            dsp(digit, 20);
            dsp(calc, 20);
            dsp(limit, 20);
            printf("compare: %d \n\n", c);
            */
            if (c == 0){
                printf("%d is finite number!", n);
                return 0;
            }
            if (c < 0) break; // found!
        }
    }
    int ret = 0;
    int cur = 1;
    while (digit[cur] == 0) cur++;
    for (int i = 0 ; i < 100 ; ++i)
        ret += digit[cur+i];
    
    for (int d = 1; d <= 101 ; ++d)
        printf("%d", digit[d]);
    printf("\n");
    return ret;
}

int main(){
    int answer = 0;
    for (int n = 2 ; n < 100 ; ++n){
        int r = sqrt(n);
        printf("%2d => %d\n", n, r);
        answer += r;
    }
    printf("\nAnswer is %d\n", answer);
}
