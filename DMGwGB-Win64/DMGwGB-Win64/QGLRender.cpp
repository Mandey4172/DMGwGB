#include "QGLRender.h"
#include <omp.h>
#include <iostream>

#include <QVector>
#include <QMath.h>
#include <QMouseEvent>
#include <QImage>


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
	alpthaRotation = 180.f;
	betaRotation = 0.f;
	scale = 100.;
	colorGenerator.generate(500 * 500);
	bShowGrains = true;
	lightPosition = QVector3D(-100,0,0);
	ca = new CellularAutomataSpace(30, 30, 30);
	for (int i = 0; i < 6; i++)
		Textures[i] = nullptr;
}
	

QGLRender::~QGLRender()
{
}

void QGLRender::setCA(CellularAutomataSpace * ca)
{
	delete this->ca;
    this->ca = new CellularAutomataSpace(*ca);
    updateTextures();
	updateCells();
	updateView();
}

void QGLRender::setShowAllGrains(bool show)
{
	bShowGrains = show;
	updateCells();
	updateView();
}

void QGLRender::setHidenGrains(QVector<int> hidenGrains)
{
	this->hidenGrains = hidenGrains;
	updateCells();
	updateView();
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

		const float alpthaRotationMin = 0.f;
		const float alpthaRotationMax = 360.f;
		const float speedDivider = 2.f;

		alpthaRotation -= (delta.x() / speedDivider);

		const float betaRotationMin = -89.f;
		const float betaRotationMax = 89.f;

        if (!((betaRotation <= betaRotationMin) && (delta.y() < 0)) && !((betaRotation >= betaRotationMax) && (delta.y() > 0)))
        {
            betaRotation += (delta.y() / speedDivider);
			if (betaRotation < betaRotationMin) betaRotation = betaRotationMin;
			if (betaRotation > betaRotationMax) betaRotation = betaRotationMax;
        }
		lastMouseClickPoint = event->pos();
		updateView();
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
            scale -= 10;
        }

        else if (event->delta() > 0)
        {
            scale += 10;
        }
		updateView();
    }
}

void QGLRender::initializeGL()
{
	OpenGL.initializeOpenGLFunctions();

	//QVector<Point> vcolors;
	//QVector<Point> vtranslations;
	//QVector<float> vmodels;

	//Pseudo inicjacja
	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];

	// Budowa i kompilacja shaderów 
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

	float vertices[] = { 
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	colorVBO.create();
	colorVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
	offsetVBO.create();
	offsetVBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);

	//
	VAO.create();	//glGenVertexArrays(1, &VAO);
	VAO.bind();

	VBO.create();

	VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
	VBO.bind();
	VBO.allocate(vertices, sizeof(vertices));
	VBO.release();

	VBO.bind();

	ShaderProgram.enableAttributeArray("position");
	ShaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * sizeof(GL_FLOAT));

	ShaderProgram.enableAttributeArray("normal");
	ShaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(GL_FLOAT), 3, 6 * sizeof(GL_FLOAT));

	VBO.release();

	offsetVBO.bind();
	ShaderProgram.enableAttributeArray("offset");
	ShaderProgram.setAttributeBuffer("offset", GL_FLOAT, 0, 3);
	offsetVBO.release();
	OpenGL.glVertexAttribDivisor(ShaderProgram.attributeLocation("offset"), 1);

	colorVBO.bind();
	ShaderProgram.enableAttributeArray("color");	
	ShaderProgram.setAttributeBuffer("color", GL_FLOAT, 0, 3);
	colorVBO.release();
	OpenGL.glVertexAttribDivisor(ShaderProgram.attributeLocation("color"), 1);

	VAO.release();

	projection.perspective(45.0f, (GLfloat)this->width() / this->height(), 0.1f, 100000.0f);
	model[0] = QMatrix4x4();
	updateView();


	ShaderProgram.setUniformValue("view", view);
	ShaderProgram.setUniformValue("projection", projection);
	ShaderProgram.setUniformValue("model", model[0]);
	ShaderProgram.setUniformValue("lightPos", lightPosition);

	ShaderProgram.release();

	OpenGL.glEnable(GL_DEPTH_TEST);
	//OpenGL.glEnable(GL_BLEND);
	//OpenGL.glEnable(GL_LIGHTING);
	//OpenGL.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	updateCells();
	updateView();
}

void QGLRender::resizeGL(int w, int h)
{
	this->OpenGL.glViewport(0, 0, w, h);
	projection = QMatrix4x4();
	projection.perspective(45.0f, (GLfloat)w / h, 0.1f, 100000.0f);
}

