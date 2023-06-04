#include "weather_provider.hpp"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

WeatherProvider::WeatherProvider(QObject *parent)
    : QObject(parent)
{
    m_network_manager = new QNetworkAccessManager(this);
    connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(network_manager_finished(QNetworkReply*)));
}

WeatherProvider::~WeatherProvider()
{
    delete m_network_manager;
}

void WeatherProvider::get_weather_forecast()
{
    QString service_url = "https://api.open-meteo.com/v1/forecast?latitude=" + QString::number(m_geo_location.latitude) +
                          "&longitude=" + QString::number(m_geo_location.longitude) +
                          "&current_weather=true";

    QNetworkRequest request(service_url);
    m_network_manager->get(request);
}

void WeatherProvider::network_manager_finished(QNetworkReply *reply)
{
    if (reply->error())
    {
        emit network_error(reply->errorString());
        return;
    }

    decode_forecast(reply->readAll());
}

void WeatherProvider::set_geo_location(const GeoLocation &geo_location)
{
    m_geo_location = geo_location;
}

const GeoLocation &WeatherProvider::get_geo_location() const
{
    return m_geo_location;
}

void WeatherProvider::decode_forecast(const QString &data)
{
    QJsonParseError jerror {};
    QJsonDocument json_doc = QJsonDocument::fromJson(data.toUtf8(), &jerror);

    if (jerror.error != 0)
    {
        emit weather_forecast_error(jerror.errorString());
        return;
    }

    QJsonObject json_root = json_doc.object();
    if (!json_root.contains("current_weather"))
    {
        emit weather_forecast_error("Weather service reply doesn't contain current weather forecast data.");
        return;
    }

    WeatherForecast forecast {};
    QJsonObject json_forecast = json_root.value("current_weather").toObject();

    if (json_forecast.contains("temperature"))
        forecast.temperature = json_forecast.value("temperature").toDouble();

    if (json_forecast.contains("windspeed"))
        forecast.wind_speed = json_forecast.value("windspeed").toDouble();

    if (json_forecast.contains("winddirection"))
        forecast.wind_direction = json_forecast.value("winddirection").toInt();

    if (json_forecast.contains("weathercode"))
        forecast.weather_code = json_forecast.value("weathercode").toInt();

    if (json_forecast.contains("is_day"))
        forecast.is_day = json_forecast.value("is_day").toBool();

    if (json_forecast.contains("time"))
        forecast.time = json_forecast.value("time").toString();

    emit weather_forecast_received(forecast);
}
