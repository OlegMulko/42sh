/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:19:01 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 23:41:29 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_readline.h"
# include "variables.h"
# include "error.h"

# define LEX_TOKENS_SIZE 1
# define SIZE_CS_FILTER 1

typedef enum		e_lex_tkn_type
{
	T_NULL,
	T_CTRL_C,
	T_ERR,
	T_END,
	T_WORD,
	T_ASSIGNMENT_WORD,
	T_PIPE,
	T_GREATER,
	T_GREATER_GREATER,
	T_LESS,
	T_LESS_LESS,
	T_LESS_AND,
	T_GREATER_AND,
	T_IO_NUMBER,
	T_SEP,
	T_CONTROL_SUB,
	T_AND_AND,
	T_AND,
	T_OR_OR,
	T_ROUND_SUB,
	T_FIGURE_SUB,
	T_ARITH_SUB,
	T_CTRL_D
}					t_lex_tkn_type;

typedef enum		e_lex_tkn_class
{
	C_WORD,
	C_REDIR,
	C_PIPE,
	C_LOG_OPERS,
	C_SEP,
	C_AND,
	C_CONTROL_SUB,
	C_SUB,
	C_NULL,
	C_END,
	C_PREFIX_SUB,
}					t_lex_tkn_class;

typedef enum		e_lex_cs_type
{
	CS_NULL,
	CS_DOUBLE_QUOTES,
	CS_SINGLE_QUOTES,
	CS_ROUND_BRK,
	CS_FIGURE_BRK,
	CS_D_ROUND_BRK,
}					t_lex_cs_type;

/*
** fr - function result
*/

typedef enum		e_lex_fr
{
	FR_NULL,
	FR_OK,
	FR_ERR,
	FR_CTRL_C,
	FR_CTRL_D,
	FR_DRBRK_OPEN,
	FR_EOL,
}					t_lex_fr;

typedef enum		e_lex_stat
{
	LS_OK,
	LS_ERR,
	LS_CTRL_C,
	LS_CTRL_D
}					t_lex_stat;

typedef struct		s_lex_tkn
{
	char			*value;
	t_lex_tkn_type	type;
	t_lex_tkn_class	class;
	size_t			start_pos;
	size_t			end_pos;

}					t_lex_tkn;

typedef	struct		s_lex_tkns
{
	t_lex_tkn		**tokens;
	size_t			malloc_size;
	size_t			size;
}					t_lex_tkns;

t_lex_stat			g_lex_stat;

/*
** lex_lexer.c
*/

t_lex_tkn			**lex_get_tkns(char **str);
t_lex_tkn			*lex_get_next_tkn(char	**str, size_t pos);

/*
** lex_tkn.c
*/

t_lex_tkn			*lex_new_tkn(void);
t_lex_tkn			*lex_del_tkn(t_lex_tkn *token);

/*
** lex_tkns.c
*/

t_lex_tkns			*lex_new_tkns(void);
t_lex_tkns			*lex_tkns_reloc(t_lex_tkns *s_tokens);
t_lex_tkn			**lex_del_tkns(t_lex_tkn **tokens);
t_lex_tkn			**lex_del_s_tokens(t_lex_tkns *s_tokens);

/*
** lex_get_tkn.c
*/

t_lex_tkn			*lex_get_next_tkn(char	**str, size_t pos);
void				lex_fill_value_pos(t_lex_tkn *token, char *str,
	size_t start_pos, size_t pos);

/*
** lex_check_tkn.c
*/

t_lex_tkn_type		lex_check_end(char **str, short is_word, size_t *pos);
t_lex_tkn_type		lex_check_alnum(char **str, short is_word, size_t *pos);
t_lex_tkn_type		lex_check_other(char **str, short is_word, size_t *pos);

/*
** lex_tkn_type.c
*/

t_lex_tkn_type		lex_check_type(char **str, short is_word, size_t *pos);

/*
** lex_tkn_class.c
*/

t_lex_tkn_class		lex_check_class(t_lex_tkn_type type);

/*
** lex_check_or.c
*/

t_lex_tkn_type		lex_check_or(char **str, short is_word, size_t *pos);

/*
** lex_check_greater.c
*/

t_lex_tkn_type		lex_check_greater(char **str, short is_word, size_t *pos);
int					lex_is_greater_and(char *str, size_t *pos);
int					lex_is_greater_greater(char *str, size_t *pos);

/*
** lex_check_less.c
*/

t_lex_tkn_type		lex_check_less(char **str, short is_word, size_t *pos);
int					lex_is_less_and(char *str, size_t *pos);
int					lex_is_less_less(char *str, size_t *pos);

/*
** lex_check_sep.c
*/

t_lex_tkn_type		lex_check_sep(char **str, short is_word, size_t *pos);

/*
** lex_lex_str.c
*/

