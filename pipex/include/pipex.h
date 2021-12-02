/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:03:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/12/02 13:08:14 by egomez-a         ###   ########.fr       */
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
	int		len;
}			t_pipex;

/* Funciones útiles */
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
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
void	free_pointers(t_pipex pipex);

/* Funciones open file */
int		open_infile(char *argv);
int		open_outfile(char *argv);

/* Funciones check */
void	check_entry(int argc);
void	*check_cmd_path(t_pipex *pipex);
void	check_cmd_pathcmd1(t_pipex *pipex, char **cmd, int i, int *check);
void	check_cmd_pathcmd2(t_pipex *pipex, char **cmd, int i, int *check);
void	check_pid(pid_t pid);
void	check_commands(int *check);
void	check_pipe(int *fd);
void	put_error(const char *error);

/* Funciones path */
char	**env_variable(char **envp);
char	**add_slash(char **paths);
void	check_error_path(char *path_line);
int		path_lenght(t_pipex *pipex);
#endif
