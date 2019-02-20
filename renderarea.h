#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include "aclass.h"
class RenderArea : public QWidget
{
Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    void getClassList(QList<AClass*> *);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *parent = 0);
private:
        void paintClass(int, int, int, int, AClass*, QPainter *);
         QPen pen;
         QBrush brush;
         bool antialiased;
         bool transformed;
         QPixmap pixmap;
         QList<AClass*> * _classList;
};

#endif // RENDERAREA_H
