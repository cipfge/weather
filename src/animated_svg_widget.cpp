#include "animated_svg_widget.hpp"
#include <QSvgRenderer>

AnimatedSvgWidget::AnimatedSvgWidget(QWidget *parent)
    : QSvgWidget(parent)
{
    m_renderer = this->renderer();
    m_renderer->setFramesPerSecond(m_frames_per_second);
}

void AnimatedSvgWidget::set_frames_per_second(int fps)
{
    m_frames_per_second = fps;
    m_renderer->setFramesPerSecond(m_frames_per_second);
}

int AnimatedSvgWidget::get_frames_per_second() const
{
    return m_frames_per_second;
}

void AnimatedSvgWidget::load(const QString &path)
{
    m_renderer->load(path);
}
