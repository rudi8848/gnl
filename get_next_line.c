/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 09:38:42 by gvynogra          #+#    #+#             */
/*   Updated: 2017/12/03 13:09:01 by gvynogra         ###   ########.fr       */
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

char			*ft_strjoin_free(char *s1, char *s2)
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
			free(s1);
				return (dest);
		}
	}
	return (NULL);
}

void		push_file(t_list **head, int fd, char *content)
{
	t_list *tmp;

	tmp = (t_list*)malloc(sizeof(t_list));
	tmp->next = (*head);
	tmp->content = content;
	tmp->content_size = (size_t)fd;
	(*head) = tmp;
}

char		*ft_getline(char *s)
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
		while (s[i] && s[i] != '\n')
			i++;
		s = ft_strsub(s, j, i - j);
		return (s);
	}
	return (NULL);
}

int			n_in_begin(char *s)
{
	size_t i;

	i = 0;
	while (s[i] == '\n')
		i++;
	return (i);
}

int			get_next_line(const int fd, char **line)
{
	char				buff[BUFF_SIZE + 1];
	char				*new_buff;
	static t_list		*node;
	t_list				*tmp;

	tmp = NULL;
	if (fd < 0 || !line || (read(fd, 0, 0) < 0))
		return (-1);
	if (!fd_search(node, fd))
	{
		new_buff = ft_strnew(BUFF_SIZE);
		if (!new_buff)
			return (-1);
		while ((read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[BUFF_SIZE] = '\0';
			if (new_buff[0] == '\0')
				new_buff = ft_strncpy(new_buff, buff, BUFF_SIZE);
			else
				new_buff = ft_strjoin_free(new_buff, buff);
		}
		printf("new_buff: %s\n", new_buff);
		push_file(&node, fd, new_buff);
	}
	tmp = fd_search(node, fd);
	//printf("content before: %s\n\n", tmp->content);
	*line = ft_getline(tmp->content);
	tmp->content += n_in_begin(tmp->content);
	tmp->content = (ft_strchr(tmp->content, '\n'));
	//printf("content after: %s\n\n", tmp->content);	
	if (line && tmp->content)
	{
		printf("<<<LINE: %s>>>\n", *line);
		return (1);
	}
	return (0);
}
