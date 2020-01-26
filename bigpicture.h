#ifndef BIGPICTURE_H
#define BIGPICTURE_H

#include <QWidget>
#include <QLabel>
#include "image_item.h"


class BigPicture
{
//    Q_OBJECT

public:
    explicit BigPicture(QList<image_item*> *pics, QScreen *screen);
    ~BigPicture();
    void updateImage(QPixmap img);

private:
    QLabel *labelImage;
    QList<image_item*> *_pics;
};

#endif // BIGPICTURE_H
