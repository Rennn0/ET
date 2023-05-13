#include"../headers/User.h"
#include<QListWidget>
#include<QScrollArea>
#include<QToolTip>
User::User(QWidget* parent)
    : QMainWindow(parent), userUi(new Ui::User),totalExams(0),studentLimit(2400)
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
    userUi->openIDMap->setEnabled(false);
    userUi->openResult->setEnabled(false);
    userUi->saveIDMap->setEnabled(false);
    userUi->saveResult->setEnabled(false);
    userUi->displayBtn->setEnabled(false);

    userUi->studentLimit->setText(QString::number(studentLimit));
    userUi->totalExams->setText(QString::number(totalExams));

    userUi->treeSession->setColumnCount(1);
    userUi->treeSession->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    userUi->treeSession->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    userUi->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    userUi->listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    
    connect(userUi->dataGenerator, SIGNAL(clicked()), this, SLOT(dataGeneratorProcess()));
    connect(userUi->openStats, SIGNAL(clicked()), this, SLOT(openStats()));
    connect(userUi->openTxt, SIGNAL(clicked()), this, SLOT(openTxt()));
    connect(userUi->createButton, SIGNAL(clicked()), this, SLOT(createProcess()));
    connect(userUi->PC, SIGNAL(clicked()), this, SLOT(openPC()));
    connect(userUi->saveResult, SIGNAL(clicked()), this, SLOT(saveResult()));
    connect(userUi->saveIDMap, SIGNAL(clicked()), this, SLOT(saveIDMap()));
    connect(userUi->openIDMap, SIGNAL(clicked()), this, SLOT(openIDMap()));
    connect(userUi->openResult, SIGNAL(clicked()), this, SLOT(openResults()));
    connect(userUi->displayBtn, SIGNAL(clicked()), this, SLOT(display()));
    connect(userUi->treeSession, &QTreeWidget::itemClicked, this, &User::onItemClicked);
    connect(userUi->studentLimit, &QLineEdit::textChanged, this, &User::enableCreate);
    connect(userUi->outputName, &QLineEdit::textChanged, this, &User::enableCreate);
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

void User::saveResult()
{
    core->newDir();
    core->save_result();
    userUi->openResult->setEnabled(true);
    userUi->saveResult->setText("Saved");
    userUi->resultsLocation->setText("OUTPUT/RESULT/" + resultName + ".txt");
}

void User::saveIDMap()
{
    core->newDir();
    core->save_IDMap();
    userUi->openIDMap->setEnabled(true);
    userUi->saveIDMap->setText("Saved");
    userUi->resultIDMap->setText("OUTPUT/RESULT/" + resultName + "IDMap.txt");
}

void User::openPC() {
    fileLocation = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;CSV Files(*.csv);;All Files(*)"));
    userUi->fileLoc->setText(fileLocation);
}

void User::createProcess() {
    
    resultName = (userUi->outputName->text() == "" ? fileName : userUi->outputName->text());
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
    core->sesiebis_dalageba();

    userUi->resultsLocation->setText("Result ready");
    userUi->resultIDMap->setText("ID Map ready");
    userUi->saveIDMap->setText("Save");
    userUi->saveResult->setText("Save");
    
    userUi->saveIDMap->setEnabled(true);
    userUi->saveResult->setEnabled(true);

    userUi->displayBtn->setEnabled(true);
    userUi->createButton->setEnabled(false);
}

void User::display() {
    userUi->treeSession->clear();
    userUi->listWidget->clear();
    uint16_t sessionIndex = 0;
    for (const auto& sesia : core->sesiebi) {
        QTreeWidgetItem* sessionItem = new QTreeWidgetItem(userUi->treeSession);
        sessionItem->setText(0, QString("Session %1").arg(sessionIndex + 1));

        for (const auto& exams : sesia) {
            QTreeWidgetItem* examItem = new QTreeWidgetItem(sessionItem);
            examItem->setText(0, QString::fromStdString(exams->exam));
        }
        sessionIndex++;
    }
    studentMap = core->revertMap(&core->ID_map);
    userUi->searchID->setValidator(validator);
    userUi->displayBtn->setEnabled(false);
    connect(userUi->searchID, &QLineEdit::returnPressed, this, &User::searchByID);
    connect(userUi->searchStudent, &QLineEdit::returnPressed, this, &User::searchByStudent);
}

void User::onItemClicked(QTreeWidgetItem* item, int column)
{
    if (item->parent() != nullptr) {
        userUi->listWidget->clear();

        int sessionIndex = userUi->treeSession->indexOfTopLevelItem(item->parent());
        int examIndex = item->parent()->indexOfChild(item);

        const auto& exam = core->sesiebi[sessionIndex][examIndex];

        for (uint16_t& id : exam->studIDs) {
            QString studentInfo = QString::fromStdString(core->ID_map[id]);
            QListWidgetItem* student = new QListWidgetItem;
            student->setText(QString::number(id));
            student->setToolTip(studentInfo);
            userUi->listWidget->addItem(student);
        }
    }
}

void User::enableCreate()
{
    userUi->resultIDMap->setText("....");
    userUi->resultsLocation->setText("....");
    userUi->createButton->setEnabled(true);
}

void User::searchByID()
{
    uint16_t ID = userUi->searchID->text().toUInt();
    auto it = core->ID_map.find(ID);
    if(it!=core->ID_map.end())
    userUi->answerID->setText(QString::fromStdString(core->ID_map[ID]));
    else {
        QToolTip::showText(userUi->searchID->mapToGlobal(QPoint()), tr("ID not found"));
        userUi->answerID->clear();
    }
}

void User::searchByStudent()
{
    std::string student =" "+userUi->searchStudent->text().toStdString();
    auto it = this->studentMap.find(student);
    if(it!=this->studentMap.end())
    userUi->answerStudent->setText(QString::number(studentMap[student]));
    else {
        QToolTip::showText(userUi->searchStudent->mapToGlobal(QPoint()), tr("Student not found"));
        userUi->searchStudent->clear();
    }
}
