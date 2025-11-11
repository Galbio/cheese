/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:23:34 by gakarbou          #+#    #+#             */
/*   Updated: 2025/11/11 19:31:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cheese.h"

board_t	clone_board(board_t *board)
{
	board_t	dest = *board;

	dest.occupied_map = NULL;
	dest.possible_moves = malloc((dest.height + 1) * sizeof(char *));
	if (!dest.possible_moves)
		exit(1);
	dest.possible_moves[dest.height] = 0;
	for (int i = 0; i < dest.height; i++) {
		dest.possible_moves[i] = malloc((dest.width + 1) * sizeof(char));
		if (!dest.possible_moves[i])
			exit(1);
		memcpy(dest.possible_moves[i], board->possible_moves[i], dest.width);
	}
	dest.tiles = malloc((dest.height + 1) * sizeof(tile_t *));
	if (!dest.tiles)
		exit(1);
	for (int j = 0; j < dest.height; j++) {
		dest.tiles[j] = malloc(dest.width * sizeof(tile_t));
		if (!dest.tiles[j])
			exit(1);
		for (int i = 0; i < dest.width; i++)
			dest.tiles[j][i] = board->tiles[j][i];
	}
	dest.tiles[dest.height] = NULL;
	return (dest);
}

int	king_in_check(board_t *board_base, int color)
{
	board_t	board = clone_board(board_base);
	int		check = 0;
	tile_t	*tile;

	for (int j = 0; j < board.height; j++) {
		for (int i = 0; i < board.width; i++) {
			tile = &board.tiles[j][i];
			if (tile->nb_piece &&
				tile->pieces[0].color == color)
				update_possible_moves(&board, j, i);
		}
	}
	for (int j = 0; j < board.height; j++) {
		for (int i = 0; i < board.width; i++) {
			tile = &board.tiles[j][i];
			if (!board.possible_moves[j][i] || !tile->nb_piece)
				continue ;
			if (tile->pieces[0].type == KING &&
				tile->pieces[0].color != color)
				check = 1;
		}
	}
	free_board(&board, 0);
	return (check);
}
