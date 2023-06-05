#include "forecast_widget.hpp"
#include "ui_forecast_widget.h"
#include "animated_svg_widget.hpp"

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
    switch (m_forecast.weather_code)
    {
    case 0:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/clear-night.svg");
        else
            m_svg_widget->load(":/assets/clear-day.svg");
        break;

    case 1:
    case 2:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/clear-night.svg");
        else
            m_svg_widget->load(":/assets/partly-cloudy-day.svg");
        break;
        break;

    case 3:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/overcast-night.svg");
        else
            m_svg_widget->load(":/assets/overcast-day.svg");
        break;

    case 45:
    case 48:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/fog-night.svg");
        else
            m_svg_widget->load(":/assets/fog-day.svg");
        break;

    case 51:
    case 53:
    case 55:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/partly-cloudy-night-drizzle.svg");
        else
            m_svg_widget->load(":/assets/partly-cloudy-day-drizzle.svg");
        break;

    case 56:
    case 57:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/partly-cloudy-night-sleet.svg");
        else
            m_svg_widget->load(":/assets/partly-cloudy-day-sleet.svg");
        break;

    case 61:
        if (!m_forecast.is_day)
            m_svg_widget->load(":/assets/partly-cloudy-night-rain.svg");
        else
            m_svg_widget->load(":/assets/partly-cloudy-day-rain.svg");
        break;

    case 63:
    case 65:
        m_svg_widget->load(":/assets/rain.svg");
        break;

    case 66:
    case 67:
        m_svg_widget->load(":/assets/sleet.svg");
        break;

    case 71:
    case 73:
    case 75:
    case 77:
        m_svg_widget->load(":/assets/snow.svg");
        break;

    case 80:
    case 81:
    case 82:
        m_svg_widget->load(":/assets/rain.svg");
        break;

    case 85:
    case 86:
        m_svg_widget->load(":/assets/snow.svg");
        break;

    case 95:
    case 96:
    case 99:
        m_svg_widget->load(":/assets/thunderstorms-rain.svg");
        break;

    default:
        m_svg_widget->load(":/assets/not-available.svg");
        break;
    }
}
