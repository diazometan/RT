/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:23:42 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/20 16:16:09 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	effect_check(char *s)
{
	if (ft_strequ(s, "noise"))
		return (NOISE);
	else if (ft_strequ(s, "chess_board"))
		return (CHESS_BOARD);
	else if (ft_strequ(s, "marble"))
		return (MARBLE);
	else if (ft_strequ(s, "wood"))
		return (WOOD);
	else
		return (0);
}
