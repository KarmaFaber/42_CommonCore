/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:40:59 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/08/06 20:50:40 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
** Returns an error message with the exact row and column for floodfill errors.
**
** @param	int x	Column position
** @param	int y	Row position
** @return	char *	Heap-allocated error message string, or NULL on malloc error
*/
char	*set_floodfill_error(int x, int y)
{
	char	*error_xy;
	char	*error_x;
	char	*error_y;

	error_x = ft_itoa(x + 1);
	if (!error_x)
		return (print_malloc_error(__FILE__, __LINE__), NULL);
	error_y = ft_itoa(y + 1);
	if (!error_y)
		return (print_malloc_error(__FILE__, __LINE__), free(error_x), NULL);
	error_xy = ft_strjoin("Error in map at row ", error_y);
	free(error_y);
	error_xy = ft_strjoin_sfree(error_xy, " and column ", error_xy, NULL);
	error_xy = ft_strjoin_sfree(error_xy, error_x, error_xy, NULL);
	free(error_x);
	if (!error_xy)
		return (print_malloc_error(__FILE__, __LINE__), NULL);
	return (error_xy);
}

/*
** Uses a dynamic stack to avoid stack overflow in large maps.
** Marks visited positions, detects open spaces, and sets an error message
** with the exact row and column if the map is open or not playable.
**
** @param	t_game *game	Pointer to the main game structure
** @param	t_map *map		Pointer to the map structure
** @param	int start_x		Starting column index (player position)
** @param	int start_y		Starting row index (player position)
** @return	int 0 if the area is closed, 1 if the map is open or invalid
*/
int	floodfill_stack(t_game *game, t_map *map, int start_x, int start_y)
{
	t_point	*stack;
	int		stack_size;
	int		top;

	stack_size = map->rows * map->cols;
	top = 0;
	stack = ft_calloc(sizeof(t_point), stack_size);
	if (!stack)
		return (print_malloc_error(__FILE__, __LINE__), 1);
	stack[top++] = (t_point){start_x, start_y};
	return (floodfill_iterative(game, map, stack, &top));
}

/*
** Processes the stack of map positions, marking visited cells and checking for
** open spaces.
** Frees the stack on error or when finished. Sets an error message with the
** exact row and column if the map is open or not playable.
**
** @param	t_game *game	Pointer to the main game structure
** @param	t_map *map		Pointer to the map structure
** @param	t_point *stack	Dynamic stack of map positions
** @param	int *top Pointer to the current stack index
** @return	int 0 if the area is closed, 1 if the map is open or invalid.
*/
int	floodfill_iterative(t_game *game, t_map *map, t_point *stack, int *top)
{
	t_point	p;
	int		x;
	int		y;

	while (*top > 0)
	{
		p = stack[--*top];
		x = p.x;
		y = p.y;
		if (x < 0 || y < 0 || y >= map->rows
			|| x >= (int)ft_strlen(map->map_str[y]))
			return (free(stack),
				game->file->error_msg = set_floodfill_error(x, y), 1);
		if (map->map_str[y][x] == '1')
			continue ;
		if (map->map_str[y][x] == ' ')
			return (free(stack),
				game->file->error_msg = set_floodfill_error(x, y), 1);
		if (map->map_str[y][x] == '0' || ft_strchr("NSEW", map->map_str[y][x]))
		{
			map->map_str[y][x] = '1';
			floodfill_adjust(map, stack, &p, top);
		}
	}
	return (free(stack), 0);
}

/*
** Uses stack overflow control to safely add neighbors for the iterative
** floodfill. Only pushes if there is space left in the stack.
**
** @param	t_map *map		Pointer to the map structure
** @param	t_point *stack	Stack of map positions
** @param	t_point *p		Current position
** @param	int *top		Pointer to stack index
*/
void	floodfill_adjust(t_map *map, t_point *stack, t_point *p, int *top)
{
	int	x;
	int	y;

	x = p->x;
	y = p->y;
	if (*top < map->rows * map->cols)
		stack[(*top)++] = (t_point){x + 1, y};
	if (*top < map->rows * map->cols)
		stack[(*top)++] = (t_point){x - 1, y};
	if (*top < map->rows * map->cols)
		stack[(*top)++] = (t_point){x, y + 1};
	if (*top < map->rows * map->cols)
		stack[(*top)++] = (t_point){x, y - 1};
}

/*
** Checks if the map is playable using floodfill and validates player count.
**
** @param	t_game *game Pointer to t_game structure
** @param	t_map *map	Pointer to t_map structure
** @return	int	1 if the map is invalid or does not meet subject, 0 if valid
*/
int	map_playable(t_game *game, t_map *map)
{
	char	**map_str_cp;

	if (map->p_total != 1)
		return (game->file->error_msg = ft_strdup(
				"Invalid number of players.\n"), 1);
	map_str_cp = map_str_copy(map->map_str, map->rows);
	if (!map_str_cp)
		return (print_malloc_error(__FILE__, __LINE__), 1);
	if (floodfill_stack(game, map, map->player_x, map->player_y) != 0)
	{
		ft_matrix_free(map_str_cp);
		return (game->file->error_msg = ft_strjoin_sfree(game->file->error_msg,
				"\nInvalid map. "
				"Not playable or does not meet subject requirements.\n",
				game->file->error_msg, NULL), 1);
	}
	ft_matrix_free(map->map_str);
	map->map_str = map_str_cp;
	return (0);
}
