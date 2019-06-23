/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/06/23 12:38:49 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*print_move(char *c, t_buff *buffer, t_cord *cord)
{
	disable_highlight(cord, buffer);
	if ((!ft_strcmp(c, tigetstr("kcub1")) || !ft_strcmp(c, tigetstr("khome")))
	&& !is_start_pos(cord))
		!ft_strcmp(c, tigetstr("kcub1")) ? go_left(1, cord) : go_left(cord->pos,
		cord);
	else if ((!ft_strcmp(c, tigetstr("kcuf1")) || !ft_strcmp(c,
	tigetstr("kend"))) && ((short)ft_strlen(buffer->buffer) > cord->pos))
		!ft_strcmp(c, tigetstr("kcuf1")) ? go_right(1, cord) :
		go_right(ft_strlen(buffer->buffer) - cord->pos, cord);
	else if (!ft_strcmp(c, CTRL_LEFT) || !ft_strcmp(c, CTRL_RIGHT))
		!ft_strcmp(c, CTRL_RIGHT) ? next_word(buffer->buffer + cord->pos, cord) :
		prev_word(buffer->buffer, cord);
	else if (!(ft_strcmp(c, CTRL_UP)) && cord->pos - cord->ws_col >= 0)
		go_left(cord->ws_col, cord);
	else if (!ft_strcmp(c, CTRL_DOWN) && (cord->pos + cord->ws_col <=
	(short)ft_strlen(buffer->buffer)))
		go_right(cord->ws_col, cord);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_symbols(char *c, t_buff *buffer, t_cord *cord,
t_history *history)
{
	if (!ft_strcmp(c, tigetstr("kLFT")) || !ft_strcmp(c, tigetstr("kRIT")) ||
		*c == CTRL_V || *c == CTRL_C || *c == CTRL_X)
		cut_copy_paste(c, buffer, cord);
	//else if (*c == TAB)
		//autocom();
	else if (!ft_strcmp(c, tigetstr("kcuu1")) || !ft_strcmp(c, tigetstr("kcud1"))
	|| *c == CTRL_R || (g_flags & HISTORY_SEARCH))
		go_history(c, history, cord, buffer);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_read(char *c, char *buffer, t_cord *cord)
{
	if (((*c == BCSP || *c == CTRL_H) && !is_start_pos(cord)) ||
	!ft_strcmp(c, tigetstr("kdch1")) || *c == CTRL_D)
	{
		if (*c == BCSP || *c == CTRL_H)
			go_left(1, cord);
		if (!ft_strlen(buffer) && *c == CTRL_D)
		{
			g_flags |= TERM_EXIT;
			return (SOMETHING);
		}
		del_symb(buffer, cord);
	}
	else if (ft_isprint(*c) || *c == '\n')
		print_symb(c, buffer, cord);
	else
		return (NULL);
	return (SOMETHING);
}

char	*cut_copy_paste(char *c, t_buff *buffer, t_cord *cord)
{
	if (!cord->highlight_pos && !(g_flags & START_POS))
		cord->highlight_pos = cord->pos;
	if (!cord->highlight_pos)
		g_flags |= START_POS;
	if (!ft_strcmp(c, tigetstr("kLFT")) && !is_start_pos(cord))
		highlight_left(buffer, cord);
	else if (!ft_strcmp(c, tigetstr("kRIT")) &&
	((short)ft_strlen(buffer->buffer) > cord->pos))
		highlight_right(buffer, cord);
	else if (*c == CTRL_C && (g_flags & TERM_HIGHLIGHT))
		copy_highlight(buffer, cord);
	else if (*c == CTRL_V && buffer->copy_buff)
		paste_highlight(buffer, cord);
	else if (*c == CTRL_X)
	{
		copy_highlight(buffer, cord);
		cut_highlight(buffer, cord);
	}
	else
		return (NULL);
	return (SOMETHING);
}

short	is_start_pos(t_cord *cord)
{
	if ((cord->x_cur == cord->x_start) && (cord->y_cur == cord->y_start))
		return (1);
	return (0);
}
