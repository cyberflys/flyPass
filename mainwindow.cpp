#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtGui>
#include <QtWidgets>
#include <QTextEdit>
#include <QLineEdit>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shes.cpp"
#include <dirent.h>
#include <unistd.h>
#include <QDialog>
#include <vector>
#include <QVBoxLayout>


QLineEdit *loginpass;
QLineEdit *createpass;
QPushButton *createbtn;
QPushButton *add;
QPushButton *passwords;
QPushButton *changekey;
QPushButton *support;
QPushButton *about;
QLabel *welcome;
QPushButton *loginbtn;
QLabel *addlab;
QPushButton *deletepass;
QLineEdit *filetodelete;
QPushButton *deletefile;

QPushButton *savepassword;
QLineEdit *passentry;
QLineEdit *servicename;
QLineEdit *newkey;
QPushButton *savenewkey;
QPushButton *back;
QPushButton *revert;
QTextEdit *passlist;
QPushButton *lab[9];

QVBoxLayout *lay;
std::string theone;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("fleonPass");




    passwords= new QPushButton("Passwords",this);
    passwords->resize(150,50);

    passwords->move(20,160);
    passwords->setStyleSheet("border:none;");
    connect(passwords,&QPushButton::clicked,this,&MainWindow::showallpass);


    changekey = new QPushButton("Change Key",this);
    changekey->resize(150,50);
    changekey->setStyleSheet("border:none;");
    changekey->move(20,220);
    connect(changekey,&QPushButton::clicked,this,&MainWindow::chgkey);

    support = new QPushButton("Support",this);
    support->resize(150,50);
    support->move(20,280);
    support->setStyleSheet("border:none;");
    connect(support,&QPushButton::clicked,this,&MainWindow::supp);
    about = new QPushButton("About",this);
    about->resize(150,50);
    about->move(20,340);
    about->setStyleSheet("border:none;");
    connect(about,&QPushButton::clicked,this,&MainWindow::aboutpage);

    welcome = new QLabel("fleonPass",this);
    welcome->setFont(QFont("Arial",60));
    welcome->resize(400,200);
    welcome->move(360,0);

    addlab = new QLabel("Add new Password",this);
    addlab->setFont(QFont("Arial",20));
    addlab->resize(400,200);
    addlab->move(410,50);

    add = new QPushButton("+",this);
    add->resize(40,50);
    add->move(475,200);
    add->setStyleSheet("border:none;");
    connect(add,&QPushButton::clicked,this,&MainWindow::passwordz);



    add->hide();
    addlab->hide();
    welcome->hide();
    about->hide();
    support->hide();
    changekey->hide();
    passwords->hide();
    loginpass = new QLineEdit(this);
    loginpass->resize(200,50);
    loginpass->move(150,130);

    loginbtn = new QPushButton("Login",this);
    loginbtn->resize(70,50);
    loginbtn->move(210,190);


    connect(loginbtn,&QPushButton::clicked,this,&MainWindow::logincheck);
    this->setFixedSize(500,300);
    this->setStyleSheet("background-image: url(:/images/login.png);");
    fstream check("key.key");
    std::string om;
    std::string zoom;
    while(check>>zoom){
        om+=zoom;
    }
    qDebug()<<"KEYZ:"<<om.c_str();
    std::string ol="";
    if(om==ol){
        add->hide();
        addlab->hide();
        welcome->hide();
        about->hide();
        support->hide();
        changekey->hide();
        passwords->hide();
        loginpass->hide();
        loginbtn->hide();
        createpass = new QLineEdit(this);
        createpass->resize(200,50);
        createpass->move(145,90);
        createpass->show();

        createpass->setPlaceholderText("Enter your new key (16 length).");

        createbtn = new QPushButton("Create",this);
        createbtn->resize(70,50);
        createbtn->move(210,160);
        createbtn->show();
        connect(createbtn,&QPushButton::clicked,this,&MainWindow::createkey);
        this->setFixedSize(500,300);
    }

}

