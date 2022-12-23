# 졸업 학기 (Graduation)

태우는 "1학년은 노는 게 남는 것"이라는 선배의 말을 믿고, 전공 과목은 다 수강취소하고 교양 과목은 다 F를 받은 방탕한 1학년 생활을 보냈습니다. 하지만, 졸업 전에 채워야 할 학점이 너무 많다는 사실을 알고 뒤늦게 자신의 행동을 후회하고 있습니다.

Taewoo believed his senior’s words, “In the first year, there is nothing left to do but play.” So, he dropped out of all his major subjects and received F in all general elective subjects, and spent a dissolute first year life. Unfortunately, he later regrets his actions after realizing that he has too many credits to complete before graduation.

졸업 필수 학점을 채우려면 전공 과목 N 개 중 K 개 이상을 수강해야 합니다.

He must take at least K out of N major subjects to meet graduation requirements.

그런데 각 과목은 해당 과목의 선수 과목을 미리 수강 했어야만 수강할 수 있으며, 각 학기마다 모든 과목이 개설되는 것이 아니기 때문에 문제가 복잡해졌습니다.

However, each subject can only be taken if you have taken the prerequisites for that subject in advance, and the problem is complicated because not all subjects are opened each semester.

어떻게 해야 최소 학기에 졸업을 할 수 있을까요?

How can he graduate in the fewest semester?

각 과목의 정보와 앞으로 M 학기 동안 개설될 과목의 목록이 주어질 때, 태우가 최소 몇 학기를 다녀야 졸업할 수 있는지 계산하는 프로그램을 작성하세요.

Write a program that calculates the minimum number of semesters that Taewoo must take to graduate, given information about each subject and a list of subjects that will be offered in the next M semesters.

한 과목도 수강하지 않는 학기는 휴학한 것으로 하며, 다닌 학기 수에 포함되지 않습니다.

Note that a semester in which no subject is taken is considered a leave of absence and is not included in the number of semesters attended.

# 입력 (Input)

입력의 첫 줄에는 테스트 케이스의 수 C (C<=50)가 주어집니다.

The first line of input gives the number of test cases C (C<=50).

각 테스트 케이스의 첫 줄에는 전공 과목의 수 N (1<=N<=12), 들어야 할 과목의 수 K (0<=K<=N), 학기의 수 M (1<=M<=10)과 태우가 한 학기에 최대로 들을 수 있는 과목의 수 L(1<=L<=10)이 주어집니다.

In the first line of each test case, the number of major subjects N (1<=N<=12), the number of subjects to be taken K (0<=K<=N), and the number of semesters M (1<=M<=10) and the maximum number of subjects L (1<=L<=10) that Taewoo can take in one semester are given.

각 과목에는 0부터 N-1까지의 번호가 매겨져 있습니다.

Each subject is numbered from 0 to N-1.

이후 N 줄에 0번 과목부터 순서대로 각 과목의 정보가 주어집니다.

In the following N lines, the information of each subject is given in order from subject number 0.

이 줄에는 해당 과목의 선수 과목의 수 R_i (0<=R_i<=N-1)가 처음 주어지고, 그 후 R_i 개의 정수로 선수 과목의 번호가 주어집니다.

In this line, the number of prerequisites R_i (0<=R_i<=N-1) for each subject is first given, followed by prerequisites (subjects).

이후 M 줄에는 이번 학기부터 순서대로 각 학기의 정보가 주어집니다.

In the following M line, the information of each semester is given in order starting from this semester.

각 줄에는 해당 학기에 개설되는 과목의 수 C_i (1<=C_i<=10)가 주어지고, 그 후 C_i 개의 개설되는 과목의 번호들이 주어집니다.

In each line, the number of courses C_i (1<=C_i<=10) offered in the semester is given, followed by subjects offered.

# 출력 (Output)

각 테스트 케이스마다 한 줄에 태우가 다녀야 할 최소 학기 수를 출력합니다.

On a single line, print the minimum number of semesters that Taewoo must attend.

M 학기 내에 졸업할 수 없는 경우 IMPOSSIBLE을 출력합니다.

If he cannot graduate within M semesters, print "IMPOSSIBLE".

예제 입력 (Sample Input)

```
2               # 테스트 케이스 2개
4 4 4 4         # 전공과목 4, 들어야 할 과목 4, 학기 수 4, 최대 수강 가능 과목 수 4
0               # 0번 과목의 선수과목 수 0
1 0             # 1번 과목의 선수과목 수 1, 선수과목 0
3 0 1 3         # 2번 과목의 선수과목 수 3, 선수과목 0, 1, 3
0               # 3번 과목의 선수과목 수 0
4 0 1 2 3       # 1학기 개설 과목 수 4, 개설 과목 0, 1, 2, 3
4 0 1 2 3       # 2학기 개설 과목 수 4, 개설 과목 0, 1, 2, 3
3 0 1 3         # 3학기 개설 과목 수 3, 개설 과목 0, 1, 3
4 0 1 2 3       # 4학기 개설 과목 수 4, 개설 과목 0, 1, 2, 3
4 2 2 4
1 1
0
1 3
1 2
3 0 2 3
3 1 2 3
```

첫번째 테스트 케이스에서는 첫 학기 0번 과목, 3번 과목을 듣고, 두번째 학기에는 1번 과목을 들은 뒤, 네 번째 학기에 2번 과목을 들으면 됩니다. 세 번째 학기에는 2번 과목이 개설되지 않으므로 다니지 않아도 됩니다.

두번째 테스트 케이스에서는 2번과 3번 과목이 서로 선수과목으로 지정되어 있기 때문에 두 과목은 들을 수 없습니다. 0번 과목을 듣기 위해 1번 과목을 미리 들어야 하므로, 첫 번째 학기에는 아무 것도 들을 수 없습니다. 두번째 학기에 1번 과목을 듣더라도 2학기 내에 졸업할 수 없습니다.

예제 출력 (Sample Output)

```
3
IMPOSSIBLE
```
