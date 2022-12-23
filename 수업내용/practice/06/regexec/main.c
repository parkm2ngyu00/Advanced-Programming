#include <stdio.h>
#include <regex.h>

int main()
{
	regex_t r1;
	int ret;

	char p1[] = "^01[016789][-]?[0-9]{3,4}[-]?[0-9]{4}$";

	char s1[] = "010-1234-5678";
	char s2[] = "017-345-7890";
	char s3[] = "01009876543";
	char s4[] = "0117892345";
	char s5[] = "02-1234-1234";

	ret = regcomp(&r1, p1, REG_EXTENDED);
	if (ret != 0) {
		printf("Failed to compile %s\n", p1);
		return -1;
	}

	ret = regexec(&r1, s1, 0, NULL, 0);
	if (ret == 0) {
		printf("Found %s\n", s1);
	} else if (ret == REG_NOMATCH) {
		printf("Failed to find %s\n", s1);
	} else {
		printf("Error!\n");
	}

	ret = regexec(&r1, s2, 0, NULL, 0);
	if (ret == 0) {
		printf("Found %s\n", s2);
	} else if (ret == REG_NOMATCH) {
		printf("Failed to find %s\n", s2);
	} else {
		printf("Error!\n");
	}

	ret = regexec(&r1, s3, 0, NULL, 0);
	if (ret == 0) {
		printf("Found %s\n", s3);
	} else if (ret == REG_NOMATCH) {
		printf("Failed to find %s\n", s3);
	} else {
		printf("Error!\n");
	}

	ret = regexec(&r1, s4, 0, NULL, 0);
	if (ret == 0) {
		printf("Found %s\n", s4);
	} else if (ret == REG_NOMATCH) {
		printf("Failed to find %s\n", s4);
	} else {
		printf("Error!\n");
	}

	ret = regexec(&r1, s5, 0, NULL, 0);
	if (ret == 0) {
		printf("Found %s\n", s5);
	} else if (ret == REG_NOMATCH) {
		printf("Failed to find %s\n", s5);
	} else {
		printf("Error!\n");
	}

	return 0;
}
