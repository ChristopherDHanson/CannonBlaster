#include "questionlister.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuestionLister w;
    w.show();

    return a.exec();
}
