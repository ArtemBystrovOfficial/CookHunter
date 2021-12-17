#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <taskobject.h>
#include <vector>
#include "tasks.h"
#include <QInputDialog>
#include <string>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Task_object
{

    void MoonLight_Style();
    void Normal_Style();
    void Normal_Style_For_Complete();

    enum Styles
    {
        Normal_Complete,
        Normal,
        MoonLight
    };

     //Constructors

     Task_object()=delete;

     Task_object(QString text,int time_s, QRect Size, Styles type, QWidget *parrent=nullptr)
    {
        Main_Container->setParent(parrent);
        Time_Container->setParent(parrent);
        Name_Container->setParent(parrent);
        Time_Line->setParent(parrent);

        Main_Container->show();
        Time_Line->show();
        Time_Container->show();
        Name_Container->show();

        Main_Container->setGeometry(Size);
        Name_Container->setText(text);
        time_begin = time_s;
        time_this=time_begin;
        Time_Container->setText(QString::number(time_begin)+" мин");

        Time_Line->setStyleSheet("background: rgb(0,255,0);");
        Time_Line->resize(Main_Container->width(),4);

        Sinhro_Contrainers();
        setStyle(type);
     }

    ~Task_object()
    {
        delete Main_Container;
        delete Time_Container;
        delete Name_Container;
        delete Time_Line;
        Main_Container=nullptr;
        Time_Container=nullptr;
        Name_Container=nullptr;
        Time_Line=nullptr;
    }

     // Functions
    void setStyle(Styles type)
    {
        switch ( type )
        {
          case Normal:
               Normal_Style();
            break;
          case MoonLight:
               MoonLight_Style();
            break;
          case Normal_Complete:
               Normal_Style_For_Complete();
            break;
         }

     }

    void Visibility(int value)
    {
        Main_Container->setStyleSheet("background-color: rgba(102,94,97,0."+QString::number(value)+");");
        Name_Container->setStyleSheet("background: rgba(171,167,154,0."+QString::number(value)+");");
        Time_Container->setStyleSheet("background: rgba(32,232,14,0."+QString::number(value)+");");
    }

    void setPause(bool value)
    {
        if(value)
        {
            Main_Container->setStyleSheet("background:rgba(255,255,255,0.25);");
            Time_Container->setStyleSheet("background:rgba(255,255,255,0.3);");
            Name_Container->setStyleSheet("background:rgba(255,255,255,0.4);");
        }
        else
        {
           setStyle(Active_Style());
        }
    }

    Styles Active_Style();

    bool Next_Second()
    {
        time_this--;

        time_this<60?
                    Time_Container->setText(QString::number(time_this) + " секунд"):
                    Time_Container->setText(QString::number(time_this/60) + " мин" +QString::number(time_this%60) + " сек");
        Time_Line_Move();
        if(time_this==0) return 1; else return 0;

    }

    void MoveYAbsolute(int value)
    {
        Main_Container->setGeometry(Main_Container->x(),value,Main_Container->width(),Main_Container->height());
        Sinhro_Contrainers();
    }

    void setComplete()
    {
        Main_Container->setStyleSheet("background : green;");
        Main_Container->resize(Main_Container->width(),int(Main_Container->height()*0.7));
    }

    void MoveY(int value)
    {
        Main_Container->setGeometry(Main_Container->x(),Main_Container->y()+value,Main_Container->width(),Main_Container->height());
        Sinhro_Contrainers();
    }

 private:

    // Functions -> private
    void Time_Line_Move()
    {
      //  Time_Container->setText(QString::number(int((float(time_this)/time_begin)*float(Main_Container->width()))));
        float kof_time=float(time_this)/time_begin;
        Time_Line->resize(int(kof_time*Main_Container->width()),Time_Line->height());
        if(kof_time>0.5)
        Time_Line->setStyleSheet("background : rgb(" + QString::number(int(255*((1.0-kof_time)*2)))
                                 +","+  QString::number(255) + ",0);");
        else
        Time_Line->setStyleSheet("background : rgb(" + QString::number(255)
                                 +","+  QString::number(255*kof_time*2) + ",0);");
    }

    void Sinhro_Contrainers()
    {


        int Height_Time_Container=int(Main_Container->height()*0.3);
        int Width_Time_Container=int(Main_Container->width()*0.3);

        int Height_Name_Container=int(Main_Container->height()*0.4);
        int Width_Name_Container=int(Main_Container->width()*0.5);
        int Space_Beetween = Main_Container->width()*(1-0.5-0.3-0.07*2);

        Name_Container->setGeometry(int(Main_Container->x()+Main_Container->width()*0.07),
                                    int(Main_Container->y()+Main_Container->height()*0.3),
                                    Width_Name_Container,
                                    Height_Name_Container);

        Time_Container->setGeometry(int(Main_Container->x()+Main_Container->width()*0.07+Width_Name_Container+Space_Beetween),
                                    int(Main_Container->y()+Main_Container->height()*0.4),
                                    Width_Time_Container,
                                    Height_Time_Container);

        Time_Line->setGeometry(Main_Container->x(),Main_Container->y()+Main_Container->height()-4,Time_Line->width(),4);
    }

protected:

    // All elements;
    QLabel* Time_Line = new QLabel();
    QLabel* Main_Container = new QLabel();
    QLabel* Time_Container = new QLabel();
    QLabel* Name_Container = new QLabel();
    int time_begin; // using seconds
    int time_this;
};

class MainWindow : public QMainWindow
{
    friend Taskobject;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     std::vector < Task_object* > Tasks;
     std::vector < Task_object* > Tasks_complite;
public slots:
    void Start();
    void Add();
    void timerEvent(QTimerEvent *event);
    void Tasks_Move_up(int index);
    void Complete_Tasks_Move_Down();
    void setStyles();
    void setBackround(QColor color);
private slots:
    void on_AddButton_clicked();

    void on_EditButton_clicked();

    void on_InfoButton_clicked();

    void on_PauseButton_clicked();

    void on_SwitchStyles_clicked();

private:
    Ui::MainWindow *ui;
    int m_timerId;
    int Task_Height=60;
    int Task_Width=300;
    bool Pause = true;

};

#endif // MAINWINDOW_H
