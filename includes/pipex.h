/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:55:12 by vatchetavit       #+#    #+#             */
/*   Updated: 2023/06/14 12:53:49 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <fcntl.h> 
# include <sys/wait.h>
# include <sys/types.h>
# include "pipex_bonus.h"

char	*find_path(char *comm, char **envp, char *buffer);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void	error_msg(char *msg);
int		check_commands(char **argv, char **envp, int argc);
int		check_first_comm(char *argv, char **envp, int argc);
void	path_to_array(char ***paths, char **envp);
int		join_commands(char **paths, char *argv, int argc);
int		set_infile(int *infile, char **argv, int argc, char **envp);
void	free_all(char **array);

#endif