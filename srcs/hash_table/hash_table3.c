/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:09:54 by filip             #+#    #+#             */
/*   Updated: 2019/05/21 15:07:15 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_hash_table(void)
{
	short	i;
	t_hash	**table;
	t_hash	*next;
    t_hash  *copy;

	i = -1;
	table = g_term.hash_table;
	while (++i < g_term.hash_table_size)
	{
        next = table[i];
        while (next)
        {
            ft_memdel((void**)&(next->name));
            ft_memdel((void**)&(next->path));
            copy = next;
            next = next->next;
			ft_memdel((void**)&(copy));
        }
	}
	g_term.hash_table_size = 0;
}