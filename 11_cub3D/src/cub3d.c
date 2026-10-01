/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:40:02 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 19:38:59 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initializing(t_game *game)
{
	int	init;

	init = init_tgame(game);
	if (!game)
		exit_unexpected("Error initializing game", __FILE__, __LINE__,
			EXIT_FAILURE);
	if (init == 1)
	{
		free_tgame(game);
		exit_unexpected("Error initializing game", __FILE__, __LINE__,
			EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = new_tgame();
	initializing(game);
	if (check_args(argc, argv, game->file)
		|| read_cubfile(game->file)
		|| read_map(game, game->map)
		|| map_playable(game, game->map))
	{
		if (game->file->error_msg)
			game->error_msg = ft_strjoin_sfree(
					game->error_msg, game->file->error_msg,
					game->error_msg, NULL);
		ft_puterr(game->error_msg);
		ft_puterr("\n" CGRAY_DARK USAGE CRESET "\n");
		free_tgame(game);
		return (1);
	}
	start_game_loop(game);
	return (0);
}
