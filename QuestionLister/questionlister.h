#ifndef QUESTIONLISTER_H
#define QUESTIONLISTER_H

#include <QMainWindow>
#include "questionmodel.h"

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

    void on_questionList_currentTextChanged(const QString &currentText);

    void on_removeQuestionButton_clicked();

    void on_addQuestionButton_clicked();

    void on_questionList_itemSelectionChanged();

private:
    Ui::QuestionLister *ui;
    QuestionModel model;
    int questionIndex;
    int correctIndex;
    int incorrectIndex;

    void updateQuestions();
    void updateAnswers();
};

#endif // QUESTIONLISTER_H
