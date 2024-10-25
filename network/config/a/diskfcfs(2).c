#include <stdio.h>

int main() {
    int i, sum = 0, n, disk;
    int ar[20], tm[20];

    printf("Enter number of requests ");
    scanf("%d", &n);

    printf("Enter initial head position : ");
    scanf("%d", &disk);

    printf("Enter the request sequence :\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &ar[i]);
        tm[i] = disk - ar[i];
        if (tm[i] < 0) {
            tm[i] = ar[i] - disk;
        }
        disk = ar[i];
        sum += tm[i];
    }

    printf("Movement of total cylinders: %d\n", sum);

    return 0;
}


