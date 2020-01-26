#include "control.h"
#include "ui_control.h"
#include "config.h"
#include <QWindow>
#include <QScreen>
#include <QHash>

Control::Control(QStringList *files, QList<image_item*> *pics, QSize thumbnail_size, QHash<QString, int> *screens, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control)
{
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

//    _pic_window->show();
    _pic_window->updateImage(ui->listView_thumbnails->model()->index(0, 0).data(ImageListModel::FullScaleRole).value<QPixmap>());
}

Control::~Control()
{
    delete ui;
//    delete _pic_window;
}

void Control::on_listView_thumbnails_doubleClicked(const QModelIndex &index)
{
    _pic_window->updateImage(index.data(ImageListModel::FullScaleRole).value<QPixmap>());
}

