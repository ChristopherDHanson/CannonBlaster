#include "questionlister.h"
#include "ui_questionlister.h"
#include "questionmodel.h"

QuestionLister::QuestionLister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionLister)
{
    model = QuestionModel();
    ui->setupUi(this);

}

QuestionLister::~QuestionLister()
{
    delete ui;
}

void QuestionLister::updateAnswers() {
    /*ui->correctList->clearSelection();
    ui->correctList->clear();
    ui->incorrectList->clearSelection();
    ui->incorrectList->clear();
    if (questionIndex != -1) {
        std::vector<std::string> correctAnswers = model.CorrectAnswers(questionIndex);
        QStringList answerList;
        for (auto it = correctAnswers.begin(); it != correctAnswers.end(); it++) {
            answerList.append(QString::fromStdString(*it.base()));
        }
        ui->correctList->addItems(answerList);

        std::vector<std::string> incorrectAnswers = model.IncorrectAnswers(questionIndex);
        answerList = QStringList();
        for (auto it = incorrectAnswers.begin(); it != incorrectAnswers.end(); it++) {
            answerList.append(QString::fromStdString(*it.base()));
        }
        ui->incorrectList->addItems(answerList);
    }*/
}

void QuestionLister::on_questionList_currentRowChanged(int currentRow)
{
    questionIndex = currentRow;
    updateAnswers();
}

void QuestionLister::on_questionList_currentTextChanged(const QString &currentText)
{
    if (questionIndex >= 0) {
        model.UpdateQuestion(questionIndex, currentText.toStdString());
    }
}

void QuestionLister::on_removeQuestionButton_clicked()
{
    model.RemoveQuestion(questionIndex);
}

void QuestionLister::on_addQuestionButton_clicked()
{
    ui->questionList->clearSelection();
    QListWidgetItem item = QListWidgetItem("Question");
    item.setFlags(item.flags() | Qt::ItemIsEditable);
    ui->questionList->addItem("Question");
    model.AddQuestion("Question");
}
