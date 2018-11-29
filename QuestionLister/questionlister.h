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

private slots:
    void on_questionList_currentRowChanged(int currentRow);

private:
    Ui::QuestionLister *ui;
    int questionIndex;
    int correctIndex;
    int incorrectIndex;
};

#endif // QUESTIONLISTER_H
