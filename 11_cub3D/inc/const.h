/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:02:31 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 21:06:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

/*** Colors ***/
# define CRESET		"\001\x1B[0m\002"
# define CRED		"\001\x1B[31m\002"
# define CGREEN		"\001\x1B[32m\002"
# define CYELLOW	"\001\x1B[33m\002"
# define CBLUE		"\001\x1B[34m\002"
# define CBLUE2		"\001\x1B[36m\002"
# define CGRAY_LIG	"\001\x1B[37m\002"
# define CGRAY_DARK	"\001\x1B[90m\002"

/*** Errors ***/
# define USAGE			"**** Usage: ****\n./cub3D <map.cub>\n"
# define ERROR			"Error:\n"
# define ERR_PATH		"Please check all file paths and permissions.\n"
# define ERR_N_ARGS		"Incorrect number of arguments.\n"
# define ERR_CUB		"Invalid file extension. Expected '.cub'.\n"
# define ERR_FILE		"Failed to open the map file.\n"
# define ERR_CUB_EMPTY	"The .cub file may be empty.\n"
# define ERR_CUB_LOAD	"Failed to load the .cub file.\n"
# define ERR_CUB_ITEMS	"Missing or invalid elements in the .cub file.\n"
# define ERR_TEXTURES	"Failed to open one or more texture files.\n"
# define ERR_CUB_NO		"Check North texture.\n"
# define ERR_CUB_SO		"Check South texture.\n"
# define ERR_CUB_EA		"Check East texture.\n"
# define ERR_CUB_WE		"Check West texture.\n"
# define ERR_CUB_F		"Check floor color.\n"
# define ERR_CUB_C		"Check ceiling color.\n"
# define ERR_CUB_DUP	"Check for duplicate elements.\n"

/*** Const ***/
# define VALID_CHARS	" 01NSEW"

# ifndef ALLOW_SPACES
#  define ALLOW_SPACES	0
# endif

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3

# define XPM_SIZE	64

# define MAX_WIDTH_WIN	1920
# define MAX_HEIGHT_WIN	1080

# define WIN_WIDTH	1024
# define WIN_HEIGHT	760

/*** Key Codes */
# define KEY_CODE_W		119
# define KEY_CODE_A		97
# define KEY_CODE_S		115
# define KEY_CODE_D		100
# define KEY_CODE_LEFT	65361
# define KEY_CODE_RIGHT	65363
# define KEY_CODE_ESC	65307

#endif