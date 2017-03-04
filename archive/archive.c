/*
** archive.c for archive in /home/mathieu/shit
** 
** Made by 
** Login   <mathieu.bigare@epitech.eu@epitech.net>
** 
** Started on  Fri Mar  3 20:48:01 2017 
** Last update Fri Mar  3 22:13:11 2017 
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int		main(int ac, char **av)
{
  FILE		*file;
  int		i;
  int		fd;
  char		*content;
  struct stat	buf;

  i = 2;
  if (ac == 1)
    {
      printf("Usage: ./my_archive [archive_name] [files ...]");
      return (0);
    }
  if ((file = fopen(av[1], "w+")) == NULL)
    return (84);
  while (i != ac)
    {
      fd = open(av[i], O_RDONLY);
      if (stat(av[i], &buf) == -1);
      fprintf(file, "%s\n", av[i]);
      fprintf(file, "%i\n", buf.st_size);
      content = malloc(buf.st_size);
      read(fd, content, buf.st_size);
      fprintf(file, "%s\n", content);
      i++;
    }
  return (0);
}