void MainWindow::createkey(){
    std::string text = createpass->text().toStdString();
    SHES shes = SHES();
    std::string encr = shes.encryptKey(text);
    std::ofstream zo("key.key");
    if(zo.is_open()){
       zo<<encr;
    }
    zo.close();
    add->show();

    about->show();
    support->show();
    changekey->show();
    passwords->show();
    loginpass->hide();
    loginbtn->hide();
    createpass->hide();
    createbtn->hide();
    this->setFixedSize(1000,600);
}
void MainWindow::chgkey(){
    add->hide();
    addlab->hide();
    welcome->hide();
    about->hide();
    support->hide();
    changekey->hide();
    passwords->hide();

    newkey = new QLineEdit(this);
    newkey->setPlaceholderText("New Key (Needs to be 14 length)");
    newkey->resize(250,50);
    newkey->move(370,200);
    newkey->show();
    savenewkey = new QPushButton("Save",this);
    savenewkey->resize(125,30);
    savenewkey->move(430,270);
    savenewkey->show();

    this->setStyleSheet("background-image: url(:/images/back.png);");
    connect(savenewkey,&QPushButton::clicked,this,&MainWindow::chkeyz);




}
void MainWindow::chkeyz(){
    std::string keyval = newkey->text().toStdString();
    if(keyval.length() ==15){
        ofstream key("key.key");
        SHES shes = SHES();
        std::string fals = shes.encryptKey(keyval);
        if(key.is_open()){
            key<<fals;
        }
        key.close();
        qDebug()<<"Key written.";
        add->show();
        this->setStyleSheet("background-image: url(:/images/main.png);");
        newkey->hide();

        about->show();
        support->show();
        changekey->show();
        passwords->show();
        savenewkey->hide();


    }else{
       newkey->setText("Length needs to be 15");
    }
}
void MainWindow::homescr(){
    add->show();

    about->show();
    support->show();
    changekey->show();
    deletepass->hide();
    passwords->show();
    revert->hide();
    char buffer[100];

    std::string cwd = getcwd(buffer,sizeof(buffer));
    struct dirent *tm;
    DIR *dir;
    int size;
    if((dir = opendir(cwd.c_str())) != NULL){
        while((tm =readdir(dir)) != NULL){
            std::string files = tm->d_name;
            if(files.find("key.key") != std::string::npos){
                qDebug()<<"not saving key.";
            }
            else if(files.find("c3958") != std::string::npos){
                qDebug()<<"Not saving garbage.";
            }
            else if(files.find(".") != std::string::npos){
                qDebug()<<"Definitely not a platform";
            }
            else if(files.find("DS_Store") != std::string::npos){
                qDebug()<<"Skipping this shit.";
            }
            else if(files.find("images") != std::string::npos){
                qDebug()<<"Skipping this shit.";
            }
            else{
                size+=1;

            }

        }
    }
    for(int i=0;i<size;i++){
        lab[i]->hide();
    }

    this->setStyleSheet("background-image: url(:/images/main.png);");

}
void MainWindow::openpop(std::string comb){

    //std::string comb =lab[i]->text().toStdString();
    QDialog *dial = new QDialog(this);
    QLabel *leb = new QLabel(comb.c_str(),dial);
    leb->resize(350,100);
    leb->move(0,0);
    leb->show();

    leb->setFont(QFont("Arial",20));
    dial->setFixedSize(350,100);
    dial->setWindowTitle("Password");
    dial->exec();
}

