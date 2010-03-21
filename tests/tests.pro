TEMPLATE = subdirs
SUBDIRS = \
    ut_coordinatesystemtransformer \
    ut_kkj

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check
