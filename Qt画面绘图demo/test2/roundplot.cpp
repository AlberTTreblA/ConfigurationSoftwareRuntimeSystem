#include "roundplot.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

RoundPlot::RoundPlot(QWidget *parent) : QWidget(parent)
{
	setAutoFillBackground(true);
	QPalette palette = this->palette();
	palette.setColor(QPalette::Background, QColor(255, 255, 255));
	setPalette(palette);

	minValue = 0;
	maxValue = 100;
	value = 0;
	precision = 0;
	angle = 40;
	unit = "";

	currentPercent = 0;
	valuePercent = 0;

	usedColor = QColor(165, 220, 62);
	freeColor = QColor(215, 215, 215);

	rangeTextColor = QColor(137, 137, 137);
	valueTextColor = QColor(52, 155, 218);

	valueBgColor = QColor(239, 239, 239);
	outBgColor = QColor(233, 233, 233);
	centerBgColorStart = QColor(45, 204, 112);
	centerBgColorEnd = QColor(51, 152, 219);

	timer = new QTimer(this);
	timer->setInterval(10);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
}

RoundPlot::~RoundPlot()
{
	if (timer->isActive()) {
		timer->stop();
	}
}

void RoundPlot::paintEvent(QPaintEvent *)
{
	int width = this->width();
	int height = this->height();

	//绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width / 2, height / 2);

	int side = qMin(width, height);
	painter.scale(side / 200.0, side / 200.0);

	//绘制已使用百分比及未使用百分比进度
	drawDial(&painter);
	//绘制最外框圆形背景
	drawBgOut(&painter);
	//绘制中间圆环渐变背景
	drawBgRound(&painter);
	//绘制最里框百分比文字圆形背景
	drawBgCenter(&painter);
	//绘制范围值及当前值文字
	drawText(&painter);
}

void RoundPlot::drawDial(QPainter *painter)
{
	int radius = 95;
	double lineWidth = 2.5;
	painter->save();
	painter->rotate(angle);

	//根据起始旋转的角度计算每次坐标需要旋转的角度,按照100等分计算
	//每次旋转的角度=360-(起始角度*2--分左右)/100
	double rotate = (double)(360 - (angle * 2)) / 100;

	//绘制已使用百分比
	painter->setPen(QPen(usedColor, lineWidth));

	for (double i = 0; i < currentPercent; i++) {
		painter->drawLine(0, radius, 0, radius / 1.2);
		painter->rotate(rotate);
	}

	//绘制未使用百分比
	painter->setPen(QPen(freeColor, lineWidth));

	for (double i = currentPercent; i < 100; i++) {
		painter->drawLine(0, radius, 0, radius / 1.2);
		painter->rotate(rotate);
	}

	painter->restore();
}

void RoundPlot::drawBgOut(QPainter *painter)
{
	int radius = 70;
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(outBgColor);
	painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
	painter->restore();
}

void RoundPlot::drawBgRound(QPainter *painter)
{
	int radius = 50;
	painter->save();
	QConicalGradient conicalGradient(radius, radius, 90);
	conicalGradient.setColorAt(0, centerBgColorStart);
	conicalGradient.setColorAt(1.0, centerBgColorEnd);
	painter->setPen(Qt::NoPen);
	painter->setBrush(conicalGradient);
	painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
	painter->restore();
}

void RoundPlot::drawBgCenter(QPainter *painter)
{
	int radius = 30;
	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(valueBgColor);
	painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
	painter->restore();
}

void RoundPlot::drawText(QPainter *painter)
{
	int radius = 100;
	painter->save();

	//绘制百分比文字及范围值文字
	double currentValue = currentPercent * ((maxValue - minValue) / 100) + minValue;

	//如果当前值超过了目标值则取目标值
	if (currentValue > value) {
		currentValue = value;
	}

	QString strValue = QString("%1%2").arg(QString::number(currentValue, 'f', precision)).arg(unit);
	QString strMinValue = QString("%1%2").arg(minValue).arg(unit);
	QString strMaxValue = QString("%1%2").arg(maxValue).arg(unit);

	painter->setFont(QFont("Arial", 13));
	painter->setPen(QPen(valueTextColor));
	QFontMetricsF fm = QFontMetricsF(painter->font());
	QSizeF size = fm.size(Qt::TextSingleLine, strValue);
	painter->drawText(-size.width() / 2, size.height() / 3, strValue);

	painter->setFont(QFont("Arial", 8));
	painter->setPen(QPen(rangeTextColor));
	fm = QFontMetricsF(painter->font());
	size = fm.size(Qt::TextSingleLine, strMinValue);
	painter->drawText(-radius / 2 - size.width() / 2 + 8, 80, strMinValue);
	size = fm.size(Qt::TextSingleLine, strMaxValue);
	painter->drawText(radius / 2 - size.width() / 2 - 8, 80, strMaxValue);

	painter->restore();
}

void RoundPlot::updateValue()
{
	if (currentPercent >= valuePercent) {
		timer->stop();
		return;
	}

	currentPercent ++;
	update();
}

void RoundPlot::setRange(double minValue, double maxValue)
{
	//如果最小值大于或者等于最大值则不设置
	if (minValue >= maxValue) {
		return;
	}

	if (timer->isActive()) {
		timer->stop();
	}

	currentPercent = 0;
	valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
	this->minValue = minValue;
	this->maxValue = maxValue;

	//如果目标值不在范围值内,则重新设置目标值
	if (value < minValue || value > maxValue) {
		setValue(value);
	}
}

void RoundPlot::setRange(int minValue, int maxValue)
{
	setRange((double)minValue, (double)maxValue);
}

void RoundPlot::setValue(double value)
{
	if (value < minValue) {
		this->value = minValue;
	} else if (value > maxValue) {
		this->value = maxValue;
	} else {
		this->value = value;
	}

	if (timer->isActive()) {
		timer->stop();
	}

	emit valueChanged(this->value);
	currentPercent = 0;
	valuePercent = 100 * (this->value - this->minValue) / (this->maxValue - this->minValue);
	timer->start();
}

void RoundPlot::setValue(int value)
{
	setValue((double)value);
}

void RoundPlot::setAngle(double angle)
{
	this->angle = angle;
	update();
}

void RoundPlot::setPrecision(int precision)
{
	//精确度最多为 3
	if (precision <= 3) {
		this->precision = precision;
		update();
	}
}

void RoundPlot::setUnit(QString unit)
{
	this->unit = unit;
	update();
}

void RoundPlot::setUsedColor(QColor usedColor)
{
	this->usedColor = usedColor;
	update();
}

void RoundPlot::setFreeColor(QColor freeColor)
{
	this->freeColor = freeColor;
	update();
}

void RoundPlot::setRangeTextColor(QColor rangeTextColor)
{
	this->rangeTextColor = rangeTextColor;
	update();
}

void RoundPlot::setValueTextColor(QColor valueTextColor)
{
	this->valueTextColor = valueTextColor;
	update();
}

void RoundPlot::setValueBgColor(QColor valueBgColor)
{
	this->valueBgColor = valueBgColor;
	update();
}

void RoundPlot::setOutBgColor(QColor outBgColor)
{
	this->outBgColor = outBgColor;
	update();
}

void RoundPlot::setCenterBgColor(QColor centerBgColorStart, QColor centerBgColorEnd)
{
	this->centerBgColorStart = centerBgColorStart;
	this->centerBgColorEnd = centerBgColorEnd;
	update();
}
