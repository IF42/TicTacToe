#include "game.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>


static bool
game_is_empty_cell(GameField game_field)
{
    for(int i = 0; i < GAME_FIELD_ROW * GAME_FIELD_COLUMN; i++)
    {
        if(game_field[i] == CellEmpty)
            return true;
    }
    
    return false;
}


static bool
game_is_player_win(Cell cell, GameField game_field)
{
    int row        = 0;
    int column     = 0;
    int diag_right = 0;
    int diag_left  = 0;

    for(int i = 0; i < GAME_FIELD_ROW; i++)
    {
        for(int j = 0; j < GAME_FIELD_COLUMN; j++)
        {
            if(game_field[i*GAME_FIELD_COLUMN + j] == cell)
               column++;

            if(game_field[j*GAME_FIELD_ROW + i] == cell)
                row++;
        }

        if(row >= GAME_FIELD_ROW 
           || column >= GAME_FIELD_COLUMN)
            return true;

        column = 0;
        row = 0;

        if(game_field[i * GAME_FIELD_COLUMN + i] == cell)
            diag_right++;

        if(game_field[i * GAME_FIELD_ROW + GAME_FIELD_ROW - i - 1] == cell)
            diag_left ++;
    }

    return diag_right >= GAME_FIELD_ROW
         || diag_left >= GAME_FIELD_COLUMN;
}


void 
game_play(
    int row
    , int column
    , GameState * game_state)
{
    assert(0 <= row);
    assert(row < GAME_FIELD_ROW);
    assert(0 <= column);
    assert(column < GAME_FIELD_COLUMN);

    if(0 <= row  
        && row < GAME_FIELD_ROW
        && 0 <= column 
        && column < GAME_FIELD_COLUMN)
    {
        switch(game_state->state)
        {
            case GSPlayerX:
                if(game_state->game_field[row*GAME_FIELD_ROW+column] == CellEmpty)
                {    
                    game_state->game_field[row*GAME_FIELD_ROW+column] = CellX;

                    if(game_is_player_win(CellX, game_state->game_field) == true)
                        game_state->state = GSPlayerXWin;
                    else
                    {
                        if(game_is_empty_cell(game_state->game_field) == true)
                            game_state->state = GSPlayerO; 
                        else
                            game_state->state = GSIndecisively;
                    }
                }

                break;
            case GSPlayerO:       
                if(game_state->game_field[row*GAME_FIELD_ROW+column] == CellEmpty)
                {
                    game_state->game_field[row*GAME_FIELD_ROW+column] = CellO;

                    if(game_is_player_win(CellO, game_state->game_field) == true)
                        game_state->state = GSPlayerOWin;
                    else
                    {
                        if(game_is_empty_cell(game_state->game_field) == true)
                            game_state->state = GSPlayerX;
                        else
                            game_state->state = GSIndecisively;
                    }
                }

                break;
            case GSPlayerXWin:
            case GSPlayerOWin:
            case GSIndecisively:
                game_state_init(game_state);    
                break;
        }
    }   
}
