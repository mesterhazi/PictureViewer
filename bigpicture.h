#ifndef BIGPICTURE_H
#define BIGPICTURE_H

#include <QWidget>

namespace Ui {
class BigPicture;
}

class BigPicture : public QWidget
{
    Q_OBJECT

public:
    explicit BigPicture(QWidget *parent = nullptr);
    ~BigPicture();

private:
    Ui::BigPicture *ui;
};

#endif // BIGPICTURE_H
