/*
 * This file is part of hildon-timeout-home-widget-example
 *
 * Copyright (C) 2009 Nokia Corporation. All rights reserved.
 *
 * This maemo code example is licensed under a MIT-style license,
 * that can be found in the file called "COPYING" in the root
 * directory.
 *
 */

#include <gtk/gtk.h>
#include <hildon/hildon.h>

#include "lib-timeout-home-widget.h"

#include "location-provider.h"

HD_DEFINE_PLUGIN_MODULE (TimeOutPlugin, time_out_plugin, HD_TYPE_HOME_PLUGIN_ITEM)

GtkTextBuffer *debugBuffer = NULL;

static void printDebug(const char *msg)
{
    if (debugBuffer != NULL) {
        gtk_text_buffer_insert_at_cursor(debugBuffer, msg, -1);
        gtk_text_buffer_insert_at_cursor(debugBuffer, "\n", -1);
    }
}

char debugStr[1024];
#define debug(...) sprintf(debugStr, __VA_ARGS__); printDebug(debugStr)

static void location_listener(double latitude, double longitude)
{
    debug("got location: %f, %f", latitude, longitude);
}

int locationTrackingOn = 0;
void search_button_clicked(GtkButton *button, gpointer user_data)
{
    if (!locationTrackingOn) {
        // Setup location tracking
        setup_location_provider();
        set_location_listener(location_listener);
        start_location_provider();

        locationTrackingOn = 1;
        debug("Location tracking started");
    } else {
        stop_location_provider();
        cleanup_location_provider();

        locationTrackingOn = 0;
        debug("Location tracking stopped");
    }
}

static GtkWidget *build_ui(void)
{
    GtkVBox *contents = GTK_VBOX(gtk_vbox_new(0, FALSE));
    GtkLabel *label = GTK_LABEL(gtk_label_new("Get me home"));
//     HildonPickerButton *action;
//     action = HILDON_PICKER_BUTTON (hildon_picker_button_new (HILDON_SIZE_FINGER_HEIGHT,
//                                         HILDON_BUTTON_ARRANGEMENT_VERTICAL));
//     HildonTouchSelector *action_selector;
//     action_selector = HILDON_TOUCH_SELECTOR (hildon_touch_selector_new_text ());
//     hildon_button_set_title (HILDON_BUTTON (action), "Action");
//     hildon_touch_selector_append_text (action_selector, "Blank Screen");
//     hildon_touch_selector_append_text (action_selector, "Suspend");
//     hildon_touch_selector_append_text (action_selector, "Turn Off");
//     hildon_picker_button_set_selector (action, action_selector);
//     hildon_picker_button_set_active (action, 0);

    GtkWidget* getmehomeButton = hildon_gtk_button_new(HILDON_SIZE_AUTO);
    gtk_button_set_label(GTK_BUTTON(getmehomeButton), "Search");

    g_signal_connect(getmehomeButton, "clicked", G_CALLBACK(search_button_clicked), NULL);

//     HildonTimeButton *time;
//     time = HILDON_TIME_BUTTON (hildon_time_button_new (HILDON_SIZE_FINGER_HEIGHT,
//                                         HILDON_BUTTON_ARRANGEMENT_VERTICAL));
//     hildon_time_button_set_time (time, 22, 00);

    GtkHBox *buttons = GTK_HBOX(gtk_hbox_new(0, TRUE));
    gtk_container_add(GTK_CONTAINER(buttons), GTK_WIDGET(getmehomeButton));
//     gtk_container_add (GTK_CONTAINER (buttons), GTK_WIDGET (action));
//     gtk_container_add (GTK_CONTAINER (buttons), GTK_WIDGET (time));

    GtkWidget *debugView = hildon_text_view_new();  // gtk_text_view_new();
    gtk_widget_set_size_request(GTK_WIDGET(debugView), 400, 200);
    debugBuffer = hildon_text_view_get_buffer(HILDON_TEXT_VIEW(debugView)); // gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    GtkWidget* debugScroller = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(debugScroller), GTK_WIDGET(debugView));

    gtk_box_pack_start(GTK_BOX(contents), GTK_WIDGET(label), FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(contents), GTK_WIDGET(buttons), FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(contents), GTK_WIDGET(debugScroller), FALSE, FALSE, 0);
    gtk_widget_show_all(GTK_WIDGET(contents));

    return GTK_WIDGET(contents);
}

static void
time_out_plugin_init (TimeOutPlugin *desktop_plugin)
{
    GtkWidget *contents = build_ui ();
    gtk_container_add (GTK_CONTAINER (desktop_plugin), contents);
}

static void
time_out_plugin_class_init (TimeOutPluginClass *class) {}

static void
time_out_plugin_class_finalize (TimeOutPluginClass *class) {}
