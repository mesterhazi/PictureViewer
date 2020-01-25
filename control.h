#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>
#include "config.h"
#include "bigpicture.h"
#include "imagelistmodel.h"

namespace Ui {
class Control;
}

class Control : public QMainWindow
{
    Q_OBJECT

public:
    explicit Control(QStringList *files, QList<image_item*> *pics, QHash<QString, int> *screens, QWidget *parent = nullptr);
    ~Control();

private slots:
    void on_listView_thumbnails_doubleClicked(const QModelIndex &index);

private:
    Ui::Control *ui;
    QList<image_item*> *_pics;
    ImageListModel *_images;
    BigPicture *_pic_window;
//    QStringList *_files;

};

#endif // CONTROL_H
