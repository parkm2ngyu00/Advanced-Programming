#include <stdio.h>

int get_pairs(int num_of_students, int friends[10][10], int selected[10])
{
    int p1 = -1, p2, ret = 0;

    int i;
    for (i=0; i<num_of_students; i++) {
        if (!selected[i]) {
            p1 = i;
            break;
        }
    }

    if (p1 == -1) {
        return 1;
    }

    for (p2=p1+1; p2<num_of_students; p2++) {
        if (!selected[p1] && !selected[p2] && friends[p1][p2]) {
            selected[p1] = 1;
            selected[p2] = 1;

            ret += get_pairs(num_of_students, friends, selected);

            selected[p1] = 0;
            selected[p2] = 0;
        }
    }

    return ret;
}

int main()
{
    int num_of_cases = 0;

    scanf("%d", &num_of_cases);

    if (num_of_cases < 1 || num_of_cases > 50) {
        return -1;
    }

    int i;
    for (i=0; i<num_of_cases; i++) {
        int num_of_students = 0;
        int num_of_pairs = 0;

        scanf("%d %d", &num_of_students, &num_of_pairs);

        if (num_of_students % 2 != 0) {
            return -1;
        }

        if (num_of_students < 2 || num_of_students > 10) {
            return -1;
        }

        if (num_of_pairs < 0 || num_of_pairs > (num_of_students*(num_of_students-1)/2)) {
            return -1;
        }

        int friends[10][10] = {{0}};

        int j;
        for (j=0; j<num_of_pairs; j++) {
            int p1, p2;

            scanf("%d %d", &p1, &p2);

            if (p1 < 0 || p1 > num_of_students-1) {
                return -1;
            }

            if (p2 < 0 || p2 > num_of_students-1) {
                return -1;
            }

            friends[p1][p2] = 1;
            friends[p2][p1] = 1;
        }

        int selected[10] = {0};

        printf("%d\n", get_pairs(num_of_students, friends, selected));
    }

    return 0;
}
