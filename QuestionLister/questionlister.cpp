#include "questionlister.h"
#include "ui_questionlister.h"

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
}
