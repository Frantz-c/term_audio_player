/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_bg_color.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:34:18 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:29:52 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_set_bg_color(int color)
{
	static const char	*bg = NULL;
	char				*cmd;

	if (!bg)
	{
		if ((bg = tgetstr("AB", NULL)) == NULL)
			return ;
	}
	cmd = tgoto(bg, 0, color);
	write(2, cmd, strlen(cmd));
}
