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
    connect(m_geo_location_provider, SIGNAL(network_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_geo_location_provider, SIGNAL(geo_location_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_geo_location_provider, SIGNAL(geo_location_received(const GeoLocation&)), this, SLOT(geo_location_received(const GeoLocation&)));

    m_weather_provider = new WeatherProvider(this);
    connect(m_weather_provider, SIGNAL(network_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_weather_provider, SIGNAL(weather_forecast_error(const QString&)), this, SLOT(show_error(const QString&)));
    connect(m_weather_provider, SIGNAL(weather_forecast_received(const Forecast&)), this, SLOT(weather_forecast_received(const Forecast&)));

    m_location_widget = new LocationWidget(this);
    m_forecast_widget = new ForecastWidget(this);
    ui->stackedWidget->insertWidget(LOCATION_WIDGET_INDEX, m_location_widget);
    ui->stackedWidget->insertWidget(FORECAST_WIDGET_INDEX, m_forecast_widget);
    ui->stackedWidget->setCurrentIndex(LOCATION_WIDGET_INDEX);

    connect(ui->btnChangeLocation, SIGNAL(clicked()), this, SLOT(change_location()));
    connect(ui->btnRefresh, SIGNAL(clicked()), this, SLOT(request_forecast()));
    connect(m_location_widget, SIGNAL(location_selected(const QString&)), this, SLOT(location_selected(const QString&)));
    ui->locTitleFrame->hide();
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

void MainWindow::location_selected(const QString &location)
{
    m_geo_location_provider->get_geo_location(location);
}

void MainWindow::geo_location_received(const GeoLocation &geo_location)
{
    m_weather_provider->set_geo_location(geo_location);
    m_weather_provider->get_weather_forecast();
}

void MainWindow::weather_forecast_received(const Forecast &forecast)
{
    m_forecast_widget->set_forecast(forecast);
    ui->stackedWidget->setCurrentIndex(FORECAST_WIDGET_INDEX);
    ui->locTitleFrame->show();
    ui->lbLocation->setText(forecast.geo_location.display_name);
}

void MainWindow::change_location()
{
    ui->stackedWidget->setCurrentIndex(LOCATION_WIDGET_INDEX);
    ui->locTitleFrame->hide();
}

void MainWindow::request_forecast()
{
    m_weather_provider->get_weather_forecast();
}
