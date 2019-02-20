#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "umldialog.h"
#include "aboutdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this->ui->actionOtw_rz, SIGNAL(triggered()), this, SLOT(onOpenTriggered()));
    QObject::connect(this->ui->actionGeneruj_diagram_UML, SIGNAL(triggered()), this, SLOT(onOpenUML()));
    QObject::connect(this->ui->actionO_programie, SIGNAL(triggered()), this, SLOT(onOpenAbout()));
    QObject::connect(this->ui->actionZamknij, SIGNAL(triggered()), this, SLOT(close()));
    this->setWindowTitle(tr("UML Class Diagram Generator"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::onOpenTriggered() {
    QFileDialog::Options options;
    QString selectedFilter = "Class Headers (*.h)";
    openFilesPath = ".\\..\\" ;
    QStringList files = QFileDialog::getOpenFileNames(
                                this, tr("Choose Files *.h"),
                                openFilesPath,
                                tr("All Files (*);;Text Files (*.txt);;Class Headers (*.h)"),
                                &selectedFilter,
                                options);
    _classList.clear();
    _symbolList.clear();
    this->ui->CodeBrowser->clear();
    if (files.count()) {
        openFilesPath = files[0];
        Logger logger(this->ui->Output);
        logger.log(QString("%1").arg(files.join("\n")));
        for (int i = 0; i < files.count(); i++)
        {
            QFile file(files[i]);
            if (!file.open(QIODevice::ReadOnly))
            {
                logger.log("Couldn't open file :" + files[i]);
            }
            QTextStream stream(&file);
            this->ui->CodeBrowser->append("\tFILE: " + files[i] + "\n");

            while(!stream.atEnd())
            {
                this->ui->CodeBrowser->append(stream.readLine()); // dodatkowo trzeba przekierowaæ do parsera
            }
            this->ui->CodeBrowser->append("\n");
            file.close();
            QString fileName = files[i];
            QStringList name = fileName.split("/", QString::SkipEmptyParts);
            fileName = name[name.size()-1];
            fileName.chop(2);
            fileName +=  + "_lexanalyse_log.txt";
            int symbolCounter;
            LexicalAnalyser analyser(fileName, &_symbolList);
            if (analyser.analyse(&file, &symbolCounter))
            {
                fileName = name[name.size()-1];
                fileName.chop(2);
                fileName +=  + "_parse_log.txt";
                Parser parser(fileName, &_symbolList, &_classList, this->ui->Output);
                parser.analyse();
            }
            else
            {
                QString msg = "Error at symbol ";
                msg += QString::number(symbolCounter);
                msg += " see " + fileName;
                msg += " for details.";
                this->ui->Output->append(msg);
            }
           _symbolList.clear();
        }
        int i = 0;
        while (i < _classList.size())
        {
            int j = 0;
            while (j < _classList.size())
            {
                if (i != j)
                {
                    if (_classList.at(i)->_ancestors.contains(_classList.at(j)->_name))  // we've found ancestor in analysed classes, his ancestors are ours as well
                    {
                        int k = 0;
                        while (k < _classList.at(j)->_ancestors.size())
                        {
                            if (! _classList.at(i)->_ancestors.contains(_classList.at(j)->_ancestors.at(k))) // we only add ancestor that are not on our ancestors list
                            {
                                _classList.at(i)->_ancestors.push_back(_classList.at(j)->_ancestors.at(k));
                                k = - 1; // we have to check the list again
                            }
                            k++;
                        }
                    }
                }
                j++;
            }
            i++;
        }
/*
        while (!_classList.empty())
        {
            QString className = "Class name: ";
            className += _classList.at(0)->_name;
            this->ui->CodeBrowser->append(className);
            this->ui->CodeBrowser->append("Ancestors:");
            int i = 0;
            while(i < _classList.at(0)->_ancestors.size())
            {
                QString classAncestor = "\t";
                classAncestor += _classList.at(0)->_ancestors.at(i);
                this->ui->CodeBrowser->append(classAncestor);
                i++;
            }
            this->ui->CodeBrowser->append("Methods:");
            i = 0;
            while(i < _classList.at(0)->_methods.size())
            {
                QString classMethod = "\t";
                int j = 0;
                while (j < _classList.at(0)->_methods.at(i)->_keywords.size())
                {
                    classMethod +=_classList.at(0)->_methods.at(i)->_keywords.at(j);
                    classMethod += " ";
                    j++;
                }
                classMethod += _classList.at(0)->_methods.at(i)->_type;
                classMethod += " ";
                classMethod += _classList.at(0)->_methods.at(i)->_name;
                classMethod += "(";
                j = 0;
                while (j <_classList.at(0)->_methods.at(i)->_attributes.size())
                {
                    int k = 0;

                    while (k < _classList.at(0)->_methods.at(i)->_attributes.at(j)->_keywords.size())
                    {
                        if (!_classList.at(0)->_methods.at(i)->_attributes.at(j)->_keywords.at(k).contains("public") && !_classList.at(0)->_methods.at(i)->_attributes.at(j)->_keywords.at(k).contains("private") && !_classList.at(0)->_methods.at(i)->_attributes.at(j)->_keywords.at(k).contains("protected"))
                        {
                            classMethod +=_classList.at(0)->_methods.at(i)->_attributes.at(j)->_keywords.at(k);
                            classMethod += " ";
                        }
                        k++;
                    }
                    classMethod +=_classList.at(0)->_methods.at(i)->_attributes.at(j)->_type;
                    classMethod += " ";
                    classMethod +=_classList.at(0)->_methods.at(i)->_attributes.at(j)->_name;
                    if (j < (_classList.at(0)->_methods.at(i)->_attributes.size() - 1))
                        classMethod += ", ";
                    j++;
                }
                classMethod += ")";
                i++;
                this->ui->CodeBrowser->append(classMethod);
            }

            this->ui->CodeBrowser->append("Attributes:");
            i = 0;
            while(i < _classList.at(0)->_attributes.size())
            {
                QString classAttribute = "\t";
                int j = 0;
                while (j < _classList.at(0)->_attributes.at(i)->_keywords.size())
                {
                    classAttribute +=_classList.at(0)->_attributes.at(i)->_keywords.at(j);
                    classAttribute += " ";
                    j++;
                }
                classAttribute += _classList.at(0)->_attributes.at(i)->_type;
                classAttribute += " ";
                classAttribute += _classList.at(0)->_attributes.at(i)->_name;
                i++;
                this->ui->CodeBrowser->append(classAttribute);
            }
            _classList.removeFirst();
        }
*/
    }
}

void MainWindow::onOpenUML()
{
    UmlDialog *umlDialog = new UmlDialog();
    umlDialog->getClassList(&_classList);
    umlDialog->exec();
}

void MainWindow::onOpenAbout()
{
    aboutDialog *about = new aboutDialog();
    about->exec();
}
