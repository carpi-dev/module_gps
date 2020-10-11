#include "GPS.h"

#ifdef GPS_LOADABLE
#include "ui_gps.h"
#endif

GPS::GPS(Logger *log, QWidget *parent): QWidget(parent)
#ifdef GPS_LOADABLE
,ui(new Ui::GPS)
#endif
,log(log), settings(new QSettings("carpi", "gps"))
{
#ifdef GPS_LOADABLE
    ui->setupUi(this);
#endif
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if(source) {
        source->setUpdateInterval(settings->value(KEY_UPDATE_INTERVAL, 420).toInt());
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &GPS::positionUpdated);
        connect(source, &QGeoPositionInfoSource::updateTimeout, this, &GPS::updateTimeout);
        source->startUpdates();
    } else log->error("GPS", "could not create source");
}

GPS::~GPS()
{
    settings->sync();
    source->stopUpdates();
    delete settings;
    delete source;
#ifdef GPS_LOADABLE
    delete ui;
#endif
}

void GPS::positionUpdated(const QGeoPositionInfo &info) {
    if(lastInfo.coordinate() != info.coordinate()){
        lastInfo = info;
        emit positionChanged(info);
    }
}

void GPS::updateTimeout() {
    // Logger::warning("GPS", "timeout");
    emit positionOld(lastInfo.timestamp());
}

#ifdef GPS_LOADABLE
extern "C" GPS_EXPORT QWidget* create(Logger *log) {
    return new GPS(log);
}

extern "C" GPS_EXPORT char* getName() {
    return (char*) "GPS";
}

extern "C" GPS_EXPORT int getDefaultIndex(){
    return -1;
}

extern "C" GPS_EXPORT QStringList getSettingsKeys(){
    return QStringList(); // << KEY_SOMETHING_SOMETHING
}

extern "C" GPS_EXPORT QStringList getDependencies(){
    return QStringList() << "Logger";
}

extern "C" GPS_EXPORT int getVersion(){
    return 1;
}
#endif
