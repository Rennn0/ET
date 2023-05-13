#include"../headers/Entry.h"

Entry::Entry(QWidget* parent) :
    QDialog(parent), entryUi(new Ui::Entry)
{
    entryUi->setupUi(this);
    setWindowIcon(QIcon("MAIN"));
    entryUi->password->setEchoMode(QLineEdit::Password);

    QMenuBar* menu = new QMenuBar(this);
    QMenu* first = menu->addMenu("...");
    QAction* instruction = new QAction("Instruction", this);
    connect(instruction, &QAction::triggered, this, &Entry::openInstruction);
    first->addAction(instruction);
    QAction* exit = new QAction("Exit", this);
    connect(exit, &QAction::triggered, this, &Entry::close);
    first->addAction(exit);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMenuBar(menu);
    layout->addLayout(this->layout());
    this->setLayout(layout);
    
    connect(entryUi->submit, &QPushButton::clicked, this, &Entry::onSubmit);
}

Entry::~Entry() { delete this->entryUi; }

void Entry::onSubmit() {
    QString password = entryUi->password->text();
    if (password=="et2023") { 
        QString name = entryUi->name->text();
        QString lastname = entryUi->lastname->text();
        User* user = new User(nullptr);
        user->setWindowTitle(name + " " + lastname);

        QTimer::singleShot(0, [this, user]() {
            user->showMaximized();
            this->close();
            });
    }
    else
        QMessageBox::critical(this, "Error", "Incorrect Password!");
}

void Entry::openInstruction() {
    QString file = QCoreApplication::applicationDirPath() + "/README.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}