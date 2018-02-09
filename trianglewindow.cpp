#include "trianglewindow.h"

#include <QScreen>
#include <QKeyEvent>

TriangleWindow::TriangleWindow()
    : m_program(nullptr)
    , m_frame(0)
    , m_speed(1)
{
}

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/sh_triangle.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/sh_triangle.frag");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(m_speed * 100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    float z = 0.5f * std::sin(m_frame / screen()->refreshRate());

    GLfloat vertices[] = {
        0.0f, 0.707f, z,
        -0.5f, -0.5f, -z,
        0.5f, -0.5f, 0.0f
    };

    GLfloat colors[] {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}

void TriangleWindow::keyPressEvent(QKeyEvent* e)
{
    if (e->text() == "q")
        close();
    else if (e->text() == "+")
        ++m_speed;
    else if (e->text() == "-")
        --m_speed;
    else QWindow::keyPressEvent(e);
}
