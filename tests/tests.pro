TEMPLATE = subdirs
SUBDIRS = \
    ut_kkj

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check
