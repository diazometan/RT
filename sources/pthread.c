/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:12:31 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/22 17:34:36 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pthread	init_t_pthread(t_rt *rt, t_sdl *sdl, int xy[2], int si[2])
{
	t_pthread	obj;

	obj.rt = rt;
	obj.sdl = sdl;
	obj.x = xy[0];
	obj.y = xy[1];
	obj.size = si[0];
	obj.index = si[1];
	return (obj);
}

void		body_pthread(t_rt *rt, t_sdl *sdl, t_body_pthread body_pthread)
{
	int					summ;
	int					index;
	int					start;
	int					finish;

	index = -1;
	summ = 0;
	while (++index < body_pthread.size)
	{
		start = ((index) / (double)body_pthread.size) * rt->win_width;
		finish = ((index + 1) / (double)body_pthread.size) * rt->win_width;
		body_pthread.new_rts[index] = *rt;
		body_pthread.new_rts[index].count = 0;
		body_pthread.blocks[index] =
			init_t_pthread(&(body_pthread.new_rts[index]), sdl,
			(int[2]){rt->win_width, rt->win_height},
			(int[2]){body_pthread.size, index});
		(void)pthread_create(&body_pthread.tid[index], NULL,
			create_img_pthread, &body_pthread.blocks[index]);
	}
	while (summ != (rt->win_height * rt->win_width))
	{
		summ = 0;
		index = -1;
		while (++index < body_pthread.size)
			summ = summ + body_pthread.new_rts[index].count;
		progress_bar(summ / (double)(rt->win_height * rt->win_width), rt, sdl);
	}
	progress_bar(1, rt, sdl);
}

void		create_pthread(t_rt *rt, t_sdl *sdl)
{
	int					size;
	pthread_t			*tid;
	t_pthread			*blocks;
	t_rt				*new_rts;

	size = rt->threads;
	tid = (pthread_t *)check_memory(malloc(sizeof(pthread_t) * size));
	blocks = (t_pthread *)check_memory(malloc(sizeof(t_pthread) * size));
	new_rts = (t_rt *)check_memory(malloc(sizeof(t_rt) * size));
	body_pthread(rt, sdl, (t_body_pthread){size, tid, blocks, new_rts});
	free(tid);
	free(blocks);
	free(new_rts);
}
