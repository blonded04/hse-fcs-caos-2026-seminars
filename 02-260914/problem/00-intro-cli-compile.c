#include <stdio.h>

int main(void) {
    int x;
    scanf("%d", &x);
    long long result = 0;
    for (int i = 1; i <= x; i++) {
        result += i;
    }
    printf("%lld\n", result);
    return 0;
}
