
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUi(std::make_shared<Ui::MainWindow>()),
    m_pFsModel(std::make_shared<BOMFileSystemModel>()),
    m_pUiAbout(std::make_shared<Ui::About>())
{
    m_pUi->setupUi(this);
    m_pUiAbout->setupUi(&m_about);
    m_about.hide();
    m_pUi->files->setModel(m_pFsModel.get());

    connect(m_pUi->chooseDir, SIGNAL(clicked()),
            this, SLOT(slotChooseDir())
            );
    connect(m_pUi->fix, SIGNAL(clicked()),
            m_pFsModel.get(), SLOT(slotFixBOM())
            );
    connect(m_pFsModel.get(), SIGNAL(fixed()),
            this, SLOT(slotFixed())
            );
    connect(m_pUi->about, SIGNAL(clicked()),
            this, SLOT(slotAbout())
            );
}

void MainWindow::slotFixed()
{
    QMessageBox msgBox;
    msgBox.setText("BOM has been fixed.");
    msgBox.exec();

    m_pUi->fix->setEnabled(false);
}

void MainWindow::slotChooseDir()
{
    QString path = QFileDialog::getExistingDirectory(this, "Choose Directory");
    m_pDir = std::make_shared<QDir>(QDir(path));
    m_pFsModel->populateDirectory(QDir(path));
    m_pUi->files->setRootIndex(m_pFsModel->index(path));
    m_pUi->files->setColumnWidth(0, 300);
    m_pUi->fix->setEnabled(true);
}

void MainWindow::slotAbout()
{
    m_about.show();
}
