/*
** my_archive.c for emacs in /home/baptiste.kissel/tmp_CPE_2016_b2rush1
** 
** Made by Baptiste Kissel
** Login   <baptiste.kissel@epitech.net>
** 
** Started on  Fri Mar  3 20:34:40 2017 Baptiste Kissel
** Last update Sat Mar  4 13:53:12 2017 
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

int	unarchive_it(FILE *file, char *name)
{
  int		length;
  char		*tmp;
  char		*content;
  size_t	size;
  FILE		*file2;

  size = 0;
  file2 = fopen(name, "+w");
  if (getline(&tmp, &size, file) == -1)
    return (84);
  length = atoi(tmp);
  read(file, content, length);
  fputs(content, file2);
  fclose(file2);
  return (0);
}

int	main(int ac, char **av)
{
  FILE		*file;
  char		*name;
  size_t	size;
  int		i;

  i = 1;
  size = 0;
  if (ac == 1)
    {
      printf("Usage: ./my_unarchive [archive_name]\n");
      return (0);
    }
  if ((file = fopen(av[i], "r")) == NULL)
    return (84);
  while (i < ac)
    {
      getline(&name, &size, file);
      name = fix_title(name);
      unarchive_it(file, name);
      i++;
    }
  fclose(file);
  return (0);
}
