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
#include <QDialogButtonBox.h>
#include <QGridLayout.h>
#include <QFormLayout.h>
#include <QComboBox.h>
#include <QOpenGLWidget.h>
#include <QOpenGLFunctions>

#include "QGLRender.h"
#include "QNewDialog.h"

#include "CalculationsThread.h"
#include "CellularAutomata.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //Ui::DMGwGBWin64Class ui;
    void createMenuBar();
    void createSimulationMenu();
    void createOpenGLDisplay();

    /*Menu*/
    QMenuBar		*menuB;
    QMenu			*fileMenu;
    /*Menu Actions*/
    QAction			*newAction;
    QAction			*exitAction;
    /* */
    QGroupBox		*simulationMenuGroupBox;

    /*Menu*/
    //Nucleation
    QLabel			*nucleonsLabel;
    QSpinBox		*nucleonsNumberSpinBox;
    QPushButton		*nubcleonsGenerateButton;
    //Neightborhood
    QLabel			*neightborhoodLabel;
    QComboBox		*neightborhoodComboBox;
    //Simulation
    QPushButton		*simulationStartButton;
    /*OpenGL*/
    QGLRender		*openGLDisplay;

	QLabel			*debugLabel;

    CalculationsThread * calculationsThread;

    QNewDialog * newDialog;

    private slots:
    void newSimulation();
    void startSimulation();
    void generateNucleons();
    void updateRender();
	void updateDebug(const QString text);
};

#endif // MAINWINDOW_H
