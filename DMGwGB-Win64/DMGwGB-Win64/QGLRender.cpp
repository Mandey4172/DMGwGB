#include "QGLRender.h"
#include <omp.h>
#include <iostream>

#include <QVector>
#include <QMath.h>
#include <QMouseEvent>
#include <QImage>

struct Point
{
	Point() : Point(0.0f, 0.0f, 0.0f) {};
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
	lightPosition = QVector3D(-100, 0, 0);
	ca = std::make_shared<CellularAutomataSpace>(100, 100, 100);
	//for (int i = 0; i < 6; i++)
	//	Textures[i] = nullptr;
}

QGLRender::~QGLRender()
{
}

void QGLRender::setCA(const std::shared_ptr<CellularAutomataSpace> new_ca)
{
	ca = new_ca;
	//updateTextures();
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
	hidenGrains = hidenGrains;
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
	if (!((scale <= 0) && (event->delta() < 0)) && !((scale >= 200) && (event->delta() > 0)))
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


	// Budowa i kompilacja shader�w
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

	projection.perspective(45.0f, (GLfloat)width() / height(), 0.1f, 100000.0f);
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
	OpenGL.glViewport(0, 0, w, h);
	projection = QMatrix4x4();
	projection.perspective(45.0f, (GLfloat)w / h, 0.1f, 100000.0f);
}

void QGLRender::paintGL()
{
	//// render
	//// ------
	OpenGL.glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	OpenGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	int m = static_cast<int>(ca->getSizeOnXAxis()),
		n = static_cast<int>(ca->getSizeOnYAxis()),
		o = static_cast<int>(ca->getSizeOnZAxis());

	unsigned int state = ca->getCells()[x][y][z];

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (current_x >= 0 && current_x < m)
		{
			for (int j = -1; j <= 1; j++)
			{
				int current_y = y + j;
				if (current_y >= 0 && current_y < n)
				{
					for (int k = -1; k <= 1; k++)
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

void QGLRender::updateCells()
{
	int m = static_cast<int>(ca->getSizeOnXAxis()),
		n = static_cast<int>(ca->getSizeOnYAxis()),
		o = static_cast<int>(ca->getSizeOnZAxis());

	position.clear();
	color.clear();

	#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				unsigned int state = ca->getCells()[i][j][k];
				if (hidenGrains.indexOf(state) == -1)
				{
					if ((i == 0) || (j == 0) || (k == 0) ||
						(i == n - 1) || (j == m - 1) || (k == o - 1) ||
						shouldDrawCell(i, j, k))
					{
						if (bShowGrains && (state <= ca->getNucleonsCount()))
						{
							#pragma omp critical
							{
								position.push_back(QVector3D(i, j, k));
								//color.push_back(QVector3D(	colorGenerator.getColor(state)[0],
								//							colorGenerator.getColor(state)[1],
								//							colorGenerator.getColor(state)[2]));

								color.push_back(QVector3D(	colorGenerator.colors[state][0],
															colorGenerator.colors[state][1],
															colorGenerator.colors[state][2]));
							}
						}
						else if (state > ca->getNucleonsCount())
						{
							state += 500 * 500 / 2;
							#pragma omp critical
							{
								position.push_back(QVector3D(i, j, k));
								//color.push_back(QVector3D(	colorGenerator.getColor(state)[0],
								//							colorGenerator.getColor(state)[1],
								//							colorGenerator.getColor(state)[2]));
								color.push_back(QVector3D(colorGenerator.colors[state][0],
									colorGenerator.colors[state][1],
									colorGenerator.colors[state][2]));

							}
						}
					}
				}
			}
		}
	}
	#pragma omp barrier
	colorVBO.bind();
	colorVBO.allocate(color.constData(), sizeof(color[0]) * color.size());
	colorVBO.release();

	offsetVBO.bind();
	offsetVBO.allocate(position.constData(), sizeof(position[0]) * position.size());
	offsetVBO.release();
}

void QGLRender::updateView()
{
	float	center_x = static_cast<float>(ca->getSizeOnXAxis() / 2),
			center_y = static_cast<float>(ca->getSizeOnYAxis() / 2),
			center_z = static_cast<float>(ca->getSizeOnZAxis() / 2);

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