void QGLRender::paintGL()
{
	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];

	

	//// render
	//// ------
	this->OpenGL.glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	this->OpenGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderProgram.bind();
	ShaderProgram.setUniformValue("view", view);
	ShaderProgram.setUniformValue("projection", projection);
	ShaderProgram.setUniformValue("lightPos", lightPosition);

	VAO.bind();
	OpenGL.glDrawArraysInstanced(GL_TRIANGLES, 0, 36, position.size());
	VAO.release();

	update();
}

bool QGLRender::shouldDrawCell(int x, int y, int z)
{
	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];
	unsigned int state = ca->getCells()[x][y][z];

	for (int i = -1; i < 1; i++)
	{
		int current_x = x + i;
		if (current_x >= 0 && current_x < m)
		{
			for (int j = -1; j < 1; j++)
			{
				int current_y = y + j;
				if (current_y >= 0 && current_y < n)
				{
					for (int k = -1; k < 1; k++)
					{
						int current_z = z + k;
						if (current_z >= 0 && current_z < o)
						{
							if (state != ca->getCells()[current_x][current_y][current_z]) return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void QGLRender::updateTextures()
{
	int m = 100, //ca->getSize()[0] ,
		n = 100, //ca->getSize()[1] ,
		o = 100; //ca->getSize()[2] ;

	QImage	TexturesData[6];

	TexturesData[0] = QImage(QSize(n, o), QImage::Format_RGB32);
	TexturesData[1] = QImage(QSize(n, o), QImage::Format_RGB32);

	TexturesData[2] = QImage(QSize(m, o), QImage::Format_RGB32);
	TexturesData[3] = QImage(QSize(m, o), QImage::Format_RGB32);

	TexturesData[4] = QImage(QSize(m, n), QImage::Format_RGB32);
	TexturesData[5] = QImage(QSize(m, n), QImage::Format_RGB32);

	float min = 0.f, max = 1.f;

	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 100; j++)
	//	{

	//	}
	//}
	/////X
	//for (int j = 0; j < n; j++)
	//{ 
	//	for (int k = 0; k < o; k++)
	//	{
	//		QColor newColorA = QColor();
	//		QColor newColorB = QColor();
	//		unsigned int s1 = this->ca->getCells()[0][j][k];
	//		unsigned int s2 = this->ca->getCells()[m - 1][j][k];
	//	
	//		if (s1 > this->ca->nucleons_count)
	//		{
	//			s1 = s1 + ((500 * 500) / 2) + 1;
	//		}
	//		if (s2 > this->ca->nucleons_count)
	//		{
	//			s2 = s2 + ((500 * 500) / 2) + 1;
	//		}
	//		
	//		if (s1 > colorGenerator.colorCount)
	//		{
	//			s1 = colorGenerator.colorCount - 1;
	//		}
	//		if (s2 > colorGenerator.colorCount)
	//		{
	//			s2 = colorGenerator.colorCount - 1;
	//		}

	//		if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
	//		else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
	//		if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
	//		else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
	//		if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
	//		else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

	//		if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
	//		else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
	//		if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
	//		else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
	//		if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
	//		else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

	//		qreal r, g, b;
	//		r = colorGenerator.colors[s1][0];
	//		g = colorGenerator.colors[s1][1];
	//		b = colorGenerator.colors[s1][2];
	//		newColorA.setRgbF(r, g, b);
	//		r = colorGenerator.colors[s2][0];
	//		g = colorGenerator.colors[s2][1];
	//		b = colorGenerator.colors[s2][2];
	//		newColorB.setRgbF(r, g, b);

	//		TexturesData[0].setPixelColor(QPoint(j, k), newColorA);
	//		TexturesData[1].setPixelColor(QPoint(j, k), newColorB);
	//	}
	//}
	/////Y
	//for (int i = 0; i < m; i++)
	//{
	//	for (int k = 0; k < o; k++)
	//	{
	//		QColor newColorA = QColor();
	//		QColor newColorB = QColor();
	//		unsigned int s1 = this->ca->getCells()[i][0][k];
	//		unsigned int s2 = this->ca->getCells()[i][n - 1][k];
	//		
	//		if (s1 > this->ca->nucleons_count)
	//		{
	//			s1 = s1 + ((500 * 500) / 2) + 1;
	//		}
	//		if (s2 > this->ca->nucleons_count)
	//		{
	//			s2 = s2 + ((500 * 500) / 2) + 1;
	//		}

	//		if (s1 > colorGenerator.colorCount)
	//		{
	//			s1 = colorGenerator.colorCount - 1;
	//		}
	//		if (s2 > colorGenerator.colorCount)
	//		{
	//			s2 = colorGenerator.colorCount - 1;
	//		}

	//		if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
	//		else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
	//		if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
	//		else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
	//		if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
	//		else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

	//		if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
	//		else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
	//		if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
	//		else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
	//		if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
	//		else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

	//		qreal r, g, b;
	//		r = colorGenerator.colors[s1][0];
	//		g = colorGenerator.colors[s1][1];
	//		b = colorGenerator.colors[s1][2];
	//		newColorA.setRgbF(r, g, b);
	//		r = colorGenerator.colors[s2][0];
	//		g = colorGenerator.colors[s2][1];
	//		b = colorGenerator.colors[s2][2];
	//		newColorB.setRgbF(r, g, b);

	//		TexturesData[2].setPixelColor(QPoint(i, k), newColorA);
	//		TexturesData[3].setPixelColor(QPoint(i, k), newColorB);
	//	}
	//}
	/////Z
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//	{
	//		QColor newColorA = QColor();
	//		QColor newColorB = QColor();
	//		unsigned int s1 = this->ca->getCells()[i][j][0];
	//		unsigned int s2 = this->ca->getCells()[i][j][o - 1];

	//		if (s1 > this->ca->nucleons_count)
	//		{
	//			s1 = s1 + ((500 * 500) / 2) + 1;
	//		}
	//		if (s2 > this->ca->nucleons_count)
	//		{
	//			s2 = s2 + ((500 * 500) / 2) + 1;
	//		}

	//		if (s1 > colorGenerator.colorCount)
	//		{
	//			s1 = colorGenerator.colorCount - 1;
	//		}
	//		if (s2 > colorGenerator.colorCount)
	//		{
	//			s2 = colorGenerator.colorCount - 1;
	//		}

	//		if (colorGenerator.colors[s1][0] > max) colorGenerator.colors[s1][0] = max;
	//		else if (colorGenerator.colors[s1][0] < min) colorGenerator.colors[s1][0] = min;
	//		if (colorGenerator.colors[s1][1] > max) colorGenerator.colors[s1][1] = max;
	//		else if (colorGenerator.colors[s1][1] < min) colorGenerator.colors[s1][1] = min;
	//		if (colorGenerator.colors[s1][2] > max) colorGenerator.colors[s1][2] = max;
	//		else if (colorGenerator.colors[s1][2] < min) colorGenerator.colors[s1][2] = min;

	//		if (colorGenerator.colors[s2][0] > max) colorGenerator.colors[s2][0] = max;
	//		else if (colorGenerator.colors[s2][0] < min) colorGenerator.colors[s2][0] = min;
	//		if (colorGenerator.colors[s2][1] > max) colorGenerator.colors[s2][1] = max;
	//		else if (colorGenerator.colors[s2][1] < min) colorGenerator.colors[s2][1] = min;
	//		if (colorGenerator.colors[s2][2] > max) colorGenerator.colors[s2][2] = max;
	//		else if (colorGenerator.colors[s2][2] < min) colorGenerator.colors[s2][2] = min;

	//		qreal r, g, b;
	//		r = colorGenerator.colors[s1][0];
	//		g = colorGenerator.colors[s1][1];
	//		b = colorGenerator.colors[s1][2];
	//		newColorA.setRgbF(r, g, b);
	//		r = colorGenerator.colors[s2][0];
	//		g = colorGenerator.colors[s2][1];
	//		b = colorGenerator.colors[s2][2];
	//		newColorB.setRgbF(r, g, b);

	//		TexturesData[5].setPixelColor(QPoint(i, j), newColorA);
	//		TexturesData[4].setPixelColor(QPoint(i, j), newColorB);
	//	}
	//}

	for (QOpenGLTexture* t : Textures)
	{
		if (t)
		{
			delete t;
		}
	}
	//if (Textures[0])
	//	delete Textures[0];
	Textures[0] = new QOpenGLTexture(TexturesData[0].mirrored(false, false));
	//if (Textures[1])
	//	delete Textures[1];
	Textures[1] = new QOpenGLTexture(TexturesData[1].mirrored(true, false));
	//if (Textures[2])
	//	delete Textures[2];
	Textures[2] = new QOpenGLTexture(TexturesData[2].mirrored(true, false));
	//if (Textures[3])
	//	delete Textures[3];
	Textures[3] = new QOpenGLTexture(TexturesData[3].mirrored(false, false));
	//if (Textures[4])
	//	delete Textures[4];
	Textures[4] = new QOpenGLTexture(TexturesData[4].mirrored(false, true));
	//if (Textures[5])
	//	delete Textures[5];
	Textures[5] = new QOpenGLTexture(TexturesData[5].mirrored(false, false));
}

void QGLRender::updateCells()
{
	int m = ca->getSize()[0],
		n = ca->getSize()[1],
		o = ca->getSize()[2];
	position.clear();
	color.clear();

#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(static) //nowait
			for (int k = 0; k < o; k++)
			{
				unsigned int state = this->ca->getCells()[i][j][k];
				if (hidenGrains.indexOf(state) == -1)
				{
					if ((i == 0) || (j == 0) || (k == 0) ||
						(i == n - 1) || (j == m - 1) || (k == o - 1) || shouldDrawCell(i, j, k))
					{
						//color.push_back(QVector3D(0.5, 0.5, 0.5));
						if (bShowGrains && (state <= ca->nucleons_count))
						{
							#pragma omp critical
							{
								position.push_back(QVector3D(i, j, k));
								color.push_back(QVector3D(this->colorGenerator.colors[state][0],
									this->colorGenerator.colors[state][1],
									this->colorGenerator.colors[state][2]));
							}
						}
						else if(state > ca->nucleons_count)
						{
							state += 500 * 500 / 2;
							#pragma omp critical
							{
								position.push_back(QVector3D(i, j, k));
								color.push_back(QVector3D(this->colorGenerator.colors[state][0],
									this->colorGenerator.colors[state][1],
									this->colorGenerator.colors[state][2]));
							}
						}
					}
					//else if (shouldDrawCell(i, j, k))
					//{
					//	//color.push_back(QVector3D(0.5, 0.5, 0.5));
					//	unsigned int state = this->ca->getCells()[i][j][k];
					//	if (state <= ca->nucleons_count)
					//	{
					//		#pragma omp critical
					//		{

					//		}
					//		position.push_back(QVector3D(i, j, k));
					//		color.push_back(QVector3D(this->colorGenerator.colors[state][0],
					//			this->colorGenerator.colors[state][1],
					//			this->colorGenerator.colors[state][2]));
					//	}
					//	else if (bShowGrainBoundaries)
					//	{
					//		state += 500 * 500 / 2;
					//		#pragma omp critical
					//		{

					//		}
					//		position.push_back(QVector3D(i, j, k));
					//		color.push_back(QVector3D(this->colorGenerator.colors[state][0],
					//			this->colorGenerator.colors[state][1],
					//			this->colorGenerator.colors[state][2]));
					//	}
					//}
				}
			}
		}
	}
//#pragma omp barrier
	colorVBO.bind();
	colorVBO.allocate(color.constData(), sizeof(color[0]) * color.size());
	colorVBO.release();
	//

	offsetVBO.bind();
	offsetVBO.allocate(position.constData(), sizeof(position[0]) * position.size());
	offsetVBO.release();
}

void QGLRender::updateView()
{
	float	center_x = static_cast<float>(ca->getSize()[0] / 2),
			center_y = static_cast<float>(ca->getSize()[1] / 2),
			center_z = static_cast<float>(ca->getSize()[2] / 2);

	float max = center_x;
	if (max > center_y) max = center_y;
	if (max > center_z) max = center_z;
	if (max < 1.f) max = 1;
	max *= 5;
	float r = max * ((static_cast<float>(scale) / 100.f));
	//if (r < max) r = max;

	float camX = r * qCos(qDegreesToRadians(betaRotation)) * qCos(qDegreesToRadians(alpthaRotation));
	float camY = r * qCos(qDegreesToRadians(betaRotation)) * qSin(qDegreesToRadians(alpthaRotation));
	float camZ = r * qSin(qDegreesToRadians(betaRotation));

	QVector3D v1 = QVector3D(center_x + camX, center_y + camY, center_z + camZ);
	QVector3D v2 = QVector3D(center_x, center_y, center_z);
	QVector3D v3 = QVector3D(0.0f, 0.0f, 1.0f);

	lightPosition = v1;

	view = QMatrix4x4();
	view.lookAt(v1, v2, v3);
}

//void QGLUpdateThread::run()
//{
//}
