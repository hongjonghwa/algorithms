#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<time.h>

int main(){
    srand(time(NULL));
    freopen("1867-input.txt", "w", stdout);
    int n = 5, k = 10;
    std::vector<std::pair<int, int>> adj; 
    for (int i = 0 ; i < k; ++i)
        adj.push_back(std::make_pair(rand()%n+1, rand()%n+1));
    std::sort(adj.begin(), adj.end());
    adj.erase(std::unique(adj.begin(), adj.end()), adj.end());
    k = adj.size();
    printf("%d %d\n", n, k);
    for (int i = 0 ; i < k; ++i)
        printf("%d %d\n", adj[i].first, adj[i].second);
}