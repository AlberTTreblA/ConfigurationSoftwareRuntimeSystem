#pragma execution_character_set("utf-8")

#include "lednumber.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

LedNumber::LedNumber(QWidget *parent) :	QWidget(parent)
{
    number = 0;
    space = 5;
    padding = 2;
    radius = 2;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    numberBgColorStart = QColor(130, 130, 130);
    numberBgColorEnd = QColor(90, 90, 90);

    numberColorStart = QColor(100, 184, 255);
    numberColorEnd = QColor(79, 148, 205);

    zero = new NumberObj();
    one = new NumberObj();
    two = new NumberObj();
    three = new NumberObj();
    four = new NumberObj();
    five = new NumberObj();
    six = new NumberObj();
    seven = new NumberObj();
    eight = new NumberObj();
    nine = new NumberObj();

    addNum(zero, 2, 1);
    addNum(zero, 3, 1);
    addNum(zero, 4, 1);
    addNum(zero, 5, 1);
    addNum(zero, 6, 1);
    addNum(zero, 2, 2);
    addNum(zero, 2, 3);
    addNum(zero, 2, 4);
    addNum(zero, 2, 5);
    addNum(zero, 2, 6);
    addNum(zero, 2, 7);
    addNum(zero, 3, 7);
    addNum(zero, 4, 7);
    addNum(zero, 5, 7);
    addNum(zero, 6, 7);
    addNum(zero, 6, 2);
    addNum(zero, 6, 3);
    addNum(zero, 6, 4);
    addNum(zero, 6, 5);
    addNum(zero, 6, 6);

    addNum(one, 3, 2);
    addNum(one, 4, 1);
    addNum(one, 4, 2);
    addNum(one, 4, 3);
    addNum(one, 4, 7);
    addNum(one, 4, 4);
    addNum(one, 4, 5);
    addNum(one, 4, 6);
    addNum(one, 3, 7);
    addNum(one, 5, 7);

    addNum(two, 2, 1);
    addNum(two, 3, 1);
    addNum(two, 4, 1);
    addNum(two, 5, 1);
    addNum(two, 6, 1);
    addNum(two, 6, 2);
    addNum(two, 6, 3);
    addNum(two, 6, 4);
    addNum(two, 2, 5);
    addNum(two, 2, 6);
    addNum(two, 2, 7);
    addNum(two, 3, 7);
    addNum(two, 4, 7);
    addNum(two, 5, 7);
    addNum(two, 6, 7);
    addNum(two, 5, 4);
    addNum(two, 4, 4);
    addNum(two, 3, 4);
    addNum(two, 2, 4);

    addNum(three, 2, 1);
    addNum(three, 3, 1);
    addNum(three, 4, 1);
    addNum(three, 5, 1);
    addNum(three, 6, 1);
    addNum(three, 6, 2);
    addNum(three, 6, 3);
    addNum(three, 6, 4);
    addNum(three, 6, 5);
    addNum(three, 6, 6);
    addNum(three, 2, 7);
    addNum(three, 3, 7);
    addNum(three, 4, 7);
    addNum(three, 5, 7);
    addNum(three, 6, 7);
    addNum(three, 2, 4);
    addNum(three, 3, 4);
    addNum(three, 4, 4);
    addNum(three, 5, 4);

    addNum(four, 4, 1);
    addNum(four, 3, 2);
    addNum(four, 2, 3);
    addNum(four, 2, 4);
    addNum(four, 3, 4);
    addNum(four, 4, 4);
    addNum(four, 5, 4);
    addNum(four, 6, 4);
    addNum(four, 4, 2);
    addNum(four, 4, 3);
    addNum(four, 4, 4);
    addNum(four, 4, 5);
    addNum(four, 4, 6);
    addNum(four, 4, 7);
    addNum(four, 1, 4);

    addNum(five, 6, 1);
    addNum(five, 5, 1);
    addNum(five, 4, 1);
    addNum(five, 3, 1);
    addNum(five, 2, 1);
    addNum(five, 2, 2);
    addNum(five, 2, 3);
    addNum(five, 2, 4);
    addNum(five, 3, 4);
    addNum(five, 4, 4);
    addNum(five, 5, 4);
    addNum(five, 6, 4);
    addNum(five, 6, 6);
    addNum(five, 6, 7);
    addNum(five, 5, 7);
    addNum(five, 4, 7);
    addNum(five, 3, 7);
    addNum(five, 2, 7);
    addNum(five, 6, 5);

    addNum(six, 6, 1);
    addNum(six, 5, 1);
    addNum(six, 4, 1);
    addNum(six, 3, 1);
    addNum(six, 2, 1);
    addNum(six, 2, 2);
    addNum(six, 2, 3);
    addNum(six, 2, 4);
    addNum(six, 3, 4);
    addNum(six, 4, 4);
    addNum(six, 5, 4);
    addNum(six, 6, 4);
    addNum(six, 6, 6);
    addNum(six, 6, 7);
    addNum(six, 5, 7);
    addNum(six, 4, 7);
    addNum(six, 3, 7);
    addNum(six, 2, 7);
    addNum(six, 6, 5);
    addNum(six, 2, 5);
    addNum(six, 2, 2);
    addNum(six, 2, 6);

    addNum(seven, 2, 1);
    addNum(seven, 3, 1);
    addNum(seven, 4, 1);
    addNum(seven, 5, 1);
    addNum(seven, 6, 1);
    addNum(seven, 6, 2);
    addNum(seven, 5, 3);
    addNum(seven, 4, 4);
    addNum(seven, 3, 5);
    addNum(seven, 2, 6);
    addNum(seven, 2, 7);

    addNum(eight, 6, 1);
    addNum(eight, 5, 1);
    addNum(eight, 4, 1);
    addNum(eight, 3, 1);
    addNum(eight, 2, 1);
    addNum(eight, 2, 2);
    addNum(eight, 2, 3);
    addNum(eight, 2, 4);
    addNum(eight, 3, 4);
    addNum(eight, 4, 4);
    addNum(eight, 5, 4);
    addNum(eight, 6, 4);
    addNum(eight, 6, 6);
    addNum(eight, 6, 7);
    addNum(eight, 5, 7);
    addNum(eight, 4, 7);
    addNum(eight, 3, 7);
    addNum(eight, 2, 7);
    addNum(eight, 6, 5);
    addNum(eight, 2, 2);
    addNum(eight, 6, 2);
    addNum(eight, 6, 3);
    addNum(eight, 2, 5);
    addNum(eight, 2, 6);

    addNum(nine, 6, 1);
    addNum(nine, 5, 1);
    addNum(nine, 4, 1);
    addNum(nine, 3, 1);
    addNum(nine, 2, 1);
    addNum(nine, 2, 2);
    addNum(nine, 2, 3);
    addNum(nine, 2, 4);
    addNum(nine, 3, 4);
    addNum(nine, 4, 4);
    addNum(nine, 5, 4);
    addNum(nine, 6, 4);
    addNum(nine, 6, 6);
    addNum(nine, 6, 7);
    addNum(nine, 5, 7);
    addNum(nine, 4, 7);
    addNum(nine, 3, 7);
    addNum(nine, 2, 7);
    addNum(nine, 6, 5);
    addNum(nine, 2, 2);
    addNum(nine, 6, 2);
    addNum(nine, 6, 3);
}

