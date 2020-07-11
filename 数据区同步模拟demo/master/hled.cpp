#include <QtGui>
#include "hled.h"

struct HLed::Private
{
public:
    Private()
        : darkerFactor(300), color(Qt::green), isOn(true)
    { }

    int darkerFactor;
    QColor color;
    bool isOn;
};

HLed::HLed(QWidget *parent)
    :QWidget(parent), m_d(new Private)
{
    alarmTimer = new QTimer(this);
    connect(alarmTimer, SIGNAL(timeout()), this, SLOT(alarmFlicker()));
    alarmTimer->setInterval(100);
}

HLed::~HLed()
{
    delete m_d;
    delete alarmTimer;
}

QColor HLed::color() const
{
    return m_d->color;
}

void HLed::setColor(const QColor &color)
{
    if (m_d->color == color)
        return;
    m_d->color = color;
    update();
}

QSize HLed::sizeHint() const
{
    return QSize(20, 20);
}

QSize HLed::minimumSizeHint() const
{
    return QSize(16, 16);
}

void HLed::toggle()
{
    m_d->isOn = !m_d->isOn;
    update();
}

void HLed::turnOn(bool on)
{
    m_d->isOn = on;
    update();
}

void HLed::turnOff(bool off)
{
    turnOn(!off);
}

void HLed::paintEvent(QPaintEvent* /* event*/)
{
    int width = ledWidth();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor color = m_d->isOn ? m_d->color
                             : m_d->color.darker(m_d->darkerFactor);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    painter.setBrush(brush);
    // draw plain
    painter.drawEllipse(1, 1, width-1, width-1);

    QPen pen;
    pen.setWidth(2);

    int pos = width / 5 + 1;
    int lightWidth = width * 2 / 3;
    int lightQuote = 130 * 2 / (lightWidth ? lightWidth : 1) + 100;

    // draw bright spot
    while (lightWidth) {
        color = color.lighter(lightQuote);
        pen.setColor(color);
        painter.setPen(pen);
        painter.drawEllipse(pos, pos, lightWidth, lightWidth);
        lightWidth--;

        if (!lightWidth)
            break;

        painter.drawEllipse(pos, pos, lightWidth, lightWidth);
        lightWidth--;

        if (!lightWidth)
            break;

        painter.drawEllipse(pos, pos, lightWidth, lightWidth);
        pos++;
        lightWidth--;
    }

    //draw border
    painter.setBrush(Qt::NoBrush);

    int angle = -720;
    color = palette().color(QPalette::Light);

    for (int arc=120; arc<2880; arc+=240) {
        pen.setColor(color);
        painter.setPen(pen);
        int w = width - pen.width()/2;
        painter.drawArc(pen.width()/2, pen.width()/2, w, w, angle+arc, 240);
        painter.drawArc(pen.width()/2, pen.width()/2, w, w, angle-arc, 240);
        color = color.darker(110);
    }
}

//void HLed::paintEvent(QPaintEvent *) {
//    QPainter painter(this);
//    painter.translate(width() / 2, height() / 2);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::transparent);
//    painter.fillRect(-width(), -height(), width() * 2, height() * 2, Qt::gray);

//    int radius = 100;

//    // Íâ±ß¿ò
//    QLinearGradient lg1(0, -radius, 0, radius);
//    lg1.setColorAt(0, QColor(255, 255, 255));
//    lg1.setColorAt(1, QColor(166, 166, 166));
//    painter.setBrush(lg1);
//    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

//    // ÄÚ±ß¿ò
//    radius -= 13;
//    QLinearGradient lg2(0, -radius, 0, radius);
//    lg2.setColorAt(0, QColor(166, 166, 166));
//    lg2.setColorAt(1, QColor(255, 255, 255));
//    painter.setBrush(lg2);
//    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

//    radius -= 4;
//    QRadialGradient rg(0, 0, radius);
//    rg.setColorAt(0, QColor(245, 0, 0));
//    rg.setColorAt(0.6, QColor(210, 0, 0));
//    rg.setColorAt(1, QColor(166, 0, 0));
//    painter.setBrush(rg);
//    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);

//    QPainterPath path;
//    path.addEllipse(-radius, -radius, radius << 1, radius << 1);
//    QPainterPath bigEllipse;

//    radius *= 2;
//    bigEllipse.addEllipse(-radius, -radius + 140, radius << 1, radius << 1);
//    path -= bigEllipse;

//    QLinearGradient lg3(0, -radius, 0, radius);
//    lg3.setColorAt(0, QColor(255, 200, 200, 180));
//    lg3.setColorAt(1, QColor(255, 200, 200, 100));
//    painter.setBrush(lg3);
//    painter.drawPath(path);
//}

int HLed::ledWidth() const
{
    int width = qMin(this->width(), this->height());
    width -= 2;
    return width > 0 ? width : 0;
}

void HLed::alarm()
{
    alarmTimer->start();
}

void HLed::unalarm()
{
    alarmTimer->stop();
    setColor(Qt::green);
}

void HLed::alarmFlicker()
{
    if(m_d->color==Qt::red)
        setColor(Qt::darkRed);
    else
        setColor(Qt::red);
}
