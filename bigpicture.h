#ifndef BIGPICTURE_H
#define BIGPICTURE_H

#include <QWidget>
#include <QLabel>
#include "image_item.h"

//namespace Ui {
//class BigPicture;
//}

//class BigPicture : public QWidget
//{
//    Q_OBJECT

//public:
//    explicit BigPicture(QList<image_item*> *pics, QWidget *parent = nullptr);
//    ~BigPicture();
//    void updateImage(image_item img);
//    void updateImage(QPixmap img);

//private:
//    Ui::BigPicture *ui;
//    QList<image_item*> *_pics;
//};


class BigPicture;

class BigPicture
{
//    Q_OBJECT

public:
    explicit BigPicture(QList<image_item*> *pics, QScreen *screen);
    ~BigPicture();
//    void updateImage(image_item img);
    void updateImage(QPixmap img);

private:
    QLabel *labelImage;
    QList<image_item*> *_pics;
};

#endif // BIGPICTURE_H
