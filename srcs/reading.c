/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/14 14:20:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_buf_print(char *buf, char *c, uint8_t *n)
{
	int len;

	*n = *n;
	if (ft_isprint(*c))
	{
		len = cord.x_cur - cord.prompt;
		buf = ft_stradd(buf, c, len);
		ft_putstr(buf + len);
		cord.x_cur += ft_strlen(c);
		len = ft_strlen(buf + len);
		while (--len)
			ft_putstr(LEFT);
	}
	check_key(c, buf);
	return (buf);
}

void	read_handler(char *c)
{
	unsigned short	nb;

	nb = read(STDIN_FILENO, c, LINE_MAX);
	c[nb] = '\0';
}

char	*reading(char *buf)
{
	char	c[LINE_MAX + 1];
	uint8_t	n;

	n = 1;
	while (RUNNING)
	{
		read_handler(c);
		if (g_flags & SHELL_SIGINT || g_flags & SHELL_SIGQUIT)
		{
			if (g_flags & SHELL_SIGINT)
				ft_strclr(buf);
			g_flags &= ~SHELL_SIGINT;
			g_flags &= ~SHELL_SIGQUIT;
			continue;
		}
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(buf) + ft_strlen(c) >= NORMAL_LINE * n)
			buf = strnew_realloc_buf(buf, &n);
		buf = make_buf_print(buf , c, &n);
	}
	return (buf);
}

char	*read_prompt()
{
	char	*str;

	if (!(str = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	set_input_mode();
	str = reading(str);
	reset_input_mode();
	ft_putchar('\n');
	return (str);
}