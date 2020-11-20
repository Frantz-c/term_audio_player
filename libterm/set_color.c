/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_color.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:31:22 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:29:56 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_set_color(int color1, int color2, int video_mode)
{
	if (color1 != LT_NONE)
		lt_set_fg_color(color1);
	if (color2 != LT_NONE)
		lt_set_bg_color(color2);
	if (video_mode != LT_NONE)
		lt_set_video_mode(video_mode);
}
