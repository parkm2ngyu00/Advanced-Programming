# 소풍 (Picnic)

꿈 유치원 익스프레스반에서는 다음 주에 하늘공원으로 소풍을 갑니다. 존 선생님은 소풍 때 학생들을 두명씩 짝을 지어 행동하게 하려고 합니다. 그런데 서로 친구가 아닌 학생들끼리 짝을 지어 주면 서로 싸우거나 같이 돌아 다니지 않기 때문에, 항상 서로 친구인 학생들끼리만 짝을 지어야 합니다.

The Express class at Dream kindergarten goes on a picnic to Sky Park next week. Teacher John wants to have his students act in pairs on a picnic. However, if he pairs students who are not friends, they will fight each other or not walk around together. Thus, he should always pair students who are friends with each other.

각 학생들의 쌍에 대해 이들이 서로 친구인지 여부가 주어질 때, 학생들을 짝 지을 수 있는 방법의 수를 계산하는 프로그램을 작성하세요. 짝이 되는 학생들이 일부만 다르더라도 다른 방법이라고 봅니다. 예를 들어 다음 두 가지 방법은 서로 다른 방법입니다.

Write a program that counts the number of ways students can be paired, given whether they are friends with each other for each pair of the students. Even if the pair of students differ only in part, we see it as a different way. For example, the following two ways are different.

```
(Tom, Jenny)(Sunny, Phil)(Jimmy, Susan)
(Tom, Jenny)(Sunny, Susan)(Jimmy, Phil)
```

# 입력 (Input)

입력 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다.

The first line of input is given the number of test cases C (C<=50).

각 테스트 케이스의 첫 줄에는 학생의 수 n(2<=n<=10)과 친구 쌍의 수 m(0<=m<=n(n-1)/2)이 주어집니다.

The first line of each test case is given the number of students, n (2<=n<=10), and the number of pairs of friends, m (0<=m<=n(n-1)/2).

그 다음 줄에 m개의 정수 쌍으로 서로 친구인 두 학생의 번호가 주어집니다. 번호는 모두 0부터 n-1사이의 정수이고, 같은 쌍은 입력에 두 번 주어지지 않습니다. 학생들의 수는 짝수입니다.

Then, the next line is given the numbers of two students who are friends with each other as m pairs of integers. The numbers are all integers between 0 and n-1. Also, the same pair is not given twice in the input. The number of students are even.

# 출력 (Output)

각 테스트 케이스마다 한 줄에 모든 학생을 친구끼리만 짝지어줄 수 있는 방법의 수를 출력합니다.

For each test case, print the number of ways in which all students can only be paired with friends on one line.

예제 입력 (Sample Input)

```
3
2 1
0 1
4 6
0 1 1 2 2 3 3 0 0 2 1 3
6 10
0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5
```

예제 출력 (Sample Output)

```
1
3
4
```
