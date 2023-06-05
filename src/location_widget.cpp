#include "location_widget.hpp"
#include "ui_location_widget.h"

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);

    connect(ui->edLocation, SIGNAL(returnPressed()), this, SLOT(return_pressed()));
}

LocationWidget::~LocationWidget()
{
    delete ui;
}

void LocationWidget::set_location(const QString &location)
{
    m_location = location;
}

const QString &LocationWidget::get_location() const
{
    return m_location;
}

void LocationWidget::return_pressed()
{
    if (ui->edLocation->text().isEmpty())
        return;

    m_location = ui->edLocation->text();
    emit location_selected(m_location);
}
