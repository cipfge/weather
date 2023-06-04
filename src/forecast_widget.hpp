#ifndef FORECAST_WIDGET_HPP
#define FORECAST_WIDGET_HPP

#include <QWidget>

namespace Ui {
class ForecastWidget;
}

class ForecastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ForecastWidget(QWidget *parent = nullptr);
    ~ForecastWidget();

private:
    Ui::ForecastWidget *ui;
};

#endif // FORECAST_WIDGET_HPP
