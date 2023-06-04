#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "weather_types.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GeoLocationProvider;
class WeatherProvider;
class LocationWidget;
class ForecastWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void show_error(const QString &error_str);
    void geo_location_received(const GeoLocation &geo_location);
    void weather_forecast_received(const WeatherForecast &forecast);
    void button_get_forecast();

private:
    Ui::MainWindow *ui;
    GeoLocationProvider *m_geo_location_provider = nullptr;
    WeatherProvider *m_weather_provider = nullptr;
    ForecastWidget *m_forecast_widget = nullptr;
    LocationWidget *m_location_widget = nullptr;
};

#endif // MAIN_WINDOW_HPP
