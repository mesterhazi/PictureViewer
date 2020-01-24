#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QStringList *files, QWidget *parent = nullptr);
    ~Config();

private slots:
    void on_button_FolderSelect_clicked();

    void on_Config_accepted();

private:
    QSettings *settings;
    void saveSettings();
    void loadSettings();
    QStringList *_files;
    Ui::Config *ui;
};

#endif // CONFIG_H
