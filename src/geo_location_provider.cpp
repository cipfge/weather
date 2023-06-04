#include "geo_location_provider.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

GeoLocationProvider::GeoLocationProvider(QObject *parent)
    : QObject{parent}
{
    m_network_manager = new QNetworkAccessManager(this);
    connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(network_manager_finished(QNetworkReply*)));
}

GeoLocationProvider::~GeoLocationProvider()
{
    delete m_network_manager;
}

void GeoLocationProvider::get_geo_location(const QString &city)
{
    QString service_url = "https://nominatim.openstreetmap.org/search?city=" + city + "&format=json";

    QNetworkRequest request(service_url);
    m_network_manager->get(request);
}

void GeoLocationProvider::network_manager_finished(QNetworkReply *reply)
{
    if (reply->error())
    {
        emit network_error(reply->errorString());
        return;
    }

    decode_geo_location(reply->readAll());
}

void GeoLocationProvider::decode_geo_location(const QString &data)
{
    QJsonParseError jerror {};
    QJsonDocument json_doc = QJsonDocument::fromJson(data.toUtf8(), &jerror);

    if (jerror.error != 0)
    {
        emit geo_location_error(jerror.errorString());
        return;
    }

    if (!json_doc.isArray())
    {
        emit geo_location_error("Invalid geo location JSON data.");
        return;
    }

    GeoLocation geo_location {};
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        if (json_obj.contains("lat"))
            geo_location.latitude = json_obj.value("lat").toDouble();
        if (json_obj.contains("lon"))
            geo_location.longitude = json_obj.value("lon").toDouble();
        if (json_obj.contains("display_name"))
            geo_location.display_name = json_obj.value("display_name").toString();
    }

    emit geo_location_received(geo_location);
}
