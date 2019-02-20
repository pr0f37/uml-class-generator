#include "umldialog.h"
#include "ui_umldialog.h"

UmlDialog::UmlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UmlDialog)
{
    ui->setupUi(this);
    _renderArea = new RenderArea();
    ui->verticalLayout->addWidget(_renderArea,0, 0);
    this->setWindowTitle(tr("UML Diagram Window"));
}

UmlDialog::~UmlDialog()
{
    delete ui;
}

void UmlDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UmlDialog::getClassList(QList<AClass *> *classList)
{
    _classList = classList;
    _renderArea->getClassList(classList);
    _renderArea->repaint();
}
