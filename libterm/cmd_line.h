/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmd_line.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 20:04:02 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 19:36:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CMD_LINE_H
# define CMD_LINE_H

# define SELECT_MODE	0x1
# define PASTE_MODE		0x2
# define EXPLORE_MODE	0x4
# define NORMAL_MODE	0x0

# define CMD_SEP		" `'\"\\+@:,;|<>&"

# define SELECT_SORT	0
# define SELECT_RESTORE	1

# define READ_LEN		128

//# include "utf8.h"
# include "cmd_struct.h"
//# include "global.h"
# include <unistd.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# define BLOCK_SIZE	80

/*
**	DEBUG (debug_print_cmd.c)
*/
void	print_cmd_info(t_cmds *cmd);

/*
** escape_action.c
*/
void	l_arrow(t_cmds *cmd);
void	u_arrow(t_cmds *cmd);
void	d_arrow(t_cmds *cmd);
void	r_arrow(t_cmds *cmd);
void	alt_left(t_cmds *cmd);
void	alt_right(t_cmds *cmd);
void	maj_right(t_cmds *cmd);
void	maj_left(t_cmds *cmd);
void	delete(t_cmds *cmd);
void	escape(t_cmds *cmd);
void	f1(t_cmds *cmd);
void	f2(t_cmds *cmd);
void	f3(t_cmds *cmd);
void	f4(t_cmds *cmd);
void	f5(t_cmds *cmd);
void	f6(t_cmds *cmd);
void	f7(t_cmds *cmd);
void	f8(t_cmds *cmd);
void	f9(t_cmds *cmd);
void	f10(t_cmds *cmd);
void	f12(t_cmds *cmd);

/*
** control_action.c
*/
void	ctrl_sp(t_cmds *cmd);
void	ctrl_a(t_cmds *cmd);
void	ctrl_b(t_cmds *cmd);
void	ctrl_c(t_cmds *cmd);
void	ctrl_d(t_cmds *cmd);
void	ctrl_e(t_cmds *cmd);
void	ctrl_f(t_cmds *cmd);
void	ctrl_g(t_cmds *cmd);
void	ctrl_h(t_cmds *cmd);
void	ctrl_k(t_cmds *cmd);
void	ctrl_l(t_cmds *cmd);
void	ctrl_n(t_cmds *cmd);
void	ctrl_o(t_cmds *cmd);
void	ctrl_p(t_cmds *cmd);
void	ctrl_r(t_cmds *cmd);
void	ctrl_t(t_cmds *cmd);
void	ctrl_u(t_cmds *cmd);
void	ctrl_v(t_cmds *cmd);
void	ctrl_w(t_cmds *cmd);
void	ctrl_x(t_cmds *cmd);
void	ctrl_y(t_cmds *cmd);
void	ctrl_z(t_cmds *cmd);

void	tabulation(t_cmds *cmd);

/*
**	cmd_line/print_prompt.c
*/
void		print_prompt(t_cmds *cmd, uint32_t *screen_y);
char		*interpret_prompt(const char *prompt);

/*
**	execute_special_keys.c
*/
uint32_t	execute_escape_sequence(t_cmds *cmd, char *buf, uint32_t *len);
void	execute_control(t_cmds *cmd, char c);

/*
**	backspace.c
*/
void	backspace(t_cmds *cmd);

/*
**	cmd_line/insert_string.c
**
**	insert an utf-8 string in the cursor position and print the modification
*/
void	insert_string_to_cmd_and_display(t_cmds *cmd, const char buf[],
											uint32_t size);

/*
**	cmd_line/display_cmd_and_move_cursor.c
*/
void	display_cmd_and_move_cursor(t_cmds *cmd);

/*
**	cmd_line/display_cmd_without_highlighting_and_move_cursor.c
*/
void	display_cmd_without_highlighting_and_move_cursor(t_cmds *cmd);

/*
**	cmd_line/display_cmd_with_highlighting_and_move_cursor.c
*/
void	display_cmd_with_highlighting_and_move_cursor(t_cmds *cmd);

/*
**	cmd_line/cmd.c
*/
void	free_cmd(t_cmds *cmd);
void	init_cmd(t_cmds *cmd, const char *prompt);

/*
**	cmd_line/is_pasted_text.c
*/
int		is_pasted_text(const char buf[], uint32_t len);

/*
**	cmd_line/nalloc.c
*/
void	*nalloc(void *ptr, uint32_t plen, uint32_t nlen, size_t elem_size);
int		nalloc_if_needed(t_cmds *cmd, uint32_t y, uint32_t size);

/*
**	cmd_line/print_cmd_from_cursor.c
*/
void	print_cmd_from_cursor(t_cmds *cmd);

/*
**	cmd_line/paste.c
*/
void	get_pasted_text_and_display(uint32_t i, uint32_t len, t_cmds *cmd, char buf[]);

/*
**	cmd_line/print_paste.c
*/
void	print_paste(t_cmds *cmd);

/*
**	cmd_line/is_cmd_bigger_than_screen.c
*/
uint8_t		is_cmd_bigger_than_screen(t_cmds *cmd);

/*
**	cmd_line/window_resized.c
*/
void	window_resized(int sig);

/*
**	cmd_line/get_user_cmd.c
*/
void	get_user_cmd(t_cmds *cmd);

/*
**	cmd_line/print_paste.c
*/
void	display_cmd_with_highlighting_and_move_cursor(t_cmds *cmd);

/*
**	cmd_line/move_cursor.c
*/
void	move_cursor(t_cmds *cmd);

/*
**	cmd_line/delete_selection.c
*/
void	delete_selection(t_cmds *cmd);

/*
**	cmd_line/sort_selection_start_end.c
**
**	flag == SELECT_SORT
**	inverte selection start and end if not sorted in ascending order
**
**	flag == SELECT_RESTORE
**	restore the initial order of the selection
*/
void	sort_selection_start_end(t_select *s, uint8_t flag);

/*
**	cmd_line/paste_buffer.c
**
**	insert the content of [buf] in [cmd] at the position of [cmd->curs]
*/
void	paste_buffer(t_cmds *cmd, char *buf, uint32_t len);

/*
**	cmd_line/insert_blank_lines.c
**
**	insert [nlines] new lines in position [y] of [cmd]
*/
void	insert_blank_lines(t_cmds *cmd, uint32_t nlines, uint32_t y);

/*
**	cmd_line/merge_cmd.c
*/
extern unsigned char	*merge_cmd(t_cmds *cmd, size_t *size);

#endif
