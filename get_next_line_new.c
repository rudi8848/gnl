/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 15:11:04 by gvynogra          #+#    #+#             */
/*   Updated: 2017/12/16 15:12:26 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#typedef struct s_seek
{
	size_t	fd;
	size_t	position; //храним индекс последнего \н
} t_seek;




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

int			get_next_line(const int fd, char **line)
{
	char				buff[BUFF_SIZE + 1];
	char				*new_buff;
	static t_list		*node;
	t_list				*tmp;
	int					n = 0;

	tmp = NULL;
	if (fd < 0 || !line || (read(fd, 0, 0) < 0))
		return (-1);
	if (!fd_search(node, fd))
	{
		new_buff = ft_strnew(BUFF_SIZE);
		if (!new_buff)
			return (-1);
		while ((n = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[BUFF_SIZE] = '\0';
			if (new_buff[0] == '\0')
				new_buff = ft_strncpy(new_buff, buff, BUFF_SIZE);
			if ()
			else
				new_buff = ft_strjoin_free(new_buff, buff);
		}
		//printf("new_buff: %s\n", new_buff);
		push_file(&node, fd, new_buff);
	}
	tmp = fd_search(node, fd);

	//printf("content before: %s\n\n", tmp->content);
	*line = ft_getline(tmp->content);

/*
***	if (n < BUFF_SIZE && !ft_strlen(tmp->content))
***		return 0;
*/

	tmp->content += n_in_begin(tmp->content);
	tmp->content = (ft_strchr(tmp->content, '\n'));

	//printf("content after: %s\n\n", tmp->content);
	if (line && tmp->content)
	{
		//printf("<<<LINE: %s>>>\n", *line);
		return (1);
	}
	return (0);
}
