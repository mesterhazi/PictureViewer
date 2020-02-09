#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>
#include <QTimer>
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
    explicit Control(QStringList *files, QList<image_item*> *pics, QSize thumbnail_size, QHash<QString, int> *screens, QList<int> *slideshow_timeouts, QWidget *parent = nullptr);
    ~Control();

private slots:
    void on_listView_thumbnails_doubleClicked(const QModelIndex &index);
    void picture_change_timeout_handler();

    void on_pushButton_clicked();

private:
    Ui::Control *ui;
    QList<image_item*> *_pics;
    ImageListModel *_images;
    BigPicture *_pic_window;
    /* slideshow and screensaver thingies */
    QList<int> *_slideshow_timeouts;
    QTimer *picture_change_timer; // 1s timer
    int time_since_last_change;
    bool slideshow_active;
    int last_picture_row;
    int last_picture_col;

    void switch_next_picture();

};

#endif // CONTROL_H
