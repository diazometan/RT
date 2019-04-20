/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:23:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/20 15:11:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	effect_check(char *s)
{
	if (ft_strequ(s, "turbulence"))
		return (TURBULENCE);
	else if (ft_strequ(s, "chess_board"))
		return (CHESS_BOARD);
	else if (ft_strequ(s, "marble"))
		return (MARBLE);
	else if (ft_strequ(s, "wood"))
		return (WOOD);
	else
		return (0);
}
