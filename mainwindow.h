#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QTextStream>
#include <QMainWindow>
#include "logger.h"
#include "analyser.h"
#include "lexicalanalyser.h"
#include "aclass.h"
#include "parser.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onOpenTriggered();
    void onOpenUML();
    void onOpenAbout();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QString openFilesPath;
    QWidget *codeBrowser;
    QList<QString> _symbolList;
    QList<AClass*> _classList;
};

#endif // MAINWINDOW_H
