#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#define GAME_FIELD_ROW 3
#define GAME_FIELD_COLUMN 3

typedef enum
{
    GSPlayerX
    , GSPlayerO
    , GSPlayerXWin
    , GSPlayerOWin
    , GSIndecisively
}GameStateID;


typedef enum
{
    CellEmpty
    , CellX
    , CellO
}Cell;

typedef Cell * GameField;


typedef struct
{
    GameStateID state;
    GameField game_field;
}GameState;


GameState *
game_state_new();


void
game_state_init(GameState * game_state);


void
game_state_finalize(GameState * game_state);

#endif
