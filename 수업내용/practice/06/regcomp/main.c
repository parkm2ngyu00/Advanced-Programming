#include <stdio.h>
#include <regex.h>

int main()
{
	char pattern[] = "[:word:]";
	regex_t r1;

	int ret = regcomp(&r1, pattern, 0);
	if (ret == 0) {
		printf("Compiled %s successfully\n", pattern);
	} else {
		printf("Failed to compile %s\n", pattern);
	}

	return 0;
}
