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
    Core* core=nullptr;
    Ui::User* userUi;
    QString fileName{}, folder{}, fileLocation{}, genLocation{}, resultName{};
    uint16_t totalExams, studentLimit;
    QIntValidator* validator=new QIntValidator(1,INT_MAX,this);

private slots:
    void dataGeneratorProcess();
    void createProcess();
    void openStats();
    void openTxt();
    void openPC();
    void openResults();
    void openIDMap();
    void saveResult();
    void saveIDMap();
};

