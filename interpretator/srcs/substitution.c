/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:31:25 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/14 01:53:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char		*tilda_substitution(char *line)
{
	char			*res;
	char			*path;
	char			*slash;
	struct passwd	*data;

	res = NULL;
	if (*(line + 1) == '/' || !*(line + 1))
	{
		if ((path = get_var("HOME", ENV)))
			if (!(res = ft_strjoin(path, line + 1)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if ((slash = ft_strchr(line, '/')))
			path = ft_strsub(line, 1, slash - (line + 1));
		else
			path = ft_strdup(line + 1);
		if ((data = getpwnam(path)))
			res = ft_strjoin(data->pw_dir, (!slash) ? "" : slash);
		ft_strdel(&path);
	}
	return (res);
}

static char	is_glob(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
			return (TRUE);
	}
	return (FALSE);
}

char		**pattern_matching(char *line)
{
	char	**res;
	glob_t	globbuf;

	res = NULL;
	if (is_glob(line))
	{
		if (!glob(line, 0, NULL, &globbuf))
		{
			if (!(res = ft_dardup(globbuf.gl_pathv)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
		globfree(&globbuf);
	}
	return (res);
}

char		*var_substitution(char *line)
{
	int		i;
	char	*to_find;
	char	*var;
	char	*res;

	i = 1;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\''
	&& line[i] != '"' && line[i + 1] != '$')
		++i;
	if (!(to_find = ft_strsub(line, 1, i - 1)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if ((var = get_var(to_find, ALL_VARS)))
	{
		if (!(res = ft_strjoin(var, line + i)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if (!(res = ft_strdup(line + i)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	ft_strdel(&to_find);
	return (res);
}
