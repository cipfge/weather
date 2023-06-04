#ifndef LOCATION_WIDGET_HPP
#define LOCATION_WIDGET_HPP

#include <QWidget>

namespace Ui {
class LocationWidget;
}

class LocationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LocationWidget(QWidget *parent = nullptr);
    ~LocationWidget();

private:
    Ui::LocationWidget *ui;
};

#endif // LOCATION_WIDGET_HPP
