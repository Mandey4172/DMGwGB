#include "QGLRender.h"
#include <omp.h>
#include <iostream>

#include <QVector>
#include <QMath.h>
#include <QMouseEvent>
#include <QImage>

//#include <CellularAutomata.h>

struct Point
{
	Point() : Point(0.0f,0.0f,0.0f) {};
	Point(GLfloat nx, GLfloat ny, GLfloat nz)
	{
		position[0] = nx;  position[1] = ny;  position[2] = nz;
	}
	GLfloat position[3];
};

QGLRender::QGLRender(QWidget *parent)
	: QOpenGLWidget(parent)
{
	alpthaRotation = 180;
	betaRotation = 0;
	scale = 100;
	colorGenerator.generate(500 * 500);
	ca = new CellularAutomata(30, 30, 30);
	for (int i = 0; i < 6; i++)
		Textures[i] = nullptr;
}
	

QGLRender::~QGLRender()
{
}

void QGLRender::setCA(CellularAutomata * ca)
{
	delete this->ca;
    this->ca = new CellularAutomata(*ca);
    updateTextures();
}

void QGLRender::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        lastMouseClickPoint = event->pos();
        mousePressed = true;
    }
}

void QGLRender::mouseMoveEvent(QMouseEvent * event)
{
    if (mousePressed)
    {
        QPoint delta;
        delta = event->pos() - lastMouseClickPoint;
        if (!((alpthaRotation <= 0) && (delta.x() < 0)) && !((alpthaRotation >= 359) && (delta.x() > 0)))
        {
            model[0].rotate(delta.x(), 0.f, 1.f, 0.f);
            model[1].rotate(delta.x(), 0.f, -1.f, 0.f);

            model[2].rotate(delta.x(), 0.f, 0.f, -1.f);
            model[3].rotate(delta.x(), 0.f, 0.f, 1.f);

            model[4].rotate(delta.x(), 0.f, 1.f, 0.f);
            model[5].rotate(delta.x(), 0.f, 1.f, 0.f);

            camera.rotate(delta.x(), 0.f, 1.f, 0.f);
            alpthaRotation += delta.x();
        }
        if (!((betaRotation <= -90) && (delta.y() > 0)) && !((betaRotation >= 90) && (delta.y() < 0)))
        {
            model[0].rotate(delta.y(), 0.f, 0.f, 1.f);
            model[1].rotate(delta.y(), 0.f, 0.f, -1.f);

            model[2].rotate(delta.y(), 0.f, 1.f, 0.f);
            model[3].rotate(delta.y(), 0.f, -1.f, 0.f);

            model[4].rotate(delta.y(), -1.f, 0.f, 0.f);
            model[5].rotate(delta.y(), 1.f, 0.f, 0.f);
            /*for (int i = 0; i < 6; i++)
                model[i].rotate(delta.y(), 0.f, 0.f, 1.f);*/
            camera.rotate(delta.y(), 0.f, 0.f, 1.f);
            betaRotation += delta.y();
        }

        lastMouseClickPoint = event->pos();
    }
}

void QGLRender::mouseReleaseEvent(QMouseEvent * event)
{
    if (mousePressed) mousePressed = false;
}

void QGLRender::wheelEvent(QWheelEvent * event)
{
    if ( !( (scale <= 0)&&(event->delta() < 0) ) && !( (scale >= 200) && (event->delta() > 0) ) )
    {
        if (event->delta() < 0)
        {
            //model.scale(0.9);
            view.scale(0.9);
            scale -= 1;
        }

        else if (event->delta() > 0)
        {
            //model.scale(1.1);
            view.scale(1.1);
            scale += 1;
        }
    }
}

