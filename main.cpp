#include "control.h"
#include "config.h"
#include "image_item.h"
#include "bigpicture.h"

#include <QApplication>
#include <QGuiApplication>
#include <QWindow>

QList<QScreen*> *screens;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* Full paths of the selected pictures */
    QStringList *files = new QStringList();
    QList<image_item*>* all_pics = new QList<image_item*>;
    QHash<QString, int> *screens = new QHash<QString, int>;
    Config *conf_win = new Config(files, screens);
    Control *w;

    if(conf_win->exec() != QDialog::Accepted)
    {
        return 1;
    }
    w = new Control(files, all_pics, screens);
    return a.exec();
}
