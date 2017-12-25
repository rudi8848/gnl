#include "get_next_line.h"
#include <fcntl.h>

int		main(void)
{
	char *line;

	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test1.txt", O_RDONLY);
	int fd3 = open("test2.txt", O_RDONLY);

	get_next_line(fd1, &line);
		printf("1 - call file 1: %s\n", line);

	get_next_line(fd2, &line);
		printf("2 - call file 2:%s\n", line);

	get_next_line(fd1, &line);
		printf("3 - call file 1:%s\n", line);

	get_next_line(fd3, &line);
		printf("4 - call file 3: %s\n", line);

	get_next_line(fd2, &line);
		printf("5 - call file 2: %s\n", line);

	get_next_line(fd1, &line);
		printf("6 - call file 1: %s\n", line);

	get_next_line(fd2, &line);
		printf("7 - call file 2:%s\n", line);

	get_next_line(fd1, &line);
		printf("8 - call file 1:%s\n", line);

	get_next_line(fd3, &line);
		printf("9 - call file 3: %s\n", line);

	get_next_line(fd2, &line);
		printf("10 - call file 2: %s\n", line);

	close(fd1);
	close(fd2);
	close(fd3);
//	system("leaks gnl");
	return 0;
}