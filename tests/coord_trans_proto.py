# -*- coding: utf-8 -*-

# Adapted from http://positio.rista.net/en/pys60gps/src/KKJWGS84.py

import math


# Constants
# Longitude0 and Center meridian of KKJ bands
KKJ_ZONE_INFO = { 0: (18.0,  500000.0), \
                  1: (21.0, 1500000.0), \
                  2: (24.0, 2500000.0), \
                  3: (27.0, 3500000.0), \
                  4: (30.0, 4500000.0), \
                  5: (33.0, 5500000.0), \
                }

###########################################################################
# Function:  KKJ_Zone_I
###########################################################################
def KKJ_Zone_I(KKJI):
    ZoneNumber = math.floor((KKJI/1000000.0))
    if ZoneNumber < 0 or ZoneNumber > 5:
        ZoneNumber = -1
    return ZoneNumber

###########################################################################
# Function:  KKJ_Zone_Lo
###########################################################################
def KKJ_Zone_Lo(KKJlo):
    # determine the zonenumber from KKJ easting
    # takes KKJ zone which has center meridian
    # longitude nearest (in math value) to
    # the given KKJ longitude
    ZoneNumber = 5
    while ZoneNumber >= 0:
        if math.fabs(KKJlo - KKJ_ZONE_INFO[ZoneNumber][0]) <= 1.5:
            break
        ZoneNumber = ZoneNumber - 1
    return ZoneNumber

###########################################################################
# Function:  KKJlalo_to_KKJxy
###########################################################################
def KKJlalo_to_KKJxy(INP, ZoneNumber):
    Lo = math.radians(INP['Lo']) - math.radians(KKJ_ZONE_INFO[ZoneNumber][0])
    a  = 6378388.0            # Hayford ellipsoid
    f  = 1/297.0
    b  = (1.0 - f) * a
    bb = b * b
    c  = (a / b) * a
    ee = (a * a - bb) / bb
    n = (a - b)/(a + b)
    nn = n * n
    cosLa = math.cos(math.radians(INP['La']))
    NN = ee * cosLa * cosLa
    LaF = math.atan(math.tan(math.radians(INP['La'])) / math.cos(Lo * math.sqrt(1 + NN)))
    cosLaF = math.cos(LaF)
    t   = (math.tan(Lo) * cosLaF) / math.sqrt(1 + ee * cosLaF * cosLaF)
    A   = a / ( 1 + n )
    A1  = A * (1 + nn / 4 + nn * nn / 64)
    A2  = A * 1.5 * n * (1 - nn / 8)
    A3  = A * 0.9375 * nn * (1 - nn / 4)
    A4  = A * 35/48.0 * nn * n
    OUT = {}
    OUT['P'] = A1 * LaF - \
        A2 * math.sin(2 * LaF) + \
            A3 * math.sin(4 * LaF) - \
                A4 * math.sin(6 * LaF)
    OUT['I'] = c * math.log(t + math.sqrt(1+t*t)) + \
        500000.0 + ZoneNumber * 1000000.0
    return OUT
      
###########################################################################
# Function:  KKJxy_to_KKJlalo
###########################################################################
def KKJxy_to_KKJlalo(KKJ):
    # Scan iteratively the target area, until find matching
    # KKJ coordinate value.  Area is defined with Hayford Ellipsoid.

    LALO = {}
    ZoneNumber = KKJ_Zone_I(KKJ['I'])
    MinLa = math.radians(59.0)
    MaxLa = math.radians(70.5)
    MinLo = math.radians(18.5)
    MaxLo = math.radians(32.0)
    
    i = 1
    while (i < 35):
        DeltaLa = MaxLa - MinLa
        DeltaLo = MaxLo - MinLo
        LALO['La'] = math.degrees(MinLa + 0.5 * DeltaLa)
        LALO['Lo'] = math.degrees(MinLo + 0.5 * DeltaLo)
        KKJt = KKJlalo_to_KKJxy(LALO, ZoneNumber)
        if (KKJt['P'] < KKJ['P']):
            MinLa = MinLa + 0.45 * DeltaLa
        else:
            MaxLa = MinLa + 0.55 * DeltaLa
        if (KKJt['I'] < KKJ['I']):
            MinLo = MinLo + 0.45 * DeltaLo
        else:
            MaxLo = MinLo + 0.55 * DeltaLo
        i = i + 1
        
    return LALO

###########################################################################
# Function:  KKJlalo_to_WGS84lalo
###########################################################################
def KKJlalo_to_WGS84lalo(KKJ):
    La = KKJ['La']
    Lo = KKJ['Lo']
    dLa = math.radians( 0.124867E+01      + \
                        -0.269982E+00 * La + \
                        0.191330E+00 * Lo + \
                        0.356119E-02 * La * La + \
                        -0.122312E-02 * La * Lo + \
                        -0.335514E-03 * Lo * Lo ) / 3600.0
    dLo = math.radians(-0.286111E+02      + \
                        0.114183E+01 * La + \
                        -0.581428E+00 * Lo + \
                        -0.152421E-01 * La * La + \
                        0.118177E-01 * La * Lo + \
                        0.826646E-03 * Lo * Lo ) / 3600.0
    WGS = {}
    WGS['La'] = math.degrees(math.radians(KKJ['La']) + dLa)
    WGS['Lo'] = math.degrees(math.radians(KKJ['Lo']) + dLo)
    return WGS