void QGLRender::initializeGL()
{
#pragma region Init - old v.01

	//OpenGL.initializeOpenGLFunctions();

	//QVector<Point> vcolors;
	//QVector<Point> vtranslations;

	////Pseudo inicjacja
	//int m = ca->getSize()[0],
	//	n = ca->getSize()[1],
	//	o = ca->getSize()[2];

	//// build and compile our shader program
	//// ------------------------------------
	//// vertex shader
	//if (!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "TransformVertexShader.vertexshader"))
	//{
	//	qDebug() << "Program :: OpenGL Initialization - Error in vertex shader : " << ShaderProgram.log();
	//	exit(1);
	//}
	//if (!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "ColorFragmentShader.fragmentshader"))
	//{
	//	qDebug() << "Program :: OpenGL Initialization - Error in vertex shader: " << ShaderProgram.log();
	//	exit(1);
	//}
	//if (!ShaderProgram.link())
	//{
	//	qDebug() << "Program :: OpenGL Initialization - Error linking shader program: " << ShaderProgram.log();
	//	exit(1);
	//}
	//ShaderProgram.bind();
	//// set up vertex data (and buffer(s)) and configure vertex attributes
	//// ------------------------------------------------------------------
	//float vertices[] = {
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	//};

	//VAO.create();	//glGenVertexArrays(1, &VAO);
	//VAO.bind();

	//VBO.create();
	//VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	//VBO.bind();
	//VBO.allocate(vertices, sizeof(vertices));
	//VBO.release();

	//translationsVBO.create();
	//translationsVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	//translationsVBO.bind();
	//translationsVBO.allocate(&vtranslations, vtranslations.size());
	//translationsVBO.release();

	//colorVBO.create();
	//colorVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	//colorVBO.bind();
	//colorVBO.allocate(&vcolors, vcolors.size());
	//colorVBO.release();

	//VBO.bind();
	//ShaderProgram.enableAttributeArray("position");
	//ShaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

	//ShaderProgram.enableAttributeArray("normal");
	//ShaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
	//VBO.release();

	//colorVBO.bind();
	//ShaderProgram.enableAttributeArray("color");
	//ShaderProgram.setAttributeBuffer("color", GL_FLOAT, 0, 3);
	//this->context()->extraFunctions()->glVertexAttribDivisor(2, 1);
	//colorVBO.release();

	//translationsVBO.bind();
	//ShaderProgram.enableAttributeArray("translation");
	//ShaderProgram.setAttributeBuffer("translation", GL_FLOAT, 0, 3);
	//this->context()->extraFunctions()->glVertexAttribDivisor(3, 1);
	//translationsVBO.release();

	//VAO.release();

	//projection.perspective(45.0f, (GLfloat)this->width() / this->height(), 0.1f, 100000.0f);

	//int max = m;
	//if (max < n) max = n;
	//if (max < o) max = 0;
	//float camY = 10 * max * sin(qDegreesToRadians(betaRotation));
	//float camX = 10 * max * cos(qDegreesToRadians(betaRotation)) * cos(qDegreesToRadians(alpthaRotation));
	//float camZ = 10 * max * cos(qDegreesToRadians(betaRotation)) * sin(qDegreesToRadians(alpthaRotation));

	////float camY = scale * sin(qDegreesToRadians(betaRotation));
	////float camX = scale * cos(qDegreesToRadians(betaRotation)) * cos(qDegreesToRadians(alpthaRotation));
	////float camZ = scale * cos(qDegreesToRadians(betaRotation)) * sin(qDegreesToRadians(alpthaRotation));

	//QVector3D v1 = QVector3D(camX, camY, camZ);
	//QVector3D v2 = QVector3D(0, 0, 0);
	//QVector3D v3 = QVector3D(0.0f, 1.0f, 0.0f);
	//view.lookAt(v1, v2, v3);

	//ShaderProgram.setUniformValue("model", model);
	//ShaderProgram.setUniformValue("view", view);
	//ShaderProgram.setUniformValue("projection", projection);

	//GLfloat lp[3] = { (GLfloat)m / 2 + 10, (GLfloat)n / 2, (GLfloat)(2 * o) / 2 };
	//QVector3D v = camera * QVector3D(0, 0, -10);
	//ShaderProgram.setUniformValue("lightPos", v);

	//ShaderProgram.release();

	//OpenGL.glEnable(GL_DEPTH_TEST);
	//OpenGL.glEnable(GL_BLEND);
	//OpenGL.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion
#pragma region Init - v.02

	OpenGL.initializeOpenGLFunctions();

	QVector<Point> vcolors;
	QVector<Point> vtranslations;
	QVector<float> vmodels;

	//Pseudo inicjacja
	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	if (!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "TransformVertexShader.vertexshader"))
	{
		qDebug() << "Program :: OpenGL Initialization - Error in vertex shader : " << ShaderProgram.log();
		exit(1);
	}
	if (!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "ColorFragmentShader.fragmentshader"))
	{
		qDebug() << "Program :: OpenGL Initialization - Error in vertex shader: " << ShaderProgram.log();
		exit(1);
	}
	if (!ShaderProgram.link())
	{
		qDebug() << "Program :: OpenGL Initialization - Error linking shader program: " << ShaderProgram.log();
		exit(1);
	}
	ShaderProgram.bind();
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {

		-0.5f, -0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 0.f, 0.f,
		0.5f, -0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 0.f, 1.f,
		0.5f,  0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 1.f, 1.f,
		0.5f,  0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 1.f, 1.f,
		-0.5f,  0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 1.f, 0.f,
		-0.5f, -0.5f, 0.5f,  0.0f,  0.0f, -1.0f, 0.f, 0.f,
	};

	model[1].rotate(180.f, 1.f, 0.f, 0.f);
	model[2].rotate(90.f, 1.f, 0.f, 0.f);
	model[3].rotate(270.f, 1.f, 0.f, 0.f);
	model[4].rotate(90.f, 0.f, 1.f, 0.f);
	model[5].rotate(270.f, 0.f, 1.f, 0.f);

	VAO.create();	//glGenVertexArrays(1, &VAO);

	VAO.bind();

	VBO.create();
	VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	VBO.bind();
	VBO.allocate(vertices, sizeof(vertices));
	VBO.release();

	VBO.bind();

	ShaderProgram.enableAttributeArray("position");
	ShaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 8 * sizeof(GLfloat));

	ShaderProgram.enableAttributeArray("normal");
	ShaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(GLfloat), 3, 8 * sizeof(GLfloat));

	ShaderProgram.enableAttributeArray("textCord");
	ShaderProgram.setAttributeBuffer("textCord", GL_FLOAT, 6 * sizeof(GLfloat), 2, 8 * sizeof(GLfloat));

	VBO.release();

	VAO.release();

	projection.perspective(45.0f, (GLfloat)this->width() / this->height(), 0.1f, 100000.0f);

	/*int max = m;
	if (max < n) max = n;
	if (max < o) max = 0;*/
	float camY = 2 * sin(qDegreesToRadians(betaRotation));
	float camX = 2 * cos(qDegreesToRadians(betaRotation)) * cos(qDegreesToRadians(alpthaRotation));
	float camZ = 2 * cos(qDegreesToRadians(betaRotation)) * sin(qDegreesToRadians(alpthaRotation));

	QVector3D v1 = QVector3D(camX, camY, camZ);
	QVector3D v2 = QVector3D(0, 0, 0);
	QVector3D v3 = QVector3D(0.0f, 1.0f, 0.0f);
	view.lookAt(v1, v2, v3);

	//ShaderProgram.setUniformValue("model", model);
	ShaderProgram.setUniformValue("view", view);
	ShaderProgram.setUniformValue("projection", projection);
	ShaderProgram.setUniformValue("model", model[0]);
	ShaderProgram.setUniformValue("texture", 0);

	GLfloat lp[3] = { (GLfloat)m / 2 + 10, (GLfloat)n / 2, (GLfloat)(2 * o) / 2 };
	QVector3D v = camera * QVector3D(0, 0, -10);
	ShaderProgram.setUniformValue("lightPos", v);

	ShaderProgram.release();

	OpenGL.glEnable(GL_DEPTH_TEST);
	OpenGL.glEnable(GL_BLEND);
	OpenGL.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	updateTextures();
