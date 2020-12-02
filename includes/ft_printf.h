/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:57:10 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/02 10:48:10 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_flags
{
	int	type;
	int etoile;
	int	etoileneg;
	int point;
	int moins;
	int zero;
	int taille;
	int affiche;
}				t_flags;

int				ft_printf(const char *format, ...);

void			ft_putchar(char c);
void			ft_putstr(char *str);

t_flags			ft_create_flag(void);
void			ft_flag_moins(t_flags *flag);
void			ft_flag_etoile(t_flags *flag, va_list arg_list);
void			ft_flag_point(char *string,
				unsigned int *i, t_flags *flag, va_list arg_list);
void			ft_flag_digit(t_flags *flag, char c);

int				ft_flag_exist(char c);
int				ft_flag_option_exist(char c);
void			ft_parse_flag(char *string, unsigned int *i,
						t_flags *flag, va_list arg_list);
int				ft_display_flag_option_taille(t_flags flag);

int				ft_display_flag_c(int c, t_flags flag);
#endif
