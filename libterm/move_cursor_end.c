/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_end.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:05:32 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:27:55 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_cursor_end(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("ll", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}
