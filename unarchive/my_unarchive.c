/*
** my_archive.c for emacs in /home/baptiste.kissel/tmp_CPE_2016_b2rush1
** 
** Made by Baptiste Kissel
** Login   <baptiste.kissel@epitech.net>
** 
** Started on  Fri Mar  3 20:34:40 2017 Baptiste Kissel
** Last update Sat Mar  4 13:03:57 2017 Baptiste Kissel
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*fix_title(char *str)
{
  int	i;
  int	size;
  char	*tmp;

  i = -1;
  size = strlen(str) - 1;
  tmp = malloc(sizeof(char) * size);
  while (++i < size)
    tmp[i] = str[i];
  return (tmp);
}

int	unarchive_it(FILE *fd, char *name)
{
  char		*length;
  char		*str;
  size_t	size;
  FILE		*fd2;

  str = malloc(sizeof(char));
  length = malloc(sizeof(char));
  if (getline(&length, &size, fd) == -1)
    return (84);
  fread(str, atoi(length), 1, fd);
  getline(&length, &size, fd);
  fd2 = fopen(name, "w");
  fputs(str, fd2);
  fclose(fd2);
  if (getline(&name, &size, fd) != -1)
    {
      name = fix_title(name);
      unarchive_it(fd, name);
    }
  return (0);
}

int	main(int ac, char **av)
{
  FILE		*fd;
  char		*name;
  size_t	size;
  int		i;

  name = malloc(sizeof(char)); 
  i = 1;
  if (ac == 1)
    {
      printf("Usage: ./my_unarchive [archive_name]\n");
      return (0);
    }
  while (i < ac)
    {
      if ((fd = fopen(av[i], "r")) == NULL)
	return (84);
      getline(&name, &size, fd);
      name = fix_title(name);
      unarchive_it(fd, name);
      fclose(fd);
      i++;
    }
  return (0);
}
