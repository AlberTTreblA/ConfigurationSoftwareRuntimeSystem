#ifndef BARRULER_H
#define BARRULER_H


#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT BarRuler : public QWidget
#else
class BarRuler : public QWidget
#endif

{
    Q_OBJECT    
    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(int longStep READ getLongStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ getShortStep WRITE setShortStep)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)

    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ getAnimationStep WRITE setAnimationStep)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBgColor READ getBarBgColor WRITE setBarBgColor)
    Q_PROPERTY(QColor barColor READ getBarColor WRITE setBarColor)

public:
    explicit BarRuler(QWidget *parent = 0);
    ~BarRuler();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawRuler(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawBar(QPainter *painter);

private:    
    double maxValue;                //��Сֵ
    double minValue;                //���ֵ
    double value;                   //Ŀ��ֵ
    int precision;                  //��ȷ��,С�����λ

    int longStep;                   //�������ȷֲ���
    int shortStep;                  //�������ȷֲ���
    int space;                      //���

    bool animation;                 //�Ƿ����ö�����ʾ
    double animationStep;           //������ʾʱ����

    QColor bgColorStart;            //�������俪ʼ��ɫ
    QColor bgColorEnd;              //�������������ɫ
    QColor lineColor;               //������ɫ
    QColor barBgColor;              //��״����ɫ
    QColor barColor;                //��״��ɫ

    bool reverse;                   //�Ƿ���
    double currentValue;            //��ǰֵ
    QTimer *timer;                  //��ʱ�����ƶ���
    QRectF barRect;                 //��״ͼ����

private slots:
    void updateValue();

public:    
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    int getPrecision()              const;

    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;
    QColor getBarBgColor()          const;
    QColor getBarColor()            const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots:
    //���������Сֵ-��Χֵ
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //���������Сֵ
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //����Ŀ��ֵ
    void setValue(double value);
    void setValue(int value);

    //���þ�ȷ��
    void setPrecision(int precision);
    //���������ȷֲ���
    void setLongStep(int longStep);
    void setShortStep(int shortStep);
    //���ü��
    void setSpace(int space);

    //�����Ƿ����ö�����ʾ
    void setAnimation(bool animation);
    //���ö�����ʾ�Ĳ���
    void setAnimationStep(double animationStep);

    //���ñ�����ɫ
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);
    //����������ɫ
    void setLineColor(const QColor &lineColor);
    //������״��ɫ
    void setBarBgColor(const QColor &barBgColor);
    void setBarColor(const QColor &barColor);

signals:
    void valueChanged(double value);
};

#endif // BARRULER_H
