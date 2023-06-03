#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WeatherProvider;
struct WeatherForecast;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void network_error(const QString &error_str);
    void decode_error(const QString &error_str);
    void weather_forecast(const WeatherForecast &forecast);
    void get_forecast();

private:
    Ui::MainWindow *ui;
    WeatherProvider *m_weather_provider = nullptr;
};

#endif // MAIN_WINDOW_HPP
