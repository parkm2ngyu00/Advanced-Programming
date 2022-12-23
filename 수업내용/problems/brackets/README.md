# 짝이 맞지 않는 괄호 (Brackets)

주어진 수식의 괄호가 쌍이 잘 맞는지 확인하고자 하며, 세 종류의 괄호가 사용됩니다.

We want to check if all brackets in a given formular match well, and there are three types of brackets used.

소괄호는 (로 열고, )로 닫습니다.

Round brackets open with (, close with ).

중괄호는 {로 열고, }로 닫습니다.

Curly brackets are opened with { and closed with }.

대괄호는 [로 열고, ]로 닫습니다.

Square brackets are opened with [ and closed with ].

수식에 있는 괄호들이 다음과 같은 성질을 모두 만족할 때 해당 수식 내 괄호가 '쌍이 맞는다' 라고 표현합니다.

When the brackets in the formula satisfy all of the following properties, the brackets in the formula are said to be 'paired'.

- 모든 괄호는 해당하는 짝이 있어야 합니다.
- 모든 괄호 쌍은 먼저 열린 뒤 닫힙니다.
- 한 괄호 쌍이 다른 괄호 쌍과 서로 교차해 있으면 안 됩니다.
    - 예를 들어 [(])는 짝이 맞지 않는 경우입니다.

- All brackets must have a corresponding pair.
- All pairs of brackets are first opened and then closed.
- One pair of brackets must not intersect with another pair of brackets.
    - For example, [(]) is not a match.

입력 받은 수식들이 짝이 잘 맞는지 확인하는 프로그램을 작성합니다.

Write a program that checks if the given formulas match well.

문제를 간소화하기 위해 괄호 외 문자는 모두 제거된 상태입니다.

All non-brackets characters are removed to simplify the problem.

# 입력 (Input)

입력 첫 줄에는 테스트 케이스의 수 C(C<=100)가 주어집니다.

The first line of input is given the number of test cases C (C<=100).

각 테스트 케이스는 하나의 문자열이 주어집니다.

Each test case is given one string.

이 문자열은 공백 없이 "(){}[]"에 포함된 문자로만 구성되며, 길이는 1이상 10,000 이하입니다.

The string consists only of characters contained "(){}[]" without spaces, and has a length of 1 or more and 10,000 or less.

# 출력 (Output)

각 테스트 케이스마다, 주어진 괄호 문자열이 짝이 잘 맞는다면 "YES"를, 안 맞는다면 "NO"를 출력합니다.

For each test case, print "YES" if the given string matches well, and "NO" if not.

예제 입력 (Sample Input)

```
3
()()
({[}])
({}[(){}])
```

예제 출력 (Sample Output)

```
YES
NO
YES
```
