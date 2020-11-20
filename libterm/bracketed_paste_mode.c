/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bracketed_paste_mode.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 10:33:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 13:45:05 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"
#include "cmd_line.h"

void	lt_enable_paste_mode(void)
{
	write(STDERR_FILENO, PASTE_MODE_ON, strlen(PASTE_MODE_ON));
}

void	lt_disable_paste_mode(void)
{
	write(STDERR_FILENO, PASTE_MODE_OFF, strlen(PASTE_MODE_OFF));
}
