#ifndef FORECAST_WIDGET_HPP
#define FORECAST_WIDGET_HPP

#include "weather_types.hpp"
#include <QWidget>

namespace Ui {
class ForecastWidget;
}

class AnimatedSvgWidget;

class ForecastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ForecastWidget(QWidget *parent = nullptr);
    ~ForecastWidget();

    void set_forecast(const Forecast &forecast);
    void update();

private:
    Ui::ForecastWidget *ui;
    AnimatedSvgWidget *m_svg_widget;
    Forecast m_forecast;

    void update_svg_icon();
};

#endif // FORECAST_WIDGET_HPP
