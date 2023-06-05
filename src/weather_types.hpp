#ifndef WEATHER_TYPES_HPP
#define WEATHER_TYPES_HPP

#include <QString>

struct GeoLocation
{
    QString display_name = "";
    double latitude = 0.0;
    double longitude = 0.0;
};

struct Forecast
{
    GeoLocation geo_location;
    double temperature = 0.0;
    double wind_speed = 0.0;
    int wind_direction = 0;
    int weather_code = 0;
    bool is_day = false;
    QString time = "";
};

#endif // WEATHER_TYPES_HPP
