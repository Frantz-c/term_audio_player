/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_list.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:19:53 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/20 13:12:28 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef KEY_LIST_H
# define KEY_LIST_H

# define L_ARROW	"\x1B[D"
# define U_ARROW	"\x1B[A"
# define D_ARROW	"\x1B[B"
# define R_ARROW	"\x1B[C"

/*
**	MAJ_UP and MAJ_DOWN are the same as U_ARROW and D_ARROW
*/

# define MAJ_RIGHT	"\x1B[1;2D"
# define MAJ_LEFT	"\x1B[1;2C"

# define ALT_LEFT	"\x1B""b"
# define ALT_RIGHT	"\x1B""f"

# define DELETE		"\x1B[3~"

/*
**	F11 doesn't exist
*/

# define F1			"\x1BOP"
# define F2			"\x1BOQ"
# define F3			"\x1BOR"
# define F4			"\x1BOS"
# define F5			"\x1B[15~"
# define F6			"\x1B[17~"
# define F7			"\x1B[18~"
# define F8			"\x1B[19~"
# define F9			"\x1B[20~"
# define F10		"\x1B[21~"
# define F12		"\x1B[24~"

/*
**	CTRL_Q and CTRL_S doesn't exist.
**	CTRL_J and CTRL_M are the same value as LINEFEED
**	CTRL_I == '\t'
*/

# define CTRL_SP	0
# define CTRL_A		1
# define CTRL_B		2
# define CTRL_C		3
# define CTRL_D		4
# define CTRL_E		5
# define CTRL_F		6
# define CTRL_G		7
# define CTRL_H		8
# define CTRL_I		'\t'
# define CTRL_J		'\n'
# define CTRL_K		11
# define CTRL_L		12
# define CTRL_M		'\n'
# define CTRL_N		14
# define CTRL_O		15
# define CTRL_P		16
# define CTRL_R		18
# define CTRL_T		20
# define CTRL_U		21
# define CTRL_V		22
# define CTRL_W		23
# define CTRL_X		24
# define CTRL_Y		25
# define CTRL_Z		26

# define NULBYTE		0
# define LINEFEED		"\xA"
# define ENTER			'\n'
# define BACKSPACE		127
# define ESCAPE			"\x1B"
# define TABULATION		'\t'

# define F5_LEN				strlen(F5)
# define F6_LEN				strlen(F6)
# define F7_LEN				strlen(F7)
# define F8_LEN				strlen(F8)
# define MAJ_LEFT_LEN		strlen(MAJ_LEFT)
# define MAJ_RIGHT_LEN		strlen(MAJ_RIGHT)
# define F9_LEN				strlen(F9)
# define F10_LEN			strlen(F10)
# define F12_LEN			strlen(F12)
# define DELETE_LEN			strlen(DELETE)
# define F1_LEN				strlen(F1)
# define F2_LEN				strlen(F2)
# define F3_LEN				strlen(F3)
# define F4_LEN				strlen(F4)
# define U_ARROW_LEN		strlen(U_ARROW)
# define D_ARROW_LEN		strlen(U_ARROW)
# define R_ARROW_LEN		strlen(R_ARROW)
# define L_ARROW_LEN		strlen(L_ARROW)
# define ALT_LEFT_LEN		strlen(ALT_LEFT)
# define ALT_RIGHT_LEN		strlen(ALT_RIGHT)

#endif
