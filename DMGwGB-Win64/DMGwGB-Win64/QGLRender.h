#ifndef QGLRENDER_H
#define QGLRENDER_H

#pragma once

#include <QOpenGLWidget>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLTexture.h>

#include"ColorGenerator.h"

#include "CellularAutomataSpace.h"


class QGLRender : public QOpenGLWidget
{
	Q_OBJECT

public:
	QGLRender(QWidget *parent = Q_NULLPTR);
	~QGLRender();

    QMatrix4x4							camera;
    CellularAutomataSpace				*ca;
    void setCA(CellularAutomataSpace	*ca);
	void setShowAllGrains(bool show);
	void setHidenGrains(QVector<int> hidenGrains);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void updateTextures();
	void updateCells();
	bool shouldDrawCell(int x, int y, int z);
	void updateView();

	QVector<QVector3D> color;
	QVector<QVector3D> position;
	QVector3D lightPosition;
/*	Render	*/
    QOpenGLShaderProgram		ShaderProgram;
    QOpenGLVertexArrayObject	VAO;
    QOpenGLBuffer				VBO;
	
	QOpenGLBuffer				colorVBO;
	QOpenGLBuffer				offsetVBO;

    QOpenGLTexture*				Textures[6];

	QOpenGLExtraFunctions		OpenGL;

    QMatrix4x4					model[6];
    QMatrix4x4					view;
    QMatrix4x4					projection;
    ColorGenerator				colorGenerator;
/*	Mouse	*/
    bool						mousePressed;
    QPoint						lastMouseClickPoint;

    float						alpthaRotation;
    float						betaRotation;
    int							scale;
	
	bool bShowGrains;
	QVector<int> hidenGrains;
};

//class QGLUpdateThread : public QThread
//{
//private:
//	void run() override;
//};

#endif // QGLRENDER_H
