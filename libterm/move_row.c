/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 13:14:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:28:56 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_row(int row)
{
	static char	*move;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("cv", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, row);
	write(2, command, strlen(command));
}
