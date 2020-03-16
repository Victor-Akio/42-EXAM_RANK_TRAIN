/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:35:18 by vminomiy          #+#    #+#             */
/*   Updated: 2020/03/11 18:01:35 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_flags
{
	int		width;
	int		precision;
	char	type;
	char	*printable;
}				t_flags;

void		initialize(t_flags *cnt)
{
	cnt->width = -1;
	cnt->precision = -1;
	cnt->type = ' ';
	cnt->printable = NULL;
}

int			isnumeric(char s)
{
	if (s >= '0' && s <= '9')
		return (1);
	return (0);
}

int		atoi_mini(char *s)
{
	int		num;
	int		i;

	i = 0;
	num = 0;
	while (isnumeric(s[i]))
	{
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	return (num);
}

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*s1;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	s1 = malloc(len + 1);
	s1[len] = '\0';
	while (i < len)
	{
		s1[i] = s[i];
		i++;
	}
	return (s1);
}

char	*add_front(char *s, char c)
{
	char	*s1;
	int		len;
	int		i;
	int		isneg;

	isneg = 0;
	if (c == '0' && s[0] == '-')
	{
		s[0] = '0';
		isneg = 1;
	}
	i = 0;
	len = ft_strlen(s);
	s1 = malloc(len + 2);
	s1[len + 1] = '\0';
	s1[0] = c;
	while (i <= len)
	{
		s1[i + 1] = s[i];
		i++;
	}
	if (isneg)
		s1[0] = '-';
	free(s);
	return (s1);
}

char	*add_back(char *s, char c)
{
	char	*s1;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	s1 = malloc(len + 2);
	s1[len + 1] = '\0';
	s1[len] = c;
	while (i <= len)
	{
		s1[i] = s[i];
		i++;
	}
	free(s);
	return (s1);
}

char	*remove_back(char *s)
{
	char	*s1;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	s1 = malloc(len);
	s1[len - 1] = '\0';
	while (i < len - 1)
	{
		s1[i] = s[i];
		i++;
	}
	free(s);
	return (s1);
}

char	*itoa_base(int n, int base)
{
	int is_negative;
	unsigned int number;
	char c;
	char *s;
	
	s = malloc(1);
	s[0] = '\0';

	is_negative = 0;
	if (n < 0 && base != 16)
	{
		is_negative = 1;
		number = (unsigned int)(n * -1);
	}
	else
		number = (unsigned int)n;
	while (number >= 0)
	{
		c = number % base;
		if (c <= 9)
			c += '0';
		else
			c += 'a' - 10;
		s = add_front(s, c);
		number = number / base;	
		if (number == 0)
			break ;
	}
	if (is_negative)
		s = add_front(s, '-');
	return (s);
}

int		get_items(char *s, t_flags *flags)
{
	int		i;

	i = 0;
	if (s[i] == '%')
		i++;
	if (isnumeric(s[i]))
	{
		flags->width = atoi_mini(&s[i]);
		while (isnumeric(s[i]))
			i++;
	}
	if (s[i] == '.')
	{
		i++;
		if (isnumeric(s[i]))
		{
			flags->precision = atoi_mini(&s[i]);
			while (isnumeric(s[i]))
				i++;
		}
	}
	flags->type = s[i];
	i++;
	return (i);
}

int		counter_d(t_flags *flags)
{
	int		len;

	len = ft_strlen(flags->printable);
	if (flags->printable[0] == '-')
		len--;
	if (flags->precision == 0 && len == 1 && flags->printable[0] == '0')
	{
		flags->printable = remove_back(flags->printable);
		len--;
	}
	while (flags->precision > len)
	{
		flags->printable = add_front(flags->printable, '0');
		len++;
	}
	len = ft_strlen(flags->printable);
	while (flags->width > len)
	{
		flags->printable = add_front(flags->printable, ' ');
		len++;
	}
	return (ft_putstr(flags->printable));
}

int		counter_s(t_flags *flags)
{
	int		len;

	len = ft_strlen(flags->printable);
	if (flags->precision >= 0)
	{
		while (len > flags->precision)
		{
			flags->printable = remove_back(flags->printable);
			len--;
		}
	}
	len = ft_strlen(flags->printable);
	while (flags->width > len)
	{
		flags->printable = add_front(flags->printable, ' ');
		len++;
	}
	return (ft_putstr(flags->printable));
}

int		print_items(t_flags *flags, va_list args)
{
	if (flags->type == 'd')
	{
		flags->printable = itoa_base((int)va_arg(args, int), 10);
		return (counter_d(flags));
	}
	else if (flags->type == 'x')
	{
		flags->printable = itoa_base((int)va_arg(args, int), 16);
		return (counter_d(flags));
	}
	else if (flags->type == 's')
	{
		flags->printable = ft_strdup((char *)va_arg(args, char*));
		return (counter_s(flags));
	}
	else
	{
		flags->printable = ft_strdup("");
		return (0);
	}
}

int		ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	t_flags flags;
	va_list args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			initialize(&flags);
			i += get_items((char *)&format[i], &flags);
			count += print_items(&flags, args);
			if (flags.printable)
				free(flags.printable);
		}
		else
		{
			write(1, &format[i], 1);
			i++;
			count++;
		}
	}
	va_end(args);
	return (count);
}
