#include "questionlister.h"
#include "ui_questionlister.h"
#include "questionmodel.h"

QuestionLister::QuestionLister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionLister)
{
    ui->setupUi(this);
}

QuestionLister::~QuestionLister()
{
    delete ui;
}

void QuestionLister::on_questionList_currentRowChanged(int currentRow)
{
    questionIndex = currentRow;
    updateAnswers();
}

void QuestionLister::on_questionList_currentTextChanged(const QString &currentText)
{
    model.UpdateQuestion(questionIndex, currentText.toStdString());
}

void QuestionLister::on_removeQuestionButton_clicked()
{
    model.RemoveQuestion(questionIndex);
}

void QuestionLister::updateAnswers() {
    ui->correctList->clear();
    ui->incorrectList->clear();

}
