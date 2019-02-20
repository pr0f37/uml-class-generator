/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 28. May 13:15:13 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOtw_rz;
    QAction *actionGeneruj_diagram_UML;
    QAction *action;
    QAction *actionZamknij;
    QAction *actionO_programie;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTextBrowser *CodeBrowser;
    QLabel *label;
    QTextBrowser *Output;
    QMenuBar *menuBar;
    QMenu *menuPlik;
    QMenu *menuPomoc;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(711, 588);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionOtw_rz = new QAction(MainWindow);
        actionOtw_rz->setObjectName(QString::fromUtf8("actionOtw_rz"));
        actionGeneruj_diagram_UML = new QAction(MainWindow);
        actionGeneruj_diagram_UML->setObjectName(QString::fromUtf8("actionGeneruj_diagram_UML"));
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        actionZamknij = new QAction(MainWindow);
        actionZamknij->setObjectName(QString::fromUtf8("actionZamknij"));
        actionO_programie = new QAction(MainWindow);
        actionO_programie->setObjectName(QString::fromUtf8("actionO_programie"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        CodeBrowser = new QTextBrowser(centralWidget);
        CodeBrowser->setObjectName(QString::fromUtf8("CodeBrowser"));
        CodeBrowser->setEnabled(true);
        sizePolicy.setHeightForWidth(CodeBrowser->sizePolicy().hasHeightForWidth());
        CodeBrowser->setSizePolicy(sizePolicy);
        CodeBrowser->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(CodeBrowser);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        Output = new QTextBrowser(centralWidget);
        Output->setObjectName(QString::fromUtf8("Output"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Output->sizePolicy().hasHeightForWidth());
        Output->setSizePolicy(sizePolicy1);
        Output->setMinimumSize(QSize(0, 100));
        Output->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(Output);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 711, 21));
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QString::fromUtf8("menuPlik"));
        menuPomoc = new QMenu(menuBar);
        menuPomoc->setObjectName(QString::fromUtf8("menuPomoc"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPlik->menuAction());
        menuBar->addAction(menuPomoc->menuAction());
        menuPlik->addAction(actionOtw_rz);
        menuPlik->addAction(actionGeneruj_diagram_UML);
        menuPlik->addSeparator();
        menuPlik->addAction(actionZamknij);
        menuPomoc->addAction(actionO_programie);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOtw_rz->setText(QApplication::translate("MainWindow", "Otw\303\263rz", 0, QApplication::UnicodeUTF8));
        actionOtw_rz->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionGeneruj_diagram_UML->setText(QApplication::translate("MainWindow", "Generuj diagram UML", 0, QApplication::UnicodeUTF8));
        actionGeneruj_diagram_UML->setShortcut(QApplication::translate("MainWindow", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("MainWindow", "_", 0, QApplication::UnicodeUTF8));
        actionZamknij->setText(QApplication::translate("MainWindow", "Zamknij", 0, QApplication::UnicodeUTF8));
        actionZamknij->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionO_programie->setText(QApplication::translate("MainWindow", "O programie", 0, QApplication::UnicodeUTF8));
        actionO_programie->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Tre\305\233\304\207 pliku", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Output", 0, QApplication::UnicodeUTF8));
        menuPlik->setTitle(QApplication::translate("MainWindow", "Plik", 0, QApplication::UnicodeUTF8));
        menuPomoc->setTitle(QApplication::translate("MainWindow", "Pomoc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
