#ifndef WEATHER_PROVIDER_HPP
#define WEATHER_PROVIDER_HPP

#include "weather_types.hpp"
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class WeatherProvider : public QObject
{
    Q_OBJECT

public:
    explicit WeatherProvider(QObject *parent = nullptr);
    ~WeatherProvider();

    void get_weather_forecast();

    void set_geo_location(const GeoLocation &geo_location);
    const GeoLocation &get_geo_location() const;

signals:
    void network_error(const QString &error_str);
    void weather_forecast_error(const QString &error_str);
    void weather_forecast_received(const WeatherForecast &forecast);

private slots:
    void network_manager_finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network_manager = nullptr;
    GeoLocation m_geo_location;

    void decode_forecast(const QString &data);
};

#endif // WEATHER_PROVIDER_HPP
