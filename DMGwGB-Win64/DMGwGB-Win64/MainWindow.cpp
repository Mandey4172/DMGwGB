#include "MainWindow.h"

#include <QGlobal.h>
#include <Qfile.h>
#include <QFileDialog.h>
#include <QMessageBox.h>
#include <QTime>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

#include <limits>

#include "QGLRender.h"
#include "QNewDialog.h"
#include "CalculationsThread.h"
#include "CellularAutomataSpace.h"
#include "MooreNeighborhood.h"
#include "HexagonalNeighborhood.h"
#include "PentagonalNeighborhood.h"
#include "VonNeummanNeighborhood.h"
#include "NucleonGenerator.h"
#include "GrainGrowthWithBoundaryCellularAutomata.h"

#include <omp.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //this->calculationsThread = new CalculationsThread();

    setWindowTitle("DMGwGB");
    this->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

    createMenuBar();
    createSimulationMenu();
    createOpenGLDisplay();

    QWidget *mainWidget = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->setMenuBar(menuB);
    mainLayout->addWidget(simulationMenuGroupBox, 0, 0, 3, 2);
    mainLayout->addWidget(openGLDisplay, 0, 2, 10, 10);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainWidget->setLayout(mainLayout);
	
	QRect monitor = QApplication::desktop()->screenGeometry();

	setCentralWidget(mainWidget);
	setMinimumSize(640, 480);

	if(monitor.width() > 1000 && monitor.height() > 900) resize(1000, 900);
	else resize(monitor.width(), monitor.height());

    connect(&calculationsThread, &CalculationsThread::updateVal, this, &MainWindow::updateRender);
	connect(&calculationsThread, &CalculationsThread::updateDeb, this, &MainWindow::updateDebug);

	show();
}

MainWindow::~MainWindow()
{
	if (calculationsThread.isRunning())
	{
		calculationsThread.terminate();
		calculationsThread.wait();
	}
	//delete this->calculationsThread;
}

void MainWindow::createMenuBar()
{
    //Create menus
    menuB = new QMenuBar();
    fileMenu = menuB->addMenu(tr("&File"));

    newAction = fileMenu->addAction(tr("N&ew"));
	loadAction = fileMenu->addAction(tr("L&oad"));
	saveAction = fileMenu->addAction(tr("S&ave"));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuB->addMenu(fileMenu);

    //Connect actions
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
	connect(loadAction, &QAction::triggered, this, &MainWindow::loadFile);
	connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(newAction, &QAction::triggered, this, &MainWindow::newSimulation);
}
 
