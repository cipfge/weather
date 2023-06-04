#include "main_window.hpp"
#include "ui_main_window.h"
#include "geo_location_provider.hpp"
#include "weather_provider.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_geo_location_provider = new GeoLocationProvider(this);

    connect(m_geo_location_provider, SIGNAL(network_error(const QString)), this, SLOT(show_error(const QString&)));
    connect(m_geo_location_provider, SIGNAL(geo_location_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_geo_location_provider, SIGNAL(geo_location_received(const GeoLocation&)), this, SLOT(geo_location_received(const GeoLocation&)));

    m_weather_provider = new WeatherProvider(this);

    connect(m_weather_provider, SIGNAL(network_error(const QString)), this, SLOT(show_error(const QString&)));
    connect(m_weather_provider, SIGNAL(weather_forecast_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_weather_provider, SIGNAL(weather_forecast_received(const WeatherForecast&)), this, SLOT(weather_forecast_received(const WeatherForecast&)));

    connect(ui->btnGetForecast, SIGNAL(clicked()), this, SLOT(button_get_forecast()));
}

MainWindow::~MainWindow()
{
    delete m_geo_location_provider;
    delete m_weather_provider;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::show_error(const QString &error_str)
{
    QMessageBox::critical(this, "Error", error_str);
}

void MainWindow::geo_location_received(const GeoLocation &geo_location)
{
    ui->lblCityName->setText(geo_location.display_name);
    m_weather_provider->set_geo_location(geo_location);
    m_weather_provider->get_weather_forecast();
}

void MainWindow::weather_forecast_received(const WeatherForecast &forecast)
{
    ui->lblTemperature->setText("Temperature: " + QString::number(forecast.temperature));
    ui->lblWeatherCode->setText("Weather code: " + QString::number(forecast.weather_code));
}

void MainWindow::button_get_forecast()
{
    if (ui->editCity->text().isEmpty())
        return;

    m_geo_location_provider->get_geo_location(ui->editCity->text());
}
