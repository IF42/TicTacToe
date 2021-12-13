#include "game_state.h"
#include <stdlib.h>
#include <assert.h>


GameState *
game_state_new()
{
    GameState * game_state = malloc(sizeof(GameState));
    
    assert(game_state != NULL);

    if(game_state != NULL)
    {
        game_state->game_field = 
            malloc(sizeof(Cell) * 
            GAME_FIELD_ROW * 
            GAME_FIELD_COLUMN);       

        assert(game_state->game_field != NULL);

        if(game_state->game_field != NULL)
            game_state_init(game_state);
    }

    return game_state;
}


void
game_state_init(GameState * game_state)
{
    game_state->state = GSPlayerX;

    for(int i = 0
        ; i < (GAME_FIELD_ROW * GAME_FIELD_COLUMN)
        ; i++)
    {
        game_state->game_field[i] = CellEmpty;
    }
}

void
game_state_finalize(GameState * game_state)
{
    if(game_state != NULL)
    {  
        free(game_state);
    }
}