void MainWindow::showallpass(){
        add->hide();
        addlab->hide();
        welcome->hide();
        about->hide();
        passwords->hide();
        support->hide();
        changekey->hide();
        this->setStyleSheet("background-image: url(:/images/back.png);");
        revert = new QPushButton("Back",this);
        revert->resize(150,50);
        revert->move(10,520);
        deletepass = new QPushButton("Delete",this);
        deletepass->resize(70,50);
        deletepass->move(920,520);
        deletepass->show();

        connect(deletepass,&QPushButton::clicked,this,&MainWindow::deletetask);

        revert->show();
        connect(revert,&QPushButton::clicked,this,&MainWindow::homescr);

        //Now starts a algorithmic part of password list.
        char buffer[100];
        std::string cwd = getcwd(buffer,sizeof(buffer));
        DIR *dir;
        vector<std::string>passwordz1;

        struct dirent *tm;
        if((dir = opendir(cwd.c_str())) != NULL){
               while((tm = readdir(dir)) != NULL){
                    std::string files = tm->d_name;
                    if(files.find("key.key") != std::string::npos){
                        qDebug()<<"not saving key.";
                    }
                    else if(files.find("c3958") != std::string::npos){
                        qDebug()<<"Not saving garbage.";
                    }
                    else if(files.find("images") != std::string::npos){
                        qDebug()<<"Skipping this shit.";
                    }
                    else if(files.find(".") != std::string::npos){
                        qDebug()<<"Definitely not a platform";
                    }
                    else if(files.find("DS_Store") != std::string::npos){
                        qDebug()<<"Skipping this shit.";
                    }

                    else{
                        passwordz1.push_back(files);
                        qDebug()<<"File saved.";
                    }
               }
        }
        if(passwordz1.size() == 0 || passwordz1.size() < 0){
            qDebug()<<"shit";
            homescr();

        }
        vector<pair<std::string,std::string>>data1;

        SHES shes = SHES();
        for(int i =0;i<passwordz1.size();i++){
            std::fstream zozo(passwordz1[i]);
            string inp;
            string ready;
            while(zozo>>inp){
                ready+=inp;

            }
            string omet = shes.decrypt(ready);

            string delimiter=":";
            string token =omet.substr(0,omet.find(delimiter));
            data1.push_back({passwordz1[i],token});
        }

        int posx=40;
        int posy=160;
        for(int i=0;i<data1.size();i++){
            if(data1.size() ==0){
                homescr();
            }

            lab[i] = new QPushButton(data1[i].first.c_str(),this);
            lab[i]->resize(150,70);
            lab[i]->move(posx,posy);
            lab[i]->setStyleSheet("background-image: url(:/images/box.png);color: black;");
            lab[i]->setFont(QFont("Arial",20));
            std::string comb ="     "+data1[i].first+"\n"+"     "+data1[i].second;
            connect(lab[i], &QPushButton::clicked, [=]{
                openpop(comb);
            });
            lab[i]->show();
            posx+=200;

            if(posx >= 1050){
                posy+=120;
                posx=40;
            }

        }



}
void MainWindow::deletefilez(){
    std::string data = filetodelete->text().toStdString();
    remove(data.c_str());
    deletefile->hide();
    filetodelete->hide();
    this->setFixedSize(1000,600);


    //this->setStyleSheet("background-image: url(:/images/main.png);");
    homescr();




}
void MainWindow::deletetask(){

    add->hide();


    about->hide();
    support->hide();
    changekey->hide();
    passwords->hide();
    loginpass->hide();
    loginbtn->hide();
    this->setFixedSize(500,300);
    //this->setStyleSheet("background-image: url(:/images/main.png);");



    deletefile = new QPushButton("Delete",this);
    deletefile->resize(70,50);
    deletefile->move(210,180);
    deletefile->show();

    filetodelete= new QLineEdit(this);
    filetodelete->resize(200,50);
    filetodelete->move(145,95);
    filetodelete->show();
    std::string file1 = filetodelete->text().toStdString();
    char buffer[100];
    std::string cwd = getcwd(buffer,sizeof(buffer));
    struct dirent *tm;
    DIR *dir;
    int size;
    if((dir = opendir(cwd.c_str())) != NULL){
        while((tm =readdir(dir)) != NULL){
            std::string files = tm->d_name;
            if(files.find("key.key") != std::string::npos){
                qDebug()<<"not saving key.";
            }
            else if(files.find("c3958") != std::string::npos){
                qDebug()<<"Not saving garbage.";
            }
            else if(files.find(".") != std::string::npos){
                qDebug()<<"Definitely not a platform";
            }
            else if(files.find("images") != std::string::npos){
                qDebug()<<"Skipping this shit.";
            }
            else if(files.find("DS_Store") != std::string::npos){
                qDebug()<<"Skipping this shit.";
            }
            else{
                size+=1;

            }

        }
    }
    for(int i=0;i<size;i++){
        lab[i]->hide();
    }
    this->setStyleSheet("background-image: url(:/images/login.png);");
    connect(deletefile,&QPushButton::clicked,this,&MainWindow::deletefilez);



}
void MainWindow::supp(){
#ifdef _WIN32
    system("explorer https://github.com/suibex");
#elif __APPLE__
    system("open https://github.com/suibex");
#elif __linux__
    system("xdg-open https://github.com/suibex");

#endif
}

