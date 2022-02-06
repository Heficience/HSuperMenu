#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <string>
#include <QWindow>
#include <QDockWidget>
#include <QTreeWidget>
#include <map>
#include <QGuiApplication>
#include <QObject>

std::map<std::string, QString> QStringMap;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

#ifdef __linux__
    QMainWindow::setWindowIcon(QIcon(":/Images/Heficience_Icone.svg"));
#elif _WIN32
    QMainWindow::setWindowIcon(QIcon(":/Images/Heficience_Icone.ico"));
#elif __APPLE__
    QMainWindow::setWindowIcon(QIcon(":/Images/Heficience_Icone.icns"));
#endif
    
    ui->setupUi(this);

    actionOptions = ui->menuFichier->addAction("Options");
    actionOptions->setEnabled(false);

    actionQuitter = ui->menuFichier->addAction("Quitter");
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(actionQuitter_activate()));

    ui->menubar->setNativeMenuBar(false);

    ui->DesinstallationHeficienceMenu->setEnabled(false);
    ui->DesinstallationHeficienceMenu->setStyleSheet("background-color: #aaa");

    QString homepath = QDir::homePath()  + "/.autocompletion";

    if (QDir(homepath).exists()) {
        ui->InstallationAutocompletion->setEnabled(false);
        ui->InstallationAutocompletion->setStyleSheet("background-color: #aaa");
    } else {
        ui->DesinstallationAutocompletion->setEnabled(false);
        ui->DesinstallationAutocompletion->setStyleSheet("background-color: #aaa");
    }

    ui->DesinstallationNoComprendo->setEnabled(false);
    ui->DesinstallationNoComprendo->setStyleSheet("background-color: #aaa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStateChanged(QProcess *procss, QWidget *widget, QWidget *testkill)
{
    if (procss->state() == QProcess::NotRunning)
    {
        widget->close();
        qApp->closeAllWindows();
        testkill->close();
    }
}

void MainWindow::actionQuitter_activate()
{
    qApp->quit();
}

void MainWindow::on_InstallationHeficienceMenu_clicked()
{
    ui->InstallationHeficienceMenu->setEnabled(false);
    ui->InstallationHeficienceMenu->setStyleSheet("background-color: #aaa");
    ui->DesinstallationHeficienceMenu->setEnabled(true);
    ui->DesinstallationHeficienceMenu->setStyleSheet("background-color: #22577a");
}

void MainWindow::on_DesinstallationHeficienceMenu_clicked()
{
    ui->DesinstallationHeficienceMenu->setEnabled(false);
    ui->DesinstallationHeficienceMenu->setStyleSheet("background-color: #aaa");
    ui->InstallationHeficienceMenu->setEnabled(true);
    ui->InstallationHeficienceMenu->setStyleSheet("background-color: #22577a");
}
void MainWindow::on_InstallationAutocompletion_clicked()
{
    ui->InstallationAutocompletion->setEnabled(false);
    ui->InstallationAutocompletion->setStyleSheet("background-color: #aaa");
    cmdScript = "konsole --nofork -e sudo bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/install_autocompletion.sh ; sleep 3 ; bash ./install_autocompletion.sh ; sleep 3 ; rm ./install_autocompletion.sh ; sleep 3\"";
    LaunchSystemApp->execute(cmdScript);
    ui->DesinstallationAutocompletion->setEnabled(true);
    ui->DesinstallationAutocompletion->setStyleSheet("background-color: #38a3a5; color: #000");
}

void MainWindow::on_DesinstallationAutocompletion_clicked()
{
    ui->DesinstallationAutocompletion->setEnabled(false);
    ui->DesinstallationAutocompletion->setStyleSheet("background-color: #aaa");
    cmdScript = "konsole --nofork -e sudo bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/uninstall_autocompletion.sh ; sleep 3 ; bash ./uninstall_autocompletion.sh ; sleep 3 ; rm ./uninstall_autocompletion.sh ; rm -rf $HOME/.autocompletion ; sleep 3\"";
    LaunchSystemApp->execute(cmdScript);
    ui->InstallationAutocompletion->setEnabled(true);
    ui->InstallationAutocompletion->setStyleSheet("background-color: #38a3a5; color: #000");
}

void MainWindow::on_OuvrirDooSearch_clicked()
{
    LaunchSystemApp->execute("xdg-open", QStringList() << "https://paulluxwaffle.synology.me/Doosearch/src/search.php" );
}

void MainWindow::on_InstallationNoComprendo_clicked()
{
    ui->InstallationNoComprendo->setEnabled(false);
    ui->InstallationNoComprendo->setStyleSheet("background-color: #aaa");
    ui->DesinstallationNoComprendo->setEnabled(true);
    ui->DesinstallationNoComprendo->setStyleSheet("background-color: #80ed99; color: #000");
}

void MainWindow::on_DesinstallationNoComprendo_clicked()
{
    ui->DesinstallationNoComprendo->setEnabled(false);
    ui->DesinstallationNoComprendo->setStyleSheet("background-color: #aaa");
    ui->InstallationNoComprendo->setEnabled(true);
    ui->InstallationNoComprendo->setStyleSheet("background-color: #80ed99; color: #000");
}

void MainWindow::on_OuvrirSiteWeb_clicked() {
    LaunchSystemApp->execute("xdg-open", QStringList() << "https://www.heficience.com/index.php" );
}