#pragma endregion
}

void QGLRender::resizeGL(int w, int h)
{
	this->OpenGL.glViewport(0, 0, w, h);
}

void QGLRender::paintGL()
{

	QVector<GLfloat> vcolors;
	QVector<GLfloat> vtranslations;

	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];

#pragma region Old_Version - v0.1
	//int m = 1,
	//	n = 1,
	//	o = 1;

	//Pseudo inicjacja
	//float camY = sin(qDegreesToRadians(camera.getBetaRotation()));
	//float camX = cos(qDegreesToRadians(camera.getBetaRotation())) * cos(qDegreesToRadians(camera.getAlphaRotation()));
	//float camZ = cos(qDegreesToRadians(camera.getBetaRotation())) * sin(qDegreesToRadians(camera.getAlphaRotation()));

	//GLfloat * c = new GLfloat[ m * n * o * 3];// = { 0.1f,0.2f,0.3f };
	//GLfloat * t = new GLfloat[m * n * o * 3];// = { 0.0f,0.0f,0.0f };

	////int x = 0;
	////for (int i = 0; i < m; i++)
	////{
	////	for (int j = 0; j < n; j++)
	////	{
	////		for (int k = 0; k < o; k++)
	////		{
	////			int assa = ca->getCells()[i][j][k];
	////			
	////			if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	////			{
	////				vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	////				vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	////				vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	////			}
	////			else
	////			{
	////				vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	////				vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	////				vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	////			}
	////			vtranslations.push_back(i - (m/2));
	////			vtranslations.push_back(j - (n/2));
	////			vtranslations.push_back(k - (o/2));
	////			x++;
	////		}
	////	}
	////}
