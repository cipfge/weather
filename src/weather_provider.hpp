#ifndef WEATHER_PROVIDER_HPP
#define WEATHER_PROVIDER_HPP

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

struct WeatherForecast
{
    double temperature;
    double wind_speed;
    int wind_direction;
    int weather_code;
    bool is_day;
    QString time;
};

class WeatherProvider : public QObject
{
    Q_OBJECT

public:
    explicit WeatherProvider(QObject *parent = nullptr);
    ~WeatherProvider();

    void get_weather_forecast();

    void set_latitude(double value);
    double get_latitude() const;
    void set_longitude(double value);
    double get_longitude() const;

signals:
    void network_error(const QString &error_str);
    void decode_error(const QString &error_str);
    void weather_forecast(const WeatherForecast &forecast);

private slots:
    void network_manager_finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network_manager = nullptr;
    double m_latitude = 0.0;
    double m_longitude = 0.0;

    void decode_forecast_data(const QString &data);
};

#endif // WEATHER_PROVIDER_HPP
