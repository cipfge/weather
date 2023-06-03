#include "main_window.hpp"
#include "ui_main_window.h"
#include "weather_provider.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_weather_provider = new WeatherProvider(this);

    connect(m_weather_provider, SIGNAL(network_error(const QString)), this, SLOT(network_error(const QString&)));
    connect(m_weather_provider, SIGNAL(decode_error(const QString&)), this, SLOT(decode_error(const QString&)));
    connect(m_weather_provider, SIGNAL(weather_forecast(const WeatherForecast&)), this, SLOT(weather_forecast(const WeatherForecast&)));

    connect(ui->btnGetForecast, SIGNAL(clicked()), this, SLOT(get_forecast()));
}

MainWindow::~MainWindow()
{
    delete m_weather_provider;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::network_error(const QString &error_str)
{
    QMessageBox::critical(this, "Network error", error_str);
}

void MainWindow::decode_error(const QString &error_str)
{
    QMessageBox::critical(this, "Decode error", error_str);
}

void MainWindow::weather_forecast(const WeatherForecast &forecast)
{
    ui->lblTemperature->setText("Temperature: " + QString::number(forecast.temperature));
    ui->lblWeatherCode->setText("Weather code: " + QString::number(forecast.weather_code));
}

void MainWindow::get_forecast()
{
    m_weather_provider->set_latitude(ui->editLatitude->text().toDouble());
    m_weather_provider->set_longitude(ui->editLongitude->text().toDouble());
    m_weather_provider->get_weather_forecast();
}