#pragma endregion
#pragma region Old_Version - v0.2
	//int x = 0;
	/////Z
	//for (int i = 0; i < m; i++)
	//{
	//	int k = 0;
	//	for (int j = 0; j < n; j++)
	//	{
	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		int k = o - 1;
	//		int assa = ca->getCells()[i][j][k];

	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
	/////Y
	//for (int i = 0; i < m; i++)
	//{
	//	for (int k = 1; k < o - 1; k++)
	//	{
	//		int j = 0;
	//		int assa = ca->getCells()[i][j][k];

	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
	//for (int i = 0; i < m; i++)
	//{
	//	for (int k = 1; k < o - 1; k++)
	//	{
	//		int j = m - 1;
	//		int assa = ca->getCells()[i][j][k];

	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
	/////X
	//for (int j = 1; j < n - 1; j++)
	//{
	//	for (int k = 1; k < o - 1; k++)
	//	{
	//		int i = 0;
	//		int assa = ca->getCells()[i][j][k];

	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
	//for (int j = 1; j < n - 1; j++)
	//{
	//	for (int k = 1; k < o - 1; k++)
	//	{
	//		int i = n - 1;
	//		int assa = ca->getCells()[i][j][k];

	//		if (ca->nucleons_count > 0 && ca->getCells()[i][j][k] >= ca->nucleons_count)
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[colorGenerator.colorCount - ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		else
	//		{
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][0]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][1]);
	//			vcolors.push_back((GLfloat)colorGenerator.colors[ca->getCells()[i][j][k]][2]); //ca.getCells()[i][j][k]
	//		}
	//		vtranslations.push_back(i - (m / 2));
	//		vtranslations.push_back(j - (n / 2));
	//		vtranslations.push_back(k - (o / 2));
	//		x++;
	//	}
	//}
