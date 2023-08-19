#include "view.h"
#include "ui.h"
#include "game.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159 
#endif


typedef struct 
{
    GtkWidget * ui;
    GameState * game_state;
}View;


static void
view_signals(View * view);


static void
view_setup(View * view);


static void
view_finalize(GtkWidget * widget, View * view);


static void
view_drawing_callback(
    GtkDrawingArea * area
    , cairo_t * cr
    , int width
    , int height
    , gpointer param);


static void
view_draw_grid(
    int width
    , int height
    , double cell_width
    , double cell_height
    , cairo_t * cr);


static void
view_draw_game_state(
    GameState * game_state
    , cairo_t * cr
    , double cell_width
    , double cell_height);


static void
view_draw_circle(
    bool loose
    , int x
    , int y
    , double cell_width
    , double cell_height
    , cairo_t * cr);


static void
view_draw_cross(
    bool loose
    , int x
    , int y
    , double cell_width
    , double cell_height
    , cairo_t * cr);


static void 
view_click_callback(
    GtkGestureClick * gesture
    , int n_press
    , double x
    , double y
    , gpointer param);


void
view_activate_callback(
    GtkApplication * application
    , GameState * param)
{
    View * view = malloc(sizeof(View));

    view->ui = ui_widget_new(application);
    view->game_state = param;

    view_setup(view);
    view_signals(view);
}


static void
view_signals(View * view)
{
    ui_widget_set_drawing_callback(
        UI_WIDGET(view->ui)
        , view_drawing_callback
        , view->game_state); 

    GtkGesture * controller = 
        gtk_gesture_click_new ();

    g_signal_connect (
        controller
        , "pressed"
        , G_CALLBACK (view_click_callback)
        , view);

    gtk_widget_add_controller (
        GTK_WIDGET(view->ui)
        , GTK_EVENT_CONTROLLER(controller));

    g_signal_connect(
        G_OBJECT(view->ui)
        , "destroy"
        , G_CALLBACK(view_finalize)
        , view);
}


static void
view_setup(View * view)
{
    gtk_widget_set_visible(view->ui, true);
}


static void
view_drawing_callback(
    GtkDrawingArea * area
    , cairo_t * cr
    , int width
    , int height
    , gpointer param)
{
    (void) area;
    GameState * game_state = param;

    double cell_width  = 
        ((double) width)/((double) GAME_FIELD_COLUMN);
    double cell_height = 
        ((double) height)/((double) GAME_FIELD_ROW);

    view_draw_grid(
        width
        , height
        , cell_width
        , cell_height
        , cr);

    view_draw_game_state(
        game_state
        , cr
        , cell_width
        , cell_height);   
}


static void
view_draw_game_state(
    GameState * game_state
    , cairo_t * cr
    , double cell_width
    , double cell_height)
{
    for(int i = 0; i < GAME_FIELD_ROW*GAME_FIELD_COLUMN; i++)
    {
        switch(game_state->game_field[i])
        {
        case CellX:
            view_draw_cross(
                game_state->state == GSPlayerOWin 
                || game_state->state == GSIndecisively
                , i%GAME_FIELD_COLUMN * cell_width
                , i/GAME_FIELD_ROW * cell_height
                , cell_width
                , cell_height
                , cr);
            break;
        case CellO:
            view_draw_circle(
                game_state->state == GSPlayerXWin
                || game_state->state == GSIndecisively
                , i%GAME_FIELD_COLUMN * cell_width
                , i/GAME_FIELD_ROW * cell_height
                , cell_width
                , cell_height
                , cr);
            break;
        case CellEmpty:
            break;
        }    
    }
}


static void
view_draw_cross(
    bool loose
    , int x
    , int y
    , double cell_width
    , double cell_height
    , cairo_t * cr)
{
    cairo_save (cr);
    
    if(loose == false)
        cairo_set_source_rgb(cr, 0, 0, 1);
    else
        cairo_set_source_rgb(cr, 0.5,0.5, 0.5);

    cairo_set_line_width(cr, 20);

    cairo_move_to(
        cr
        , x+cell_width*0.2
        , y+cell_height*0.2);

    cairo_line_to(
        cr
        , x+cell_width*0.8
        , y+cell_height*0.8);

    cairo_move_to(
        cr
        , x+cell_width*0.8
        , y+cell_height*0.2);
    
    cairo_line_to(
        cr
        , x+cell_width*0.2
        , y+cell_height*0.8);

    cairo_stroke(cr);

    cairo_restore (cr);
}


static void
view_draw_circle(
    bool loose
    , int x
    , int y
    , double cell_width
    , double cell_height
    , cairo_t * cr)
{
    cairo_save (cr);

    if(loose == false)
        cairo_set_source_rgb(cr, 1, 0, 0);
    else
        cairo_set_source_rgb(cr, 0.5,0.5, 0.5);
    
    cairo_translate (
        cr
        , x + cell_width / 2.0
        , y + cell_height / 2.0);

    cairo_scale(
        cr
        , cell_width*0.6/10.0
        , cell_height*0.6/10.0);
    
    cairo_set_line_width(cr, 10);

    cairo_arc(cr, 0, 0, 1, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_restore (cr);
}


static void
view_draw_grid(
    int width
    , int height
    , double cell_width
    , double cell_height
    , cairo_t * cr)
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 4);

    for(int i = 0; i < GAME_FIELD_ROW; i++)
    {
        cairo_move_to(cr, 0, cell_height*i);
        cairo_line_to(cr, width, cell_height*i);
    }

    for(int i = 0; i < GAME_FIELD_COLUMN; i++)
    {
        cairo_move_to(cr, cell_width*i, 0);
        cairo_line_to(cr, cell_width*i, height);
    }

    cairo_stroke(cr);
}


static void 
view_click_callback(
    GtkGestureClick * gesture
    , int n_press
    , double x
    , double y
    , gpointer param)
{
    (void) gesture;

    if(n_press >=2)
    {
        View * view = param;
    
        int row =  y / (800/GAME_FIELD_COLUMN);
        int column = x / (800/GAME_FIELD_ROW);

        game_play(row, column, view->game_state);   
        gtk_widget_queue_draw(UI_WIDGET_DRAWING(view->ui));
    }
}


static void
view_finalize(GtkWidget * widget, View * view)
{
    (void) widget;

    if(view != NULL)
        free(view);
}

