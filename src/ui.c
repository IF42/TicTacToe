#include "ui.h"
#include <stdbool.h>
#include <gdk/gdk.h>


struct _UiWidget
{
    GtkWindow parrent;
    GtkWidget * drawing;
};


G_DEFINE_TYPE(UiWidget, ui_widget, GTK_TYPE_WINDOW)


static void
ui_widget_init(UiWidget * ui);


static void
ui_widget_class_init(UiWidgetClass * class);


static void
ui_widget_build(UiWidget * ui);


static void 
ui_widget_setup(UiWidget * ui);


static void
ui_widget_pack(UiWidget * ui);


static void
ui_widget_signals(UiWidget * ui);


GtkWidget *
ui_widget_new(GtkApplication * application)
{
    GtkWidget * widget = 
        GTK_WIDGET(g_object_new(
                        UI_TYPE_WIDGET
                        , "application"
                        , application
                        , NULL));

    ui_widget_build(UI_WIDGET(widget));
    ui_widget_pack(UI_WIDGET(widget));
    ui_widget_signals(UI_WIDGET(widget));
    ui_widget_setup(UI_WIDGET(widget));

    return widget;
}


GtkWidget *
ui_widget_drawing(UiWidget * ui)
{
    return ui->drawing;
}

void
ui_widget_set_drawing_callback(
        UiWidget * ui
        ,GtkDrawingAreaDrawFunc draw_func
        , gpointer param)
{
    gtk_drawing_area_set_draw_func(
            GTK_DRAWING_AREA(ui->drawing)
            , draw_func
            , param
            , NULL);
}


static void
ui_widget_build(UiWidget * ui)
{
    ui->drawing = gtk_drawing_area_new();
}


static void 
ui_widget_setup(UiWidget * ui)
{
    gtk_window_set_default_size(
        GTK_WINDOW(ui), 
        800, 
        800);
    
    gtk_window_set_resizable(GTK_WINDOW(ui), false);
}


static void
ui_widget_pack(UiWidget * ui)
{
    gtk_window_set_child(
          GTK_WINDOW(ui)
          , ui->drawing);
}


static void
ui_widget_signals(UiWidget * ui)
{
}


static void
ui_widget_init(UiWidget * ui)
{

}

static void
ui_widget_class_init(UiWidgetClass * class)
{

}

