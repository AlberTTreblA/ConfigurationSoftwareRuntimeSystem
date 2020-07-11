#ifndef ROUNDPLOT_H
#define ROUNDPLOT_H


#include <QWidget>

class RoundPlot : public QWidget
{
	Q_OBJECT
public:
	RoundPlot(QWidget *parent = 0);
	~RoundPlot();

protected:
	void paintEvent(QPaintEvent *);
	void drawDial(QPainter *painter);
	void drawBgOut(QPainter *painter);
	void drawBgRound(QPainter *painter);
	void drawBgCenter(QPainter *painter);
	void drawText(QPainter *painter);

private:
	double minValue;            //��Сֵ
	double maxValue;            //���ֵ
	double value;               //Ŀ��ֵ
	double angle;               //��ʼ��ת�Ƕ�
    int precision;              //��ȷ��,С���㼸λ
	QString unit;               //��λ

	double currentPercent;      //��ǰ�Ѵ���İٷֱ�
	double valuePercent;        //Ŀ��ֵ�ٷֱ�

	QColor usedColor;           //��ʹ�ðٷֱ���ɫ
	QColor freeColor;           //δʹ�ðٷֱ���ɫ

	QColor rangeTextColor;      //��Χֵ������ɫ
	QColor valueTextColor;      //Ŀ��ֵ������ɫ

	QColor valueBgColor;        //Ŀ��ֵ����ɫ
	QColor outBgColor;          //��߿򱳾�ɫ
	QColor centerBgColorStart;  //�м�Բ�����䱳����ʼ��ɫ
	QColor centerBgColorEnd;    //�м�Բ�����䱳��������ɫ

    QTimer *timer;              //���ƶ�ʱ��

private slots:
	void updateValue();

public:
	//��ȡ��Сֵ
	double getMinValue()const
	{
		return minValue;
	}

	//��ȡ���ֵ
	double getMaxValue()const
	{
		return maxValue;
	}

	//��ȡĿ��ֵ
	double getValue()const
	{
		return value;
	}

	//��ȡ��ת�Ƕ�
	double getAngle()const
	{
		return angle;
	}

	//��ȡС�����λ
    int getPrecision()const
	{
        return precision;
	}

	//��ȡ��λ
	QString getUnit()const
	{
		return unit;
	}

public slots:
	//���������Сֵ-��Χֵ
	void setRange(double minValue, double maxValue);
	void setRange(int minValue, int maxValue);

	//����Ŀ��ֵ
	void setValue(double value);
	void setValue(int value);

	//������ת�Ƕ�
	void setAngle(double angle);

	//����С�����λ
    void setPrecision(int precision);

	//�������ֺ���ĵ�λ
	void setUnit(QString unit);

	//������ʹ�ðٷֱ���ɫ
	void setUsedColor(QColor usedColor);
	//����δʹ�ðٷֱ���ɫ
	void setFreeColor(QColor freeColor);

	//���÷�Χֵ������ɫ
	void setRangeTextColor(QColor rangeTextColor);
	//����Ŀ��ֵ������ɫ
	void setValueTextColor(QColor valueTextColor);

	//����Ŀ��ֵ����ɫ
	void setValueBgColor(QColor valueBgColor);
	//������߿򱳾�ɫ
	void setOutBgColor(QColor outBgColor);
	//��������Բ������ɫ
	void setCenterBgColor(QColor centerBgColorStart, QColor centerBgColorEnd);

signals:
	void valueChanged(double value);
};

#endif // ROUNDPLOT_H
