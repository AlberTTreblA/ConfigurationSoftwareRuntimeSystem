#ifndef GENSOURCECODE_H
#define GENSOURCECODE_H

#include <QWidget>

namespace Ui {
class GenSourceCode;
}

class GenSourceCode : public QWidget
{
    Q_OBJECT

public:
    explicit GenSourceCode(QWidget *parent = 0);
    ~GenSourceCode();

private:
    Ui::GenSourceCode *ui;
};

#endif // GENSOURCECODE_H
