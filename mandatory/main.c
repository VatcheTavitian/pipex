/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:54:25 by vatchetavit       #+#    #+#             */
/*   Updated: 2023/06/14 12:54:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_pipe_helper(char *argv, int argc, char **envp, int *pipes)
{
	char	buffer[1024];
	char	**argsread;

	close(pipes[0]);
	find_path(argv, envp, buffer);
	argsread = ft_split(&(*argv), ' ');
	dup2(pipes[1], STDOUT_FILENO);
	execve(buffer, argsread, envp);
}

static void	run_pipe(char **argv, int argc, char **envp, int i)
{
	int		pipes[2];
	int		pid;

	if (pipe(pipes) == -1)
		return ;
	if (check_command(argv[i], envp, argc) == 0)
		write(1, "command not found:\n", 19);
	else
	{
		pid = fork();
		{
			if (pid == 0)
				run_pipe_helper(argv[i], argc, envp, pipes);
			else
			{	
				close(pipes[1]);
				dup2(pipes[0], STDIN_FILENO);
				close(pipes[0]);
				waitpid(pid, NULL, 0);
			}
		}
	}
}

static void	execute_last(int argc, char **argv, char **envp, int i)
{
	char	buffer[1024];
	char	**argsread;

	find_path(argv[i], envp, buffer);
	argsread = ft_split(argv[i], ' ');
	execve(buffer, argsread, envp);
}

static void	set_outfile(int *outfile, int *i, char **argv, int argc)
{
	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*i = 2;
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		i;
	int		tempfile;

	infile = 0;
	outfile = 0;
	i = 2;
	if (argc != 5)
		error_msg("Error\nInvalid number of arguments!");
	set_outfile(&outfile, &i, argv, argc);
	tempfile = set_infile(&infile, argv, argc, envp);
	dup2(infile, STDIN_FILENO);
	while (i < (argc - 2))
		run_pipe(argv, argc, envp, i++);
	if (tempfile == 1)
		unlink("TEMPORARYFILETODELETE");
	if (check_command(argv[i], envp, argc) == 0)
		error_msg("command not found:");
	dup2(outfile, STDOUT_FILENO);
	execute_last(argc, argv, envp, i);
	return (0);
}
