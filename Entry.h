#pragma once
#ifndef ENTRY
#define ENTRY
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QMessageBox>
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


#endif // !ENTRY