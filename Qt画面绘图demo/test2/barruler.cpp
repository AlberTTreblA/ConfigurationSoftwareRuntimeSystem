#pragma execution_character_set("utf-8")

#include "barruler.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

BarRuler::BarRuler(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    longStep = 10;
    shortStep = 1;
    space = 20;

    animation = false;
    animationStep = 0.5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    barBgColor = QColor(220, 220, 220);
    barColor = QColor(100, 184, 255);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
}

BarRuler::~BarRuler()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void BarRuler::paintEvent(QPaintEvent *)
{
    //����׼������,���÷����
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //���Ʊ���
    drawBg(&painter);
    //���Ʊ��
    drawRuler(&painter);
    //������״����
    drawBarBg(&painter);
    //������״
    drawBar(&painter);
}

void BarRuler::drawBg(QPainter *painter)
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

void BarRuler::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    //������������ 20�ĳ���Ϊ�̶ȳ����ֵĿ��
    double initX = space + 20;
    double initY = space;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - space);
    painter->drawLine(topPot, bottomPot);

    //���������߿̶�
    double length = height() - 2 * space;
    //����ÿһ���ƶ�����
    double increment = length / (maxValue - minValue);
    //����������������
    int longLineLen = 10;
    int shortLineLen = 7;

    //���ݷ�Χֵ���ƿ̶�ֵ���̶�ֵ
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontWidth = painter->fontMetrics().width(strValue);
            double fontHeight = painter->fontMetrics().height();
            QPointF textPot(initX - fontWidth - 5, initY + fontHeight / 3);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void BarRuler::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //20�ĳ���Ϊ�̶ȳ����ֵĿ�� 15Ϊ�̶ȳߵ���״ͼ�Ŀ��
    double initX = space + 20 + 15;
    QPointF topLeftPot(initX, space);
    QPointF bottomRightPot(width() - space , height() - space);
    barRect = QRectF(topLeftPot, bottomRightPot);

    painter->setBrush(barBgColor);
    painter->drawRect(barRect);
    painter->restore();
}

void BarRuler::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    double barHeight = barRect.height();
    double increment = (double)barHeight / (maxValue - minValue);
    double initY = (currentValue - minValue) * increment;

    QPointF topLeftPot(barRect.topLeft().x(), barRect.bottomLeft().y() - initY);
    QPointF bottomRightPot(barRect.bottomRight());
    QRectF currentRect(topLeftPot, bottomRightPot);

    painter->setBrush(barColor);
    painter->drawRect(currentRect);
    painter->restore();
}

double BarRuler::getMinValue() const
{
    return this->minValue;
}

double BarRuler::getMaxValue() const
{
    return this->maxValue;
}

double BarRuler::getValue() const
{
    return this->value;
}

int BarRuler::getPrecision() const
{
    return this->precision;
}

int BarRuler::getLongStep() const
{
    return this->longStep;
}

int BarRuler::getShortStep() const
{
    return this->shortStep;
}

int BarRuler::getSpace() const
{
    return this->space;
}

bool BarRuler::getAnimation() const
{
    return this->animation;
}

double BarRuler::getAnimationStep() const
{
    return this->animationStep;
}

QColor BarRuler::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor BarRuler::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor BarRuler::getLineColor() const
{
    return this->lineColor;
}

QColor BarRuler::getBarBgColor() const
{
    return this->barBgColor;
}

QColor BarRuler::getBarColor() const
{
    return this->barColor;
}

QSize BarRuler::sizeHint() const
{
    return QSize(100, 350);
}

QSize BarRuler::minimumSizeHint() const
{
    return QSize(20, 50);
}

void BarRuler::setRange(double minValue, double maxValue)
{
    //�����Сֵ���ڻ��ߵ������ֵ������
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //���Ŀ��ֵ���ڷ�Χֵ��,����������Ŀ��ֵ
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void BarRuler::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void BarRuler::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void BarRuler::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void BarRuler::setValue(double value)
{
    //ֵС����Сֵ����ֵ�������ֵ�����账��
    if (value < minValue || value > maxValue) {
        return;
    }

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        update();
    } else {
        timer->start();
    }
}

void BarRuler::setValue(int value)
{
    setValue((double)value);
}

void BarRuler::setPrecision(int precision)
{
    //���ȷ��Ϊ 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void BarRuler::setLongStep(int longStep)
{
    //�̲������ܳ���������
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        update();
    }
}

void BarRuler::setShortStep(int shortStep)
{
    //�̲������ܳ���������
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        update();
    }
}

void BarRuler::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void BarRuler::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void BarRuler::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void BarRuler::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void BarRuler::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void BarRuler::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void BarRuler::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void BarRuler::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}

void BarRuler::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}
