#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window ;
    QGridLayout grid;
    QPushButton *button[29];
    QString s;

    for(int i=0; i<30; i++){
        s = QString::number(i+1);
        button[i] = new QPushButton(s);
        grid.addWidget(button[i],i%5,i%6);

    }
    window.setLayout(&grid);
    window.show();
    return app.exec();
}
