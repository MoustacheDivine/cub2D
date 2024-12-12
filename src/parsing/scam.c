/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:48:52 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 02:39:02 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static long	loop_scam(int *i, const char *str)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result *= 10;
		result += str[(*i)++] - '0';
	}
	return (result);
}

long	ft_atoi_scam(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '+' && str[i] != '-' && !ft_isdigit(str[i]))
		return (ERROR_VALUE);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = loop_scam(&i, str);
	result *= sign;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0' && result >= 0 && result <= 255)
		return (result);
	return (ERROR_VALUE);
}
