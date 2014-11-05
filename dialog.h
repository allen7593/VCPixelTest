#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>

class VCImp : public QDialog
{
    Q_OBJECT

public:
    VCImp(QWidget *parent = 0);
    ~VCImp();

private:
    QLabel* share1;
    QLabel* share2;
    QImage* secret;
    QImage* secretEx;
    QImage* s1;
    QImage* s2;
    QVBoxLayout* layout;

    static const int height=25;
    static const int weigth=50;

    void extend();

    void shareGen(const QImage*);

    void setToBlack(int,int);
    void setToWhite(int,int);

    void topHor(QImage*,int,int);
    void botHor(QImage*,int,int);
    void lefVer(QImage*,int,int);
    void rigVer(QImage*,int,int);
    void lefRig(QImage*,int,int);
    void rigLef(QImage*,int,int);
    void empty(QImage*,int,int);
    void allBlack(QImage*,int,int);


};

#endif // VCIMP_H