void MainWindow::createSimulationMenu()
{
    simulationMenuGroupBox = new QGroupBox(tr(" Simulation Menu "));
    QGridLayout *layout = new QGridLayout();

    nucleationLabel = new QLabel(tr("Nucleons: "));
    nucleationLabel->setMaximumHeight(50);
    nucleationNumberSpinBox = new QSpinBox();
    nucleationNumberSpinBox->setRange(0, std::numeric_limits<int>::max());
    nucleationNumberSpinBox->setValue(10);

	statesCountLabel = new QLabel(tr("Grain Count: "));
	statesCountLabel->setMaximumHeight(50);
	statesCountNumberSpinBox = new QSpinBox();
	statesCountNumberSpinBox->setRange(0, std::numeric_limits<int>::max());
	statesCountNumberSpinBox->setValue(10);
    
	nucleationTypeLabel = new QLabel(tr("Nucelation type: "));
	nucleationTypeComboBox = new QComboBox;
	nucleationTypeComboBox->setFixedWidth(100);
	nucleationTypeComboBox->setMaximumWidth(200);
	nucleationTypeComboBox->addItem(" Random ");
	nucleationTypeComboBox->addItem(" Random with minimum radius ");
	nucleationTypeComboBox->addItem(" Regular ");
	connect(nucleationTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(nucleonGenerationTypeChanged(int)));

	nucleationOptionLabel1 = new QLabel(tr("Option 1"));
	nucleationOptionTextBox1 = new QSpinBox;
	nucleationOptionLabel2 = new QLabel(tr("Option 2"));
	nucleationOptionTextBox2 = new QSpinBox;
	nucleationOptionLabel3 = new QLabel(tr("Option 3"));
	nucleationOptionTextBox3 = new QSpinBox;
	nucleationOptionLabel4 = new QLabel(tr("Option 4"));
	nucleationOptionTextBox4 = new QComboBox;
	nucleationOptionTextBox4->addItem(" 0 ");
	nucleationOptionTextBox4->addItem(" 1");
	nucleationOptionTextBox4->addItem(" 2 ");
	nucleationOptionTextBox4->addItem(" 3 ");
	nucleationOptionTextBox4->addItem(" 4 ");
	nucleationOptionTextBox4->addItem(" 5 ");

	nucleationOptionLabel1->hide();
	nucleationOptionLabel2->hide();
	nucleationOptionLabel3->hide();
	nucleationOptionLabel4->hide();
	nucleationOptionTextBox1->hide();
	nucleationOptionTextBox2->hide();
	nucleationOptionTextBox3->hide();
	nucleationOptionTextBox4->hide();

	nucleationGenerateButton = new QPushButton(tr(" Generate "));
    connect(nucleationGenerateButton, SIGNAL(released()), this, SLOT(generateNucleons()));
    //nubcleonsGenerateButton->setGeometry(QRect(QPoint(0, 0),QSize(200, 50)));

	boundaryConditionsLabel = new QLabel(tr("Boundary Conditions:"));
	boundaryConditionsComboBox = new QComboBox;
	boundaryConditionsComboBox->addItem(" Blocking ");
	boundaryConditionsComboBox->addItem(" Periodic ");
	boundaryConditionsComboBox->addItem(" Reflectiong ");

    neightborhoodLabel = new QLabel(tr(" Neightborhood type: "));
    neightborhoodLabel->setMaximumHeight(50);
    neightborhoodComboBox = new QComboBox;
    neightborhoodComboBox->addItem(" Moore ");
	neightborhoodComboBox->addItem(" VonNeumman ");
	neightborhoodComboBox->addItem(" Pentagonal ");
	neightborhoodComboBox->addItem(" Hexagonal ");

	neightborhoodRadiusLabel = new QLabel(tr(" Neightborhood radius "));
	neightborhoodRadiusSpinBox = new QSpinBox;
	neightborhoodRadiusSpinBox->setMinimum(1);

	boundaryNeightborhoodLabel = new QLabel(tr(" Boundary neightborhood type: "));
	boundaryNeightborhoodLabel->setMaximumHeight(50);
	boundaryNeightborhoodComboBox = new QComboBox;
	boundaryNeightborhoodComboBox->addItem(" Moore ");
	boundaryNeightborhoodComboBox->addItem(" VonNeumman ");
	boundaryNeightborhoodComboBox->addItem(" Pentagonal ");
	boundaryNeightborhoodComboBox->addItem(" Hexagonal ");

	grainBoundarySizeLabel = new QLabel(tr(" Grain boundary size: "));
	grainBoundarySizeTextBox = new QSpinBox;
	grainBoundarySizeTextBox->setMinimum(1);

    simulationStartButton = new QPushButton(tr(" Start "));
    connect(simulationStartButton, SIGNAL(released()), this, SLOT(startSimulation()));

	debugLabel = new QLabel(tr("DEBUG "));
	debugLabel->setMaximumHeight(50);

    layout->addWidget(nucleationLabel, 0, 0, 1, 2);
    layout->addWidget(nucleationNumberSpinBox, 0, 2, 1, 2);

	layout->addWidget(statesCountLabel, 1, 0, 1, 2);
	layout->addWidget(statesCountNumberSpinBox, 1, 2, 1, 2);\

	layout->addWidget(nucleationTypeLabel, 2, 0, 1, 2);
	layout->addWidget(nucleationTypeComboBox, 2, 2, 1, 2);

	layout->addWidget(nucleationOptionLabel1, 3, 0, 1, 2);
	layout->addWidget(nucleationOptionTextBox1, 3, 2, 1, 2);
	layout->addWidget(nucleationOptionLabel2, 4, 0, 1, 2);
	layout->addWidget(nucleationOptionTextBox2, 4, 2, 1, 2);
	layout->addWidget(nucleationOptionLabel3, 5, 0, 1, 2);
	layout->addWidget(nucleationOptionTextBox3, 5, 2, 1, 2);
	layout->addWidget(nucleationOptionLabel4, 6, 0, 1, 2);
	layout->addWidget(nucleationOptionTextBox4, 6, 2, 1, 2);

    layout->addWidget(nucleationGenerateButton, 7, 0, 1, 4);
	
	layout->addWidget(boundaryConditionsLabel, 8, 0, 1, 4);
	layout->addWidget(boundaryConditionsComboBox, 9, 0, 1, 4);

    layout->addWidget(neightborhoodLabel, 10, 0, 1, 4);
    layout->addWidget(neightborhoodComboBox, 11, 0, 1, 4);

	layout->addWidget(neightborhoodRadiusLabel, 12, 0, 1, 4);
	layout->addWidget(neightborhoodRadiusSpinBox, 13, 0, 1, 4);

	layout->addWidget(boundaryNeightborhoodLabel, 14, 0, 1, 4);
	layout->addWidget(boundaryNeightborhoodComboBox, 15, 0, 1, 4);

	layout->addWidget(grainBoundarySizeLabel, 16, 0, 1, 4);
	layout->addWidget(grainBoundarySizeTextBox, 17, 0, 1, 4);

    layout->addWidget(simulationStartButton, 18, 0, 1, 4);

	layout->addWidget(debugLabel, 19, 0, 1, 4);

 //   layout->setRowMinimumHeight(0, 20);
 //   layout->setRowMinimumHeight(1, 20);
 //   layout->setRowMinimumHeight(2, 20);
 //   layout->setRowMinimumHeight(3, 20);
 //   layout->setRowMinimumHeight(4, 20);
 //   layout->setRowMinimumHeight(5, 20);
	//layout->setRowMinimumHeight(6, 20);
	//layout->setRowMinimumHeight(7, 20);
	//layout->setRowMinimumHeight(8, 20);
	//layout->setRowMinimumHeight(9, 20);
	//layout->setRowMinimumHeight(10, 20);

	layout->setColumnMinimumWidth(0, 10);
	layout->setColumnMinimumWidth(1, 10);
	layout->setColumnMinimumWidth(2, 10);
	layout->setColumnMinimumWidth(3, 10);

    layout->setHorizontalSpacing(10);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    /*layout->setRowStretch(0, 10);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setRowStretch(4, 1);
    layout->setRowStretch(5, 1);*/

    simulationMenuGroupBox->setLayout(layout);
	nucleationTypeComboBox->setCurrentIndex(0);
}

