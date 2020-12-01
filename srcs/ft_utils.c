/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:15:37 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/01 23:20:49 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
