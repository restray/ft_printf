/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelhomm </var/mail/tbelhomm>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:53:47 by tbelhomm          #+#    #+#             */
/*   Updated: 2020/12/01 23:21:55 by tbelhomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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
	while (string[*i])
	{
		if (!ft_isdigit(string[*i]) && !ft_flag_exist(string[*i]) && !ft_flag_option_exist(string[*i]))
			break ;
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

int		ft_display_flag_option_taille(t_flags flag)
{
	int	size;

	size = 0;
	while (flag.taille - flag.moins > 0)
	{
		if (flag.zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		(flag.taille)--;
		size++;
	}
	return (size);
}

int		ft_display_flag_c(int c, t_flags flag)
{
	int size;
	int	moins;

	size = 0;
	moins = flag.moins;
	if (moins == 1)
		ft_putchar(c);
	flag.zero = 0;
	flag.moins = 1;
	size = ft_display_flag_option_taille(flag);
	if (moins == 0)
		ft_putchar(c);
	return (size + 1);
}

int		ft_putstr_len(char *s, size_t len)
{
	size_t	size;

	size = 0;
	while (s[size] && size < len)
		ft_putchar(s[size++]);
	return (size);
}

static int	ft_putchar_size(int zero, int size)
{
	int	i;

	i = 0;
	while (++i < size)
		ft_putchar(zero > 0 ? '0' : ' ');
	return (size < 0 ? 0 : size);
}

int		ft_display_flag_p(unsigned long long p, t_flags flag)
{
	int				size;
	char			ptr[100];
	char			ptr_copy[100];
	unsigned int	i;
	unsigned int	j;
	int				exist;

	size = 2;
	i = 0;
	exist = 0;
	while (p != 0)
	{
		if (p % 16 < 10)
			ptr[i++] = p % 16 + '0';
		else
			ptr[i++] = p % 16 - 10 + 'a';
		p = p / 16;
		size++;
		exist++;
	}
	if (exist > 0)
		size--;
	if (flag.moins == 0)
		size += ft_putchar_size(flag.zero, flag.taille - size);
	j = 0;
	while (i > 0)
		ptr_copy[j++] = ptr[--i];
	ptr_copy[j] = '\0';
	ft_putstr_len("0x", 2);
	if (exist > 0)
		ft_putstr_len(ptr_copy, ft_strlen(ptr_copy));
	else
	{
		size++;
		ft_putchar('0');
	}
	if (flag.moins == 1)
		size += ft_putchar_size(flag.zero, flag.taille - size);
	return (size);
}

int		ft_display_flag_s(char *s, t_flags flag)
{
	int		size;
	int		tmpTaille;

	size = 0;
	if (s == NULL)
		s = "(null)";
	if ((flag.point >= 0 && (size_t)flag.point > ft_strlen(s)) || flag.point < 0)
	{
		flag.point = ft_strlen(s);
		tmpTaille = flag.taille;
		flag.taille = ft_strlen(s);
	}
	else
	{
		tmpTaille = flag.taille;
		flag.taille = flag.point;
	}
	if (flag.moins == 1)
		size += ft_putstr_len(s, flag.taille);
	while (tmpTaille > flag.taille)
	{
		ft_putchar(' ');
		size++;
		tmpTaille--;
	}
	if (flag.moins == 0)
		size += ft_putstr_len(s, flag.taille);
	return (size);
}

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

int		ft_putspace_int(int taille, int longueur, int zero)
{
	int	size;

	size = 0;
	while (taille > longueur)
	{
		ft_putchar_fd(zero ? '0' : ' ', 1);
		size++;
		taille--;
	}
	return (size);
}

int		ft_display_flag_integer(int number, t_flags flag)
{
	char			*num;
	char			*tmp;
	int				size;

	if (flag.point == 0 && number == 0)
		return (ft_putchar_size(0, flag.taille + 1));
	size = 0;
	num = ft_itoa(number);
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
		size += ft_putspace_int(flag.taille, ft_strlen(num), flag.etoileneg == 1 ? 0 : flag.zero);
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

int		ft_display_flag_unsigned_int(unsigned int number, t_flags flag)
{	
	char			*num;
	char			*tmp;
	int				size;

	if (flag.point == 0 && number == 0)
		return (ft_putchar_size(0, flag.taille + 1));
	size = 0;
	num = ft_itoa_l(number);
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

static char	*ft_itoa_hex(unsigned int num, int minuscule)
{
	int		i;
	char	*str;
	char	str_tmp[100];
	int		j;

	if (!(str = malloc(100 * sizeof(char*))))
		return (NULL);
	i = 0;
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
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
	str[i] = '\0';
	return (str);
}

int		ft_display_flag_hex(unsigned int number, int minuscule, t_flags flag)
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

int		ft_display_flag(t_flags flag, va_list arg_list)
{
	int		size;

	size = 0;
	if (flag.type == 'c')
		size = ft_display_flag_c(va_arg(arg_list, int), flag);
	else if (flag.type == 's')
		size = ft_display_flag_s(va_arg(arg_list, char *), flag);
	else if (flag.type == 'p')
		size = ft_display_flag_p(va_arg(arg_list, unsigned long long), flag);
	else if (flag.type == '%')
		size = ft_display_flag_pourcentage(flag);
	else if (flag.type == 'i' || flag.type == 'd')
		size = ft_display_flag_integer(va_arg(arg_list, int), flag);
	else if (flag.type == 'u')
		size = ft_display_flag_unsigned_int(va_arg(arg_list, unsigned int), flag);
	else if (flag.type == 'x' || flag.type == 'X')
		size = ft_display_flag_hex(va_arg(arg_list, unsigned int), flag.type == 'x' ? 0 : 1, flag);
	return (size);
}

int		ft_traitement(char *string, va_list arg_list)
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
			ft_parse_flag(string, &i, &flag, arg_list);
			if (ft_flag_exist(string[i]))
				size += ft_display_flag(flag, arg_list);
			else
			{
				size++;
				ft_putchar(string[i]);
			}
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
