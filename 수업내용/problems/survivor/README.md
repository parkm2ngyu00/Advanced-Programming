# 생존자 (Survivor)

1세기에 살던 역사학자 조세푸스는 로마와의 전행에서 패해 N-1명의 동료 병사들과 함께 출구가 없는 동굴에 포위당했다고 합니다.

It is said that the historian Josephus, who lived in the 1st century, was defeated in a battle against Rome and surrounded by N-1 fellow soldiers in a cave with no exit.

동료 병사들은 로마에 항복하느니 차라리 자살하자고 결의했습니다.

Fellow soldiers decided to commit suicide rather than surrender to Rome.

그리고, 포위당한 N명의 사람들이 모두 원형으로 둘러선 뒤 순서대로 죽기로 했습니다.

After all N men besieged in a circle, they then decided to die in order.

한 사람이 죽으면, 다음에는 그 사람으로 부터 시계 방향으로 K번째 살아 있는 사람이 죽기로 하였다고 합니다.

When one person dies, the next K-th living person in a clockwise direction from that person is to die.

조세푸스의 책에 따르면 조세푸스와 다른 병사 하나만이 살아남았을 때 이들은 마음을 바꿔 로마에 항복해서 살아남았다고 합니다.

According to Josephus' book, when Josephus and the other soldiers only survived, they changed their minds and surrendered to Rome and survived.

마지막 두 명 중 하나가 되기 위해서는 조세푸스는 첫 번째 병사로부터 몇 자리 떨어진 곳에 있어야 했을까요?

How many places did Josephus have to be from the first soldier to be one of the last two?

# 입력 (Input)

입력 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다.

The first line of input is given the number of test cases C (C<=50).

각 테스트 케이스는 두 개의 정수 N (3<=N<=1000), K (K<=1000)로 주어집니다.

Each test case is given by two integers N (3<=N<=1000), K (K<=1000).

# 출력 (Output)

각 테스트 케이스에 두 개의 정수로, 마지막 살아남는 두 사람의 번호를 오름차 순으로 출력합니다.

Print the numbers of the last two surviving people in ascending order, with two integers for each test case.

첫 번째로 자살하는 병사의 번호가 1이며, 다른 사람들의 번호는 첫 번째 병사에서 부터 시계 방향으로 정해집니다.

The first soldier to commit suicide is numbered 1, and the others are numbered clockwise from the first soldier.

예제 입력 (Sample Input)

```
2
6 3
40 3
```

예제 출력 (Sample Output)

```
3 5
11 26
```
