/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:15:50 by mzolotar          #+#    #+#             */
/*   Updated: 2025/06/03 07:57:52 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

/**
 * @brief Rotates the camera to the left by applying a negative angle.
 *
 * Updates direction and plane vectors using trigonometric rotation.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_camara_left(t_game *game)
{
	t_player	*p;
	double		rot;
	double		old_dir_x;
	double		old_plane_x;

	p = &game->player;
	rot = -p->rot_speed;
	old_dir_x = p->dir_x_player;
	p->dir_x_player = p->dir_x_player * cos(rot) - p->dir_y_player * sin(rot);
	p->dir_y_player = old_dir_x * sin(rot) + p->dir_y_player * cos(rot);
	old_plane_x = p->plane_x_player;
	p->plane_x_player = p->plane_x_player * cos(rot) - p->plane_y_player
		* sin(rot);
	p->plane_y_player = old_plane_x * sin(rot) + p->plane_y_player * cos(rot);
	re_draw_window(game);
}

/**
 * @brief Rotates the camera to the right by applying a positive angle.
 *
 * Uses rotation matrix to update player's direction and camera plane.
 *
 * @param game Pointer to the main game structure.
 * @return void
 */
void	move_camara_right(t_game *game)
{
	t_player	*p;
	double		rot;
	double		old_dir_x;
	double		old_plane_x;

	p = &game->player;
	rot = p->rot_speed;
	old_dir_x = p->dir_x_player;
	p->dir_x_player = p->dir_x_player * cos(rot) - p->dir_y_player * sin(rot);
	p->dir_y_player = old_dir_x * sin(rot) + p->dir_y_player * cos(rot);
	old_plane_x = p->plane_x_player;
	p->plane_x_player = p->plane_x_player * cos(rot) - p->plane_y_player
		* sin(rot);
	p->plane_y_player = old_plane_x * sin(rot) + p->plane_y_player * cos(rot);
	re_draw_window(game);
}

/**
 * @brief Handles key inputs and triggers movement or camera rotation.
 *
 * Maps keycodes to player movement, rotation, and exit functionality.
 *
 * @param keycode Integer representing the key pressed.
 * @param game Pointer to the main game structure.
 * @return int Always returns 0.
 */
int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_CODE_ESC)
		close_window(game);
	if (keycode == KEY_CODE_W)
		move_forward(game);
	if (keycode == KEY_CODE_A)
		move_left(game);
	if (keycode == KEY_CODE_S)
		move_backward(game);
	if (keycode == KEY_CODE_D)
		move_right(game);
	if (keycode == KEY_CODE_LEFT)
		move_camara_left(game);
	if (keycode == KEY_CODE_RIGHT)
		move_camara_right(game);
	return (0);
}
