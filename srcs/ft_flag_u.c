/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm <tbelhomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:47:47 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/02 18:47:49 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (2);
	i = (n < 0 ? 2 : 1);
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (++i);
}

static char	*ft_itoa_l(unsigned int n)
{
	char			*str;
	unsigned int	i;

	i = ft_intlen(n);
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[--i] = '\0';
	while (n > 9)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	str[--i] = n + '0';
	return (str);
}

static void	ft_flag_u_display_moins(char *num, t_flags flag, int *size,
									unsigned int number)
{
	if (flag.point >= 0)
	{
		if (number < 0)
			ft_putstr_len("-", 1);
		(*size) += ft_putspace_int(flag.point - 1, ft_strlen(num) - 1, 1);
	}
	(*size) += ft_putstr_len(num, ft_strlen(num));
}

static char	*ft_flag_u_init(t_flags *flag, unsigned int number,
							int *tmp_size, int *size)
{
	char			*tmp;
	char			*num;

	if ((*flag).point == 0 && number == 0)
	{
		*tmp_size = ft_putchar_size(0, (*flag).taille + 1);
		return (NULL);
	}
	*size = 0;
	num = ft_itoa_l(number);
	if (number < 0 && ((*flag).point >= 0 || (*flag).zero > 0))
	{
		if ((*flag).zero > 0 && (*flag).point == -1)
			ft_putstr_len("-", 1);
		tmp = ft_strtrim(num, "-");
		free(num);
		num = tmp;
		(*flag).zero = 1;
		(*flag).taille -= 1;
		(*size)++;
	}
	*tmp_size = -1;
	return (num);
}

int			ft_display_flag_unsigned_int(unsigned int number, t_flags flag)
{
	char			*num;
	int				size;
	int				tmp_size;

	num = ft_flag_u_init(&flag, number, &tmp_size, &size);
	if (tmp_size > -1)
		return (tmp_size);
	if (flag.moins == 1)
		ft_flag_u_display_moins(num, flag, &size, number);
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
		ft_flag_u_display_moins(num, flag, &size, number);
	free(num);
	return (size);
}
