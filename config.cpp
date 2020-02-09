#include "config.h"
#include "ui_config.h"
#include <QString>
#include <QFileDialog>
#include <QScreen>
#include <QGuiApplication>
#include <QVariant>
#include <QTimer>

#include <QDebug>

Config::Config(QStringList *files, QHash<QString, int> *screens, QSize *thumbnail_size, QList<int> *slideshow_timeouts, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    _files = files;
    _slideshow_timeouts = slideshow_timeouts;
    ui->setupUi(this);
    int biggest, smallest;
    QList<QScreen*> temp_screens;
    QString list_item_screen;
    // get every available screen (=monitor)
    temp_screens = QGuiApplication::screens();

    this->screens = screens;
    this->thumbnail_size = thumbnail_size;

    // add monitors to the screen selector combo
    auto iter = temp_screens.begin();
    biggest = smallest = 0;
    int idx = 0;
    while( iter != temp_screens.end())
    {
        every_screen->insert(idx, *iter);
        QScreen *temp = *iter;
        if (every_screen->value(idx) > every_screen->value(biggest))
            biggest = idx;
        if (every_screen->value(idx) < every_screen->value(smallest))
            smallest = idx;

        list_item_screen = temp->name() + " - " + QString::number(temp->size().width()) + "x" + QString::number(temp->size().height());
        ui->comboImageWindow->addItem(list_item_screen, idx);
        ui->comboControlWindow->addItem(list_item_screen, idx);
        iter ++;
        idx ++;
    }

    int index;
    index = ui->comboImageWindow->findData(QVariant::fromValue(biggest));
    ui->comboImageWindow->setCurrentIndex(index);
    index = ui->comboControlWindow->findData(QVariant::fromValue(smallest));
    ui->comboControlWindow->setCurrentIndex(index);

    settings = new QSettings("adamthebaddest", "PictureViewer");
    Config::loadSettings();

    /* Timer setup for aut starting after a certain time */
    Config::max_timeout_s = DEFAULT_AUTOSTART_TIMEOUT;
    interaction_timeout = new QTimer(this);
    auto con = connect(interaction_timeout, SIGNAL(timeout()), this, SLOT(handle_timeout()));
    interaction_timeout->setSingleShot(false);
    restart_timeout();
    interaction_timeout->start(1000);
}

Config::~Config()
{
    delete ui;
}

void Config::saveSettings()
{
    settings->setValue("config/folderurl", ui->textEdit_FolderDir->toPlainText());
    settings->setValue("config/thumbnail_width", ui->lineEdit_ThumbnailWidth->text());
    settings->setValue("config/thumbnail_height", ui->lineEdit_ThumbnailHeight->text());
    settings->setValue("config/autostart_timeout", ui->lineEdit_AutoStartTimeout->text());
    settings->setValue("config/slideshow_timeout", ui->lineEdit_SlideshowTimeout->text());
    settings->setValue("config/screensaver_timeout", ui->lineEdit_ScreensaverTimeout->text());
    settings->sync();
}

void Config::loadSettings()
{
    ui->textEdit_FolderDir->setPlainText(settings->value("config/folderurl").toString());
    ui->lineEdit_ThumbnailWidth->setText(settings->value("config/thumbnail_width").toString());
    ui->lineEdit_ThumbnailHeight->setText(settings->value("config/thumbnail_height").toString());
    ui->lineEdit_AutoStartTimeout->setText(settings->value("config/autostart_timeout").toString());
    ui->lineEdit_SlideshowTimeout->setText(settings->value("config/slideshow_timeout").toString());
    ui->lineEdit_ScreensaverTimeout->setText(settings->value("config/screensaver_timeout").toString());

}

void Config::on_button_FolderSelect_clicked()
{
    QString folder_url_str;
    QUrl folder_url;
    QFileDialog file_selector(this);
    file_selector.setFileMode(QFileDialog::Directory);
    file_selector.setOption(QFileDialog::ShowDirsOnly);
    folder_url_str = ui->textEdit_FolderDir->toPlainText();
    if(folder_url_str != "")
    {
        file_selector.setDirectory(folder_url_str);
    }
    folder_url = file_selector.getExistingDirectoryUrl(this, "Folder containing the pictures", folder_url);

    ui->textEdit_FolderDir->setPlainText(folder_url.toString(QUrl::RemoveScheme));

    restart_timeout();
}

void Config::on_Config_accepted()
{
    QStringList filters, filenames;
    QString temp;
    QDir *image_dir = new QDir(ui->textEdit_FolderDir->toPlainText());
    filters << "*.jpg" << "*.jpeg" << "*.png";
    if (image_dir->exists())
    {
        image_dir->setFilter(QDir::Files);
        image_dir->setNameFilters(filters);
        filenames = image_dir->entryList();
        auto iter = filenames.begin();
        while(iter != filenames.end())
        {
            temp = *iter;
            temp = image_dir->absoluteFilePath(temp);
            _files->append(temp);
            iter ++;
        }
    }

    // TODO: try-catch
    thumbnail_size->setWidth(ui->lineEdit_ThumbnailWidth->text().toUInt());
    thumbnail_size->setHeight(ui->lineEdit_ThumbnailHeight->text().toUInt());

    _slideshow_timeouts->append(ui->lineEdit_SlideshowTimeout->text().toUInt());
    _slideshow_timeouts->append(ui->lineEdit_ScreensaverTimeout->text().toUInt());

    screens->insert("image", ui->comboImageWindow->itemData(ui->comboImageWindow->currentIndex()).toInt());
    screens->insert("control", ui->comboControlWindow->currentData().toInt());
    Config::saveSettings();
}

void Config::restart_timeout()
{
    Config::timeout_s = Config::max_timeout_s;
}

void Config::handle_timeout()
{
    timeout_s --;
    if(timeout_s <= 0)
    {
        Config::accept();
    }
    else
    {
        QString msg = "Starting automatically in " + QString::number(timeout_s) + "s!";
        ui->label_AutoLoadCounter->setText(msg);
    }
}

void Config::on_comboImageWindow_activated(int index)
{
    restart_timeout();
}

void Config::on_comboControlWindow_activated(int index)
{
    restart_timeout();
}

void Config::on_lineEdit_AutoStartTimeout_editingFinished()
{
    restart_timeout();
    try {
        Config::max_timeout_s = ui->lineEdit_AutoStartTimeout->text().toUInt();
    } catch (...) {

    }
}

void Config::on_lineEdit_SlideshowTimeout_editingFinished()
{
    restart_timeout();
}

void Config::on_lineEdit_ScreensaverTimeout_editingFinished()
{
    restart_timeout();
}

void Config::on_lineEdit_ThumbnailWidth_editingFinished()
{
    restart_timeout();
}

void Config::on_lineEdit_ThumbnailHeight_editingFinished()
{
    restart_timeout();
}
