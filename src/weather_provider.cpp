#include "weather_provider.hpp"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

WeatherProvider::WeatherProvider(QObject *parent)
    : QObject{parent}
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
    QString service_url = "https://api.open-meteo.com/v1/forecast?latitude=" + QString::number(m_latitude) +
                          "&longitude=" + QString::number(m_longitude) +
                          "&current_weather=true";

    QNetworkRequest request(service_url);
    m_network_manager->get(request);
}

void WeatherProvider::network_manager_finished(QNetworkReply *reply)
{
    if (reply->error())
    {
        network_error(reply->errorString());
        return;
    }

    QString data = reply->readAll();
    decode_forecast_data(data);
}

void WeatherProvider::set_latitude(double value)
{
    m_latitude = value;
}

double WeatherProvider::get_latitude() const
{
    return m_latitude;
}

void WeatherProvider::set_longitude(double value)
{
    m_longitude = value;
}

double WeatherProvider::get_longitude() const
{
    return m_longitude;
}

void WeatherProvider::decode_forecast_data(const QString &data)
{
    QJsonParseError jerror {};
    QJsonDocument json_doc = QJsonDocument::fromJson(data.toUtf8(), &jerror);

    if (jerror.error != 0)
    {
        emit decode_error(jerror.errorString());
        return;
    }

    QJsonObject json_root = json_doc.object();
    if (!json_root.contains("current_weather"))
    {
        emit decode_error("Weather service reply doesn't contain current weather forecast data.");
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

    emit weather_forecast(forecast);
}
