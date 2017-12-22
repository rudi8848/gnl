#include "get_next_line.h"
#include <fcntl.h>

int		main(void)
{
	char *line;

	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test1.txt", O_RDONLY);
	int fd3 = open("test2.txt", O_RDONLY);

	get_next_line(fd1, &line);
		printf("call file 1: %s\n", line);

	get_next_line(fd2, &line);
		printf("call file 2:%s\n", line);

	get_next_line(fd1, &line);
		printf("call file 1:%s\n", line);

	get_next_line(fd3, &line);
		printf("call file 3: %s\n", line);

	get_next_line(fd2, &line);
		printf("call file 2: %s\n", line);

	get_next_line(fd1, &line);
		printf("call file 1: %s\n", line);

	get_next_line(fd2, &line);
		printf("call file 2:%s\n", line);

	get_next_line(fd1, &line);
		printf("call file 1:%s\n", line);

	get_next_line(fd3, &line);
		printf("call file 3: %s\n", line);

	get_next_line(fd2, &line);
		printf("call file 2: %s\n", line);

	close(fd1);
	close(fd2);
	close(fd3);
//	system("leaks gnl");
	return 0;
}