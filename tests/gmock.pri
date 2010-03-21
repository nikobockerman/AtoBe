GMOCKBUILDDIR = ../gmock/build
QMAKE_CXXFLAGS += $$system($$GMOCKBUILDDIR/scripts/gmock-config --cppflags --cxxflags)
QMAKE_LIBS += ../$$GMOCKBUILDDIR/lib/.libs/libgmock.a ../$$GMOCKBUILDDIR/gtest/lib/.libs/libgtest.a
