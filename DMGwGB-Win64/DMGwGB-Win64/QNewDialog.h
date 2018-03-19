#pragma once

#ifndef QNEWDIALOG_H
#define QNEWDIALOG_H
#include <QDialog>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel.h>
#include <QtWidgets/QPushButton.h>
#include <QtWidgets/QGroupBox.h>
#include <QtWidgets/QSpinBox.h>

class QNewDialog : public QDialog
{
	Q_OBJECT
public:
	QNewDialog(QWidget *parent = Q_NULLPTR);
	~QNewDialog();
	
	void getValues(int &x, int &y, int &z);

private:
	void createDialog();
	void createBottom();

	QGroupBox * newGroupBox;

	QLabel * xLabel;
	QLabel * yLabel;
	QLabel * zLabel;

	QSpinBox * xNumberSpinBox;
	QSpinBox * yNumberSpinBox;
	QSpinBox * zNumberSpinBox;

	QPushButton * acceptButton;
	QPushButton * cancelButton;

private slots:
	void acceptButtoClick();
	void cancelButtoClick();

};

#endif //QNEWDIALOG_H
