/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:03:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 15:19:46 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>	/* necesario para funcion perror */
# include <unistd.h>	/* necesario para funcion access dup2 execve */
# include <stdio.h>		/* necesario para funcion perror */
# include <sys/wait.h>	/* necesario para funcion wait */
# include <fcntl.h>		/* necesario para funcion open */
# include <errno.h>		/* necesario para funcion errno */

# define FD_READ_END    0    /* index pipe extremo lectura */
# define FD_WRITE_END   1    /* index pipe extremo escritura */

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
	char	**path;
}			t_pipex;

/* Funciones útiles */
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *hst, const char *ndl, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
size_t	ft_begtrim(char const *s1, char const *set);
void	leaks(void);
void	freematrix(char **split);

/* Funciones pipex */
int		main(int argc, char **argv, char **envp);
void	start_child_1(int *fd, char **argv, t_pipex pipex, char **envp);
void	start_child_2(int *fd, pid_t pid, t_pipex pipex, char **envp);
void	freepointers(t_pipex pipex);

/* Funciones open file */
int		open_infile(char *argv, t_pipex pipex);
int		open_outfile(char *argv);

/* Funciones check */
void	check_entry(int argc);
int		*check_cmd_path(t_pipex pipex);
void	check_cmd_pathcmd1(t_pipex pipex, char **cmd, int i);
void	check_cmd_pathcmd2(t_pipex pipex, char **cmd, int i);
void	check_program(t_pipex pipex, char **cmd, int *check);
void	check_pid(pid_t pid);
void	check_commands(int *check);
void	check_pipe(int *fd);

/* Funciones path */
char	**env_variable(char **envp);
char	**add_slash(char **paths);
void	check_error_path(char *path_line);
#endif