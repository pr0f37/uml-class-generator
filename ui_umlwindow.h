/********************************************************************************
** Form generated from reading UI file 'umlwindow.ui'
**
** Created: Mon 24. May 15:35:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UMLWINDOW_H
#define UI_UMLWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UmlWindow
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *UmlWindow)
    {
        if (UmlWindow->objectName().isEmpty())
            UmlWindow->setObjectName(QString::fromUtf8("UmlWindow"));
        UmlWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UmlWindow->sizePolicy().hasHeightForWidth());
        UmlWindow->setSizePolicy(sizePolicy);
        UmlWindow->setMinimumSize(QSize(400, 400));
        UmlWindow->setMaximumSize(QSize(800, 600));
        UmlWindow->setCursor(QCursor(Qt::OpenHandCursor));
        UmlWindow->setSizeGripEnabled(true);
        UmlWindow->setModal(false);
        verticalLayout = new QVBoxLayout(UmlWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        retranslateUi(UmlWindow);

        QMetaObject::connectSlotsByName(UmlWindow);
    } // setupUi

    void retranslateUi(QDialog *UmlWindow)
    {
        UmlWindow->setWindowTitle(QApplication::translate("UmlWindow", "Dialog", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        UmlWindow->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class UmlWindow: public Ui_UmlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UMLWINDOW_H