void MainWindow::aboutpage(){
    add->hide();
    addlab->hide();
    welcome->hide();
    about->hide();
    support->hide();

    changekey->hide();
    passwords->hide();
    loginpass->hide();
    loginbtn->hide();
    back = new QPushButton("Back",this);
    this->setStyleSheet("background-image: url(:/images/about.png);");
    back->resize(70,50);
    back->move(920,520);
    back->show();

    connect(back,&QPushButton::clicked,this,&MainWindow::backed);
}
void MainWindow::backed(){
    add->show();


    about->show();
    support->show();
    changekey->show();
    passwords->show();
    loginpass->hide();
    back->hide();
    revert->hide();
    this->setStyleSheet("background-image: url(:/images/main.png);");



}
void MainWindow::passwordz(){
    add->hide();
    addlab->hide();
    welcome->hide();
    about->hide();
    support->hide();
    changekey->hide();
    passwords->hide();
    loginpass->hide();
    loginbtn->hide();
    passentry= new QLineEdit(this);
    passentry->setPlaceholderText("Password");
    passentry->resize(250,50);
    passentry->move(370,270);
    passentry->show();

    servicename= new QLineEdit(this);
    servicename->setPlaceholderText("Name for service");
    servicename->resize(250,50);
    servicename->move(370,200);
    servicename->show();
    this->setStyleSheet("background-image: url(:/images/back.png);");

    savepassword=  new QPushButton("Save",this);
    savepassword->resize(125,30);
    savepassword->move(430,340);
    savepassword->show();

    connect(savepassword,&QPushButton::clicked,this,&MainWindow::savepass);

}

void MainWindow::savepass(){
    std::string text=passentry->text().toStdString();
    if(text.length() == 12){
        passentry->setText("Length cannot be 12.");

    }else{


        SHES shes1 =  SHES();
        std::string filename = servicename->text().toStdString();

        std::string content = shes1.encrypt(text);
        ofstream omg1(filename);
        if(omg1.is_open()){
            omg1<<content;
        }


        qDebug()<<"SAVED!";
        add->show();

        about->show();
        support->show();
        changekey->show();
        passwords->show();
        loginpass->hide();

        savepassword->hide();
        servicename->hide();
        passentry->hide();
        this->setStyleSheet("background-image: url(:/images/main.png);");


    }
}
void MainWindow::logincheck(){
    std::fstream file("/Users/gavrilo/Desktop/fleonPass/GUI/passwords/key.key");
    std::string key1;

    std::string input;
    while(file>>input){
        key1+=input;
    }
    SHES shes = SHES();
   std::string key = shes.decrypt(key1);

   QString om = key.c_str();
   qDebug()<<"KEY:"<<om;
   std::string text =loginpass->text().toStdString();

    if(text == key){
        add->show();

        about->show();
        support->show();
        changekey->show();
        passwords->show();
        loginpass->hide();
        loginbtn->hide();

        this->setStyleSheet("background-image: url(:/images/main.png);");
        this->setFixedSize(1000,600);

    }
    else{
        exit(1);

    }

}



MainWindow::~MainWindow()
{
    delete ui;
}

