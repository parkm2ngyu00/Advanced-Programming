#include <stdio.h>

typedef struct _time {
    int hours;
    int minutes;
    int seconds;
} time;

int main(void) {
    int test_case;
    scanf("%d", &test_case);
    int i;
    for (i=0; i<test_case; i++) {
        time time;
        int T;
        scanf("%d %d %d %d", &time.hours, &time.minutes, &time.seconds, &T);
        time.seconds += T;
        time.minutes += time.seconds / 60;
        time.seconds %= 60;
        time.hours += time.minutes / 60;
        time.minutes %= 60;
        while (time.hours > 24)
        {
            time.hours -= 24;
        }
        
        printf("%d %d %d\n", time.hours, time.minutes, time.seconds);
    }
    return 0;
}