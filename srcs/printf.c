/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:53:47 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/11/26 12:53:51 by tbelhomm         ###   ########.fr       */
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

int		ft_printf(const char *args, ...)
{
	va_list		arg_list;
	size_t		printed_chars;

	printed_chars = 0;
	va_start(arg_list, args);
	while (args && *args != '\0')
	{
		ft_putchar(*args);
		//if (actual_char != '%')
		//{
		//	printed_chars++;
		//	ft_putchar(actual_char);
		//}
		//else
		//{
		//	while (args && ((actual_char = *args) != ' ' || actual_char != '\0'))
		//	{
		//		if (actual_char == 's')
		//		{
		//			printf("%s", va_arg(arg_list, char *));
		//			ft_putstr(va_arg(arg_list, char *));
		//			break;
		//		}
		//		args++;
		//	}
		//}
		args++;

	}
	va_end(arg_list);
	return (1);
}
