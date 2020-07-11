#ifndef LEDNUMBER_H
#define LEDNUMBER_H


#include <QWidget>

class NumberObj : public QWidget
{
    Q_OBJECT
public:
    NumberObj(QWidget *parent = 0) {}

    bool hasThisPair(int hCoor, int vCoor)
    {
        int count = vec.count();

        for (int i = 0; i < count ; i++) {
            if (vec.at(i).first == hCoor &&
                    vec.at(i).second == vCoor) {
                return true;
            }
        }

        return false;
    }

    void addPair(int i, int j)
    {
        vec.append(qMakePair(i, j));
    }

private:
    QVector<QPair<int, int> > vec;
};


#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT LedNumber : public QWidget
#else
class LedNumber : public QWidget
#endif

{
    Q_OBJECT
    Q_PROPERTY(int number READ getNumber WRITE setNumber)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)
    Q_PROPERTY(int padding READ getPadding WRITE setPadding)
    Q_PROPERTY(int radius READ getRadius WRITE setRadius)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)

    Q_PROPERTY(QColor numberBgColorStart READ getNumberBgColorStart WRITE setNumberBgColorStart)
    Q_PROPERTY(QColor numberBgColorEnd READ getNumberBgColorEnd WRITE setNumberBgColorEnd)

    Q_PROPERTY(QColor numberColorStart READ getNumberColorStart WRITE setNumberColorStart)
    Q_PROPERTY(QColor numberColorEnd READ getNumberColorEnd WRITE setNumberColorEnd)

public:
    explicit LedNumber(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawNumberBg(QPainter *painter);
    void drawNumber(QPainter *painter);

private:
    int number;                     //Ŀ��ֵ
    int space;                      //���
    int padding;                    //���ֵļ��
    int radius;                     //Բ�ǽǶ�

    QColor bgColorStart;            //�������俪ʼ��ɫ
    QColor bgColorEnd;              //�������������ɫ

    QColor numberBgColorStart;      //�����ֱ������俪ʼ��ɫ
    QColor numberBgColorEnd;        //�����ֱ������������ɫ

    QColor numberColorStart;        //���ֽ��俪ʼ��ɫ
    QColor numberColorEnd;          //���ֽ��������ɫ

    NumberObj *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;

private:
    void addNum(NumberObj *numberObj, int i, int j);
    void drawNum(NumberObj *numberObj, int i, int j, QPainter *painter);

public:
    int getNumber()                 const;
    int getSpace()                  const;
    int getPadding()                const;
    int getRadius()                 const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;

    QColor getNumberBgColorStart()  const;
    QColor getNumberBgColorEnd()    const;

    QColor getNumberColorStart()    const;
    QColor getNumberColorEnd()      const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public slots:
    //����ֵ
    void setNumber(int number);
    //���ü��
    void setSpace(int space);
    //�������ּ�ļ��
    void setPadding(int padding);
    //����Բ�ǽǶ�
    void setRadius(int radius);

    //���ñ�����ɫ
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    //������������ɫ
    void setNumberBgColorStart(const QColor &numberBgColorStart);
    void setNumberBgColorEnd(const QColor &numberBgColorEnd);

    //����������ɫ
    void setNumberColorStart(const QColor &numberColorStart);
    void setNumberColorEnd(const QColor &numberColorEnd);

};

#endif // LEDNUMBER_H
