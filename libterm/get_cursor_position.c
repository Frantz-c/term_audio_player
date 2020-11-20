/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_cursor_position.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 14:56:18 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:44:37 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_get_cursor_position(uint32_t *x, uint32_t *y)
{
	char	buf[8];

	*x = 0u;
	*y = 0u;
	write(STDERR_FILENO, "\x1B[6n", 4);
	while (read(STDIN_FILENO, buf, 2) && *buf != '\x1B');
	while (read(STDIN_FILENO, buf, 1) && *buf != ';')
		*y = (*y * 10) + (*buf - '0');
	while (read(STDIN_FILENO, buf, 1) && *buf != 'R')
		*x = (*x * 10) + (*buf - '0');
	(*y)--;
	(*x)--;
}
