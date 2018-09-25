#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QGroupBox.h>
#include <QTextEdit.h>
#include <QSpinBox.h>
#include <QPushButton.h>
#include <QLabel.h>
#include <QCheckBox.h>
#include <QLineEdit.h>
#include <QDialogButtonBox.h>
#include <QGridLayout.h>
#include <QFormLayout.h>
#include <QComboBox.h>
#include <QOpenGLWidget.h>
#include <QOpenGLFunctions>

#include "QGLRender.h"
#include "QNewDialog.h"

#include "CalculationsThread.h"
//#include "CellularAutomataSpace.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void createMenuBar();
	void createNewMenu();
	void createNucleationMenu();
    void createSimulationMenu();
    void createOpenGLDisplay();

    /*Menu*/
    QMenuBar		*menuB;
    QMenu			*fileMenu;
    /*Menu Actions*/
    QAction			*newAction;
	QAction			*loadAction;
	QAction			*saveAction;
    QAction			*exitAction;
    
    /*Menu*/
		//New 
	QGroupBox		*newMenuGroupBox;
	QPushButton		*newMicrostructureButton;
	QPushButton		*loadMicrostructureButton;

		//Nucleation
	QGroupBox		*nucleationMenuGroupBox;

	QLabel			*nucleationLabel;
    QSpinBox		*nucleationNumberSpinBox;

	QLabel			*nucleationTypeLabel;
	QComboBox		*nucleationTypeComboBox;

	QLabel			*nucleationOptionLabel1;
	QSpinBox		*nucleationOptionTextBox1;
	QLabel			*nucleationOptionLabel2;
	QSpinBox		*nucleationOptionTextBox2;
	QLabel			*nucleationOptionLabel3;
	QSpinBox		*nucleationOptionTextBox3;
	QLabel			*nucleationOptionLabel4;
	QComboBox		*nucleationOptionTextBox4;

	QPushButton		*nucleationGenerateButton;

		//Simulation
	QGroupBox		*simulationMenuGroupBox;

    QLabel			*neightborhoodLabel;
    QComboBox		*neightborhoodComboBox;

	QLabel			*neightborhoodRadiusLabel;
	QSpinBox		*neightborhoodRadiusSpinBox;

	QLabel			*boundaryNeightborhoodLabel;
	QComboBox		*boundaryNeightborhoodComboBox;

	QLabel			*boundaryConditionsLabel;
	QComboBox		*boundaryConditionsComboBox;

	QLabel			*grainBoundarySizeLabel;
	QSpinBox		*grainBoundarySizeTextBox;
	
	QLabel			*fuseAfterSimulationLabel;
	QCheckBox		*fuseAfterSimulationChechBox;

    QPushButton		*simulationStartButton;
	QLabel			*debugLabel;

	/*OpenGL*/
	QGroupBox		*displayMenuGroupBox;
    QGLRender		*openGLDisplay;

	QLabel			*showGrainBoundariesLabel;
	QCheckBox		*showGrainBoundariesChechBox;

	QLabel			*hidenGrainsLabel;
	QLineEdit		*hidenGrainsLineEdit;

    CalculationsThread calculationsThread;

    private slots:
    void newSimulation();

    void startSimulation();

    void generateNucleons();
	void nucleonGenerationTypeChanged(const int & index);
	void showGrainBoundariesStateChanged(bool state);
	void hidenGrainsStateChanged(const QString &text);
	void hidenGrainsEditEnded();

    void updateRender();
	void updateDebug(const QString text);

	void loadFile();
	void saveFile();
};

#endif // MAINWINDOW_H
