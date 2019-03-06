/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:17:14 by bsprigga          #+#    #+#             */
/*   Updated: 2019/02/13 15:14:12 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_format	*g_f;
va_list		g_ap;
int			g_count;

int		ft_printf(const char *format, ...)
{
	int	i;

	g_count = 0;
	g_f = g_f_new();
	va_start(g_ap, format);
	i = 0;
	parse_print_format((char *)format, i);
	va_end(g_ap);
	clear_all_exit(0);
	return (g_count);
}
