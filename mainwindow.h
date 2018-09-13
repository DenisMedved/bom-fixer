#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QDir>
#include <QMainWindow>

#include "bomfilesystemmodel.h"

namespace Ui {
class MainWindow;
class About;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::shared_ptr<QDir> m_pDir;
    std::shared_ptr<BOMFileSystemModel> m_pFsModel;
    std::shared_ptr<Ui::MainWindow> m_pUi;
    std::shared_ptr<Ui::About> m_pUiAbout;
    QWidget m_about;

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void slotChooseDir();
    void slotFixed();
    void slotAbout();
};

#endif // MAINWINDOW_H
