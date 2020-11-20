/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_delete_char.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:48:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:33:37 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


/*
**	?????????????????????? don't work with utf8 !
**	if size is 0, function use strlen
*/
void	lt_insert_string_at(const char *s, uint32_t size)
{
	if (size == 0)
		size = strlen(s);
	lt_insert_mode_on();
	lt_insert_n_blank_char((int32_t)size);
	write(STDOUT_FILENO, s, size);
//	move_n_right(utf8_strlen(s));
	lt_insert_mode_off();
}
