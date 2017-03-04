/*
** my_archive.c for emacs in /home/baptiste.kissel/tmp_CPE_2016_b2rush1
** 
** Made by Baptiste Kissel
** Login   <baptiste.kissel@epitech.net>
** 
** Started on  Fri Mar  3 20:34:40 2017 Baptiste Kissel
** Last update Sat Mar  4 15:56:00 2017 Baptiste Kissel
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	unarchive_it(int fd, char *name)
{
  int		length;
  char		*tmp;
  char		*content;
  size_t	size;
  FILE		*file;

  size = 0;
  file = fopen(name, "w+");
  if ((tmp = get_next_line(fd)) == NULL)
    return (84);
  length = atoi(tmp);
  content = malloc(sizeof(char) * length);
  read(fd, content, length);
  fprintf(file, "%s", content);
  fclose(file);
  return (0);
}

int	main(int ac, char **av)
{
  char		*name;
  size_t	size;
  int		fd;

  size = 0;
  if (ac == 1)
    {
      printf("Usage: ./my_unarchive [archive_name]\n");
      return (0);
    }
  if ((fd = open(av[1], O_RDONLY)) == -1)
    return (84);
  name = get_next_line(fd);
  unarchive_it(fd, name);
  close(fd);
  return (0);
}
