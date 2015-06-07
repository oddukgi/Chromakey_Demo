#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#define IMGSOURCE ":res/Img_demo.png"
#define IMGTARGET ":res/panda.png"

// created by darongE
// 2015-06-07 SUN

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));

    originQImage = QImage(IMGSOURCE);
    sourceQImage = QImage(IMGSOURCE);
    targetQImage = QImage(IMGTARGET);
    //resultQImage = QImage(640,480);
    resultQImage = QImage(QSize(640, 480), QImage::Format_RGB32);

    uchar *pSourceData = sourceQImage.bits();
    uchar *pTargetData = targetQImage.bits();
    uchar *pResultData = resultQImage.bits();

    qDebug("size : %d", sourceQImage.byteCount());

    int sPixBlue,sPixGreen,sPixRed;

   QColor maskColor = QColor::fromRgb(sourceQImage.pixel(1,1));
   int kred= maskColor.red();
   int kgreen = maskColor.green();
   int kblue = maskColor.blue();
   QColor maskTemp;


   for(int inc = 0; inc <sourceQImage.size().width()*sourceQImage.size().height()*4 ; inc+=4)
   {

       sPixBlue = pSourceData[inc+0];
       sPixGreen = pSourceData[inc+1];
       sPixRed = pSourceData[inc+2];

       if((abs(kred - sPixRed) + abs(kgreen-sPixGreen)+abs(kblue-sPixBlue))/5<25){
           // background : copy pixel from target
           pSourceData[inc+2] = pTargetData[inc+2];
           pSourceData[inc+1] = pTargetData[inc+1];
           pSourceData[inc]   = pTargetData[inc];
       }else{
           // people : copy pixel from original
           pResultData[inc+2] = pSourceData[inc+2];
           pResultData[inc+1] = pSourceData[inc+1];
           pResultData[inc]   = pSourceData[inc];
       }
   }



}

Widget::~Widget()
{
    delete ui;
}


//  Original image
void Widget::on_pushButton_clicked()
{
    QPixmap drawPixmap = QPixmap::fromImage(originQImage);
    ui->label->setPixmap(drawPixmap.scaled(ui->label->size())); //source image

}

//  Composed image
void Widget::on_pushButton_2_clicked()
{
    QPixmap drawPixmap = QPixmap::fromImage(sourceQImage);
    ui->label_2->setPixmap(drawPixmap.scaled(ui->label_2->size())); //source image

    qDebug("composed image ");
}
