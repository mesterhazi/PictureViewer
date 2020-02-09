#include "control.h"
#include "ui_control.h"
#include "config.h"
#include <QWindow>
#include <QScreen>
#include <QHash>

Control::Control(QStringList *files, QList<image_item*> *pics, QSize thumbnail_size, QHash<QString, int> *screens, QList<int> *slideshow_timeouts, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control)
{
    _slideshow_timeouts = slideshow_timeouts;
    QList<QScreen*> temp_screens;
    // get every available screen (=monitor)
    temp_screens = QGuiApplication::screens();
    _pic_window = new BigPicture(pics, temp_screens[screens->value("image")]);

    ui->setupUi(this);
    ui->listView_thumbnails->setModel(new ImageListModel(*files, pics, thumbnail_size, ui->listView_thumbnails));
    ui->listView_thumbnails->setViewMode(QListView::IconMode);
    ui->listView_thumbnails->setFlow(QListView::Flow::TopToBottom);
    this->show();
    this->move(temp_screens[screens->value("control")]->geometry().topLeft());

    _pic_window->updateImage(ui->listView_thumbnails->model()->index(0, 0).data(ImageListModel::FullScaleRole).value<QPixmap>());

    time_since_last_change = 0;
    picture_change_timer = new QTimer();
    connect(picture_change_timer, SIGNAL(timeout), this, SLOT(picture_change_timeout_handler));
    picture_change_timer->setSingleShot(false);
    picture_change_timer->start(1000);
}

Control::~Control()
{
    delete ui;
//    delete _pic_window;
}

void Control::on_listView_thumbnails_doubleClicked(const QModelIndex &index)
{
    _pic_window->updateImage(index.data(ImageListModel::FullScaleRole).value<QPixmap>());
    last_picture_col = index.column();
    last_picture_row = index.row();
}

void Control::switch_next_picture()
{
    int max_col, max_row;
    QModelIndex idx;
    QPixmap actual_pic;
    max_col = ui->listView_thumbnails->model()->columnCount();
    max_row = ui->listView_thumbnails->model()->rowCount();

    if(last_picture_col < max_col)
        last_picture_col ++;
    else if (last_picture_row < max_row)
    {
        last_picture_col = 0;
        last_picture_row ++;
    }
    else
    {
        last_picture_col = 0;
        last_picture_row = 0;
    }

    idx = ui->listView_thumbnails->model()->index(last_picture_row, last_picture_col);
    actual_pic = idx.data(ImageListModel::FullScaleRole).value<QPixmap>();
    if(actual_pic.isNull())
    {
        switch_next_picture(); // if this is not a valid QPixmap check the next slot
        return;
    }
    _pic_window->updateImage(idx.data(ImageListModel::FullScaleRole).value<QPixmap>());
}


void Control::picture_change_timeout_handler()
{
    int change_threshold;
    time_since_last_change ++;
    change_threshold = slideshow_active ? _slideshow_timeouts->at(0) : _slideshow_timeouts->at(1);



}

void Control::on_pushButton_clicked()
{
    switch_next_picture();
}
