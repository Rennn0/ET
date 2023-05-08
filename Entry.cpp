#include"Entry.h"
#include"qeventloop.h"
#include"qtimer.h"

Entry::Entry(QWidget* parent) :
    QDialog(parent), entryUi(new Ui::Entry)
{
    entryUi->setupUi(this);
    setWindowIcon(QIcon("main.ico"));
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
    ///////////////
    connect(entryUi->name, &QLineEdit::textChanged, this, &Entry::textRequired);
    connect(entryUi->password, &QLineEdit::textChanged, this, &Entry::textRequired);
    connect(entryUi->submit, &QPushButton::clicked, this, &Entry::onSubmit);
}

Entry::~Entry() { delete this->entryUi; }

void Entry::onSubmit() {
    QString password = entryUi->password->text();
    if (1) { // change to et2023
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

void Entry::textRequired(const QString& text) {
    bool N = !entryUi->name->text().isEmpty();
    bool LN = !entryUi->lastname->text().isEmpty();
    bool P = !entryUi->password->text().isEmpty();
    entryUi->submit->setEnabled(N && LN &&P);
}

void Entry::openInstruction() {
    QString file = QCoreApplication::applicationDirPath() + "/README.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file));
}