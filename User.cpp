#include"User.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QDir>
    User::User(QWidget* parent)
        : QMainWindow(parent), userUi(new Ui::User)
    {
        userUi->setupUi(this);
        setAttribute(Qt::WA_DeleteOnClose);
        setWindowIcon(QIcon("main.ico"));


        connect(userUi->dataGenerator, SIGNAL(clicked()), this, SLOT(dataGeneratorProcess()));
    }

User::~User()
{
    delete this->userUi;
}

void User::dataGeneratorProcess() {
    QProcess* process = new QProcess(this);
    QString program = "process/data_generator.exe"; // exea shesacvleli, arasworad agdebs folderebs
    QStringList args;
    args << "data/raw_small.csv" << "tested";

    process->start(program, args);
}