/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:03:40 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:27:46 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_cursor(int col, int row)
{
	static char	*move;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("cm", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, col, row);
	write(2, command, strlen(command));
}
