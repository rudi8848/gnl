#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

# define BUFF_SIZE 2

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

///////////////ДЛЯ ВИЗУАЛИЗАЦИИ////////////////
///////////////////////////////////////////////
int elementsCount(t_list *head)
	{
		int i = 0;
		if (!head)
			return 0;
		while(head->next)
		{
			head = head->next;
			i++;
		}
		//printf("%i\n", i);
		return (i);
	}

void printValues(t_list *head, int last)
	{
		printf("==========now the list is==========\n");
		int i = 0;
		printf("%zu --> ", head->content_size);
		while (i < last)
		{
			head = head->next;
			printf("%zu --> ", head->content_size);
			i++;
		}
		printf("NULL\n===================================\n");
	}
	//////////////////////////////////////////
	//////////////////////////////////////////
	size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}


	char	*ft_strchr(const char *str, int c)
{
	char			*ptr;
	unsigned char	find;
	int				i;

	i = 0;
	ptr = (char*)str;
	find = (unsigned char)c;
	if (find == '\0')
		return (ptr + ft_strlen(str));
	else
	{
		while (str[i])
		{
			if (ptr[i] == find)
				return (ptr + i);
			i++;
		}
	}
	return (NULL);
}

char			*ft_strrchr(const char *str, int c)
{
	char			*ptr;
	unsigned char	find;
	int				i;

	i = ft_strlen(str);
	ptr = (char*)str;
	find = (unsigned char)c;
	while (i >= 0)
	{
		if (ptr[i] == find)
			return (ptr + i);
		i--;
	}
	return (NULL);
}


	void	ft_bzero(void *s, size_t n)
{
	char				*ptr;
	size_t				i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;

	i = 0;
	ft_bzero(dst, len);
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_strnew(size_t size)
{
	char		*str;

	str = (char*)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}


char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;

	i = 0;
	if (s)
	{
		sub = ft_strnew(len);
		if (!sub)
			return (NULL);
		while (i < len)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
		return (sub);
	}
	return (NULL);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		len;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		dest = (char*)malloc(sizeof(char) * (len + 1));

		if (dest)
		{
			ft_bzero(dest, len+1);
			while (s1[i])
			{
				dest[i] = s1[i];
				i++;
			}
			while (s2[j])
				dest[i++] = s2[j++];
			dest[i++] = '\0';
			return (dest);
		}
	}
	return (NULL);
}


////////////////////////////////////////////////////////////
/*char *ft_strrealloc(char *str, size_t size)
{
    char *ptr;

    ptr = str;
    str = ft_strnew(size);
    str = ft_strncpy(str, ptr, size);
    ptr = NULL;
    return (str);
}
*/
t_list		*fd_search(t_list *head, int fd)
{
	printf("in search\n");
	while (head)
	{
		if ((size_t)fd == head->content_size)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	push_file(t_list **head, int fd, char *content)
{
	printf("in push\n");
	t_list *tmp;
	tmp = (t_list*)malloc(sizeof(t_list));
	tmp->next = (*head);
	tmp->content = content;
	tmp->content_size = (size_t)fd;
	(*head) = tmp;
}

char *ft_getline(char *s)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (s)
	{
		while (s[i] && s[i] == '\n')
		{
			i++;
			j++;
		}
		while(s[i] && s[i] != '\n')
			i++;
		if (j)
			s = ft_strsub(s, j, i - j-1);
		else
			s = ft_strsub(s, 0, i );
		return (s);
	}
	return (NULL);
}

int		n_in_begin(char *s)
{
	size_t i = 0;
	while (s[i] == '\n')
		i++;
		return (i);
	}

int		get_next_line(const int fd, char **line)
{
	char buff[BUFF_SIZE+1];
	char *new_buff; 
	int n;
	static t_list *node;
	t_list *tmp = NULL;
	//int i = 0;
	n = 0;
	new_buff = NULL;

	if (fd < 0 || !line)
		return (-1);
	printf("fd is: %d\n", fd);

	//если в списке еще нет такого фд
	if (!fd_search(node, fd))
	{
		new_buff = ft_strnew(BUFF_SIZE);
		if (!new_buff)
			return (-1);
		while ((n = (read(fd, buff, BUFF_SIZE)) > 0))
		{
			buff[BUFF_SIZE] = '\0';
			//printf("buff: %s\n", buff);	
			if(new_buff[0] == '\0')
				new_buff = ft_strncpy(new_buff, buff, BUFF_SIZE);
			else
				new_buff = ft_strjoin(new_buff, buff);
			//printf("new_buff: %s\n", new_buff);			
			//new_buff = ft_strrealloc(new_buff, ft_strlen(new_buff) + BUFF_SIZE);
			
		}
			//if (n > BUFF_SIZE)//если прочитано больше байт, чем размер буффера

		//printf("bytes read: %d, buffer after reading:%s\n",n, buff);
		push_file(&node, fd, new_buff);//добавляем новый узел, кладем туда фд и буфер		
		 //free(new_buff);
		// new_buff = NULL;	
	}
		//подвигаемся к узлу с нужным фд
	tmp = fd_search(node, fd);
	printf("content before: %s\n\n", tmp->content);
	*line = ft_getline(tmp->content);

	tmp->content += n_in_begin(tmp->content);
	tmp->content = (ft_strchr(tmp->content, '\n'));
	printf("content after: %s\n\n", tmp->content);
	if (tmp->content == NULL)
		return (0);
	//printf("fd in list: %zu\n", tmp->content_size);
	
	
	//printValues(node, elementsCount(node));
	if (line)
		return 1;
	return 0;
}

int		main(void)
{
	char *line;

	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test1.txt", O_RDONLY);
	int fd3 = open("test2.txt", O_RDONLY);

	get_next_line(fd1, &line);
		printf("call 1: %s\n", line);
	get_next_line(fd2, &line);
		printf("call 2:%s\n", line);
	get_next_line(fd1, &line);
		printf("call 3:%s\n", line);
	get_next_line(fd3, &line);
		printf("call 4: %s\n", line);
	get_next_line(fd2, &line);
		printf("call 5: %s\n", line);


	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}