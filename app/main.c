#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>

#include "../src/view.h"
#include "../src/game_state.h"

int 
main(int argc, char ** argv)
{
    GtkApplication * application = 
        gtk_application_new( 
             "edit.training.tictactoe"
             , G_APPLICATION_FLAGS_NONE);

    GameState * game_state = game_state_new();
    
    if(game_state == NULL)
        return EXIT_FAILURE;

     g_signal_connect(
         G_OBJECT(application)
         , "activate"
         , G_CALLBACK(view_activate_callback)
         , game_state);

     int result = g_application_run(
                      G_APPLICATION(application)
                      , argc
                      , argv);

    g_object_unref(application);
    game_state_finalize(game_state);
    
    return result;
}
