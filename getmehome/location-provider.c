#include "location-provider.h"

#include <location/location-gps-device.h>
#include <location/location-gpsd-control.h>

void (*listener)(double, double) = NULL;

/*static void on_error(LocationGPSDControl *control, LocationGPSDControlError error, gpointer data)
{
	g_debug("location error: %d... quitting", error);
	g_main_loop_quit((GMainLoop *) data);
}*/

static void on_changed(LocationGPSDevice *device, gpointer data)
{
    if (device == NULL || listener == NULL) {
        return;
    }

    if (device->fix) {
        if (device->fix->fields & LOCATION_GPS_DEVICE_LATLONG_SET) {
            listener(device->fix->latitude, device->fix->longitude);
        }
    }
}

/*static void on_stop(LocationGPSDControl *control, gpointer data)
{
	g_debug("quitting");
	g_main_loop_quit((GMainLoop *) data);
}*/

/*static gboolean start_location(gpointer data)
{
	location_gpsd_control_start((LocationGPSDControl *) data);
	return FALSE;
}*/

LocationGPSDControl *control = NULL;
LocationGPSDevice *device = NULL;

void setup_location_provider()
{
// 	GMainLoop *loop;

// 	g_type_init();

// 	loop = g_main_loop_new(NULL, FALSE);

    if (control != NULL) {
        return;
    }

    control = location_gpsd_control_get_default();
    device = g_object_new(LOCATION_TYPE_GPS_DEVICE, NULL);

    g_object_set(G_OBJECT(control),
        "preferred-method", LOCATION_METHOD_USER_SELECTED,
        "preferred-interval", LOCATION_INTERVAL_DEFAULT,
        NULL);

// 	g_signal_connect(control, "error-verbose", G_CALLBACK(on_error), loop);
    g_signal_connect(device, "changed", G_CALLBACK(on_changed), control);
// 	g_signal_connect(control, "gpsd-stopped", G_CALLBACK(on_stop), loop);

// 	g_idle_add(start_location, control);

// 	g_main_loop_run(loop);
}

void cleanup_location_provider()
{
    if (control != NULL) {
        location_gpsd_control_stop(control);

        g_object_unref(device);
        g_object_unref(control);
        device = NULL;
        control = NULL;
    }
}

void start_location_provider()
{
    if (control != NULL) {
        location_gpsd_control_start(control);
    }
}

void stop_location_provider()
{
    if (control != NULL) {
        location_gpsd_control_stop(control);
    }
}

void set_location_listener(void (*newListener)(double, double))
{
    listener = newListener;
}
