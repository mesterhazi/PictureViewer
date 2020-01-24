#include "bigpicture.h"
#include "ui_bigpicture.h"

BigPicture::BigPicture(QList<image_item*> *pics, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigPicture)
{
    _pics = pics;
    ui->setupUi(this);
}

BigPicture::~BigPicture()
{
    delete ui;
}

void BigPicture::updateImage(QPixmap img)
{
    ui->labelImage->setPixmap(img);
}

void BigPicture::updateImage(image_item img)
{
    ui->labelImage->setPixmap(img._fullsize);
}
