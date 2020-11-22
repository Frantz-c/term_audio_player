/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_terminal_size.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:31:08 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 19:39:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

void	lt_get_terminal_size(uint32_t *term_w, uint32_t *term_h)
{
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	*term_w = (uint32_t)ws.ws_col;
	*term_h = (uint32_t)ws.ws_row;
}
