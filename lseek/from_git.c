#include "libft.h"
//#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFF_SIZE 106
#define ENDL '\n'

int	read_from_fd_into_stock(int const fd, char **stock)
{
	printf("in read\n");
		static char	buff[BUFF_SIZE+1] = { ENDL };
			int			read_bytes;
			char        *nstr = NULL;

			read_bytes = read(fd, buff, BUFF_SIZE);
			if (read_bytes > 0)
			{
			    buff[read_bytes] = '\0';
			    printf("buff: %s\n", buff);
			    nstr = ft_strjoin(*stock, buff);
			    if (!nstr)
			        return (-1);
			     free(*stock);
			     *stock = nstr;
			}
			printf("nstr: %s\n", nstr);
			printf("read bytes: %d\n", read_bytes);
		return (read_bytes);
}

int get_next_line(int const fd, char ** line)
{
	printf("in gnl\n");
		static char	*stock = NULL;
		char		*endl_index;
		int         ret;

		if (!stock && (stock = (char *)ft_memalloc(sizeof(char))) == NULL)
		    return (-1);
		printf("stock: %s\n", stock);
		printf("after if\n");
		endl_index = ft_strchr(stock, ENDL);
		printf("endl_index: %s\n", endl_index);
		while (endl_index == NULL)
		{
			printf("in loop\n");
		    ret = read_from_fd_into_stock(fd, &stock);
		    if (ret == 0)
		    {
		       if ( (endl_index = ft_strchr(stock, '\0')) == stock )
		            return (0);
		    } else if (ret < 0)
		        return (-1);
			else
			endl_index = ft_strchr(stock, ENDL);
		}
			*line = ft_strsub(stock, 0, endl_index - stock);
		    if (!*line)
		        return (-1);
		    endl_index = ft_strdup(endl_index + 1);
		    free(stock);
		    stock = endl_index;
		return (1);
}
/*
int main() {
	//t_seek *elem = NULL;
	char *line;
	//int fd1 = open("test.txt", O_RDONLY);
	 int fd2 = open("test1.txt", O_RDONLY);
	// // int fd3 = open("test2.txt", O_RDONLY);
	//
	//get_next_line(fd1,&line);
	 //printf(" call line: %s\n", line);
	 get_next_line(fd2,&line);
	   printf(" call line: %s\n", line);
	//   // get_next_line(fd3,&line);
	//   // printf(" call line: %s\n", line);
	//   //printValues(elem, elementsCount(elem));
	//   get_next_line(fd1,&line);
	//   printf(" call line: %s\n", line);
	//  get_next_line(fd1,&line);
	 // printf(" call line: %s\n", line);
	 get_next_line(fd2,&line);
	 printf(" call line: %s\n", line);
	  get_next_line(fd2,&line);
	 printf(" call line: %s\n", line);
	//   // get_next_line(fd3,&line);
	//
	 //  close(fd1);
	 close(fd2);
	//   // close(fd3);
	system("leaks ggnl");
	//   /*
	//   push_elem(&elem, 3,0);
	//   push_elem(&elem, 5,0);
	//   push_elem(&elem, 13,0);
	//   printValues(elem, 2);
	//   change_pos(elem, 13, 19);
	//   change_pos(elem, 5, 1);
	//   change_pos(elem, 3, 100);
	//   printValues(elem, elementsCount(elem));
	     return 0;
	    }
*/