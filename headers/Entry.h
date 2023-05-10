#include <QTimer>
#include <QMessageBox>
#include <QDesktopServices>
#include <QBoxLayout>
#include <QMenuBar>
#include <QDialog>
#include"User.h"
#include"ui_Entry.h"
class Entry : public QDialog {
	Q_OBJECT;
public:
	explicit Entry(QWidget* parent = nullptr);
	~Entry();
private slots:
	void onSubmit();
	void textRequired(const QString& text);
	void openInstruction();
private:
	Ui::Entry* entryUi;
};
