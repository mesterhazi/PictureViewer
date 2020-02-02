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

    void on_comboImageWindow_activated(int index);

    void on_comboControlWindow_activated(int index);

    void on_textEdit_ThumbnailWidth_textChanged();

    void on_textEdit_ThumbnailHeight_textChanged();

private:
    QSettings *settings;
    void saveSettings();
    void loadSettings();
    QStringList *_files;
    Ui::Config *ui;
    QSize *thumbnail_size;
    QTimer *interaction_timeout;
    const int timeout_ms = 30000;
    void restart_timeout();
    QHash<QString, int> *screens;
    QHash<int, QScreen*> *every_screen = new QHash<int, QScreen*>;
};

#endif // CONFIG_H
