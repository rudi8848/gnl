/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 12:50:56 by gvynogra          #+#    #+#             */
/*   Updated: 2017/12/25 13:02:20 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		push_file(t_list **head, int fd)
{
	t_list			*tmp;

	tmp = (t_list*)malloc(sizeof(t_list));
	tmp->next = (*head);
	tmp->content = NULL;
	tmp->content_size = (size_t)fd;
	(*head) = tmp;
}

int			read_file(int const fd, void **data)
{
	char			buff[BUFF_SIZE + 1];
	int				read_bytes;
	char			*nstr;

	nstr = NULL;
	read_bytes = read(fd, buff, BUFF_SIZE);
	if (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		nstr = ft_strjoin(*data, buff);
		if (!nstr)
			return (-1);
		free(*data);
		*data = nstr;
	}
	return (read_bytes);
}

int			get_next_line(int const fd, char **line)
{
	static t_list	*file;
	t_list			*tmp;
	char			*remainder;
	int				bytes;

	if (!line || fd < 0 || (read(fd, 0, 0)) < 0)
		return (-1);
	if (!fd_search(file, fd))
		push_file(&file, fd);
	tmp = fd_search(file, fd);
	if ((!(char*)tmp->content &&
				!((tmp->content = (char *)ft_memalloc(sizeof(char))))))
		return (-1);
	remainder = ft_strchr((char*)tmp->content, '\n');
	while (remainder == NULL)
	{
		bytes = read_file(fd, &tmp->content);
		if (bytes == 0)
		{
			if ((remainder = ft_strchr((char*)tmp->content, '\0'))
					== (char*)tmp->content)
				return (0);
		}
		else if (bytes < 0)
			return (-1);
		else
			remainder = ft_strchr(tmp->content, '\n');
	}
	*line = ft_strsub(tmp->content, 0, remainder - (char*)tmp->content);
	if (!*line)
		return (-1);
	remainder = ft_strdup(remainder + 1);
	free(tmp->content);
	tmp->content = remainder;
	return (1);
}
