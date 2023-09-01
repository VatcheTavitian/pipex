/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:59:47 by vtavitia          #+#    #+#             */
/*   Updated: 2023/06/14 13:20:00 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

void	do_here_doc(char *lim, int argc);
int		setting_out_files(char **argv, int *outfile, int argc);
int		setting_in_files(int *infile, char **argv, char **envp, int argc);
int		check_command(char *argv, char **envp, int argc);
int		setting_files(int *i, int argc, char **argv, char **envp);

#endif