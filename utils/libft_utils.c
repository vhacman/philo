/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:37:37 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/05 15:37:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Compares two strings lexicographically
** s1: First string to compare
** s2: Second string to compare
** Return: 0 if strings are equal,
** negative if s1 < s2, positive if s1 > s2
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
** Compares at most n characters of two strings
** s1: First string to compare
** s2: Second string to compare
** n: Maximum number of characters to compare
** Return: 0 if strings are equal within n chars, negative if s1 < s2,
**         positive if s1 > s2
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (i == n)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

/*
** Checks if a character is a decimal digit
** determines if the given character is a decimal digit.
** Return: 1 if c is a digit, 0 otherwise
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
** Converts a string to an integer
** It skips leading whitespace characters,
** handles an optional sign (+ or -),
** then converts consecutive digits.
** Return: The converted integer value
*/
int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((result * sign));
}

/*
** Checks whether a given string represents
** a valid non-negative integer.
** The string must contain only digit characters (0–9)
** and must not be empty.
*/
int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
