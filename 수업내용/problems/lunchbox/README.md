# 도시락 데우기 (Heating Lunchboxes)

안나는 알고리즘 겨울 캠프를 진행하며 점심으로 n개의 도시락을 주문하였습니다. 주문량이 많아서 한 가지 도시락만 주문할 수 없었기 때문에 여러 도시락을 주문해야 했습니다. 안나는 도착한 도시락을 모두 냉장고에 넣어 두었습니다.

Anna ordered n lunchboxes for lunch while conducting an algorithm winter camp. Due to the high volume of orders, she could not order only one kind of lunchbox, so she had to order several lunchboxes. Then, Anna put all the lunchboxes that had arrived in the refrigerator.

점심 시간이 거의 다 되어서야 안나는 도시락을 데울 수 있는 전자레인지가 하나 밖에 없다는 사실을 깨달았습니다. 설상가상으로 이 전자레인지의 출력이 작기 대문에 한 번에 한 개의 도시락 밖에 데울 수 없습니다. i번째 도시락을 데우는 데는 m_i초가 걸리고, 먹는 데는 e_i초가 걸립니다.

It was almost the time for lunch, and Anna realized that she had only one microwave to heat lunchboxes. To make matters worse, the microwave can only heat one lunchbox at once. It takes m_i seconds to heat the i_th lunchbox and e_i seconds it it.

도시락은 전자레인지 밖에 나오면 빠르게 식기 때문에, 도시락을 두번에 나누어 데울 수는 없습니다. 예를 들어 데우는 데 20초 걸리는 도시락을 10초씩 나누어 데우기는 불가능합니다. 도시락은 식으면 맛이 없기 때문에, 각 사람은 자기 도시락을 다 데우는 대로 다른 사람들을 기다리지 않고 곧장 먹기 시작합니다.

Since the lunchbox cools quickly when taken out of the microwave, it is not possible to reheat the lunchbox in two. For example, it is impossible to heat a lunchbox that takes 20 seconds to heat for 10 seconds and heat for 10 seconds again. Also, since the lunchbox would be tasteless when cold, people start eating their lunchboxes without waiting for others as soon as they get their lunchboxes.

안나는 점심을 먹는 데 걸리는 시간을 최소화하는 계획을 짜고 싶습니다. 점심을 먹는 데 걸리는 시간이란 첫 번째 도시락을 데우기 시작할 때부터 모든 사람이 도시락을 다 먹을 때까지 걸리는 시간을 의미합니다.

Anna wants to come up with a plan that minimizes the time it takes to eat lunch. The time it takes to eat lunch is the amount of time it takes from the time the first lunchbox is heated until everyone has finished lunch.

어느 순서로 도시락을 데워야 가장 빨리 점심을 마칠 수 있을지 결정하는 프로그램을 작성하세요.

Write a program to determine in which order the lunchboxes need to be heated to finish lunch as fast as possible.

# 입력 (Input)

입력 첫 줄에는 테스트 케이스의 수 C(C<=300)가 주어집니다.

The first line of input is given the number of test cases C (C<=300).

각 테스트 케이스는 세 줄로 구성됩니다.

Each test case consists of three lines.

첫 줄에는 도시락의 수 n (1<=n<=10000)이 주어집니다.

The first line is given the number n of lunchboxes.

두번째 줄에는 n개의 정수로 각 도시락을 데우는 데 걸리는 시간이 주어집니다.

The second line is n integers giving the time it takes to heat each lunchbox.

세번째 줄에는 역시 n개의 정수로 각 도시락을 먹는 데 걸리는 시간이 주어집니다.

The third line is n integers giving the time it takes to eat each lunchbox.

# 출력 (Output)

각 테스트 케이스마다 한 줄에 접심을 먹는 데 걸리는 최소 시간을 출력합니다.

For each test case, print the minimum time it takes to eat lunchboxes on one line.

이 값은 항상 2^31 보다 작습니다.

The value is always less than 2^31.

예제 입력 (Sample Input)

```
2
3
2 2 2
2 2 2
3
1 2 3
1 2 1
```

예제 출력 (Sample Output)

```
8
7
```
