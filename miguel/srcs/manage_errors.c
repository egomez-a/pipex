/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:47:30 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/15 22:11:09 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	open_infile(char *argv)
{
	int	fd;

	fd = open(argv, O_RDWR);
	if (fd < 0)
		show_error("Cannot open fd");
	return (fd);
}

int	open_outfile(char *argv)
{
	int	fd;

	fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		show_error("Cannot open fd");
	return (fd);
}

void	show_error(const char *error)

{
	perror(error);
	exit(1);
}

void	check_argc(int argc)
{
	if (argc != 5)
		show_error("Incorrect number of arguments");
}

void	manage_errors(int argc, char **argv, char **envp, t_pipex *args)
{
	check_argc(argc);
	args->path = get_path(envp);
	if (!args->path)
		show_error("Program couldnt detect $PATH");
	check_rights(argv[2], argv[3], args);
}