void MainWindow::createOpenGLDisplay()
{
    openGLDisplay = new QGLRender();
    this->openGLDisplay->setCA(calculationsThread.simulation->cellularautomata);
    openGLDisplay->setGeometry(0,0,100, 100);
	//openGLDisplay->show();
}

void MainWindow::startSimulation()
{
	unsigned int negihtborhoodRadius = static_cast<unsigned int>(neightborhoodRadiusSpinBox->value());
	unsigned int grainSize = static_cast<unsigned int>(grainBoundarySizeTextBox->value());
	
	this->calculationsThread.simulation->neighborhood->setRadius(negihtborhoodRadius);
	
	GrainGrowthWithBoundaryCellularAutomata * simulation = dynamic_cast<GrainGrowthWithBoundaryCellularAutomata *>(this->calculationsThread.simulation);
	if (simulation) simulation->grainSize = grainSize;

	if (calculationsThread.simulation->neighborhood) delete calculationsThread.simulation->neighborhood;
	if (neightborhoodComboBox->itemText(neightborhoodComboBox->currentIndex()) == " VonNeumman ")
	{
		calculationsThread.simulation->neighborhood = new VonNeummanNeighborhood();
	}
	else if (neightborhoodComboBox->itemText(neightborhoodComboBox->currentIndex()) == " Pentagonal ")
	{
		calculationsThread.simulation->neighborhood = new PentagonalNeighborhood();
	}
	else if (neightborhoodComboBox->itemText(neightborhoodComboBox->currentIndex()) == " Hexagonal ")
	{
		calculationsThread.simulation->neighborhood = new HexagonalNeighborhood();
	}
	else
	{
		calculationsThread.simulation->neighborhood = new MooreNeighborhood();
	}

	if (simulation)
	{
		delete simulation->boundary_neighborhood;
		if (boundaryNeightborhoodComboBox->itemText(boundaryNeightborhoodComboBox->currentIndex()) == " VonNeumman ")
		{
			simulation->boundary_neighborhood = new VonNeummanNeighborhood();
		}
		else if (boundaryNeightborhoodComboBox->itemText(boundaryNeightborhoodComboBox->currentIndex()) == " Pentagonal ")
		{
			simulation->boundary_neighborhood = new PentagonalNeighborhood();
		}
		else if (boundaryNeightborhoodComboBox->itemText(boundaryNeightborhoodComboBox->currentIndex()) == " Hexagonal ")
		{
			simulation->boundary_neighborhood = new HexagonalNeighborhood();
		}
		else
		{
			simulation->boundary_neighborhood = new MooreNeighborhood();
		}
	}
	

	if (boundaryConditionsComboBox->itemText(boundaryConditionsComboBox->currentIndex()) == " Blocking ")
	{
		calculationsThread.simulation->cellularautomata->setBoundaryContidion(BoundaryContidionTypes::Blocking);
	}
	else if (boundaryConditionsComboBox->itemText(boundaryConditionsComboBox->currentIndex()) == " Periodic ")
	{
		calculationsThread.simulation->cellularautomata->setBoundaryContidion(BoundaryContidionTypes::Periodic);
	}
	else if (boundaryConditionsComboBox->itemText(boundaryConditionsComboBox->currentIndex()) == " Reflectiong ")
	{
		calculationsThread.simulation->cellularautomata->setBoundaryContidion(BoundaryContidionTypes::Reflecting);
	}



    connect(&calculationsThread, &CalculationsThread::updateVal, this, &MainWindow::updateRender);
    calculationsThread.start();
}

