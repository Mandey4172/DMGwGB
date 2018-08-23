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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void updateTextures();
	void updateView();

/*	Render	*/
    QOpenGLShaderProgram		ShaderProgram;
    QOpenGLVertexArrayObject	VAO;
    QOpenGLBuffer				VBO;
    QOpenGLTexture*				Textures[6];
    /*QImage						*TexturesData[6];*/
    //QOpenGLBuffer				translationsVBO;
    //QOpenGLBuffer				colorVBO;
    QOpenGLFunctions			OpenGL;

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
};

#endif // QGLRENDER_H
