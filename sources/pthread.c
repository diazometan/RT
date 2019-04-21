/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:12:31 by lwyl-the          #+#    #+#             */
/*   Updated: 2019/04/21 18:38:02 by lwyl-the         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pthread	init_t_pthread(t_rt *rt, t_sdl *sdl, int x[2], int y[2])
{
	t_pthread	obj;

	obj.rt = rt;
	obj.sdl = sdl;
	obj.x[0] = x[0];
	obj.x[1] = x[1];
	obj.y[0] = y[0];
	obj.y[1] = y[1];
	return (obj);
}

void		body_pthread(t_rt *rt, t_sdl *sdl, t_body_pthread body_pthread)
{
<<<<<<< HEAD
	int					index;
	int					start;
	int					finish;
=======
	int		index;
	int		start;
	int		finish;
>>>>>>> f82271f87eea397a7f1032d5c700a88e71a9e304

	index = -1;
	while (++index < body_pthread.size)
	{
		start = ((index) / (double)body_pthread.size) * rt->win_width;
		finish = ((index + 1) / (double)body_pthread.size) * rt->win_width;
		body_pthread.new_rts[index] = *rt;
		body_pthread.blocks[index] =
			init_t_pthread(&(body_pthread.new_rts[index]), sdl,
			(int[2]){start, finish},
			(int[2]){0, rt->win_height});
		(void)pthread_create(&body_pthread.tid[index], NULL,
			create_img_pthread, &body_pthread.blocks[index]);
	}
	index = -1;
	while (++index < body_pthread.size)
	{
		progress_bar(index / (double)body_pthread.size, rt, sdl);
		pthread_join(body_pthread.tid[index], NULL);
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
	tid = (pthread_t *)malloc(sizeof(pthread_t) * size);
	blocks = (t_pthread *)malloc(sizeof(t_pthread) * size);
	new_rts = (t_rt *)malloc(sizeof(t_rt) * size);
	body_pthread(rt, sdl, (t_body_pthread){size, tid, blocks, new_rts});
	free(tid);
	free(blocks);
	free(new_rts);
}