void MainWindow::generateNucleons()
{
    if (!calculationsThread.isRunning())
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
		NucleonGenerator generator;
        CellularAutomataSpace * ca = this->calculationsThread.simulation->cellularautomata;
		if ( nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Random " )
		{
			generator.random(ca,
				static_cast<unsigned int>(this->nucleationNumberSpinBox->value()),
				static_cast<unsigned int>(this->statesCountNumberSpinBox->value()));
		}
		else if (nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Random with minimum radius " )
		{
			generator.random(ca, 
				static_cast<unsigned int>(this->nucleationNumberSpinBox->value()),
				static_cast<unsigned int>(this->statesCountNumberSpinBox->value()),
				static_cast<unsigned int>(this->nucleationOptionTextBox1->value()) );
		}
		else if (nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Regular ")
		{
			generator.regular(ca,
				static_cast<unsigned int>(this->nucleationOptionTextBox1->value()),
				static_cast<unsigned int>(this->nucleationOptionTextBox2->value()),
				static_cast<unsigned int>(this->nucleationOptionTextBox3->value()),
				static_cast<unsigned int>(this->statesCountNumberSpinBox->value()));
		}
		else if (nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " GradientA ")
		{

		}
        this->openGLDisplay->setCA(new CellularAutomataSpace(*ca));
    }

}

void MainWindow::updateRender()
{
    this->openGLDisplay->setCA(new CellularAutomataSpace(*calculationsThread.simulation->cellularautomata));
}

void MainWindow::updateDebug(const QString text)
{
	this->debugLabel->setText(text);
}

void MainWindow::nucleonGenerationTypeChanged(const int & index)
{
	nucleationTypeComboBox->setCurrentIndex(index);
	if ( nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Random ")
	{
		nucleationNumberSpinBox->show();
		nucleationOptionLabel1->hide();
		nucleationOptionLabel2->hide();
		nucleationOptionLabel3->hide();
		nucleationOptionLabel4->hide();
		nucleationOptionTextBox1->hide();
		nucleationOptionTextBox2->hide();
		nucleationOptionTextBox3->hide();
		nucleationOptionTextBox4->hide();
	}
	else if ( nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Random with minimum radius ")
	{
		nucleationNumberSpinBox->show();
		nucleationOptionLabel1->show();
		nucleationOptionLabel2->hide();
		nucleationOptionLabel3->hide();
		nucleationOptionLabel4->hide();
		nucleationOptionTextBox1->show();
		nucleationOptionTextBox2->hide();
		nucleationOptionTextBox3->hide();
		nucleationOptionTextBox4->hide();

		nucleationOptionLabel1->setText(" Radius : ");
	}
	else if ( nucleationTypeComboBox->itemText(nucleationTypeComboBox->currentIndex()) == " Regular ")
	{
		nucleationNumberSpinBox->hide();
		nucleationOptionLabel1->show();
		nucleationOptionLabel2->show();
		nucleationOptionLabel3->show();
		nucleationOptionLabel4->hide();
		nucleationOptionTextBox1->show();
		nucleationOptionTextBox2->show();
		nucleationOptionTextBox3->show();
		nucleationOptionTextBox4->hide();
		
		nucleationOptionLabel1->setText(" Count on X axis: ");
		nucleationOptionLabel2->setText(" Count on Y axis: ");
		nucleationOptionLabel3->setText(" Count on Z axis: ");
	}
}

void MainWindow::loadFile()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Save Microstructure"), "File.txt",
		tr("TextFile (*.txt);;All Files (*)"));

	if (fileName.isEmpty())
		return;
	else
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			QMessageBox::information(this, tr("Unable to open file"),
				file.errorString());
			return;
		}
		QString data = file.readAll();
		this->calculationsThread.simulation->cellularautomata->load(data.toStdString());
		file.close();
		this->openGLDisplay->setCA(this->calculationsThread.simulation->cellularautomata);
	}
}

void MainWindow::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Microstructure"), "File.txt",
		tr("TextFile (*.txt);;All Files (*)"));
	if (fileName.isEmpty())
		return;
	else {
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly)) {
			QMessageBox::information(this, tr("Unable to open file"),
				file.errorString());
			return;
		}
		QTextStream saveText(&file);
		saveText << QString::fromStdString(this->calculationsThread.simulation->cellularautomata->save());
		file.close();
	}
}

void MainWindow::newSimulation()
{
	QNewDialog * newDialog = new QNewDialog(this);
    if (newDialog->exec())
    {
        int x, y, z;
		delete calculationsThread.simulation->cellularautomata;
        newDialog->getValues(x, y, z);
        this->openGLDisplay->setCA(new CellularAutomataSpace(x, y, z));
        calculationsThread.simulation->cellularautomata = new CellularAutomataSpace(x, y, z);
    }
    delete newDialog;
}


