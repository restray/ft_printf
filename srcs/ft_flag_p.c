/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:34:05 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/02 14:36:35 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char[100]	ft_flag_p_dec_to_hex(unsigned long long p, int *exist,
                                        int *size)
{
	char			ptr[100];
	char			ptr_copy[100];
    int             i;
    int             j;

    i = 0;
	while (p != 0)
	{
		if (p % 16 < 10)
			ptr[i++] = p % 16 + '0';
		else
			ptr[i++] = p % 16 - 10 + 'a';
		p = p / 16;
		(*size)++;
		exist++;
	}
    j = 0;
	while (i > 0)
		ptr_copy[j++] = ptr[--i];
	ptr_copy[j] = '\0';
    *exist = j;
    return (ptr_copy);
}

int		    		ft_display_flag_p(unsigned long long p, t_flags flag)
{
	int				size;
	char			ptr[100];
	int				exist;

	size = 2;
    ptr = ft_flag_p_dec_to_hex(p, &exist, &size);
	if (exist > 0)
		size--;
	if (flag.moins == 0)
		size += ft_putchar_size(flag.zero, flag.taille - size);
	ft_putstr_len("0x", 2);
	if (exist > 0)
		ft_putstr_len(ptr_copy, ft_strlen(ptr_copy));
	else
		size += ft_putchar('0');
	if (flag.moins == 1)
		size += ft_putchar_size(flag.zero, flag.taille - size);
	return (size);
}