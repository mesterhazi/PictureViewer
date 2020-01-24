#include "control.h"
#include "config.h"
#include "image_item.h"
#include "bigpicture.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* Full paths of the selected pictures */
    QStringList *files = new QStringList();
    QList<image_item*>* all_pics = new QList<image_item*>;
    Config *conf_win = new Config(files);
    Control *w;

    if(conf_win->exec() != QDialog::Accepted)
    {
        return 1;
    }
    w = new Control(files, all_pics);
    w->show();
    return a.exec();
}
