#ifndef  _GL_WIDGET_H_
#define  _GL_WIDGET_H_

#include "CCDirector.h"
#include "CCCommon.h"

#include <QtOpenGL/QGLWidget>
#include <QTimer>

USING_NS_CC;

class CC_DLL GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

    typedef void(*PTRFUN_MOUSE)(QMouseEvent *event);
    typedef void(*PTRFUNC_RESIZE)(QResizeEvent *event);

    QBasicTimer pTimer;

//    QTimer pResizeTimer;

public:
    GLWidget(QWidget *parent = 0, int width = 800, int height = 600, CCDirector* director = NULL);

    void setMouseMoveFunc(PTRFUN_MOUSE func);
    void setMousePressFunc(PTRFUN_MOUSE func);
    void setMouseReleaseFunc(PTRFUN_MOUSE func);
    void setViewResizeFunc(PTRFUNC_RESIZE func);

    void startUpdate();
    void stopUpdate();

    bool isReadyToDelete;

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    void timerEvent(QTimerEvent *e);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    virtual void resizeEvent(QResizeEvent *);

    virtual void showEvent(QShowEvent *);

signals:
    void didShowed(GLWidget* widget);
    void mouseMoveSignal(QMouseEvent *event);
    void mousePressSignal(QMouseEvent *event);
    void mouseReleaseSignal(QMouseEvent *event);

private:
    PTRFUN_MOUSE mouseMoveFunc;
    PTRFUN_MOUSE mousePressFunc;
    PTRFUN_MOUSE mouseReleaseFunc;
    PTRFUNC_RESIZE viewResizeFunc;

    CCDirector* m_director;
};

#endif // _GL_WIDGET_H_
