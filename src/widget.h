#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    QImage originQImage;
    QImage sourceQImage;
    QImage targetQImage;   //target pic
    QImage resultQImage;   //composed pic


};

#endif // WIDGET_H
