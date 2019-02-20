#ifndef UMLDIALOG_H
#define UMLDIALOG_H
#include <QDialog>
#include "renderarea.h"
#include "aclass.h"

namespace Ui {
    class UmlDialog;
}

class UmlDialog : public QDialog {
    Q_OBJECT
public:
    UmlDialog(QWidget *parent = 0);
    ~UmlDialog();
    void getClassList(QList<AClass *> *);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::UmlDialog *ui;
    QList<AClass *> * _classList;
    RenderArea * _renderArea;
};

#endif // UMLDIALOG_H
