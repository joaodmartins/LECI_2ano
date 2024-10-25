#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int coin_row_rec(int coins[], int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return coins[1];
    } else {
        return max(coins[n] + coin_row_rec(coins, n - 2), coin_row_rec(coins, n - 1));
    }
}

int main() {
    int coins[] = {0, 5, 1, 2, 10, 6, 2};
    printf("Soluçao otima: %d\n", coin_row_rec(coins, 6));
    return 0;
}
