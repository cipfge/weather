#include "location_widget.hpp"
#include "ui_location_widget.h"

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);
}

LocationWidget::~LocationWidget()
{
    delete ui;
}
