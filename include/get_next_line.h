/*
** get_next_line.h for get_next_line in /home/mathieu.bigare/rendus/Pas_Piscine/CPE/CPE_2016_getnextline
** 
** Made by Mathieu Bigare
** Login   <mathieu.bigare@epitech.net>
** 
** Started on  Mon Jan  2 21:26:47 2017 Mathieu Bigare
** Last update Sat Mar  4 13:55:23 2017 
*/

#ifndef READ_SIZE
#define READ_SIZE (1)
#endif /* !READ_SIZE */

#ifndef MY_H_
#define MY_H_

char    *get_next_line(const int fd);
int	check_line(char *buff);
char    *bigger(char *str, char *src);
char	*stuff(int fd, char *buff);

#endif /* !MY_H_ */
