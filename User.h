#pragma once
#include<QMainWindow>
#include<QIcon>
#include<qdialog.h>
#include"ui_User.h"

class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget* parent = nullptr);
    ~User();

private:
    Ui::User* userUi;

private slots:
    void dataGeneratorProcess();
};