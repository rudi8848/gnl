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

t_list		*fd_search(t_list **head, int fd)
{
	t_list			*tmp;

	tmp = *head;
	while (tmp)
	{
		if ((size_t)fd == tmp->content_size)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(head, tmp);
	tmp = (*head);
	return (tmp);
}

int			read_file(int const fd, void **data)
{
	char			buff[BUFF_SIZE + 1];
	int				read_bytes;
	char			*new_buff;

	new_buff = NULL;
	read_bytes = read(fd, buff, BUFF_SIZE);
	if (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		new_buff = ft_strjoin(*data, buff);
		if (!new_buff)
			return (-1);
		free(*data);
		*data = new_buff;
	}
	return (read_bytes);
}

int 		func(void **tmp_content, char **remainder, char *line)
{
	free(line);
	line = ft_strsub(*tmp_content, 0, *remainder - (char*)tmp_content);
	if (!line)
		return (-1);
	*remainder = ft_strdup(*remainder + 1);
	free(*tmp_content);
	*tmp_content = *remainder;
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_list	*file;
	t_list			*tmp;
	char			*remainder;
	int				bytes;

	if ((!line || !(*line = ft_strnew(1))) || fd < 0 || (read(fd, 0, 0)) < 0)
		return (-1);
	tmp = fd_search(&file, fd);
	if ((!tmp->content && !((tmp->content = ft_memalloc(sizeof(char))))))
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
	return (func(&tmp->content, &remainder, *line) == 1 ? 1 : -1);
/*
	free(*line);
	if (!(*line = ft_strsub(tmp->content, 0, remainder - (char*)tmp->content)))
		return (-1);
	remainder = ft_strdup(remainder + 1);
	free(tmp->content);
	tmp->content = remainder;
	return (1);*/
}
