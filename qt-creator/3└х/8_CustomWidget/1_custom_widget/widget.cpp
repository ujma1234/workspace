#include "widget.h"

#include <QtWidgets>
#include <QBitmap>

Widget::Widget(QWidget *parent)
    //: QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
    : QWidget(0, Qt::FramelessWindowHint), m_embedded(false)
{
    Q_UNUSED(parent);

    update_background();

    setWindowTitle(tr("Custom Widget"));

    slider_widget = new custom_slider_widget(this);
    slider_widget->slider_set_widget_resize(24, 100);
    slider_widget->slider_set_max_value(22);
    slider_widget->slider_set_min_value(0);
    slider_widget->slider_set_current_value(12);

    cpu_widget = new custom_cpu_widget(this);
    cpu_widget->cpu_set_widget_level
                    (slider_widget->slider_get_current_value());

    cpu_widget->setGeometry(40, 100, 80, 100);
    slider_widget->setGeometry(130, 100, 24, 100);

    connect(slider_widget, SIGNAL(valuchanged(int)), this,
                           SLOT(mvaluechanged(int)));
}

Widget::~Widget()
{

}

void Widget::update_background()
{
    m_device = QPixmap(":/resources/background.png", "png");
    QBitmap bitmap = m_device.createHeuristicMask();
    setFixedSize(m_device.size());
    setMask(bitmap);
    update();
}

void Widget::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.drawPixmap(e->rect(), m_device, e->rect());

    painter.setPen(QColor(116, 116, 118));
    painter.setBrush(QColor(116, 116, 118));
    painter.drawRect(25, 65, 145, 260);
}

void Widget::mvaluechanged(int value)
{
    cpu_widget->cpu_set_widget_level(value);
}













