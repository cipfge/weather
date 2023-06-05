#ifndef GEO_LOCATION_HPP
#define GEO_LOCATION_HPP

#include "weather_types.hpp"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class GeoLocationProvider : public QObject
{
    Q_OBJECT

public:
    explicit GeoLocationProvider(QObject *parent = nullptr);
    ~GeoLocationProvider();

    void get_geo_location(const QString &location);

signals:
    void network_error(const QString &error_str);
    void geo_location_error(const QString &error_str);
    void geo_location_received(const GeoLocation &geo_location);

private slots:
    void network_manager_finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network_manager = nullptr;

    void decode_geo_location(const QString &data);
};

#endif // GEO_LOCATION_HPP
