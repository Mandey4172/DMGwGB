#include "MainWindow.h"

#include <QGlobal.h>
#include <QTime>
#include <limits>

#include "QGLRender.h"
#include "QNewDialog.h"
#include "CalculationsThread.h"
#include "CellularAutomata.h"


#include <omp.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	int x = omp_get_max_threads();

	int nthreads, tid;
	omp_set_num_threads(4);
	/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid) num_threads(4)
	{
		/* Obtain thread number */
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);

		/* Only master thread does this */
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

	}  /* All threads join master thread and disband */

    this->calculationsThread = new CalculationsThread();

    setWindowTitle("DMGwGB");
    this->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

    /*QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);*/

    createMenuBar();
    createSimulationMenu();
    createOpenGLDisplay();

    QWidget *mainWidget = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    //layout()->setGeometry(QRect(0,0,0,0));
    mainLayout->setMenuBar(menuB);
    mainLayout->addWidget(simulationMenuGroupBox, 0, 0, 3, 2);
    mainLayout->addWidget(openGLDisplay, 0, 2, 10, 10);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    //mainLayout->setDefaultPositioning();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    setMinimumSize(640, 480);
    //resize(800, 600);
    resize(640, 480);

    this->calculationsThread->simulation->cellularautomata = new CellularAutomata(30, 30, 30);

    connect(this->calculationsThread, &CalculationsThread::updateVal, this, &MainWindow::updateRender);
    //connect(this->calculationsThread, &CalculationsThread::finished, this, &MainWindow::updateRender);
}

MainWindow::~MainWindow()
{
	delete this->calculationsThread;
}

void MainWindow::createMenuBar()
{

    //Create actions
    newAction = new QAction(tr("&New"));
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Star new simulation"));

    //Create menus
    menuB = new QMenuBar();
    fileMenu = menuB->addMenu(tr("&File"));

    newAction = fileMenu->addAction(tr("N&ew"));
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuB->addMenu(fileMenu);

    //Connect actions
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    connect(newAction, &QAction::triggered, this, &MainWindow::newSimulation);
}

void MainWindow::createSimulationMenu()
{
    simulationMenuGroupBox = new QGroupBox(tr(" Simulation Menu "));
    QGridLayout *layout = new QGridLayout();

    nucleonsLabel = new QLabel(tr("Nucleons: "));
    nucleonsLabel->setMaximumHeight(50);
    nucleonsNumberSpinBox = new QSpinBox();
    nucleonsNumberSpinBox->setRange(0, std::numeric_limits<int>::max());
    nucleonsNumberSpinBox->setValue(10);
    nubcleonsGenerateButton = new QPushButton(tr(" Generate "));
    connect(nubcleonsGenerateButton, SIGNAL(released()), this, SLOT(generateNucleons()));
    //nubcleonsGenerateButton->setGeometry(QRect(QPoint(0, 0),QSize(200, 50)));

    neightborhoodLabel = new QLabel(tr(" Neightborhood type: "));
    neightborhoodLabel->setMaximumHeight(50);
    neightborhoodComboBox = new QComboBox;
    neightborhoodComboBox->addItem(" Lol ");

    simulationStartButton = new QPushButton(tr(" Start "));
    connect(simulationStartButton, SIGNAL(released()), this, SLOT(startSimulation()));

    layout->addWidget(nucleonsLabel, 0, 0, 1, 2);
    layout->addWidget(nucleonsNumberSpinBox, 0, 2, 1, 2);
    layout->addWidget(nubcleonsGenerateButton, 1, 0, 1, 4);

    layout->addWidget(neightborhoodLabel, 2, 0, 1, 4);
    layout->addWidget(neightborhoodComboBox, 3, 0, 1, 4);

    layout->addWidget(simulationStartButton, 4, 0, 1, 4);

    layout->setRowMinimumHeight(0, 20);
    layout->setRowMinimumHeight(1, 20);
    layout->setRowMinimumHeight(2, 20);
    layout->setRowMinimumHeight(3, 20);
    layout->setRowMinimumHeight(4, 20);
    layout->setRowMinimumHeight(5, 20);
    layout->setHorizontalSpacing(10);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    /*layout->setRowStretch(0, 10);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setRowStretch(4, 1);
    layout->setRowStretch(5, 1);*/

    simulationMenuGroupBox->setLayout(layout);
}

void MainWindow::createOpenGLDisplay()
{
    openGLDisplay = new QGLRender();
    this->openGLDisplay->setCA(this->calculationsThread->simulation->cellularautomata);
    openGLDisplay->setGeometry(0,0,100, 100);
}

void MainWindow::startSimulation()
{
    connect(this->calculationsThread, &CalculationsThread::updateVal, this, &MainWindow::updateRender);
    calculationsThread->start();
}

void MainWindow::generateNucleons()
{
    if (!calculationsThread->isRunning())
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        CellularAutomata * ca = new CellularAutomata(*this->calculationsThread->simulation->cellularautomata);
        for (int i = 0; i < this->nucleonsNumberSpinBox->value(); i++)
        {
            int x, y, z;
            x = qrand() % this->openGLDisplay->ca->getSize()[0];
            y = qrand() % this->openGLDisplay->ca->getSize()[1];
            z = qrand() % this->openGLDisplay->ca->getSize()[2];
            if (ca->getCells()[x][y][z] == 0)
            {
                ca->getCells()[x][y][z] = ca->nucleons_count + 1;
                ca->nucleons_count++;
            }
        }
        calculationsThread->simulation->cellularautomata = new CellularAutomata(*ca);
        this->openGLDisplay->setCA(new CellularAutomata(*ca));
    }

}

void MainWindow::updateRender(CellularAutomata * ca)
{
    this->openGLDisplay->setCA(new CellularAutomata(*ca));
}

void MainWindow::newSimulation()
{
    newDialog = new QNewDialog(this);
    if (newDialog->exec())
    {
        int x, y, z;
        newDialog->getValues(x, y, z);
        this->openGLDisplay->setCA(new CellularAutomata(x, y, z));
        calculationsThread->simulation->cellularautomata = new CellularAutomata(x, y, z);
    }
    delete newDialog;
}


