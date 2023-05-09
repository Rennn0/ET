#include"../headers/User.h"

#include <QPushButton>
#include <QProgressDialog>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QFutureWatcher>
#include <QDesktopServices>
User::User(QWidget* parent)
    : QMainWindow(parent), userUi(new Ui::User)
{
    userUi->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon("MAIN"));

    userUi->openStats->setEnabled(false);
    userUi->openTxt->setEnabled(false);
    userUi->genLocation->setEnabled(false); // CONST
    userUi->totalExams->setEnabled(false);  // CONST
    userUi->studentLimit->setEnabled(false);
    userUi->outputName->setEnabled(false);
    userUi->createButton->setEnabled(false);

    connect(userUi->dataGenerator, SIGNAL(clicked()), this, SLOT(dataGeneratorProcess()));
    connect(userUi->openStats, SIGNAL(clicked()), this, SLOT(openStats()));
    connect(userUi->openTxt, SIGNAL(clicked()), this, SLOT(openTxt()));
}

User::~User()
{
    delete this->userUi;
}

void User::dataGeneratorProcess() {
    fileName = userUi->fileName->text(), fileLocation= userUi->fileLoc->text();
    int generateClicked = Core::generate(fileLocation.toStdString(), fileName.toStdString());

    if (generateClicked) {
        userUi->openStats->setEnabled(true);
        userUi->openTxt->setEnabled(true);
        userUi->studentLimit->setEnabled(true);
        userUi->outputName->setEnabled(true);
        userUi->createButton->setEnabled(true);

        userUi->generatedLocation->setText("OUTPUT/"+fileName+".txt");
        userUi->genLocation->setText("OUTPUT/" + fileName + ".txt");
        userUi->generatedExamN->setText("OUTPUT/" + fileName + "Stats.txt");
        userUi->totalExams->setText(QString::number(generateClicked));
    }
    else {
        userUi->generatedLocation->setText("Invalid Location!");
    }
}

void User::openStats() {
    QString file = "OUTPUT/"+fileName+"Stats.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}

void User::openTxt() {
    QString file = "OUTPUT/" + fileName + ".txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}