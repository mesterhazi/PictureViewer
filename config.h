#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QSettings>
#include <QHash>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QStringList *files, QHash<QString, int> *screens, QSize *thumbnail_size, QWidget *parent = nullptr);
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
    QSize *thumbnail_size;
    QHash<QString, int> *screens;
    QHash<int, QScreen*> *every_screen = new QHash<int, QScreen*>;
};

#endif // CONFIG_H