char				*lex_strjoin(char *s1, char *s2);
char				*lex_add_eol(char *str);

/*
** lex_quotation_marks.c
*/

int					lex_is_quotation_marks(char *str, size_t pos);
t_lex_tkn_type		lex_quotation_marks(char **str, short is_word, size_t *pos);

/*
** lex_io_num.c
*/

int					lex_is_ionum(char *str, short is_word, size_t *pos);
t_lex_tkn_type		lex_ionum(short is_word);

/*
** lex_asig_name.c
*/

t_lex_fr			lex_is_asig_name(char **str, short is_word, size_t *pos,
	int *err);
t_lex_tkn_type		lex_asig_name(short is_word, int err, t_lex_fr fr);

/*
** lex_asig_name2.c
*/

void				lex_an_cut_quotes(t_lex_tkn *token, const char *str);

/*
** lex_log_opers.c
*/

t_lex_tkn_type		lex_is_and_and(char **str, size_t pos);
t_lex_tkn_type		lex_check_and_and(char **str, short is_word, size_t *pos);
t_lex_tkn_type		lex_is_or_or(char **str, size_t pos);
t_lex_tkn_type		lex_check_or_or(char **str, short is_word, size_t *pos);
int					lex_is_fin_log_oper(char *str, size_t pos, size_t *offset);

/*
** lex_check_and.c
*/

t_lex_tkn_type		lex_check_and(char **str, short is_word, size_t *pos);

/*
** lex_ctrl_c.c
*/

t_lex_tkn_type		lex_ctrl_c(char **s1, char **s2);
void				lex_clear_strs(char **s1, char **s2);
t_lex_fr			lex_cs_ctrl_c(char **s1, char **s2);

/*
** lex_ctrl_d.c
*/

t_lex_fr			lex_cs_ctrl_d(char **s1, char is_quotes);
t_lex_tkn_type		lex_ctrl_d(void);
t_lex_tkn_type		lex_al_ctrl_d(char **s1);

/*
** lex_double_quotes.c
*/

t_lex_tkn_type		lex_double_quotes(char **str, size_t *pos);

/*
** lex_single_quotes.c
*/

t_lex_tkn_type		lex_single_quotes(char **str, size_t *pos);

/*
** lex_cs.c
*/

t_lex_tkn_type		lex_cs(char **str, size_t *pos, t_lex_cs_type type);

/*
** lex_cs_open_close.c
*/

int					lex_cs_is_quotes(t_lex_cs_type type);
int					lex_cs_is_brk(t_lex_cs_type type);
int					lex_cs_check_open(int check, t_lex_cs_type *cs_filter,
	int cs_count, t_lex_cs_type type);
int					lex_cs_check_close(int check, t_lex_cs_type	*cs_filter,
	int cs_count, t_lex_cs_type type);

/*
** lex_cs_inc_dec.c
*/

t_lex_fr			lex_cs_inc_dec(const char *str, int *cs_count,
	size_t *offset);

/*
** lex_cs_filter.c
*/

t_lex_cs_type		*lex_new_cs_filter(size_t size);
int					lex_reloc_cs_filter(t_lex_cs_type **cs_filter,
	size_t *size);
void				lex_init_cs_filter(t_lex_cs_type **cs_filter,
	size_t *filter_size);

/*
** lex_val_tkn_processing.c
*/

void				lex_cut_tkn_value(t_lex_tkn *token, const char *str);

/*
** lex_substitutions.c
*/

int					lex_is_brk(char c);
t_lex_tkn_type		lex_substitutions(char **str, short is_word, size_t *pos);

/*
** lex_backslash.c
*/

t_lex_fr			lex_bs(char **str, size_t *pos);
t_lex_tkn_type		lex_check_bs(char **str, size_t *pos);

/*
** lex_backslash2.c
*/

char				*lex_del_backslash(char *str, size_t pos);

/*
** lex_preprocessing.c
*/

void				lex_preprocessing(const char *str, size_t *pos);

/*
** lex_arith_sub.c
*/

t_lex_tkn_type		lex_arith_sub(char **str, short is_word, size_t *pos);

/*
** lex_insert_tkns.c
*/

size_t				lex_tkns_size(t_lex_tkn **tkns);
t_lex_tkn			**lex_insert_tkns(t_lex_tkn **src,
	t_lex_tkn **ins, size_t ins_index);

/*
** lex_history_exp.c
*/

int					lex_history_exp(char **str, size_t pos);
int					lex_is_hist_exp(const char *str, size_t pos);

/*
** lex_check_hist_exp.c
*/

t_lex_tkn_type		lex_check_hist_exp(char **str, size_t *pos);

/*
** lex_stat.c
*/

t_lex_tkn			*lex_status(t_lex_tkn_type type, t_lex_tkn *token);
#endif
