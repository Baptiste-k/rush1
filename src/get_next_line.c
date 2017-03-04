/*
** get_next_line.c for get_next_line in /home/mathieu.bigare/rendus/Pas_Piscine/CPE/CPE_2016_getnextline
** 
** Made by Mathieu Bigare
** Login   <mathieu.bigare@epitech.net>
** 
** Started on  Mon Jan  2 18:21:39 2017 Mathieu Bigare
** Last update Thu Feb 16 16:28:14 2017 
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

char		*get_next_line(const int fd)
{
  static char	*buff = NULL;
  char		*str;
  int		i;

  i = -1;
  if (fd == -1 || READ_SIZE < 1)
    return (NULL);
  if (buff == NULL)
    if ((buff = malloc(READ_SIZE)) == NULL)
      return (NULL);
  if ((buff = stuff(fd, buff)) == NULL)
    return (NULL);
  while (buff[++i] != '\n' && buff[i] != '\0');
  if ((str = malloc(sizeof(char) * i)) == NULL)
    return (NULL);
  str[i] = '\0';
  i = -1;
  while (buff[++i] != '\n' && buff[i] != '\0')
    str[i] = buff[i];
  buff += i + 1;
  return (str);
}

int	check_line(char *buff)
{
  int	i;

  i = 0;
  if (buff == NULL)
    return (1);
  while (buff[i] != '\0')
    {
      if (buff[i] == '\n' || buff[i++] == '\0')
	return (0);
    }
  return (1);
}

char	*bigger(char *str, char *src)
{
  int	i;
  int	j;
  int	length;
  char	*new_buff;

  i = 0;
  j = 0;
  length = 0;
  while (str[length] != '\0')
    length++;
  if ((new_buff = malloc(length + READ_SIZE + 1)) == NULL)
    return (NULL);
  new_buff[length + READ_SIZE] = '\0';
  while (str[i] != '\0')
    {
      new_buff[j] = str[i];
      i++;
      j++;
    }
  i = 0;
  while (i < READ_SIZE)
    new_buff[j++] = src[i++];
  return (new_buff);
}

char	*stuff(int fd, char *buff)
{
  char	*tmp;
  char	*new_buff;

  if (check_line(buff) == 0)
    return (buff);
  if ((tmp = malloc(sizeof(char) * (READ_SIZE + 1))) == NULL)
    return (NULL);
  tmp[READ_SIZE] = '\0';
  if (read(fd, tmp, READ_SIZE) < 1)
    return (NULL);
  if ((new_buff = bigger(buff, tmp)) == NULL)
    return (NULL);
  while (check_line(new_buff) == 1)
    {
      if ((tmp = malloc(sizeof(char) * READ_SIZE)) == NULL)
	return (NULL);
      if (read(fd, tmp, READ_SIZE) < 1)
	return (new_buff);
      tmp[READ_SIZE] = '\0';
      if ((new_buff = bigger(new_buff, tmp)) == NULL)
	return (NULL);
    }
  return (new_buff);
}
