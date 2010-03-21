TEMPLATE = subdirs
SUBDIRS = ut_coord_trans

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check
