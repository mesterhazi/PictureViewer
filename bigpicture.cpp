#include "bigpicture.h"
#include "ui_bigpicture.h"

BigPicture::BigPicture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigPicture)
{
    ui->setupUi(this);
}

BigPicture::~BigPicture()
{
    delete ui;
}
