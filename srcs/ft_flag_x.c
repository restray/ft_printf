/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:26:43 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/02 15:26:43 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_hex(unsigned int num, int minuscule)
{
	int		i;
	char	*str;
	char	str_tmp[100];
	int		j;

	if (!(str = ft_calloc(100, sizeof(char))))
		return (NULL);
	i = 0;
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (num != 0)
	{
		if (num % 16 > 9)
			str_tmp[i++] = num % 16 - 10 + (minuscule ? 'A' : 'a');
		else
			str_tmp[i++] = num % 16 + '0';
		num /= 16;
	}
	j = 0;
	while (i-- > 0)
		str[j++] = str_tmp[i];
	return (str);
}

int			ft_display_flag_hex(unsigned int number, int minuscule, t_flags flag)
{
	char			*num;
	char			*tmp;
	int				size;

	if (flag.point == 0 && number == 0)
		return (ft_putchar_size(0, flag.taille + 1));
	size = 0;
	num = ft_itoa_hex(number, minuscule);
	if (number < 0 && (flag.point >= 0 || flag.zero > 0))
	{
		if (flag.zero > 0 && flag.point == -1)
			ft_putstr_len("-", 1);
		tmp = ft_strtrim(num, "-");
		free(num);
		num = tmp;
		flag.zero = 1;
		flag.taille -= 1;
		size++;
	}
	if (flag.moins == 1)
	{
		if (flag.point >= 0)
		{
			if (number < 0)
				ft_putstr_len("-", 1);
			size += ft_putspace_int(flag.point - 1, ft_strlen(num) - 1, 1);
		}
		size += ft_putstr_len(num, ft_strlen(num));
	}
	if (flag.point >= 0)
	{
		if ((size_t)flag.point < ft_strlen(num))
			flag.point = ft_strlen(num);
		flag.taille -= flag.point;
		size += ft_putspace_int(flag.taille, 0, 0);
	}
	else
		size += ft_putspace_int(flag.taille, ft_strlen(num), flag.zero);
	if (flag.moins == 0)
	{
		if (flag.point >= 0)
		{
			if (number < 0)
				ft_putstr_len("-", 1);
			size += ft_putspace_int(flag.point - 1, ft_strlen(num) - 1, 1);
		}
		size += ft_putstr_len(num, ft_strlen(num));
	}	
	free(num);
	return (size);
}