#ifndef CARPI_QT_GPS_H
#define CARPI_QT_GPS_H

#ifdef GPS_LOADABLE
#include "GPS_global.h"
#endif

#include "Logger/Logger.h"

#include <QWidget>
#include <QSettings>
#include <QTimer>
#include <QObject>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

#define KEY_GROUP_GPS "GPS"
#define KEY_UPDATE_INTERVAL "updateInterval"

#ifdef GPS_LOADABLE
QT_BEGIN_NAMESPACE
namespace Ui { class GPS; }
QT_END_NAMESPACE
#endif

class GPS : public QWidget
{
Q_OBJECT
private:
#ifdef GPS_LOADABLE
    Ui::GPS *ui;
#endif
    Logger *log;
    QSettings *settings;
    QGeoPositionInfoSource *source;
    QGeoPositionInfo lastInfo;

private slots:
    void updateTimeout();
    void positionUpdated(const QGeoPositionInfo &info);

signals:
    void positionChanged(const QGeoPositionInfo &info);
    void positionOld(const QDateTime &ts);

public:
    explicit GPS(Logger *log, QWidget *parent = nullptr);
    ~GPS() override;
};

#ifdef GPS_LOADABLE
extern "C" {
    GPS_EXPORT int getDefaultIndex();
    GPS_EXPORT char* getName();
    GPS_EXPORT QWidget* create(Logger *log);
    GPS_EXPORT int getVersion();
    GPS_EXPORT QStringList getSettingsKeys();
    GPS_EXPORT QStringList getDependencies();
};
#endif

#endif //CARPI_QT_GPS_H
