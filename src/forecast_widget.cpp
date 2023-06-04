#include "forecast_widget.hpp"
#include "ui_forecast_widget.h"

ForecastWidget::ForecastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForecastWidget)
{
    ui->setupUi(this);
}

ForecastWidget::~ForecastWidget()
{
    delete ui;
}
