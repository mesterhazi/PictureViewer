#include "imagelistmodel.h"

ImageListModel::ImageListModel(QStringList paths, QList<image_item*> *pics, QSize thumbnail_size, QObject *parent)
: QAbstractListModel(parent)
{
    pics = &_data;
    auto iter = paths.begin();

    while(iter != paths.end())
    {
        QPixmap fullpic(*iter);
        image_item *actual = new image_item();
        actual->_file = *iter;
        actual->_fullsize = fullpic;
        actual->_thumbnail = fullpic.scaled(thumbnail_size.width(), thumbnail_size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        _data.append(actual);
        iter ++;
    }
}

ImageListModel::~ImageListModel()
{
    qDeleteAll(_data);
}

int ImageListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return _data.size();
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DecorationRole:
    {
        return _data.value(index.row())->_thumbnail;
    }
    case UrlRole:
    {
        return _data.value(index.row())->_file;
    }
    case FullScaleRole:
    {
        return _data.value(index.row())->_fullsize;
    }
    default:
        return QVariant();
    }
}
