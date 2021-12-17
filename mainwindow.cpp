#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Start();
    setStyles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Start()
{
    m_timerId = startTimer(1000);
    ui->EditButton->setEnabled(false);
     ui->Pause->setEnabled(false);
     ui->ShadowPause->setHidden(true);
     ui->Pause->setHidden(true);
}

Task_object::Styles styles=Task_object::Normal;

void MainWindow::Add()
{
    QRect cord;
    cord.setRect(0,100+Tasks.size()*Task_Height,Task_Width,Task_Height);
    Task_object *one = new Task_object(
                QInputDialog::getText(this,"Название","Название задачи",QLineEdit::Normal)
               ,std::stoi(QInputDialog::getText(this,"Время","Количество минут",QLineEdit::Normal).toStdString())*60,cord,styles,this);
    Tasks.push_back(one);
}

void MainWindow::on_AddButton_clicked()
{
        Add();
        if(Tasks.size()>8)ui->AddButton->setEnabled(false);
        ui->EditButton->setEnabled(true);
}

void MainWindow::Tasks_Move_up(int index)
{
    for(int i=index;i<Tasks.size();i++)
    {
        Tasks[i]->MoveY(-Task_Height);
    }
}

void MainWindow::Complete_Tasks_Move_Down()
{
   Tasks_complite[Tasks_complite.size()-1]->MoveYAbsolute(650);

   if(Tasks_complite.size()>3){
   delete Tasks_complite[0];
   Tasks_complite[0]=nullptr;
   Tasks_complite.erase(Tasks_complite.begin()+0);}

    for(int i=Tasks_complite.size()-1;i>=0;i--)
    {
        switch(i){
        case 2:
            Tasks_complite[i]->Visibility(8);
            break;
        case 1:
            Tasks_complite[i]->Visibility(5);
            break;
        case 0:
            Tasks_complite[i]->Visibility(2);
            break;
        }

        Tasks_complite[i]->MoveY(int(Task_Height*0.7));
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if ( event->timerId() == m_timerId && Pause )
    {
         for(int i=0;i<Tasks.size();i++)
         {
             if(Tasks[i]->Next_Second())
             {

                 Tasks[i]->setComplete();
                 Tasks[i]->setStyle(Task_object::Styles::Normal_Complete);
                 Tasks_complite.push_back(Tasks[i]);
                 Complete_Tasks_Move_Down();
                 Tasks.erase(Tasks.begin()+i);
                 Tasks_Move_up(i);
                 ui->AddButton->setEnabled(true);
             }
         }
    }

}

void MainWindow::on_EditButton_clicked()
{
    delete Tasks[Tasks.size()-1];
    Tasks[Tasks.size()-1]=nullptr;
    Tasks.erase(Tasks.begin()+Tasks.size()-1);

    ui->AddButton->setEnabled(true);
    if(Tasks.size()==0)ui->EditButton->setEnabled(false);
}

void MainWindow::on_InfoButton_clicked()
{
    QLabel *Help = new QLabel;
    Help->setGeometry(0,0,400,500);
    Help->show();
}

void MainWindow::on_PauseButton_clicked()
{
    Pause?Pause=false:Pause=true;
    if(!Pause)
    {
        // активация
        for(int i=0;i<Tasks.size();i++)
        {
           Tasks[i]->setPause(true);
        }
        ui->SwitchStyles->setEnabled(false);
        ui->Pause->setHidden(false);
        ui->AddButton->setEnabled(false);
        ui->EditButton->setHidden(true);
        ui->ShadowPause->setHidden(false);
    }
    else
    {
        // выключение
        for(int i=0;i<Tasks.size();i++)
        {
           Tasks[i]->setPause(false);
        }
        ui->SwitchStyles->setEnabled(true);
        ui->Pause->setHidden(true);
        ui->AddButton->setEnabled(true);
        ui->EditButton->setHidden(false);
        ui->ShadowPause->setHidden(true);
    }
}

void MainWindow::on_SwitchStyles_clicked()
{
   QColor bgcolor;
    if(styles==Task_object::Styles::Normal)
    {
        bgcolor.setRgb(43, 0, 61);

        styles=Task_object::Styles::MoonLight;
        for(int i=0;i<Tasks.size();i++)
        {
            Tasks[i]->setStyle(Task_object::Styles::MoonLight);
        }
    }
    else
    {

        bgcolor.setRgb(73, 77, 69);
        styles=Task_object::Styles::Normal;
        for(int i=0;i<Tasks.size();i++)
        {
            Tasks[i]->setStyle(Task_object::Styles::Normal);
        }
    }
    MainWindow::setBackround(bgcolor);
}

Task_object::Styles Task_object::Active_Style()
{
   return styles;
}

void Task_object::Normal_Style()
{
    Main_Container->setStyleSheet("background: #BED8D4;""border-radius:10px;");
    Name_Container->setStyleSheet("background: #F7F9F9;""color:rgba(0,0,0,0.7);""border-radius:10px;""font-family:sans-serif;""font-weight:700;");
    Name_Container->setAlignment(Qt::AlignCenter);
    Time_Container->setStyleSheet("background: #F7F9D9;""color:rgba(0,0,0,0.7);""border-radius:10px;""font-family:sans-serif;""font-weight:700;");
}

void Task_object::Normal_Style_For_Complete()
{
    Main_Container->setStyleSheet("background: #665e61;");
    Name_Container->setStyleSheet("background: #aba79a;""color:black");
    Name_Container->setAlignment(Qt::AlignCenter);
    Time_Container->setStyleSheet("background: #20e80e;""color:black");
    Time_Container->setText("Complete");
    Time_Container->setAlignment(Qt::AlignCenter);
}

void Task_object::MoonLight_Style()
{
    Main_Container->setStyleSheet("background: #133C55;""border-radius:10px;");
    Name_Container->setStyleSheet("background: #386FA4;""color:white;""border-radius:10px;""font-family:sans-serif;""font-weight:700;");
    Name_Container->setAlignment(Qt::AlignCenter);
    Time_Container->setStyleSheet("background: #59A5D0;""color:black;""border-radius:10px;""font-family:sans-serif;""font-weight:700;");

}

void MainWindow::setBackround(QColor color)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, color);
    this->setPalette(palette);
}

void MainWindow::setStyles()
{
    QColor color;
    color.setRgb(73, 77, 69);
    MainWindow::setBackround(color);
    ui->AddButton->setStyleSheet("background: url(Img/button_1.png);\nborder-radius:10px;"); // кнопка добавить
    ui->EditButton->setStyleSheet("background: url(Img/button_2.png);\nborder-radius:10px;"); //- кнопка назад
    ui->SwitchStyles->setStyleSheet("background: url(Img/button_3.png);\nborder-radius:10px;"); //- кнопка назад
    ui->PauseButton->setStyleSheet(""); //- кнопка паузы
}