void LedNumber::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制数字背景
    drawNumberBg(&painter);
    //绘制数字
    drawNumber(&painter);
}

void LedNumber::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void LedNumber::drawNumberBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    double initX = space;
    double initY = space;
    double ledWidth = (double)(width() - 2 * space - (9 - 1) * padding) / 9;
    double ledHeight = (double)(height() - 2 * space - (9 - 1) * padding) / 9;

    //无数字渐变背景
    QLinearGradient numberBgGradient(QPointF(0, 0), QPointF(0, height()));
    numberBgGradient.setColorAt(0.0, numberBgColorStart);
    numberBgGradient.setColorAt(1.0, numberBgColorEnd);
    painter->setBrush(numberBgGradient);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QRectF ledRect(QPointF(initX, initY), QPointF(initX + ledWidth, initY + ledHeight));
            painter->drawRoundedRect(ledRect, radius, radius);
            initX += ledWidth + padding;
        }

        initX = space;
        initY += ledHeight + padding;
    }

    painter->restore();
}

void LedNumber::drawNumber(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QLinearGradient numberGradient(QPointF(0, 0), QPointF(0, height()));
    numberGradient.setColorAt(0.0, numberColorStart);
    numberGradient.setColorAt(1.0, numberColorEnd);
    painter->setBrush(numberGradient);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            switch (number) {
            case 0:
                drawNum(zero, i, j, painter);
                break;

            case 1:
                drawNum(one, i, j, painter);
                break;

            case 2:
                drawNum(two, i, j, painter);
                break;

            case 3:
                drawNum(three, i, j, painter);
                break;

            case 4:
                drawNum(four, i, j, painter);
                break;

            case 5:
                drawNum(five, i, j, painter);
                break;

            case 6:
                drawNum(six, i, j, painter);
                break;

            case 7:
                drawNum(seven, i, j, painter);
                break;

            case 8:
                drawNum(eight, i, j, painter);
                break;

            case 9:
                drawNum(nine, i, j, painter);
                break;
            }
        }
    }

    painter->restore();
}