###########################################################################
# Function:  WGS84lalo_to_KKJlalo
###########################################################################
def WGS84lalo_to_KKJlalo(WGS):
    La = WGS['La']
    Lo = WGS['Lo']
    dLa = math.radians(-0.124766E+01      +           0.269941E+00 * La +                          -0.191342E+00 * Lo +  -0.356086E-02 * La * La +                          0.122353E-02 * La * Lo +                           0.335456E-03 * Lo * Lo ) / 3600.0
    dLo = math.radians( 0.286008E+02      + \
                        -0.114139E+01 * La + \
                        0.581329E+00 * Lo + \
                        0.152376E-01 * La * La + \
                        -0.118166E-01 * La * Lo + \
                        -0.826201E-03 * Lo * Lo ) / 3600.0
    KKJ = {}
    KKJ['La'] = math.degrees(math.radians(WGS['La']) + dLa)
    KKJ['Lo'] = math.degrees(math.radians(WGS['Lo']) + dLo)
    return KKJ
      
###########################################################################
# Function:  KKJxy_to_WGS84lalo
###########################################################################
# Input:     dictionary with ['P'] is KKJ Northing
#                            ['I'] in KKJ Eeasting
# Output:    dictionary with ['La'] is latitude in degrees (WGS84)
#                            ['Lo'] is longitude in degrees (WGS84)
###########################################################################
def KKJxy_to_WGS84lalo(KKJin):
    KKJz = KKJxy_to_KKJlalo(KKJin)
    WGS = KKJlalo_to_WGS84lalo(KKJz)
    return WGS

###########################################################################
# Function:  WGS84lalo_to_KKJxy
###########################################################################
# Input:     dictionary with ['La'] is latitude in degrees (WGS84)
#                            ['Lo'] is longitude in degrees (WGS84)
# Output:    dictionary with ['P'] is KKJ Northing
#                            ['I'] in KKJ Eeasting
###########################################################################
def WGS84lalo_to_KKJxy(WGSin):
    KKJlalo = WGS84lalo_to_KKJlalo(WGSin)
    ZoneNumber = KKJ_Zone_Lo(KKJlalo['Lo'])
    KKJxy = KKJlalo_to_KKJxy(KKJlalo, ZoneNumber)
    return KKJxy

###########
# Test code
###########

class testCoordinate:
    def __init__(self, x, y, lon, lat):
        self.x = x
        self.y = y
        self.lon = lon
        self.lat = lat

testData = []
# Test data extracted from example on page
# http://developer.reittiopas.fi/pages/fi/http-get-interface.php
testData.append(testCoordinate(2556686, 6682815, 25.02051, 60.2528))
testData.append(testCoordinate(2546340, 6675352, 24.832, 60.18713))
testData.append(testCoordinate(2557985, 6685213, 25.04465, 60.27414))
testData.append(testCoordinate(2556532, 6682578, 25.01767, 60.2507))
testData.append(testCoordinate(2524959, 6686629, 24.44804, 60.2902))
testData.append(testCoordinate(2559094, 6693721, 25.06718, 60.35033))
testData.append(testCoordinate(2556861, 6683030, 25.02373, 60.25471))
testData.append(testCoordinate(2556888, 6682971, 25.0242, 60.25417))
testData.append(testCoordinate(2560257, 6698983, 25.08981, 60.39737))
testData.append(testCoordinate(2562518, 6686969, 25.12709, 60.28923))
testData.append(testCoordinate(2536615, 6673635, 24.65643, 60.1727))
testData.append(testCoordinate(2559118, 6693833, 25.06764, 60.35133))
testData.append(testCoordinate(2559182, 6693629, 25.06874, 60.34949))
testData.append(testCoordinate(2556947, 6682640, 25.02518, 60.25119))
testData.append(testCoordinate(2556822, 6682723, 25.02294, 60.25196))
testData.append(testCoordinate(2559089, 6693605, 25.06705, 60.34929))
testData.append(testCoordinate(2546445, 6675512, 24.83393, 60.18855))
testData.append(testCoordinate(2556964, 6682609, 25.02547, 60.25091))
testData.append(testCoordinate(2556740, 6682861, 25.0215, 60.25321))
testData.append(testCoordinate(2559002, 6694007, 25.06559, 60.35291))


def testKKJxytoWGS84lalo(x, y):
    test = { 'P': y, 'I': x }
    result = KKJxy_to_WGS84lalo(test)
    return [result['Lo'], result['La']]

testsPass = True

# Test transforming from KKJxy to WGS84latlon
for t in testData:
    [lon, lat] = testKKJxytoWGS84lalo(t.x, t.y)
    if math.fabs(t.lon - lon) < 0.001 and math.fabs(t.lat - lat) < 0.001:
        pass
    else:
        print "Got: (",lon,lat,"), expected: (",t.lon,t.lat,")"
        testsPass = False

if testsPass:
    print "All tests in testKKJxytoWGS84lalo passed"


def testWGS84lalotoKKJxy(lon, lat):
    test = { 'La': lat, 'Lo': lon }
    result = WGS84lalo_to_KKJxy(test)
    return [result['I'], result['P']]

testsPass = True

# Test transforming from WGS84latlon to KKJxy
for t in testData:
    [x, y] = testWGS84lalotoKKJxy(t.lon, t.lat)
    if abs(t.x - x) < 2 and abs(t.y - y) < 2:
        pass
    else:
        print "Got: (",x,y,"), expected: (",t.x,t.y,")"
        testsPass = False

if testsPass:
    print "All tests in testWGS84lalotoKKJxy passed"
