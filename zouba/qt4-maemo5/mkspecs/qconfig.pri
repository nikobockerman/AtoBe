#configuration
CONFIG +=  exceptions maemo5 no_mocdepend release stl qt_no_framework
QT_ARCH = armv6
QT_EDITION = OpenSource
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config phonon phonon-backend accessibility egl opengl opengles2 reduce_exports reduce_relocations ipv6 clock-gettime clock-monotonic mremap getaddrinfo ipv6ifname getifaddrs inotify system-jpeg no-mng system-png png gif system-tiff system-freetype system-zlib nis iconv glib gstreamer dbus openssl x11sm xshape xsync xrender mitshm fontconfig xkb alsa xmlpatterns multimedia audio-backend svg webkit script scripttools maemo5 release

#versioning
QT_VERSION = 4.6.2
QT_MAJOR_VERSION = 4
QT_MINOR_VERSION = 6
QT_PATCH_VERSION = 2

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 
QT_NAMESPACE_MAC_CRC = 

QMAKE_RPATHDIR += "/opt/qt4-maemo5/lib"
