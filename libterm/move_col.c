/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_col.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:05:57 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:27:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_col(int col)
{
	static char	*move;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("ch", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, col);
	write(2, command, strlen(command));
}
