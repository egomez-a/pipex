/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:23:22 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/16 16:15:11 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	t_pipex	args;

	manage_errors(argc, argv, envp, &args);
	args.fd_in = open_infile(argv[1]);
	if (pipe(fd) < 0)
		show_error("Pipe error");
	pid = fork();
	if (!pid)
		child_process(fd, &args, envp);
	else if (pid > 0)
	{
		args.fd_out = open_outfile(argv[4]);
		parent_process(fd, pid, &args, envp);
	}
	else
		show_error("Fork error");
	wait(&status);
	wait(&status);
	ft_dfree(args.cmd1);
	ft_dfree(args.cmd2);
	return (0);
}
