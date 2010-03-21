#include "coordinatesystemtransformer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "stlhelpers.h"

#include <QPair>

class CoordinateSystemTransformerTest : public ::testing::Test
{
public:
    QList<QPair<QTM_NAMESPACE::QGeoCoordinate, KKJ> > testData;

    CoordinateSystemTransformerTest() {
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.2528, 25.02051), KKJ(6682815, 2556686));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.18713, 24.832), KKJ(6675352, 2546340));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.27414, 25.04465), KKJ(6685213, 2557985));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.2507, 25.01767), KKJ(6682578, 2556532));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.2902, 24.44804), KKJ(6686629, 2524959));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.35033, 25.06718), KKJ(6693721, 2559094));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25471, 25.02373), KKJ(6683030, 2556861));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25417, 25.0242), KKJ(6682971, 2556888));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.39737, 25.08981), KKJ(6698983, 2560257));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.28923, 25.12709), KKJ(6686969, 2562518));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.1727, 24.65643), KKJ(6673635, 2536615));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.35133, 25.06764), KKJ(6693833, 2559118));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.34949, 25.06874), KKJ(6693629, 2559182));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25119, 25.02518), KKJ(6682640, 2556947));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25196, 25.02294), KKJ(6682723, 2556822));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.34929, 25.06705), KKJ(6693605, 2559089));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.18855, 24.83393), KKJ(6675512, 2546445));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25091, 25.02547), KKJ(6682609, 2556964));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.25321, 25.0215), KKJ(6682861, 2556740));
        testData << qMakePair(QTM_NAMESPACE::QGeoCoordinate(60.35291, 25.06559), KKJ(6694007, 2559002));
    }
};

TEST_F(CoordinateSystemTransformerTest, WGS84CoordinatesToKKJCoordinates)
{
    QListIterator<QPair<QTM_NAMESPACE::QGeoCoordinate, KKJ> > it(testData);
    while (it.hasNext()) {
        const QPair<QTM_NAMESPACE::QGeoCoordinate, KKJ> &datum = it.next();
        KKJ result = CoordinateSystemTransformer::transformToKKJ(datum.first);
        KKJ expected = datum.second;
        // Allow one unit difference from the expected
        int northDiff = abs((long)expected.northing() - (long)result.northing());
        int eastDiff = abs((long)expected.easting() - (long)result.easting());
        EXPECT_LE(northDiff, 1);
        EXPECT_LE(eastDiff, 1);
    }
}

TEST_F(CoordinateSystemTransformerTest, KKJCoordinatesToWGS84Coordinates)
{
    QListIterator<QPair<QTM_NAMESPACE::QGeoCoordinate, KKJ> > it(testData);
    while (it.hasNext()) {
        const QPair<QTM_NAMESPACE::QGeoCoordinate, KKJ> &datum = it.next();
        QTM_NAMESPACE::QGeoCoordinate result = CoordinateSystemTransformer::transformToWGS84(datum.second);
        QTM_NAMESPACE::QGeoCoordinate expected = datum.first;
        // Allow small difference from the expected
        double latitudeDiff = fabs(expected.latitude() - result.latitude());
        double longitudeDiff = fabs(expected.longitude() - result.longitude());
        EXPECT_LE(latitudeDiff, 0.00001);
        EXPECT_LE(longitudeDiff, 0.00001);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
