TEMPLATE=subdirs
SUBDIRS = \
	ut_location/ \
	ut_route/ \
	ut_gpscontroller/ \

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check
