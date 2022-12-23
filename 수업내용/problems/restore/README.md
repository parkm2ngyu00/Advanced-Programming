# 실험 데이터 복구 (Restoring Experiment Data)

토요일에 출근해서 연구실에서 놀고 있던 대학원생 진호는 실수로 실험에 사용하던 데이터를 삭제하고 말았습니다.

Graduate student Jin-ho, who was playing in the lab on Saturday, accidentally deleted the data used for experiments.

복사본도 없는 터라 이대로라면 교수님의 진노를 한 몸에 받을 것이 자명했습니다. 그래서, 진호는 그럴 듯해 보이는 데이터를 위조하여 (실제로 따라 하지 말 것) 교수님의 분노를 피해 가기로 합니다.

Unfortunately, it was obvious that he would incur the wrath of his professor since there were no backups (copies). Thus, Jin-ho decided to forge the seemingly plausible data (don't try it) to avoid the professor's anger.

우리가 데이터에 대해 알고 있는 것은, 데이터가 k개의 문자열 조각을 부분 문자열로 포함하며, 모두 알파벳 소문자로 구성된다는 사실 밖에 없습니다. (어떤 문자열의 부분 문자열은 해당 문자열의 연속된 일부분입니다.)

All he knows about the data is that it contains k pieces of string as substrings, all of which are lowercase letters. (A substring of a string is a contiguous part of the string.)

주어진 문자열 조각들을 모두 부분 문자열로 포함하는 문자열 중 가장 짧은 것을 계산하는 프로그램을 작성하세요. 만약 이와 같은 문자열이 여럿이라면 아무 문자열이나 출력하면 됩니다.

Write a program that creates the shortest string containing all given string fragments as substrings. If there are multiple strings that can be created, print any of them.

# 입력 (Input)

입력 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다.

The first line of input is given the number of test cases C (C<=50).

각 테스트 케이스의 첫 줄에는 부분 문자열의 수 k(1<=k<=15)가 주어지고, 다음 k줄에 알파벳 소문자로만 구성된 문자열 조각이 주어집니다.

The first line of each test case is given the number of substrings k (1<=k<=15), and the next k lines are given pieces of string consisting of only lowercase letters of the alphabet.

각 문자열 조각의 길이는 1 이상 20 이하입니다.

Each string fragment is 1 or more and 20 or less in length.

# 출력 (Output)

각 테스트 케이스마다 한 줄로, 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력합니다.

For each test case, print one of the shortest strings containing all of them.

예제 입력 (Sample Input)

```
3
3
geo
oji
jing
2
world
hello
3
abrac
cadabra
dabr
```

예제 출력 (Sample Output)

```
geojing
helloworld
cadabrac
```
