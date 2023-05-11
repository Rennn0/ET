#include"../headers/User.h"
#include<QProgressBar>
#include<QTimer>


User::User(QWidget* parent)
    : QMainWindow(parent), userUi(new Ui::User),totalExams(0),studentLimit(2400)
{
    userUi->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":/MAIN/main.ico"));
    
    userUi->openStats->setEnabled(false);
    userUi->openTxt->setEnabled(false);
    userUi->genLocation->setEnabled(false); // CONST
    userUi->totalExams->setEnabled(false);  // CONST
    userUi->studentLimit->setEnabled(false);
    userUi->outputName->setEnabled(false);
    userUi->createButton->setEnabled(false);
    userUi->openIDMap->setEnabled(false);
    userUi->openResult->setEnabled(false);
    userUi->saveIDMap->setEnabled(false);
    userUi->saveResult->setEnabled(false);

    userUi->studentLimit->setText(QString::number(studentLimit));
    userUi->totalExams->setText(QString::number(totalExams));

    connect(userUi->dataGenerator, SIGNAL(clicked()), this, SLOT(dataGeneratorProcess()));
    connect(userUi->openStats, SIGNAL(clicked()), this, SLOT(openStats()));
    connect(userUi->openTxt, SIGNAL(clicked()), this, SLOT(openTxt()));
    connect(userUi->createButton, SIGNAL(clicked()), this, SLOT(createProcess()));
    connect(userUi->PC, SIGNAL(clicked()), this, SLOT(openPC()));

}

User::~User()
{
    delete this->userUi;
    delete this->validator;

}


void User::dataGeneratorProcess() {
    if (userUi->fileLoc->text() == "")return;

    static int suffix = 1;
    if (userUi->fileName->text() == "") {
        QString sample = "Sample" + QString::number(suffix++);
        fileName = sample;
    }
    else
    fileName = userUi->fileName->text();
    
    folder = QFileInfo(fileLocation).absolutePath();
    genLocation = folder+ "/OUTPUT/" + fileName + ".txt";
   
    userUi->dataGenerator->setEnabled(false);
    userUi->PC->setEnabled(false);
    
    try
    {
        totalExams = Core::generate(fileLocation.toStdString(), folder.toStdString(), fileName.toStdString());
    }
    catch (const ET::format_error&) {
        userUi->generatedLocation->setText("Ivalid Data Format!");
        userUi->generatedExamStats->setText("------------------");
        userUi->dataGenerator->setEnabled(true);
        userUi->PC->setEnabled(true);
        return;
    }

    userUi->generatedLocation->setText(genLocation);
    userUi->genLocation->setText(fileName+".txt");
    userUi->generatedExamStats->setText(folder+"/OUTPUT/" + fileName + "Stats.txt");
    userUi->totalExams->setText(QString::number(totalExams));

    userUi->dataGenerator->setEnabled(true);
    userUi->PC->setEnabled(true);    

    userUi->studentLimit->setValidator(validator);
    userUi->openStats->setEnabled(true);
    userUi->openTxt->setEnabled(true);
    userUi->studentLimit->setEnabled(true);
    userUi->outputName->setEnabled(true);
    userUi->createButton->setEnabled(true);

}

void User::openStats() {
    QString file = folder + "/OUTPUT/" + fileName + "Stats.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}

void User::openTxt() {
    QString file = folder + "/OUTPUT/" + fileName + ".txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}

void User::openResults()
{
    QString file = folder + "/OUTPUT/RESULT/" + resultName + ".txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}

void User::openIDMap()
{
    QString file = folder + "/OUTPUT/RESULT/" + resultName + "IDMap.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}
void User::openPC() {
    fileLocation = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;CSV Files(*.csv);;All Files(*)"));
    userUi->fileLoc->setText(fileLocation);
}

void User::createProcess() {
    resultName = userUi->outputName->text();
    studentLimit=userUi->studentLimit->text().toUInt();
    
    core = new Core(genLocation.toStdString(), folder.toStdString(), resultName.toStdString(), studentLimit, totalExams);

    core->hashmap();
    try
    {
        core->check_limit();
    }
    catch (const ET::limit_error&)
    {
        userUi->resultIDMap->setText("Limit is Low");
        return;
    }

    core->sort_mtavari_exam();
    
    
}
