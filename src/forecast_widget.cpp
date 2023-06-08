#include "forecast_widget.hpp"
#include "ui_forecast_widget.h"
#include "animated_svg_widget.hpp"

// Weather code, day icon, night icon
QMap<int, QPair<QString, QString>> ForecastWidget::m_weather_icons = {
    {  0, { ":/assets/clear-day.svg",                 ":/assets/clear-night.svg"                 } },
    {  1, { ":/assets/partly-cloudy-day.svg",         ":/assets/clear-night.svg"                 } },
    {  2, { ":/assets/partly-cloudy-day.svg",         ":/assets/clear-night.svg"                 } },
    {  3, { ":/assets/overcast-day.svg",              ":/assets/overcast-night.svg"              } },
    { 45, { ":/assets/fog-day.svg",                   ":/assets/fog-night.svg"                   } },
    { 48, { ":/assets/fog-day.svg",                   ":/assets/fog-night.svg"                   } },
    { 51, { ":/assets/partly-cloudy-day-drizzle.svg", ":/assets/partly-cloudy-night-drizzle.svg" } },
    { 52, { ":/assets/partly-cloudy-day-drizzle.svg", ":/assets/partly-cloudy-night-drizzle.svg" } },
    { 53, { ":/assets/partly-cloudy-day-drizzle.svg", ":/assets/partly-cloudy-night-drizzle.svg" } },
    { 56, { ":/assets/partly-cloudy-day-sleet.svg",   ":/assets/partly-cloudy-night-sleet.svg"   } },
    { 57, { ":/assets/partly-cloudy-day-sleet.svg",   ":/assets/partly-cloudy-night-sleet.svg"   } },
    { 61, { ":/assets/partly-cloudy-day-rain.svg",    ":/assets/partly-cloudy-night-rain.svg"    } },
    { 63, { ":/assets/rain.svg",                      ":/assets/rain.svg"                        } },
    { 65, { ":/assets/rain.svg",                      ":/assets/rain.svg"                        } },
    { 66, { ":/assets/sleet.svg",                     ":/assets/sleet.svg"                       } },
    { 67, { ":/assets/sleet.svg",                     ":/assets/sleet.svg"                       } },
    { 71, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 73, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 75, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 77, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 80, { ":/assets/rain.svg",                      ":/assets/rain.svg"                        } },
    { 81, { ":/assets/rain.svg",                      ":/assets/rain.svg"                        } },
    { 82, { ":/assets/rain.svg",                      ":/assets/rain.svg"                        } },
    { 85, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 86, { ":/assets/snow.svg",                      ":/assets/snow.svg"                        } },
    { 95, { ":/assets/thunderstorms-rain.svg",        ":/assets/thunderstorms-rain.svg"          } },
    { 96, { ":/assets/thunderstorms-rain.svg",        ":/assets/thunderstorms-rain.svg"          } },
    { 99, { ":/assets/thunderstorms-rain.svg",        ":/assets/thunderstorms-rain.svg"          } },
};

ForecastWidget::ForecastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForecastWidget)
{
    ui->setupUi(this);
    m_svg_widget = new AnimatedSvgWidget(this);
    ui->svgFrameLayout->addWidget(m_svg_widget);
}

ForecastWidget::~ForecastWidget()
{
    delete m_svg_widget;
    delete ui;
}

void ForecastWidget::set_forecast(const Forecast &forecast)
{
    m_forecast = forecast;
    update();
}

void ForecastWidget::update()
{
    update_svg_icon();
    ui->lbTemperature->setText(QString::number(m_forecast.temperature) + " °C");
}

void ForecastWidget::update_svg_icon()
{
    const auto &icon = m_weather_icons.find(m_forecast.weather_code) ;
    if (icon == m_weather_icons.end())
    {
        m_svg_widget->load(":/assets/not-available.svg");
        return;
    }

    if (m_forecast.is_day)
        m_svg_widget->load(icon->first);
    else
        m_svg_widget->load(icon->second);
}
