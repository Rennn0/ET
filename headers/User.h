#include <QDesktopServices>
#include <QIntValidator>
#include <QFileDialog>
#include <QPainter>
#include"core.h"
#include"ui_User.h"


class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget* parent = nullptr);
    ~User();

private:
    Ui::User* userUi;
    QString fileName{}, folder{}, fileLocation{}, genLocation{}, resultName{};
    int totalExams, studentLimit;
    QIntValidator* validator=new QIntValidator(1,INT_MAX,this);
    bool isLoading = false;


private slots:
    void dataGeneratorProcess();
    void createProcess();
    void openStats();
    void openTxt();
    void openPC();
};

