/*
** archive.c for archive in /home/mathieu/shit
** 
** Made by 
** Login   <mathieu.bigare@epitech.eu@epitech.net>
** 
** Started on  Fri Mar  3 20:48:01 2017 
** Last update Sat Mar  4 19:19:55 2017 
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

char    *bigger(char *str, char *src)
{
  int   i;
  int   j;
  char  *new_buff;

  i = 0;
  j = 0;
  if ((new_buff = malloc(strlen(str) + strlen(src) + 1)) == NULL)
    return (NULL);
  new_buff[strlen(str) + strlen(src) + 1] = '\0';
  while (str[i] != '\0')
    {
      new_buff[j] = str[i];
      i++;
      j++;
    }
  i = 0;
  while (i < strlen(src))
    new_buff[j++] = src[i++];
  return (new_buff);
}


int		write_data(char *cfile, struct stat buf, char *name, FILE *file_archive)
{
  int		fd;
  char		*content;

  if ((fd = open(my_strcat(cfile,  name), O_RDONLY)) == -1)
    return (84);
  fprintf(file_archive, "%s\n", my_strcat(cfile, name));
  fprintf(file_archive, "%i\n", buf.st_size);
  content = malloc(buf.st_size);
  read(fd, content, buf.st_size);
  fprintf(file_archive, "%s\n", content);
}

int		fill_archive_src(FILE *file_archive, char *cfile, int fd_archive)
{
  struct stat	buf;
  int		fd;
  DIR		*dir;

  stat(cfile, &buf);
  if (S_ISDIR(buf.st_mode))
    {
      dir = opendir(cfile);
      if ((fill_archive_dir(dir, file_archive, cfile, fd_archive)) == 84)
	return (84);
    }
  else
    {
      write_data(cfile, buf, "", file_archive);
    }
}

int		fill_archive_dir(DIR *dir, FILE *file_archive, char *cfile, int fd_archive)
{
  struct dirent	*dirent;
  struct stat	buf;
  int		fd;
  char		*name;

  if (cfile[strlen(cfile) - 1] != '/')
    cfile = bigger(cfile, "/");
  while ((dirent = readdir(dir)) != NULL)
    {
      if ((strcmp(dirent->d_name, ".") != 0) && (strcmp(dirent->d_name, "..") != 0))
	{
	  stat(my_strcat(cfile, dirent->d_name), &buf);
	  if (S_ISDIR(buf.st_mode))
	    fill_archive_dir(opendir(my_strcat(cfile, dirent->d_name)),
	    file_archive,my_strcat(cfile, my_strcat(dirent->d_name, "/")), fd_archive);
	  else
	    write_data(cfile, buf, dirent->d_name, file_archive);
	}
    }
  return (0);
}

int		main(int ac, char **av)
{
  FILE		*file;
  int		i;

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
      fill_archive_src(file, av[i], open(av[1], O_RDWR));
      i++;
    }
  return (0);
}
