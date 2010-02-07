#include "coordinate-system.h"

#include <math.h>
#include <stdio.h>

struct TestCoordinate {
    KKJ x, y;
    double lon, lat;
};

// Test data extracted from example on page
// http://developer.reittiopas.fi/pages/fi/http-get-interface.php
struct TestCoordinate testData[] = {
    { 2556686, 6682815, 25.02051, 60.2528 },
    { 2546340, 6675352, 24.832, 60.18713 },
    { 2557985, 6685213, 25.04465, 60.27414 },
    { 2556532, 6682578, 25.01767, 60.2507 },
    { 2524959, 6686629, 24.44804, 60.2902 },
    { 2559094, 6693721, 25.06718, 60.35033 },
    { 2556861, 6683030, 25.02373, 60.25471 },
    { 2556888, 6682971, 25.0242, 60.25417 },
    { 2560257, 6698983, 25.08981, 60.39737 },
    { 2562518, 6686969, 25.12709, 60.28923 },
    { 2536615, 6673635, 24.65643, 60.1727 },
    { 2559118, 6693833, 25.06764, 60.35133 },
    { 2559182, 6693629, 25.06874, 60.34949 },
    { 2556947, 6682640, 25.02518, 60.25119 },
    { 2556822, 6682723, 25.02294, 60.25196 },
    { 2559089, 6693605, 25.06705, 60.34929 },
    { 2546445, 6675512, 24.83393, 60.18855 },
    { 2556964, 6682609, 25.02547, 60.25091 },
    { 2556740, 6682861, 25.0215, 60.25321 },
    { 2559002, 6694007, 25.06559, 60.35291 }};


int testKKJxytoWGS84lola() {
    double lon, lat;
    int result = 0;
    int i;

    for (i = 0; i < sizeof(testData) / sizeof(struct TestCoordinate); ++i) {
        KKJxy_to_WGS84lola(testData[i].x, testData[i].y, &lon, &lat);

        if (fabs(testData[i].lon - lon) < 0.001 && fabs(testData[i].lat - lat) < 0.001) {
            ;
        } else {
            printf("Got: (%f, %f), expected: (%f, %f)\n", lon, lat, testData[i].lon, testData[i].lat);
            result = -1;
        }
    }

    return result;
}


int testWGS84lolatoKKJxy() {
    KKJ x, y;
    int result = 0;
    int i;

    for (i = 0; i < sizeof(testData) / sizeof(struct TestCoordinate); ++i) {
        WGS84lola_to_KKJxy(testData[i].lon, testData[i].lat, &x, &y);

        if (abs(testData[i].x - x) < 2 && abs(testData[i].y - y) < 2) {
            ;
        } else {
            printf("Got: (%u, %u), expected: (%u, %u)\n", x, y, testData[i].x, testData[i].y);
            result = -1;
        }
    }

    return result;
}



int main(int argc, char* argv[]) {
    int testResult = 0;

    // Test transforming from KKJxy to WGS84lonlat
    testResult = testKKJxytoWGS84lola();

    if (testResult == 0) {
        printf("All tests in testKKJxytoWGS84lola passed\n");
    }

    // Test transforming from WGS84lonlat to KKJxy
    testResult = testWGS84lolatoKKJxy();

    if (testResult == 0) {
        printf("All tests in testWGS84lolatoKKJxy passed\n");
    }


    return 0;
}
