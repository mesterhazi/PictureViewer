#include "control.h"
#include "ui_control.h"
#include "config.h"

Control::Control(QStringList *files, QList<image_item*> *pics, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control)
{
    _pic_window = new BigPicture(pics);
    ui->setupUi(this);
    ui->listView_thumbnails->setModel(new ImageListModel(*files, pics, ui->listView_thumbnails));
    ui->listView_thumbnails->setViewMode(QListView::IconMode);
    ui->listView_thumbnails->setFlow(QListView::Flow::TopToBottom);

    _pic_window->show();
    _pic_window->updateImage(ui->listView_thumbnails->model()->index(0, 0).data(ImageListModel::FullScaleRole).value<QPixmap>());
}

Control::~Control()
{
    delete ui;
    delete _pic_window;
}

void Control::on_listView_thumbnails_doubleClicked(const QModelIndex &index)
{
    _pic_window->updateImage(index.data(ImageListModel::FullScaleRole).value<QPixmap>());
}

