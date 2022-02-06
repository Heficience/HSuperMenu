#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProcess>
#include <QWidget>
#include <QApplication>
#include <QUrl>
#include <QMessageBox>
#include <QRect>
#include <QDesktopWidget>
#include <QSettings>
#include <QAction>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QAction *actionQuitter;
    QAction *actionOptions;
    QPushButton *InstallationHeficienceMenu;
    QPushButton *DesinstallationHeficienceMenu;
    QPushButton *InstallationAutocompletion;
    QPushButton *DesinstallationAutocompletion;
    QPushButton *OuvrirDooSearch;
    QPushButton *InstallationNoComprendo;
    QPushButton *DesinstallationNoComprendo;
    QPushButton *OuvrirSiteWeb;
    QProcess *LaunchSystemApp;
    QString cmdScript;
    QString pathCommandExec;
    QString pathCommandRm;
    static void handleStateChanged(QProcess *procss, QWidget *widget, QWidget *killtest);

private:
    Ui::MainWindow *ui;

private slots:
    void actionQuitter_activate();
    void on_InstallationHeficienceMenu_clicked();
    void on_DesinstallationHeficienceMenu_clicked();
    void on_InstallationAutocompletion_clicked();
    void on_DesinstallationAutocompletion_clicked();
    void on_OuvrirDooSearch_clicked();
    void on_InstallationNoComprendo_clicked();
    void on_DesinstallationNoComprendo_clicked();
    void on_OuvrirSiteWeb_clicked();
};

#endif // MAINWINDOW_H
 
