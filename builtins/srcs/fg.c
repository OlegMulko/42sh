/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:05:23 by lcrawn            #+#    #+#             */
/*   Updated: 2020/01/26 16:16:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	fg(int argc, char **argv)
{
	char	*tmp;
	t_job	*j;
	int		i;

	if (argc > 1)
		i = ft_atoi(argv[1]);
	else
		i = max_job() - 1;
	j = g_first_job;
	while (j && j->num != i)
		j = j->next;
	if (j)
	{
		mark_job_as_running(j);
		put_job_in_foreground(j, 1);
	}
	else if (argv[1])
		err("42sh", "fg", argv[1], "no such job");
	else
	{
		tmp = ft_itoa(i);
		err("42sh", "fg", tmp, "no such job");
		ft_strdel(&tmp);
	}
}