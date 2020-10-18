#include "Windows.h"
#include "stdio.h"
#include "wincrypt.h"
#include "iostream"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}
QString name;
QString file;
HCRYPTPROV hProv;
HCRYPTKEY hSessionKey;
DWORD     *pdwDataLen;
BYTE      *pbData;
HCRYPTKEY hPubKey;

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_OpenButton_clicked()
{
    ui->Text->clear();
    file = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    name = file.right(file.size()-file.lastIndexOf("/")-1);
    ui->Text->append(name);

    QFile f(file);
    QString textStr;
    if(f.open(QIODevice::ReadOnly)){
    textStr = f.readAll();
    f.close();
    }




    std::string s = textStr.toStdString();
    int n = s.length();
    char string[n + 1];
    strcpy(string, s.c_str());

    DWORD count = strlen(string);

    if (!CryptAcquireContext(&hProv, NULL, NULL,PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
    return;
    }
    hSessionKey = name.toUInt();
    //if(CryptImportKey(hProv,pbData,pdwDataLen,0,0,&hPubKey))
    //{}

    if (!CryptDecrypt(hSessionKey, 0, true, 0, (BYTE*)string, &count))
    {
    return;
    }
    ui->Text->append(string);
}

void MainWindow::on_pushButton_clicked()
{


    QString str=ui->Text->toPlainText();

    std::string s = str.toStdString();
    int n = s.length();
    char string[n + 1];
    strcpy(string, s.c_str());

    DWORD count = strlen(string);

    // Получение контекста криптопровайдера
    if (!CryptAcquireContext(&hProv, NULL, NULL,PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
    return;
    }

    // Генерация сессионного ключа
    if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey))
    {
    return;
    }

    if (!CryptEncrypt(hSessionKey, 0, true, 0,(BYTE*)string, &count, strlen(string)))
    {
    return;
    }
    unsigned long int NAME = hSessionKey;
    QString strName = QString::number(NAME);
    QString Text = QString(QByteArray(string, 255));
    QFile f(file);
    if (f.open(QIODevice::WriteOnly))
    {
        f.write(Text.toUtf8());
        f.rename(strName);
        f.close();
    }
    //if(CryptExportKey(hSessionKey,NULL,0,0,NULL,&pdwDataLen)){
    //    return;
    //}
}
