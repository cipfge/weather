#ifndef ANIMATED_SVG_WIDGET_HPP
#define ANIMATED_SVG_WIDGET_HPP

#include <QSvgWidget>

class QSvgRenderer;

class AnimatedSvgWidget : public QSvgWidget
{
    Q_OBJECT

public:
    explicit AnimatedSvgWidget(QWidget *parent = nullptr);

    void set_frames_per_second(int fps);
    int get_frames_per_second() const;
    void load(const QString &path);

private:
    QSvgRenderer *m_renderer = nullptr;
    int m_frames_per_second = 60;
};

#endif // ANIMATED_SVG_WIDGET_HPP
