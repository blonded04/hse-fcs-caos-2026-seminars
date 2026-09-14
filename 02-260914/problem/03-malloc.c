#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    // TODO: create arr[n] without variable-length arrays
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }

    for (int i = 0; i < n; i++) {
        assert(arr[i] == i * i);
    }
    // TODO: destroy arr[n]
}
