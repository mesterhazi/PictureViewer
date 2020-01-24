#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QPixmap>
#include <QUrl>
#include "image_item.h"


class ImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // QAbstractItemModel retrieves various information (like text, color, ...)
   // from the same index using roles. We can define custom ones, however to
   // avoid a clash with predefined roles, ours must start at Qt::UserRole.
   // All numbers below this one are reserved for Qt internals.
    enum Roles
    {
        NewRole = Qt::UserRole + 1,
        UrlRole = NewRole + 1,
        FullScaleRole = NewRole + 2,
    };
    //  TODO:is this a good parameter type? what can I get from a folder?
    ImageListModel(QStringList paths, QList<image_item*> *pics, QObject *parent = 0);
    ~ImageListModel();

    // needed by QAbstractListModel
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<image_item*> _data;
};

#endif // IMAGELISTMODEL_H
