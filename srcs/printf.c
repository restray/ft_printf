/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:53:47 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/11/26 15:41:44 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	size_t	len;

	len = 0;
	while (str)
	{
		ft_putchar(*str);
		str++;
	}
}

t_flags	ft_create_flag()
{
	t_flags	flag;

	flag.type = 0;
	flag.moins = 0;
	flag.etoile = 0;
	flag.point = 0;
	flag.taille = 0;
	flag.affiche = 0;
	return (flag);
}

void	ft_flag_moins(t_flags *flag)
{
	(*flag).moins = 1;
	(*flag).zero = 0;
}

void	ft_flag_etoile(t_flags *flag, va_list arg_list)
{
	(*flag).etoile = 1;
	(*flag).taille = va_arg(arg_list, int);
	if ((*flag).taille < 0)
	{
		(*flag).moins = 1;
		(*flag).taille *= -1;
	}
}

void	ft_flag_point(char *string, unsigned int *i, t_flags *flag, va_list arg_list)
{
	if (string[++(*i)] == '*')
	{
		(*flag).point = va_arg(arg_list, int);
		(*i)++;
	}
	else
	{
		(*flag).point = 0;
		while (ft_isdigit(string[*i]))
			(*flag).point = ((*flag).point * 10) + (string[(*i)++] - '0');
	}
}

void	ft_flag_digit(t_flags *flag, char c)
{
	if ((*flag).etoile == 1)
		(*flag).taille = 0;
	(*flag).taille = ((*flag).taille * 10) + (c - '0');
}

int		ft_flag_exist(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || 
			c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int		ft_flag_option_exist(char c)
{
	return (c == '-' || c == '.' || c == '0' || c == ' ' || c == '*');
}

void	ft_parse_flag(char *string, unsigned int *i, t_flags *flag, va_list arg_list)
{
	while (string[*i] && !ft_isdigit(string[*i]) && !ft_flag_exist(string[*i]) 
					&& !ft_flag_option_exist(string[*i]))
	{
		if (string[*i] == '0' && (*flag).taille == 0 && (*flag).moins == 0)
			(*flag).zero = 1;
		if (string[*i] == '.')
			ft_flag_point(string, i, flag, arg_list);
		if (string[*i] == '-')
			ft_flag_moins(flag);
		if (string[*i] == '*')
			ft_flag_etoile(flag, arg_list);
		if (ft_isdigit(string[*i]))
			ft_flag_digit(flag, string[*i]);
		if (ft_flag_exist(string[*i]))
		{
			(*flag).type = string[*i];
			break ;
		}
		(*i)++;
	}
}

int		ft_traitement(char *string, va_list args)
{
	unsigned int	i;
	int				size;
	t_flags			flag;

	i = 0;
	size = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%' && string[i + 1])
		{
			++i;
			flag = ft_create_flag();
			ft_parse_flag(string, &i, &flag, args);
		}
		else
		{
			size++;
			ft_putchar(string[i]);
		}
		i++;
	}
	return (size);
}

int		ft_printf(const char *args, ...)
{
	va_list		arg_list;
	int			printed_chars;
	char		*string;

	string = ft_strdup(args);
	va_start(arg_list, args);
	printed_chars = ft_traitement(string, arg_list);
	va_end(arg_list);
	free(string);
	return (printed_chars);
}
