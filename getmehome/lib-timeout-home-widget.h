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

#ifndef TIME_OUT_PLUGIN_H
#define TIME_OUT_PLUGIN_H

#include <glib-object.h>

#include <libhildondesktop/libhildondesktop.h>

G_BEGIN_DECLS

typedef struct _TimeOutPlugin TimeOutPlugin;
typedef struct _TimeOutPluginClass TimeOutPluginClass;

#define TIME_OUT_TYPE_HOME_PLUGIN (time_out_home_plugin_get_type ())

#define TIME_OUT_HOME_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                        TIME_OUT_TYPE_HOME_PLUGIN, TimeOutHomePlugin))

#define TIME_OUT_HOME_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), \
                        TIME_OUT_TYPE_HOME_PLUGIN, TimeOutHomePluginClass))

#define TIME_OUT_IS_HOME_PLUGIN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                        TIME_OUT_TYPE_HOME_PLUGIN))

#define TIME_OUT_IS_HOME_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                        TIME_OUT_TYPE_HOME_PLUGIN))

#define TIME_OUT_HOME_PLUGIN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                        TIME_OUT_TYPE_HOME_PLUGIN, TimeOutHomePluginClass))

struct _TimeOutPlugin
{
    HDHomePluginItem hitem;
};

struct _TimeOutPluginClass
{
    HDHomePluginItemClass parent_class;
};

GType time_out_home_plugin_get_type(void);

G_END_DECLS

#endif
