#ifndef LOCATION_PROVIDER_H
#define LOCATION_PROVIDER_H

void setup_location_provider();
void cleanup_location_provider();

void start_location_provider();
void stop_location_provider();

void set_location_listener(void (*newListener)(double, double));

#endif
