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
    connect(actionQuitter, &QAction::triggered, this, &MainWindow::actionQuitter_activate);

    ui->menubar->setNativeMenuBar(false);

    appPath = QDir::homePath()  + "/Applications/Heficience-Menu-x86_64.AppImage";
    initButton(*ui->InstallationHeficienceMenu,*ui->DesinstallationHeficienceMenu,appPath);

    appPath = "/usr/bin/autocompletion";
    initButton(*ui->InstallationAutocompletion,*ui->DesinstallationAutocompletion,appPath);

    appPath = "/usr/bin/nocomprendo";
    initButton(*ui->InstallationNoComprendo,*ui->DesinstallationNoComprendo,appPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initButton(QPushButton &Install, QPushButton &Desintall, QString appPathHere)
{
    if (QFile(appPathHere).exists()) {
        Install.setEnabled(false);
        Install.setStyleSheet("background-color: #aaa");
    } else {
        Desintall.setEnabled(false);
        Desintall.setStyleSheet("background-color: #aaa");
    }
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
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/install_heficience-menu.sh ; sleep 3 ; bash ./install_heficience-menu.sh ; sleep 3 ; rm ./install_heficience-menu.sh ; sleep 3\"";
    installApp(*ui->InstallationHeficienceMenu, *ui->DesinstallationHeficienceMenu, cmdScript,
               "background-color: #22577a");
}

void MainWindow::on_DesinstallationHeficienceMenu_clicked()
{
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/uninstall_heficience-menu.sh ; sleep 3 ; bash ./uninstall_heficience-menu.sh ; sleep 3 ; rm ./uninstall_heficience-menu.sh sleep 3\"";
    installApp(*ui->DesinstallationHeficienceMenu, *ui->InstallationHeficienceMenu, cmdScript,
               "background-color: #22577a");
}
void MainWindow::on_InstallationAutocompletion_clicked()
{
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/install_autocompletion.sh ; sleep 3 ; bash ./install_autocompletion.sh ; sleep 3 ; rm ./install_autocompletion.sh ; sleep 3\"";
    installApp(*ui->InstallationAutocompletion, *ui->DesinstallationAutocompletion, cmdScript,
               "background-color: #38a3a5; color: #000");
}

void MainWindow::on_DesinstallationAutocompletion_clicked()
{
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/uninstall_autocompletion.sh ; sleep 3 ; bash ./uninstall_autocompletion.sh ; sleep 3 ; rm ./uninstall_autocompletion.sh ; rm -rf $HOME/.autocompletion ; sleep 3\"";
    installApp(*ui->DesinstallationAutocompletion, *ui->InstallationAutocompletion, cmdScript,
               "background-color: #38a3a5; color: #000");
}

void MainWindow::on_OuvrirDooSearch_clicked()
{
    LaunchSystemApp->execute("xdg-open", QStringList() << "https://paulluxwaffle.synology.me/Doosearch/src/search.php" );
}

void MainWindow::on_InstallationNoComprendo_clicked()
{
    cmdScript = "x-terminal-emulator --nofork -e sudo bash -c \"wget https://github.com/Heficience/HSuperMenu/raw/main/nocomprendo-without-qt-default.deb ; apt update ; apt install ./nocomprendo-without-qt-default.deb ; rm nocomprendo-without-qt-default.deb ; sleep 3\"";
    installApp(*ui->InstallationNoComprendo, *ui->DesinstallationNoComprendo, cmdScript,
               "background-color: #80ed99; color: #000");
}

void MainWindow::on_DesinstallationNoComprendo_clicked()
{
    cmdScript = "x-terminal-emulator --nofork -e sudo bash -c \"apt update ; apt remove nocomprendo ; sleep 3 \"";
    installApp(*ui->DesinstallationNoComprendo, *ui->InstallationNoComprendo, cmdScript,
               "background-color: #80ed99; color: #000");
}

void MainWindow::on_OuvrirSiteWeb_clicked() {
    LaunchSystemApp->execute("xdg-open", QStringList() << "https://www.heficience.com/index.php" );
}

void MainWindow::installApp(QPushButton &Install, QPushButton &Desintall, QString cmdSCriptUnique, QString Style) {
    Install.setEnabled(false);
    Install.setStyleSheet("background-color: #aaa");
    LaunchSystemApp->execute(cmdSCriptUnique);
    Desintall.setEnabled(true);
    Desintall.setStyleSheet(Style);
}