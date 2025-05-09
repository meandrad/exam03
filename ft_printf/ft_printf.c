/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:51:31 by meandrad          #+#    #+#             */
/*   Updated: 2025/05/08 22:26:48 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	int		count;
	long	num;

	num  = n;
	count = 0;
	if (num < 0)
	{
		count += ft_putchar('-');
		num *= -1;
	}
	if (num >= 10)
		count += ft_putnbr(num / 10);
	count += ft_putchar((num % 10) + '0');
	return (count);
}

int	ft_putstr(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		count += ft_putchar(s[i]);
		i++;
	}
	return (count);
}

int	handle_hex(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += handle_hex(n / 16);
	if ((n % 16) < 10)
		count += ft_putchar((n % 16) + '0');
	else
		count += ft_putchar((n % 16) - 10 + 'a');
	return (count);
}

int	handle_format(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'x')
		count += handle_hex(va_arg(args, unsigned int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, const char *));
	else if (c == 'd')
		count += ft_putnbr(va_arg(args, int));
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			count += handle_format(args, s[i + 1]);
			i++;
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int main (void)
{
	int count;
	int	count2;
	count = ft_printf("ola %s! %d %x\n", "teste", -42, 16);
	count2 = printf("ola %s! %d %x\n", "teste", -42, 16);
	printf("%d\n%d\n", count, count2);
}