#pragma endregion
#pragma region Version - v0.3

	/////X
	//for (int j = 0; j < n; j++)
	//{
	//	for (int k = 0; k < o; k++)
	//	{
	//		QColor newColorA = QColor(	colorGenerator.colors[this->ca->getCells()[0][j][k]][0],
	//									colorGenerator.colors[this->ca->getCells()[0][j][k]][1],
	//									colorGenerator.colors[this->ca->getCells()[0][j][k]][2]);
	//		QColor newColorB = QColor(	colorGenerator.colors[this->ca->getCells()[m - 1][j][k]][0],
	//									colorGenerator.colors[this->ca->getCells()[m - 1][j][k]][1],
	//									colorGenerator.colors[this->ca->getCells()[m - 1][j][k]][2]);
	//		TexturesData[0].setPixelColor(QPoint(j, k), newColorA);
	//		TexturesData[1].setPixelColor(QPoint(j, k), newColorB);
	//	}
	//}
	/////Y
	//for (int i = 0; i < m; i++)
	//{
	//	for (int k = 0; k < o; k++)
	//	{
	//		QColor newColorA = QColor(	colorGenerator.colors[this->ca->getCells()[i][0][k]][0],
	//									colorGenerator.colors[this->ca->getCells()[i][0][k]][1],
	//									colorGenerator.colors[this->ca->getCells()[i][0][k]][2]);
	//		QColor newColorB = QColor(	colorGenerator.colors[this->ca->getCells()[i][n - 1][k]][0],
	//									colorGenerator.colors[this->ca->getCells()[i][n - 1][k]][1],
	//									colorGenerator.colors[this->ca->getCells()[i][n - 1][k]][2]);
	//		TexturesData[2].setPixelColor(QPoint(i, k), newColorA);
	//		TexturesData[3].setPixelColor(QPoint(i, k), newColorB);
	//	}
	//}
	/////Z
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		QColor newColorA = QColor(	colorGenerator.colors[this->ca->getCells()[i][j][0]][0],
	//									colorGenerator.colors[this->ca->getCells()[i][j][0]][1],
	//									colorGenerator.colors[this->ca->getCells()[i][j][0]][2]);
	//		QColor newColorB = QColor(	colorGenerator.colors[this->ca->getCells()[i][j][o - 1]][0],
	//									colorGenerator.colors[this->ca->getCells()[i][j][o - 1]][1],
	//									colorGenerator.colors[this->ca->getCells()[i][j][o - 1]][2]);
	//		TexturesData[4].setPixelColor(QPoint(i, j), newColorA);
	//		TexturesData[5].setPixelColor(QPoint(i, j), newColorB);
	//	}
	//}
	//

#pragma endregion

#pragma region Render v.02
	//// render
	//// ------
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//translationsVBO.bind();
	//translationsVBO.allocate(&vtranslations[0], vtranslations.size() * sizeof(GLfloat));
	//translationsVBO.release();

	//colorVBO.bind();
	//colorVBO.allocate(&vcolors[0], vcolors.size() * sizeof(GLfloat));
	//colorVBO.release();

	//ShaderProgram.bind();
	//ShaderProgram.setUniformValue("model", model);

	//ShaderProgram.setUniformValue("view", view);
	//ShaderProgram.setUniformValue("projection", projection);

	//VAO.bind();
	//this->context()->extraFunctions()->glDrawArraysInstanced(GL_TRIANGLES, 0, 36, vcolors.size());
	//VAO.release();
	//update();
#pragma endregion
#pragma region Render Old v.01

	// render
	// ------
	this->OpenGL.glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	this->OpenGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderProgram.bind();
	//ShaderProgram.setUniformValue("model", model);
	ShaderProgram.setUniformValue("view", view);
	ShaderProgram.setUniformValue("projection", projection);

	VAO.bind();
	for (int i = 0; i < 6; i++)
	{
		ShaderProgram.setUniformValue("model", model[i]);
		if (Textures[i])
		{
			Textures[i]->setMinMagFilters(QOpenGLTexture::Filter::Nearest, QOpenGLTexture::Filter::Nearest);
			Textures[i]->bind();
		}
		OpenGL.glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	VAO.release();


	update();

#pragma endregion
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//// draw our first triangle
	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

}

void QGLRender::updateTextures()
{
	int m = ca->getSize()[0] ,
		n = ca->getSize()[1] ,
		o = ca->getSize()[2] ;

	QImage	TexturesData[6];

	TexturesData[0] = QImage(QSize(n, o), QImage::Format_RGB32);
	TexturesData[1] = QImage(QSize(n, o), QImage::Format_RGB32);

	TexturesData[2] = QImage(QSize(m, o), QImage::Format_RGB32);
	TexturesData[3] = QImage(QSize(m, o), QImage::Format_RGB32);

	TexturesData[4] = QImage(QSize(m, n), QImage::Format_RGB32);
	TexturesData[5] = QImage(QSize(m, n), QImage::Format_RGB32);

	float min = 0.f, max = 1.f;

	///X
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < o; k++)
		{
			QColor newColorA = QColor();
			QColor newColorB = QColor();
			unsigned int s1 = this->ca->getCells()[0][j][k];
			unsigned int s2 = this->ca->getCells()[m - 1][j][k];
		
			if (s1 > this->ca->nucleons_count)
			{
				s1 = s1 + ((500 * 500) / 2) + 1;
			}
			if (s2 > this->ca->nucleons_count)
			{
				s2 = s2 + ((500 * 500) / 2) + 1;
			}
			
			if (s1 > colorGenerator.colorCount)
			{
				s1 = colorGenerator.colorCount - 1;
			}
			if (s2 > colorGenerator.colorCount)
			{
				s2 = colorGenerator.colorCount - 1;
			}

			if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
			else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
			if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
			else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
			if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
			else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

			if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
			else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
			if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
			else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
			if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
			else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

			qreal r, g, b;
			r = colorGenerator.colors[s1][0];
			g = colorGenerator.colors[s1][1];
			b = colorGenerator.colors[s1][2];
			newColorA.setRgbF(r, g, b);
			r = colorGenerator.colors[s2][0];
			g = colorGenerator.colors[s2][1];
			b = colorGenerator.colors[s2][2];
			newColorB.setRgbF(r, g, b);

			TexturesData[0].setPixelColor(QPoint(j, k), newColorA);
			TexturesData[1].setPixelColor(QPoint(j, k), newColorB);
		}
	}
	///Y
	for (int i = 0; i < m; i++)
	{
		for (int k = 0; k < o; k++)
		{
			QColor newColorA = QColor();
			QColor newColorB = QColor();
			unsigned int s1 = this->ca->getCells()[i][0][k];
			unsigned int s2 = this->ca->getCells()[i][n - 1][k];
			
			if (s1 > this->ca->nucleons_count)
			{
				s1 = s1 + ((500 * 500) / 2) + 1;
			}
			if (s2 > this->ca->nucleons_count)
			{
				s2 = s2 + ((500 * 500) / 2) + 1;
			}

			if (s1 > colorGenerator.colorCount)
			{
				s1 = colorGenerator.colorCount - 1;
			}
			if (s2 > colorGenerator.colorCount)
			{
				s2 = colorGenerator.colorCount - 1;
			}

			if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
			else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
			if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
			else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
			if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
			else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

			if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
			else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
			if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
			else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
			if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
			else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

			qreal r, g, b;
			r = colorGenerator.colors[s1][0];
			g = colorGenerator.colors[s1][1];
			b = colorGenerator.colors[s1][2];
			newColorA.setRgbF(r, g, b);
			r = colorGenerator.colors[s2][0];
			g = colorGenerator.colors[s2][1];
			b = colorGenerator.colors[s2][2];
			newColorB.setRgbF(r, g, b);

			TexturesData[2].setPixelColor(QPoint(i, k), newColorA);
			TexturesData[3].setPixelColor(QPoint(i, k), newColorB);
		}
	}
	///Z
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			QColor newColorA = QColor();
			QColor newColorB = QColor();
			unsigned int s1 = this->ca->getCells()[i][j][0];
			unsigned int s2 = this->ca->getCells()[i][j][o - 1];

			if (s1 > this->ca->nucleons_count)
			{
				s1 = s1 + ((500 * 500) / 2) + 1;
			}
			if (s2 > this->ca->nucleons_count)
			{
				s2 = s2 + ((500 * 500) / 2) + 1;
			}

			if (s1 > colorGenerator.colorCount)
			{
				s1 = colorGenerator.colorCount - 1;
			}
			if (s2 > colorGenerator.colorCount)
			{
				s2 = colorGenerator.colorCount - 1;
			}

			if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
			else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
			if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
			else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
			if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
			else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

			if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
			else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
			if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
			else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
			if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
			else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

			qreal r, g, b;
			r = colorGenerator.colors[s1][0];
			g = colorGenerator.colors[s1][1];
			b = colorGenerator.colors[s1][2];
			newColorA.setRgbF(r, g, b);
			r = colorGenerator.colors[s2][0];
			g = colorGenerator.colors[s2][1];
			b = colorGenerator.colors[s2][2];
			newColorB.setRgbF(r, g, b);

			TexturesData[5].setPixelColor(QPoint(j, i), newColorA);
			TexturesData[4].setPixelColor(QPoint(j, i), newColorB);
		}
	}

	if (Textures[0])
		delete Textures[0];
	Textures[0] = new QOpenGLTexture(TexturesData[0].mirrored(false, false));
	if (Textures[1])
		delete Textures[1];
	Textures[1] = new QOpenGLTexture(TexturesData[1].mirrored(true, false));
	if (Textures[2])
		delete Textures[2];
	Textures[2] = new QOpenGLTexture(TexturesData[2].mirrored(true, false));
	if (Textures[3])
		delete Textures[3];
	Textures[3] = new QOpenGLTexture(TexturesData[3].mirrored(false, false));
	if (Textures[4])
		delete Textures[4];
	Textures[4] = new QOpenGLTexture(TexturesData[4].mirrored(false, false));
	if (Textures[5])
		delete Textures[5];
	Textures[5] = new QOpenGLTexture(TexturesData[5].mirrored(false, true));
}