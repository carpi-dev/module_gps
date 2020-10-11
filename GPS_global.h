#ifndef CARPI_QT_GPS_GLOBAL_H
#define CARPI_QT_GPS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GPS_LIBRARY)
#  define GPS_EXPORT Q_DECL_EXPORT
#else
#  define GPS_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_GPS_GLOBAL_H
