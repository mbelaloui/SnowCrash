#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{

	if (argc != 2)
		return (0);
	int len = strlen(argv[1]);
	int i = 0;
	while(i < len)
	{
		printf("%d - %d  %d  %c \n", 
				((char)argv[1][i]),
				i,
				((char)argv[1][i]) - i,
				((char)argv[1][i]) - i);
		i++;
	}
	printf("\n");
	return (0);
}
