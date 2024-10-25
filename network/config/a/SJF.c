#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void main() {
    int i, j, p[20], b[20], g[20], w[20], t[20], a[20], n;
    int k = 1, min, btime = 0;
    float avgw = 0, avgt = 0;

    printf("Enter the number of process : ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nProcess id : ");
        scanf("%d", &p[i]);
        printf("Burst Time : ");
        scanf("%d", &b[i]);
        printf("ArrivalTime:");
        scanf("%d", &a[i]);
    }

    // Sort the jobs based on burst time.
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                swap(&b[j], &b[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    for (i = 0; i < n; i++) {
        btime = btime + b[i];
        min = b[k];
        for (j = k; j < n; j++) {
            if (btime >= a[j] && b[j] < min) {
                swap(&a[j], &a[j - 1]);
                swap(&b[j], &b[j - 1]);
                swap(&p[j], &p[j - 1]);
                min = b[j];
            }
        }
        k++;
    }

    g[0] = a[0];
    for (i = 0; i < n; i++) {
        g[i + 1] = g[i] + b[i];
        if (g[i] < a[i])
            g[i] = a[i]; // Ensure non-preemptive behavior
    }

    for (i = 0; i < n; i++) {
        t[i] = g[i + 1] - a[i];
        w[i] = t[i] - b[i];
        avgw += w[i];
        avgt += t[i];
    }

    avgw = avgw / n;
    avgt = avgt / n;

    printf("pid\tBrustTime\tGantChart\tWaitingtime\t\tTurnarroundTime\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d-%d\t\t%d\t\t\t%d\n", p[i], b[i], g[i], g[i + 1], w[i], t[i]);
    }
    printf("\nAverage waiting time %f", avgw);
    printf("\nAverageturnarroundtime %f\n", avgt);
}

