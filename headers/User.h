#pragma once
#include<QMainWindow>
#include<QIcon>
#include<QProcess>
#include<QDir>
#include<qdialog.h>
#include<iostream>
#include<fstream>
#include"ui_User.h"
#include"core.h"

class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget* parent = nullptr);
    ~User();

private:
    Ui::User* userUi;
    QString fileName,fileLocation;
    
private slots:

    void dataGeneratorProcess();
    void openStats();
    void openTxt();
};