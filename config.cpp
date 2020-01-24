#include "config.h"
#include "ui_config.h"
#include <QFileDialog>

Config::Config(QStringList *files, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    _files = files;
    ui->setupUi(this);
    settings = new QSettings("adamthebaddest", "PictureViewer");
    Config::loadSettings();
}

Config::~Config()
{
    delete ui;
}

void Config::saveSettings()
{
    settings->setValue("config/folderurl", ui->textEdit_FolderDir->toPlainText());
    settings->setValue("config/grid_cols", ui->textEdit_PreviewCols->toPlainText());
    settings->setValue("config/grid_rows", ui->textEdit_PreviewRows->toPlainText());
    settings->setValue("config/monitor_control", ui->textEdit_MonitorControlNr->toPlainText());
    settings->setValue("config/monitor_image", ui->textEdit_MonitorImageNr->toPlainText());
    settings->sync();
}

void Config::loadSettings()
{
    ui->textEdit_FolderDir->setPlainText(settings->value("config/folderurl").toString());
    ui->textEdit_PreviewCols->setPlainText(settings->value("config/grid_cols").toString());
    ui->textEdit_PreviewRows->setPlainText(settings->value("config/grid_rows").toString());
    ui->textEdit_MonitorControlNr->setPlainText(settings->value("config/monitor_control").toString());
    ui->textEdit_MonitorImageNr->setPlainText(settings->value("config/monitor_image").toString());

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
    Config::saveSettings();
}
