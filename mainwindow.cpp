#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>

float lr = 0.01;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int layers[] = {2,3,1};
    network = new NeuralNetwork(layers,3,1);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    network->deleteNetwork();
    delete  network;
    delete ui;
}

QPoint MainWindow::resultToPoint(QPoint point)
{


    point.setY((this->height() - point.y()));
    point.setX(point.x());
    return point;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Z)
    {
        lr *=2;
    }
    if( event->key() == Qt::Key_S)
    {
        lr /=2;
    }
    if( event->key() == Qt::Key_Space)
    {
        for (int i = 0; i < 50 ; i++ ) {
            int x = rand()%1001 - 500;
            int y = rand()%1001 - 500;
            lstPoints.push_back(QPoint(x,y));

        }
        repaint();

    }
    if( event->key() == Qt::Key_T)
    {
        lstAnswer.clear();
        vector<float> errorAverage;
        errorAverage.push_back(0);
        for(QPoint p: lstPoints)
        {
            vector<vector<float>> inputs;
            vector<float> temp;
            QPoint max = getMax(lstPoints);
            QPoint min = getMin(lstPoints);
            temp.push_back(((float)p.x() - min.x()) / ((float)max.x() - min.x()));
            inputs.push_back(temp);
            temp.clear();
            temp.push_back((((float)p.y() - min.y())) / ((float)max.y() - min.y()));
            inputs.push_back(temp);

            int goodAnswer = 0;

            if(p.y() > funct(p.x()) )
            {
                goodAnswer = 1;
            }


            int giveAnswer = 0;
            vector<float> networkAnswer = network->propagation(inputs);
            if(networkAnswer[0] > 0.5)
            {
                giveAnswer = 1;
            }

            if(giveAnswer == goodAnswer)
            {
                lstAnswer.push_back(p);
            }
            else
            {
                errorAverage[0] += (networkAnswer[0] - goodAnswer);
            }






        }
        errorAverage[0] /= lstPoints.count()- lstAnswer.count();
        vector<float> err;
        err.push_back((errorAverage[0]));
        network->trainNetwork(err,lr);
        qDebug() << errorAverage[0] << endl;


        repaint();

    }
    qDebug()<< "------------------------------------------------------------------" << endl;

}



int MainWindow::funct(int x)
{
    return 0.05*x*x;
}

QPoint MainWindow::getMax(QList<QPoint> lstPoints)
{
    if (lstPoints.count() > 0)
    {
        int xMax = lstPoints.begin()->x();
        int yMax = lstPoints.begin()->y();
        for (QPoint p:lstPoints)
        {
            if(xMax < p.x())
            {
                xMax = p.x();
            }
            if(yMax < p.y())
            {
                yMax = p.y();
            }
        }

        return QPoint(xMax,yMax);
    }
    else
    {
        return QPoint(0,0);
    }

}

QPoint MainWindow::getMin(QList<QPoint> lstPoints)
{
    if (lstPoints.count() > 0)
    {
        int xMin = lstPoints.begin()->x();
        int yMin = lstPoints.begin()->y();
        for (QPoint p:lstPoints)
        {
            if(xMin > p.x())
            {
                xMin = p.x();
            }
            if(yMin > p.y())
            {
                yMin = p.y();
            }
        }

        return QPoint(xMin,yMin);
    }
    else
    {
        return QPoint(0,0);
    }

}

void MainWindow::paintEvent(QPaintEvent *paintEvent)
{
        QPainter * painter = new QPainter(this);
        QBrush bad = QBrush(Qt::red,Qt::SolidPattern);
        QBrush valid = QBrush(Qt::green,Qt::SolidPattern);

        QPoint max = getMax(lstPoints);
        QPoint min = getMin(lstPoints);
        QPoint substract = max - min;
        for(QPoint p:lstPoints)
        {
            painter->setBrush(bad);
            for(QPoint pAnswer:lstAnswer)
            {
                if(p.x() == pAnswer.x() && p.y() == pAnswer.y())
                {
                    painter->setBrush(valid);
                }
            }
            double ratioX = geometry().width()* (p.x()-min.x()) / substract.x();
            double ratioY = geometry().height()* (p.y()-min.y()) / substract.y();
            painter->drawEllipse(ratioX,geometry().height()-ratioY,7,7);
        }

        painter->end();
        delete  painter;
}


