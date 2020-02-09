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
    /* Full list of images: pixmap, thumbnail, path */
    QList<image_item*>* all_pics = new QList<image_item*>;
    /* Avaialable screens (monitors) */
    QHash<QString, int> *screens = new QHash<QString, int>;
    /* pixel*pixel size of the thumbnail images */
    QSize thumbnail_size;
    /* Slideshow timeouts: [slideshow_on [s], slideshow_off [s]]
    Slideshow off image changing acts as a screensaver */
    QList<int> *slideshow_timeouts = new QList<int>();
    Config *conf_win = new Config(files, screens, &thumbnail_size, slideshow_timeouts);
    Control *w;

    if(conf_win->exec() != QDialog::Accepted)
    {
        return 1;
    }
    w = new Control(files, all_pics, thumbnail_size, screens, slideshow_timeouts);
    return a.exec();
}
