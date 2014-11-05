#include "dialog.h"
#include <QLineEdit>
#include <QPixmap>
#include <cstdlib>
#include <QPainter>
#include <QFont>
#include <ctime>

VCImp::VCImp(QWidget *parent)
    : QDialog(parent)
{
    srand(time(NULL));
    share1=new QLabel;
    share2=new QLabel;
    QSize s(1000,500);
    QRgb value=qRgba(255,255,255,255);
    layout=new QVBoxLayout;
    secret=new QImage(weigth,height,QImage::Format_RGBA8888)/*("3.bmp")*/;
    secretEx=new QImage(weigth*2,height*2,QImage::Format_RGBA8888);
    for(int i=0;i<weigth;i++)
        for(int j=0;j<height;j++)
            secret->setPixel(i,j,value);
    QPainter painter;
    QFont font;
    font.setPixelSize(18);
    font.setBold(true);
    font.setStyleHint(QFont::TypeWriter);
    painter.begin(secret);
    painter.setFont(font);
    painter.drawText(0,15,"ALB48");
    painter.end();

    secret->save("secret.bmp");
    extend();
    secretEx->save("secretEx.bmp");
    s1=new QImage(weigth*4,height*4,QImage::Format_RGBA8888);
    s2=new QImage(weigth*4,height*4,QImage::Format_RGBA8888);


    shareGen(secret);



    share1->setPixmap(QPixmap::fromImage(s1->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation)));
    share2->setPixmap(QPixmap::fromImage(s2->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation)));
    *s1=s1->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation);
    *s2=s2->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation);
    s1->save("shareo.bmp");
    s2->save("sharet.bmp");

    layout->addWidget(share1);
    layout->addStretch();
    layout->addWidget(share2);
    setLayout(layout);
}

void VCImp::extend()
{
    QRgb black=qRgb(0,0,0);
    for(int i=0;i<weigth;++i)
    {
        for(int j=0;j<height;j++)
        {
            if(secret->pixel(i,j)==black)
            {
                allBlack(secretEx,i*2,j*2);
            }
            else
            {
                empty(secretEx,i*2,j*2);
            }
        }
    }
}

void VCImp::shareGen(const QImage* secret)
{
    QRgb black=qRgb(0,0,0);
    for(int i=0;i<weigth*2;i+=2)
    {
        for(int j=0;j<height*2;j+=2)
        {
            if(secretEx->pixel(i,j)==black)
            {
                setToBlack(i,j);
            }
            else
            {
                setToWhite(i,j);
            }
        }
    }
}

void VCImp::setToBlack(int i,int j)
{
    int caseNum=0;
    caseNum=rand()%3;
    switch(caseNum)
    {
        case 0:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                topHor(s1,i*2,j*2);
                botHor(s2,i*2,j*2);
            }
            else
            {
                topHor(s2,i*2,j*2);
                botHor(s1,i*2,j*2);
            }
            break;
        case 1:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                lefVer(s1,i*2,j*2);
                rigVer(s2,i*2,j*2);
            }
            else
            {
                lefVer(s2,i*2,j*2);
                rigVer(s1,i*2,j*2);
            }
            break;
        case 2:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                lefRig(s1,i*2,j*2);
                rigLef(s2,i*2,j*2);
            }
            else
            {
                lefRig(s2,i*2,j*2);
                rigLef(s1,i*2,j*2);
            }
            break;

    }
}

void VCImp::setToWhite(int i,int j)
{
    int caseNum=0;
    caseNum=rand()%3;
    switch(caseNum)
    {
        case 0:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                topHor(s1,i*2,j*2);
                topHor(s2,i*2,j*2);
            }
            else
            {
                botHor(s2,i*2,j*2);
                botHor(s1,i*2,j*2);
            }
            break;
        case 1:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                lefVer(s1,i*2,j*2);
                lefVer(s2,i*2,j*2);
            }
            else
            {
                rigVer(s2,i*2,j*2);
                rigVer(s1,i*2,j*2);
            }
            break;
        case 2:
            caseNum=rand()%2;
            if(caseNum==0)
            {
                lefRig(s1,i*2,j*2);
                lefRig(s2,i*2,j*2);
            }
            else
            {
                rigLef(s2,i*2,j*2);
                rigLef(s1,i*2,j*2);
            }
            break;
    }
}

void VCImp::topHor(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i,j);
    allBlack(pic,i,j+2);
    value=qRgba(255,255,255,0);
    empty(pic,i+2,j);
    empty(pic,i+2,j+2);
}

void VCImp::botHor(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i+2,j);
    allBlack(pic,i+2,j+2);
    value=qRgba(255,255,255,0);
    empty(pic,i,j);
    empty(pic,i,j+2);
}

void VCImp::lefVer(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i,j);
    allBlack(pic,i+2,j);
    value=qRgba(255,255,255,0);
    empty(pic,i,j+2);
    empty(pic,i+2,j+2);
}

void VCImp::rigVer(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i,j+2);
    allBlack(pic,i+2,j+2);
    value=qRgba(255,255,255,0);
    empty(pic,i,j);
    empty(pic,i+2,j);
}

void VCImp::rigLef(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i,j+2);
    allBlack(pic,i+2,j);
    value=qRgba(255,255,255,0);
    empty(pic,i,j);
    empty(pic,i+2,j+2);
}

void VCImp::lefRig(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    allBlack(pic,i,j);
    allBlack(pic,i+2,j+2);
    value=qRgba(255,255,255,0);
    empty(pic,i,j+2);
    empty(pic,i+2,j);
}

void VCImp::empty(QImage *pic,int i,int j)
{
    QRgb value;
    value=qRgba(255,255,255,0);
    pic->setPixel(i,j,value);
    pic->setPixel(i,j+1,value);
    pic->setPixel(i+1,j,value);
    pic->setPixel(i+1,j+1,value);
}

void VCImp::allBlack(QImage* pic,int i,int j)
{
    QRgb value;
    value=qRgba(0,0,0,255);
    pic->setPixel(i,j,value);
    pic->setPixel(i,j+1,value);
    pic->setPixel(i+1,j,value);
    pic->setPixel(i+1,j+1,value);
}

VCImp::~VCImp()
{
    delete share1;
    delete share2;
    delete s1;
    delete s2;
    delete secret;
    delete layout;
}
