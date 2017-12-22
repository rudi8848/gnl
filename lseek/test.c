#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

#define BUFF_SIZE 12

typedef struct s_seek
{
  int fd;
  int pos;
  char *endl;
  struct s_seek *next;
  } t_seek;

///////////////ДЛЯ ВИЗУАЛИЗАЦИИ////////////////
///////////////////////////////////////////////
int elementsCount(t_seek *head)
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

void printValues(t_seek *head, int last)
  {
    printf("==========now the list is==========\n");
    int i = 0;
    if (head)
    printf("%d | %d --> ", head->fd, head->pos);
    while (i < last)
    {
      head = head->next;
      printf("%d | %d --> ", head->fd, head->pos);
      i++;
    }
    printf("NULL\n===================================\n");
  }
  //////////////////////////////////////////
  //////////////////////////////////////////


void push_elem(t_seek **head, int fd, int pos)
{
  printf("in push_elem\n");
  t_seek *tmp;

  
//  t_seek *pos;
  tmp = (t_seek*)malloc(sizeof(t_seek));
  //pos = (t_seek*)malloc(sizeof(t_seek));
  tmp->next = (*head);
  tmp->pos = pos;
  tmp->fd = fd;
  (*head) = tmp;
  }

  t_seek    *fd_search(t_seek *head, int fd)
{
  printf("in fd_search\n");
  while (head)
  {
    if (fd == head->fd)
      return (head);
    head = head->next;
  }
  return (NULL);
}
  
 char     *ft_strjoin_free(char *s1, char *s2)
{
  char    *dest;
  size_t    len;
  size_t    i;
  size_t    j;

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

 
t_seek *change_pos(t_seek *head, int fd, int pos)
  {
    while (head)
    {
      if (fd == head->fd)
        {
          head->pos = pos;
          return (head);
        }
      else
      head = head->next;
      }
  return NULL;
    }

int find_pos(char *s, int start, char c)
{
    printf("in find_pos\n");
    int i = 0;
    int curr = 0;
    while (s[i])
    {
      // while (s[i] == c)
      //   i++;
      if (s[i] == c)
      {
        curr = start + i;
        return curr;
      }
      i++;
    }
    return 0;
    printf("curr pos %d\n", curr);
}

char *read_file(t_seek *file, int fd, char **line)
{
  printf("in read_file\n");
  char buff[BUFF_SIZE + 1];
  char *new_buff = "";
  int i;
  int n = 0;
  int start_pos = file->pos;
  //читаем кусок, проверяем на \н, передаем позицию, освобождаем
  printf("start-pos: %d\n", file->pos);
  while ((n = read(fd, buff, BUFF_SIZE)) > 0)
    {
     printf("in loop\n");
     printf("read: %s\n", buff);
      buff[BUFF_SIZE] = '\0';
        if (ft_strlen(new_buff) > 0)
          new_buff = ft_strjoin_free(new_buff, buff);
        else
          new_buff = ft_strjoin(new_buff, buff);
        i = find_pos(new_buff, start_pos, '\n');
        printf("read bytes: %d\n", n);
        if (i)
          break;
        // else if (!find_pos(new_buff, start_pos, '\n'))
        //   continue;
        if (n < BUFF_SIZE)
        {
          // *line = ft_strrchr(new_buff, '\n');
          printf("EOF!\n");
          return NULL;
        }
    }
    printf("i: %d\n", i);
    change_pos(file, fd, i);
    printf("new_buff: %s\n", new_buff);
    printf("new file->pos: %d\n", file->pos);

    *line = ft_strsub(new_buff, start_pos, (file->pos - start_pos));
    free(new_buff);
    return *line;
}

int   get_next_line(const int fd, char **line)
{
    // printf("in get_next_line\n");
    static t_seek *file = NULL;
    t_seek *tmp = NULL;

    if (fd < 0 || !line || (read(fd, 0, 0) < 0))
    return (-1);
  //printValues(file, elementsCount(file));
    if (!fd_search(file, fd))
      {
        push_elem(&file, fd, 0);
        *line = read_file(file, fd, line);
      }
      else
      {
        tmp = fd_search(file, fd);
        printf("pos: %d\n", tmp->pos);
        *line = read_file(tmp, fd, line);
      }
      printf("the line: %s\n", *line);
      printValues(file, elementsCount(file));
    return 0;
}


int main() {
//t_seek *elem = NULL;
char *line;
int fd1 = open("test.txt", O_RDONLY);
 int fd2 = open("test1.txt", O_RDONLY);
// int fd3 = open("test2.txt", O_RDONLY);

get_next_line(fd1,&line);
printf(" call line: %s\n", line);
 get_next_line(fd2,&line);
 printf(" call line: %s\n", line);
// get_next_line(fd3,&line);
// printf(" call line: %s\n", line);
//printValues(elem, elementsCount(elem));
get_next_line(fd1,&line);
get_next_line(fd1,&line);
// get_next_line(fd2,&line);
// get_next_line(fd3,&line);

close(fd1);
// close(fd2);
// close(fd3);
//system("leaks gnl");
/*
push_elem(&elem, 3,0);
push_elem(&elem, 5,0);
push_elem(&elem, 13,0);
printValues(elem, 2);
change_pos(elem, 13, 19);
change_pos(elem, 5, 1);
change_pos(elem, 3, 100);
printValues(elem, elementsCount(elem));*/
  return 0;
}
