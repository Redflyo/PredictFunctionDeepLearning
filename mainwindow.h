#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include "neuralnetwork.h"
#include <vector>
#include <QEvent>
#include <QPainter>
#include <QKeyEvent>
#include <list>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint resultToPoint(QPoint point);
    void keyReleaseEvent(QKeyEvent *event);
    int funct(int x);
    ///
    /// \brief getMax
    /// \return X and Y max
    ///
    QPoint getMax(QList<QPoint> lstPoints);
    QPoint getMin(QList<QPoint> lstPoints);
    void paintEvent(QPaintEvent * paintEvent);

private:
    NeuralNetwork * network ;
    Ui::MainWindow *ui;
    QList<QPoint> lstPoints;
    QList<QPoint> lstAnswer;
};
#endif // MAINWINDOW_H
