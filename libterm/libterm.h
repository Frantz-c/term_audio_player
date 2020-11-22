/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 12:52:12 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 20:41:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBTERM_H
# define LIBTERM_H

# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdint.h>
# include <string.h>
# include "key_list.h"
# include "cmd_struct.h"

# define MOVE_CURSOR			"cm"
# define MOVE_CURSOR_HOME		"ho"
# define MOVE_CURSOR_END		"ll"
# define MOVE_UP				"up"
# define MOVE_N_UP				"UP"
# define MOVE_DOWN				"do"
# define MOVE_N_DOWN			"DO"
# define MOVE_LEFT				"le"
# define MOVE_N_LEFT			"LE"
# define MOVE_RIGHT				"nd"
# define MOVE_N_RIGHT			"RI"
# define CLEAR_SCREEN			"cl"
# define CLEAR_SCREEN_FROM		"cd"
# define CLEAR_LINE_AFTER		"ce"
# define CLEAR_N_CHAR			"ec"
# define INSERT_MODE_ON			"im"
# define INSERT_MODE_OFF		"ei"
# define INSERT_BLANK_CHAR		"ic"
# define INSERT_N_BLANK_CHAR	"IC"

# define LT_NONE				0xffff

# define LT_NOECHO				1u
# define LT_RESTORE				2u
# define LT_NOBLOC				4u
# define LT_NOSIG				8u

# define LT_BOLD				0x1
# define LT_UNDERLINE			0x2
# define LT_BLINK				0x4
# define LT_HALFBRIGHT			0x8
# define LT_INVISIBLE			0x10
# define LT_PROTECTED			0x20
# define LT_REVERSE				0x40
# define LT_MODE_END			0x80

# define LT_TRUE				1
# define LT_FALSE				0

# define LT_ON					1
# define LT_OFF					0

# define W_RESIZED				0x1u
# define H_RESIZED				0x2u

# define PASTE_MODE_ON			"\x1B[?2004h"
# define PASTE_MODE_OFF			"\x1B[?2004l"
# define PASTE_START			"\x1B[200~"
# define PASTE_END				"\x1B[201~"

//extern t_term				g_term;

/*
**	libterm/init.c
*/
int		lt_init(void);

/*
**	libterm/update_terminal_size.c
*/
void	lt_get_terminal_size(uint32_t *term_w, uint32_t *term_h);

/*
**	libterm/terminal_mode.c
*/
int		lt_terminal_mode(uint32_t mode);

/*
**	libterm/clear_screen.c
*/
void	lt_clear_screen(void);

/*
**	libterm/clear_screen_from_cursor.c
*/
void	lt_clear_screen_from_cursor(void);

/*
**	libterm/clear_n_char.c
*/
void	lt_clear_n_char(int n);

/*
**	libterm/erase_end_of_line.c
*/
void	lt_clear_end_of_line(void);

/*
**	libterm/move_right.c
*/
void	lt_move_right(void);
void	lt_move_n_right(int n);

/*
**	libterm/move_left.c
*/
void	lt_move_left(void);
void	lt_move_n_left(int n);

/*
**	libterm/move_up.c
*/
void	lt_move_up(void);
void	lt_move_n_up(int n);

/*
**	libterm/move_down.c
*/
void	lt_move_down(void);
void	lt_move_n_down(int n);

/*
**	libterm/move_cursor.c
*/
void	lt_move_cursor(int col, int row);

/*
**	libterm/move_cursor_home.c
*/
void	lt_move_cursor_home(void);

/*
**	libterm/move_cursor_end.c
*/
void	lt_move_cursor_end(void);

/*
**	libterm/move_col.c
*/
void	lt_move_col(int col);

/*
**	libterm/move_row.c
*/
void	lt_move_row(int row);

/*
**	libterm/insert_line_before_cursor.c
*/
void	lt_insert_line_before(void);

/*
**	libterm/insert_n_lines_before.c
*/
void	lt_insert_n_lines_before(int n);

/*
**	libterm/delete_current_line.c
*/
void	lt_delete_current_line(void);

/*
**	libterm/delete_n_lines_from.c
*/
void	lt_delete_n_lines_from(int n);

/*
**	libterm/insert_mode.c
*/
void	lt_insert_mode_on(void);
void	lt_insert_mode_off(void);

/*
**	libterm/insert_n_blank_char.c
*/
void	lt_insert_n_blank_char(int n);

/*
**	libterm/insert_blank_char.c
*/
void	lt_insert_blank_char(void);

/*
**	libterm/insert_string_at.c
**	if size is 0, function use strlen
*/
void	lt_insert_string_at(const char *s, uint32_t size);

/*
**	libterm/bracketed_paste_mode.c
*/
void	lt_enable_paste_mode(void);
void	lt_disable_paste_mode(void);

/*
**	libterm/display_set_color.c
*/
void	lt_set_color(int color1, int color2, int video_mode);

/*
**	libterm/reset_attributes.c
*/
void	lt_reset_attr(void);

/*
**	libterm/set_fg_color.c
*/
void	lt_set_fg_color(int color);

/*
**	libterm/set_bg_color.c
*/
void	lt_set_bg_color(int color);

/*
**	libterm/set_video_mode.c
*/
void	lt_set_video_mode(int mode);

/*
**	libterm/scroll.c
*/
void	lt_scroll_up(void);
void	lt_scroll_down(void);
void	lt_scroll_n_up(int n);
void	lt_scroll_n_down(int n);


/*
**	libterm/get_cutsor_position.c
*/
void	lt_get_cursor_position(uint32_t *x, uint32_t *y);

/*
**`libterm/full_screen_mode.c
*/
void	lt_full_screen_mode(uint8_t on);

void	lt_show_cursor(uint8_t show_cursor);
	
#endif
