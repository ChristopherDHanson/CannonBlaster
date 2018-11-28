#ifndef QUESTIONLISTER_H
#define QUESTIONLISTER_H

#include <QMainWindow>

namespace Ui {
class QuestionLister;
}

class QuestionLister : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestionLister(QWidget *parent = nullptr);
    ~QuestionLister();

private:
    Ui::QuestionLister *ui;
};

#endif // QUESTIONLISTER_H
