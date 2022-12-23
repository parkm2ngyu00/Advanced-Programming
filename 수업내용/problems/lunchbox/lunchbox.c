#include <stdio.h>

#define MAX_LUNCHBOXES 10000
#define MAX(a, b) (((a)>(b))?(a):(b))

struct lunchbox_t {
    int heating_time;
    int eating_time;
};

void quick_sort(struct lunchbox_t lunchbox[], int left, int right) {
    int L = left, R = right;
    int pivot = lunchbox[(left + right) / 2].eating_time;
    struct lunchbox_t temp;

    while (L <= R) {
        while (lunchbox[L].eating_time > pivot)
            L++;
        while (lunchbox[R].eating_time < pivot)
            R--;

        if (L <= R) {
            if (L != R) {
                temp = lunchbox[L];
                lunchbox[L] = lunchbox[R];
                lunchbox[R] = temp;
            }

            L++;
            R--;
        }
    }

    if (left < R)
        quick_sort(lunchbox, left, R);
    if (L < right)
        quick_sort(lunchbox, L, right);
}

int shortest_time(int num_of_lunchboxes, struct lunchbox_t lunchbox[])
{
    int total_time = lunchbox[0].heating_time;
    int i;
    
    for (i=0; i<num_of_lunchboxes; i++) {
        if (lunchbox[i+1].heating_time > lunchbox[i].eating_time) {
            total_time += lunchbox[i+1].heating_time;
        } else {
            total_time += lunchbox[i].eating_time;
        }
    }

    return total_time;
}

int main(void)
{
    int num_of_cases = 0;

    scanf("%d", &num_of_cases);

    if (num_of_cases < 1 || num_of_cases > 300) {
        return -1;
    }

    int i;
    for (i=0; i<num_of_cases; i++) {
        int num_of_lunchboxes = 0;
        int num_of_pairs = 0;
        
        scanf("%d", &num_of_lunchboxes);

        if (num_of_lunchboxes < 1 || num_of_lunchboxes > MAX_LUNCHBOXES) {
            return -1;
        }

        struct lunchbox_t lunchbox[MAX_LUNCHBOXES];
        
        int j;
        for (j=0; j<num_of_lunchboxes; j++) {
            scanf("%d", &lunchbox[j].heating_time);
        }
        for (j=0; j<num_of_lunchboxes; j++) {
            scanf("%d", &lunchbox[j].eating_time);
        }

        quick_sort(lunchbox, 0, num_of_lunchboxes-1);
        
        printf("%d\n", shortest_time(num_of_lunchboxes, lunchbox));
    }

    return 0;
}