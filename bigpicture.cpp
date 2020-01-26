#include "bigpicture.h"
#include "ui_bigpicture.h"
#include <QWindow>
#include <QScreen>

//BigPicture::BigPicture(QList<image_item*> *pics, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::BigPicture)
//{
//    _pics = pics;
//    this->showFullScreen();
//    ui->setupUi(this);
//    ui->labelImage->setWindowFlag(Qt::Window);
//    ui->labelImage->showMaximized();

//}

//BigPicture::~BigPicture()
//{
//    delete ui;
//}

//void BigPicture::updateImage(QPixmap img)
//{
//    ui->labelImage->setPixmap(img);
//}

//void BigPicture::updateImage(image_item img)
//{
//    ui->labelImage->setPixmap(img._fullsize);
//}

BigPicture::BigPicture(QList<image_item*> *pics, QScreen *screen)
{
    _pics = pics;
    labelImage = new QLabel;
    labelImage->setWindowFlag(Qt::SplashScreen);
    labelImage->setStyleSheet("QLabel { background-color : black; }");
    labelImage->show();
    labelImage->move(screen->geometry().topLeft());
    labelImage->showFullScreen();
    screen_size.setWidth(screen->size().width());
    screen_size.setHeight(screen->size().height());

}

BigPicture::~BigPicture()
{
}

void BigPicture::updateImage(QPixmap img)
{
    labelImage->setPixmap(img.scaled(screen_size.width(), screen_size.height(), Qt::KeepAspectRatio));
    labelImage->setAlignment(Qt::AlignCenter);
}
