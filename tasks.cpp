#include "tasks.h"
#include "mainwindow.h"
struct Task_object
{
    enum Styles
    {
        Normal,
        MoonLight
    };

    Task_object()=delete;

    Task_object(QString text,int time_s, QRect Size, Styles type, QWidget *parrent=nullptr)
    {
        Main_Container->setParent(parrent);
        Time_Container->setParent(parrent);
        Name_Container->setParent(parrent);

        Main_Container->setGeometry(Size);
        Name_Container->setText(text);
        time = time_s;
        Time_Container->setText(QString::number(time)+" мин");

        Time_Container->setStyleSheet("background: green");
        Main_Container->setStyleSheet("background: red");
        Name_Container->setStyleSheet("background: yellow");

        Sinhro_Contrainers();

        switch (type) {

        case Normal:

        break;

        case MoonLight:

        break;

        default: break;

        }
    }

    ~Task_object()
    {
        delete Main_Container;
        delete Time_Container;
        delete Name_Container;
        Main_Container=nullptr;
        Time_Container=nullptr;
        Name_Container=nullptr;
    }

 private:
    QLabel* Main_Container = new QLabel();
    QLabel* Time_Container = new QLabel();
    QLabel* Name_Container = new QLabel();
    int time; // using seconds

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
    }
};
