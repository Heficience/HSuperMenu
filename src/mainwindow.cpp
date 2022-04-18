#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QWindow>
#include <QDockWidget>
#include <QTreeWidget>
#include <map>
#include <QGuiApplication>
#include <QObject>
#include <QtSvg>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

#ifdef __linux__
    this->setWindowIcon(QIcon(":/Images/Heficience_Icone.svg"));
#elif _WIN32
    this->setWindowIcon(QIcon(":/Images/Heficience_Icone.ico"));
#elif __APPLE__
    this->setWindowIcon(QIcon(":/Images/Heficience_Icone.icns"));
#endif

    this->setWindowTitle("Pour Installer/Ouvrir nos Logiciels");

    actionOptions = ui->menuFichier->addAction("Options");
    actionOptions->setEnabled(false);

    actionQuitter = ui->menuFichier->addAction("Quitter");
    connect(actionQuitter, &QAction::triggered, this, &MainWindow::actionQuitter_activate);

    ui->menubar->setNativeMenuBar(false);

#ifdef __linux__
    appPath = QDir::homePath()  + "/Applications/Heficience-Menu-x86_64.AppImage";
#elif _WIN32
    appPath = "C:\\Program Files\\Heficience\\Heficience Menu";
#elif __APPLE__

#endif

    initButton(*ui->InstallationHeficienceMenu,*ui->DesinstallationHeficienceMenu,appPath);

#ifdef __linux__
    appPath = "/usr/bin/autocompletion";
#elif _WIN32
    appPath = ".\\autocompletion_windows.exe";
#elif __APPLE__

#endif
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
        Install.setStyleSheet("background-color: #aaa; color:#777;");
    } else {
        Desintall.setEnabled(false);
        Desintall.setStyleSheet("background-color: #aaa; color:#777;");
    }
}

void MainWindow::actionQuitter_activate()
{
    qApp->quit();
}

void MainWindow::on_InstallationHeficienceMenu_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/install_heficience-menu.sh ; sleep 3 ; bash ./install_heficience-menu.sh ; sleep 3 ; rm ./install_heficience-menu.sh ; sleep 3\"";
#elif _WIN32
    cmdScript = "Start PowerShell \
                \"Write-Output \'Récupération de la dernière version du logiciel\'; \
                Start-Sleep -s 2 ; \
                Invoke-WebRequest \
                -Uri 'https://github.com/Heficience/Heficience-menu/releases/download/4.20/Windows-Heficience-Menu-4.20.exe' \
                -OutFile '.\\Windows-Heficience-Menu-4.20.exe'; \
                Write-Output \'Installation de la dernière version du logiciel\' ; \
                Start-Sleep -s 3 ; \
                Start-Process Windows-Heficience-Menu-4.20.exe -Wait; \
                Write-Output \'Suppression du fichier téléchargé\'; \
                Start-Sleep -s 2 ; \
                cmd /c 'del /f Windows-Heficience-Menu-4.20.exe' \" ";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->InstallationHeficienceMenu, *ui->DesinstallationHeficienceMenu, cmdScript,
               "background-color: #22577a");
}

void MainWindow::on_DesinstallationHeficienceMenu_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/uninstall_heficience-menu.sh ; sleep 3 ; bash ./uninstall_heficience-menu.sh ; sleep 3 ; rm ./uninstall_heficience-menu.sh sleep 3\"";
#elif _WIN32
    cmdScript = "Start PowerShell \
                \"Write-Output \'Désinstallation du logiciel\'; \
                Start-Sleep -s 2 ; \
                Get-Package -Name \'Heficience Menu\' | Uninstall-Package ; \
                Write-Output \'Désinstallation effectuée\' ; \
                Start-Sleep -s 5; \" ";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->DesinstallationHeficienceMenu, *ui->InstallationHeficienceMenu, cmdScript,
               "background-color: #22577a");
}
void MainWindow::on_InstallationAutocompletion_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/install_autocompletion.sh ; sleep 3 ; bash ./install_autocompletion.sh ; sleep 3 ; rm ./install_autocompletion.sh ; sleep 3\"";
#elif _WIN32
    cmdScript = "Start PowerShell \
                \"Write-Output \'Récupération de la dernière version du logiciel\'; \
                Start-Sleep -s 5 ; \
                Invoke-WebRequest \
                -Uri 'https://github.com/Heficience/autocompletion/releases/download/0.1.0-dev.1/autocompletion_windows.exe' \
                -OutFile '.\\autocompletion_windows.exe' ; \
                Write-Output \'Installation de la dernière version du logiciel\'; \
                Start-Sleep -s 5 ; \
                Start-Process autocompletion_windows.exe \" ";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->InstallationAutocompletion, *ui->DesinstallationAutocompletion, cmdScript,
               "background-color: #38a3a5; color: #000");
}

void MainWindow::on_DesinstallationAutocompletion_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e bash -c \"wget https://github.com/Heficience/heficience-scripts/raw/main/linux/uninstall_autocompletion.sh ; sleep 3 ; bash ./uninstall_autocompletion.sh ; sleep 3 ; rm ./uninstall_autocompletion.sh ; rm -rf $HOME/.autocompletion ; sleep 3\"";
#elif _WIN32
    cmdScript = "Start PowerShell \
                \"Write-Output \'Désinstallation du logiciel\'; \
                Start-Sleep -s 5 ; \
                cmd /c 'del /f autocompletion_windows.exe' ; \
                Write-Output \'Désinstallation effectuée\'; \
                Start-Sleep -s 5;\"";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->DesinstallationAutocompletion, *ui->InstallationAutocompletion, cmdScript,
               "background-color: #38a3a5; color: #000");
}

void MainWindow::on_OuvrirDooSearch_clicked()
{
    QString link = "https://heficience.search.paulluxwaffle.synology.me";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_InstallationNoComprendo_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e sudo bash -c \"wget https://github.com/Heficience/HSuperMenu/raw/main/nocomprendo-without-qt-default.deb ; apt update ; apt install ./nocomprendo-without-qt-default.deb ; rm nocomprendo-without-qt-default.deb ; sleep 3\"";
#elif _WIN32
    cmdScript = "";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->InstallationNoComprendo, *ui->DesinstallationNoComprendo, cmdScript,
               "background-color: #80ed99; color: #000");
}

void MainWindow::on_DesinstallationNoComprendo_clicked()
{
#ifdef __linux__
    cmdScript = "x-terminal-emulator --nofork -e sudo bash -c \"apt update ; apt remove nocomprendo ; sleep 3 \"";
#elif _WIN32
    cmdScript = "";
#elif __APPLE__
    cmdScript = "";
#endif
    installApp(*ui->DesinstallationNoComprendo, *ui->InstallationNoComprendo, cmdScript,
               "background-color: #80ed99; color: #000");
}

void MainWindow::on_OuvrirSiteWeb_clicked() {
    QString link = "https://www.heficience.com/index.php";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::installApp(QPushButton &Install, QPushButton &Desintall, QString cmdSCriptUnique, QString Style) {
    Install.setEnabled(false);
    Install.setStyleSheet("background-color: #aaa");
#ifdef __linux__
    LaunchSystemApp->execute(cmdSCriptUnique);
#elif _WIN32
    std::system(cmdSCriptUnique.toLocal8Bit().data());
#elif __APPLE__
    LaunchSystemApp->execute(cmdSCriptUnique);
#endif
    Desintall.setEnabled(true);
    Desintall.setStyleSheet(Style);
}