#ifndef IMAGE_ITEM_H
#define IMAGE_ITEM_H
#include <Qt>
#include <QPixmap>

struct image_item
{
//public:
    QString _file;
    QPixmap _thumbnail;
    QPixmap _fullsize;
};


#endif // IMAGE_ITEM_H
