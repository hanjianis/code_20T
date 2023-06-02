#pragma once

#include <QDialog>
#include "ui_EditSubject.h"

class EditSubject : public QDialog
{
	Q_OBJECT

public:
	EditSubject(QString subjectid,QWidget *parent = Q_NULLPTR);
	~EditSubject();

private:
	Ui::EditSubject ui;
	QString m_subjectid ;

public slots:
	void on_ok_clicked();
	void on_cancel_clicked();
};
