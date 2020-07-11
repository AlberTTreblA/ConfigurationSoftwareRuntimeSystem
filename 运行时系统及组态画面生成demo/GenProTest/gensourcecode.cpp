#include "gensourcecode.h"
#include "ui_gensourcecode.h"

GenSourceCode::GenSourceCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenSourceCode)
{
    ui->setupUi(this);
}

GenSourceCode::~GenSourceCode()
{
    delete ui;
}
