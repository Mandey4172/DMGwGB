#include "QNewDialog.h"

#include <QtWidgets/QGridLayout.h>

QNewDialog::QNewDialog(QWidget *parent)
	:QDialog(parent)
{
	setWindowTitle("New");
	setMinimumSize(250, 150);
	resize(250, 150);

	createDialog();
	createDialog();

	QWidget *mainWidget = new QWidget();
	QGridLayout *mainLayout = new QGridLayout();

	acceptButton = new QPushButton(tr("Accept"));
	connect(acceptButton, SIGNAL(released()), this, SLOT(acceptButtoClick()));
	cancelButton = new QPushButton(tr("Cancel"));
	connect(cancelButton, SIGNAL(released()), this, SLOT(cancelButtoClick()));

	mainLayout->addWidget(newGroupBox, 0, 0, 1, 2);
	mainLayout->addWidget(acceptButton, 1, 0);
	mainLayout->addWidget(cancelButton, 1, 1);
	
	//setCentralWidget(mainWidget);
	this->setLayout(mainLayout);
}


QNewDialog::~QNewDialog()
{
	delete xLabel;
	delete yLabel;
	delete zLabel;

	delete xNumberSpinBox;
	delete yNumberSpinBox;
	delete zNumberSpinBox;

	delete acceptButton;
	delete cancelButton;
}

void QNewDialog::getValues(int & x, int & y, int & z)
{
	x = this->xNumberSpinBox->value();
	y = this->yNumberSpinBox->value();
	z = this->zNumberSpinBox->value();
}

void QNewDialog::createDialog()
{
	int beginValue = 10;

	newGroupBox = new QGroupBox(tr(" Options "));
	QGridLayout *layout = new QGridLayout();

	xLabel = new QLabel("x :");
	yLabel = new QLabel("y :");
	zLabel = new QLabel("z :");

	xNumberSpinBox = new QSpinBox();
	xNumberSpinBox->setRange(1, 10000);
	xNumberSpinBox->setValue(beginValue);

	yNumberSpinBox = new QSpinBox();
	yNumberSpinBox->setRange(1, 10000);
	yNumberSpinBox->setValue(beginValue);

	zNumberSpinBox = new QSpinBox();
	zNumberSpinBox->setRange(1, 10000);
	zNumberSpinBox->setValue(beginValue);

	layout->addWidget(xLabel, 0, 0, 1, 2);
	layout->addWidget(yLabel, 1, 0, 1, 2);
	layout->addWidget(zLabel, 2, 0, 1, 2);

	layout->addWidget(xNumberSpinBox, 0, 2);
	layout->addWidget(yNumberSpinBox, 1, 2);
	layout->addWidget(zNumberSpinBox, 2, 2);

	layout->setHorizontalSpacing(10);

	newGroupBox->setLayout(layout);
}

void QNewDialog::createBottom()
{
	
}

void QNewDialog::acceptButtoClick()
{
	this->accept();
}

void QNewDialog::cancelButtoClick()
{
	this->reject();
}