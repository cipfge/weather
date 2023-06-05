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

    void set_location(const QString &location);
    const QString &get_location() const;

signals:
    void location_selected(const QString &location);

private slots:
    void return_pressed();

private:
    Ui::LocationWidget *ui;
    QString m_location;
};

#endif // LOCATION_WIDGET_HPP
