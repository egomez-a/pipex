/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:03:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/11 11:47:44 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>		/* necesario para funcion dup2 */
# include <stdio.h>			/* necesario para funcion perror */
# include <sys/wait.h>		/* necesario para funcion wait */
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

# define FD_READ_END    0    /* index pipe extremo lectura */
# define FD_WRITE_END   1    /* index pipe extremo escritura */

/* Funciones útiles */
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* Funciones pipex */
int 	main(int argc, char* argv[]);//, char* env[]);
void 	start_child(int *fd, char **argv);

/* Funciones check */
void	check_entry(int argc);
void	check_fd(int fd, char *filename);


#endif