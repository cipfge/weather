#include "main_window.hpp"
#include "ui_main_window.h"
#include "geo_location_provider.hpp"
#include "weather_provider.hpp"
#include "forecast_widget.hpp"
#include "location_widget.hpp"
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

    m_forecast_widget = new ForecastWidget(this);
    ui->mainWidget->layout()->addWidget(m_forecast_widget);

    m_location_widget = new LocationWidget(this);
    ui->statusbar->addWidget(m_location_widget);
}

MainWindow::~MainWindow()
{
    delete m_forecast_widget;
    delete m_location_widget;
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
    m_weather_provider->set_geo_location(geo_location);
    m_weather_provider->get_weather_forecast();
}

void MainWindow::weather_forecast_received(const WeatherForecast &forecast)
{
}

void MainWindow::button_get_forecast()
{
}
