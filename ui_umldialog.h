/********************************************************************************
** Form generated from reading UI file 'umldialog.ui'
**
** Created: Fri 28. May 13:15:13 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UMLDIALOG_H
#define UI_UMLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UmlDialog
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *UmlDialog)
    {
        if (UmlDialog->objectName().isEmpty())
            UmlDialog->setObjectName(QString::fromUtf8("UmlDialog"));
        UmlDialog->resize(1070, 600);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UmlDialog->sizePolicy().hasHeightForWidth());
        UmlDialog->setSizePolicy(sizePolicy);
        UmlDialog->setMinimumSize(QSize(400, 300));
        UmlDialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(UmlDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        retranslateUi(UmlDialog);

        QMetaObject::connectSlotsByName(UmlDialog);
    } // setupUi

    void retranslateUi(QDialog *UmlDialog)
    {
        UmlDialog->setWindowTitle(QApplication::translate("UmlDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UmlDialog: public Ui_UmlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UMLDIALOG_H
