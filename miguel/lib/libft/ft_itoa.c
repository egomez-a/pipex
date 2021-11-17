/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:28:10 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/08 17:34:51 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_sign(int n, int len)
{
	int	nbr;

	if (n < 0)
	{
		nbr = -n;
		len++;
	}
	else
		nbr = n;
	return (nbr);
}

static void	ft_fill(size_t n, int i, char *str)
{
	if (n >= 10)
		ft_fill(n / 10, i - 1, str);
	str[i] = n % 10 + '0';
}

static void	ft_fill_sign(size_t n, int len, char *str)
{
	if (n < 0)
		ft_fill(-n, len - 1, str);
	else
		ft_fill(n, len - 1, str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nbr;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 1;
	nbr = nbr_sign(n, len);
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_fill_sign(n, len, str);
	if (n < 0)
		str[0] = '-';
	return (str);
}
