/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:51:25 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/02 18:20:48 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_display_flag_pourcentage(t_flags flag)
{
	int	size;

	size = 0;
	if (flag.moins == 0)
		size += ft_putchar_size(flag.zero, flag.taille);
	ft_putchar('%');
	size++;
	if (flag.moins == 1)
		size += ft_putchar_size(flag.zero, flag.taille);
	return (size);
}