void LedNumber::addNum(NumberObj *numberObj, int i, int j)
{
    numberObj->addPair(i, j);
}

void LedNumber::drawNum(NumberObj *numberObj, int i, int j, QPainter *painter)
{
    if (numberObj->hasThisPair(i, j)) {
        double ledWidth = (double)(width() - 2 * space - (9 - 1) * padding) / 9;
        double ledHeight = (double)(height() - 2 * space - (9 - 1) * padding) / 9;
        double ledX = space + i * ledWidth + i * padding;
        double ledY = space + j * ledHeight + j * padding;
        QRectF ledRect(QPointF(ledX, ledY), QPointF(ledX + ledWidth, ledY + ledHeight));
        painter->drawRoundedRect(ledRect, radius, radius);
    }
}

int LedNumber::getNumber() const
{
    return this->number;
}

int LedNumber::getSpace() const
{
    return this->space;
}

int LedNumber::getPadding() const
{
    return this->padding;
}

int LedNumber::getRadius() const
{
    return this->radius;
}

QColor LedNumber::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LedNumber::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LedNumber::getNumberBgColorStart() const
{
    return this->numberBgColorStart;
}

QColor LedNumber::getNumberBgColorEnd() const
{
    return this->numberBgColorEnd;
}

QColor LedNumber::getNumberColorStart() const
{
    return this->numberColorStart;
}

QColor LedNumber::getNumberColorEnd() const
{
    return this->numberColorEnd;
}

QSize LedNumber::sizeHint() const
{
    return QSize(150, 160);
}

QSize LedNumber::minimumSizeHint() const
{
    return QSize(10, 10);
}

void LedNumber::setNumber(int number)
{
    if (this->number != number) {
        this->number = number;
        update();
    }
}

void LedNumber::setSpace(int space)
{
    if ( this->space != space) {
        this->space = space;
        update();
    }
}

void LedNumber::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        update();
    }
}

void LedNumber::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        update();
    }
}

void LedNumber::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void LedNumber::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void LedNumber::setNumberBgColorStart(const QColor &numberBgColorStart)
{
    if (this->numberBgColorStart != numberBgColorStart) {
        this->numberBgColorStart = numberBgColorStart;
        update();
    }
}

void LedNumber::setNumberBgColorEnd(const QColor &numberBgColorEnd)
{
    if (this->numberBgColorEnd != numberBgColorEnd) {
        this->numberBgColorEnd = numberBgColorEnd;
        update();
    }
}

void LedNumber::setNumberColorStart(const QColor &numberColorStart)
{
    if (this->numberColorStart != numberColorStart) {
        this->numberColorStart = numberColorStart;
        update();
    }
}

void LedNumber::setNumberColorEnd(const QColor &numberColorEnd)
{
    if (this->numberColorEnd != numberColorEnd) {
        this->numberColorEnd = numberColorEnd;
        update();
    }
}
