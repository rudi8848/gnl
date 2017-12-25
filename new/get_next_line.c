#include "get_next_line.h"

t_list		*fd_search(t_list *head, int fd)
{
	while (head)
	{
		if ((size_t)fd == head->content_size)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void		push_file(t_list **head, int fd/*, char *content*/)
{
	t_list *tmp;

	tmp = (t_list*)malloc(sizeof(t_list));
	tmp->next = (*head);
	tmp->content = NULL;
	tmp->content_size = (size_t)fd;
	(*head) = tmp;
}

int	read_file(int const fd, void **data)
{
	// printf("in read\n");
	// printf("fd: %d, tmp->content: %s\n", fd, *data);
	/*static*/ char	buff[BUFF_SIZE+1] = { '\n' };
	int			read_bytes;
	char        *nstr = NULL;
	read_bytes = read(fd, buff, BUFF_SIZE);
	if (read_bytes > 0)
	{
	    buff[read_bytes] = '\0';
	   // printf("buff: %s\n", buff);
	    nstr = ft_strjoin(*data, buff);
	    if (!nstr)
	        return (-1);
	     free(*data);
	    *data = nstr;
	}
	// printf("nstr: %s\n", nstr);
	// printf("read bytes: %d\n", read_bytes);
	return (read_bytes);
}

int get_next_line(int const fd, char ** line)
{
	//printf("in gnl\n");
	///*static*/ char		*data = NULL;
	static t_list	*file;
	t_list			*tmp;
	char			*remainder;
	int         	bytes;

	if (!line || fd < 0 || (read(fd, 0, 0)) < 0)
		return (-1);
	if (!fd_search(file, fd))
		push_file(&file, fd);
	tmp = fd_search(file, fd);
	//printf("before\n");
	//tmp->content = data;
	//printf("after\n");
	if ((/*!data*/!(char*)tmp->content && !((tmp->content/*data*/ = (char *)ft_memalloc(sizeof(char))))) )
	    return (-1);
	
	//printf("data: %s\n", data);
	//printf("after if\n");
	remainder = ft_strchr(/*data*/(char*)tmp->content, '\n');
	//printf("remainder: %s\n", remainder);
	while (remainder == NULL)
	{
	//printf("in loop\n");
	    bytes = read_file(fd, /*&data*/&tmp->content);
	    if (bytes == 0)
	    {
	       if ((remainder = ft_strchr(/*data*/(char*)tmp->content, '\0')) == /*data*/(char*)tmp->content )
	        return (0);
	    } else if (bytes < 0)
	        return (-1);
		else
			remainder = ft_strchr(/*data*/tmp->content, '\n');
	}
	*line = ft_strsub(/*data*/tmp->content, 0, remainder - /*data*/(char*)tmp->content);
	   if (!*line)
	    return (-1);
	remainder = ft_strdup(remainder + 1);
	    free(/*data*/tmp->content);
	/*data*/tmp->content = remainder;
	return (1);
}
