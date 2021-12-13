#ifndef _UI_H_
#define _UI_H_

#include <gtk/gtk.h>

#define UI_TYPE_WIDGET (ui_widget_get_type())
#define UI_WIDGET_DRAWING(ui) (ui_widget_drawing(UI_WIDGET(ui)))

struct _UiWidget;


G_DECLARE_FINAL_TYPE(UiWidget, ui_widget, UI, WIDGET, GtkWindow)


GtkWidget *
ui_widget_new(GtkApplication * application);


GtkWidget *
ui_widget_drawing(UiWidget * ui);

void
ui_widget_set_drawing_callback(
        UiWidget * ui
        ,GtkDrawingAreaDrawFunc draw_func
        , gpointer param);


#endif
