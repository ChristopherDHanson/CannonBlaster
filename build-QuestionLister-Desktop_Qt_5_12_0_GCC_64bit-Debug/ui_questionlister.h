/********************************************************************************
** Form generated from reading UI file 'questionlister.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONLISTER_H
#define UI_QUESTIONLISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestionLister
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_As;
    QWidget *centralWidget;
    QLabel *questionLabel;
    QPushButton *addQuestionButton;
    QPushButton *removeQuestionButton;
    QListWidget *questionList;
    QLabel *correctLabel;
    QListWidget *correctList;
    QPushButton *removeCorrectButton;
    QPushButton *addCorrectButton;
    QPushButton *addIncorrectButton;
    QListWidget *incorrectList;
    QLabel *incorrectLabel;
    QPushButton *remooveIncorrectButton;
    QMenuBar *menuBar;
    QMenu *menuQuestion_Lister;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *QuestionLister)
    {
        if (QuestionLister->objectName().isEmpty())
            QuestionLister->setObjectName(QString::fromUtf8("QuestionLister"));
        QuestionLister->resize(580, 511);
        actionNew = new QAction(QuestionLister);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(QuestionLister);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave_As = new QAction(QuestionLister);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        centralWidget = new QWidget(QuestionLister);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        questionLabel = new QLabel(centralWidget);
        questionLabel->setObjectName(QString::fromUtf8("questionLabel"));
        questionLabel->setGeometry(QRect(20, 10, 71, 17));
        addQuestionButton = new QPushButton(centralWidget);
        addQuestionButton->setObjectName(QString::fromUtf8("addQuestionButton"));
        addQuestionButton->setGeometry(QRect(40, 430, 89, 25));
        removeQuestionButton = new QPushButton(centralWidget);
        removeQuestionButton->setObjectName(QString::fromUtf8("removeQuestionButton"));
        removeQuestionButton->setGeometry(QRect(160, 430, 89, 25));
        questionList = new QListWidget(centralWidget);
        questionList->setObjectName(QString::fromUtf8("questionList"));
        questionList->setGeometry(QRect(20, 30, 261, 391));
        correctLabel = new QLabel(centralWidget);
        correctLabel->setObjectName(QString::fromUtf8("correctLabel"));
        correctLabel->setGeometry(QRect(300, 10, 121, 17));
        correctList = new QListWidget(centralWidget);
        correctList->setObjectName(QString::fromUtf8("correctList"));
        correctList->setGeometry(QRect(300, 30, 261, 161));
        removeCorrectButton = new QPushButton(centralWidget);
        removeCorrectButton->setObjectName(QString::fromUtf8("removeCorrectButton"));
        removeCorrectButton->setGeometry(QRect(440, 200, 89, 25));
        addCorrectButton = new QPushButton(centralWidget);
        addCorrectButton->setObjectName(QString::fromUtf8("addCorrectButton"));
        addCorrectButton->setGeometry(QRect(320, 200, 89, 25));
        addIncorrectButton = new QPushButton(centralWidget);
        addIncorrectButton->setObjectName(QString::fromUtf8("addIncorrectButton"));
        addIncorrectButton->setGeometry(QRect(320, 430, 89, 25));
        incorrectList = new QListWidget(centralWidget);
        incorrectList->setObjectName(QString::fromUtf8("incorrectList"));
        incorrectList->setGeometry(QRect(300, 260, 261, 161));
        incorrectLabel = new QLabel(centralWidget);
        incorrectLabel->setObjectName(QString::fromUtf8("incorrectLabel"));
        incorrectLabel->setGeometry(QRect(300, 240, 131, 17));
        remooveIncorrectButton = new QPushButton(centralWidget);
        remooveIncorrectButton->setObjectName(QString::fromUtf8("remooveIncorrectButton"));
        remooveIncorrectButton->setGeometry(QRect(440, 430, 89, 25));
        QuestionLister->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QuestionLister);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 580, 22));
        menuQuestion_Lister = new QMenu(menuBar);
        menuQuestion_Lister->setObjectName(QString::fromUtf8("menuQuestion_Lister"));
        QuestionLister->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QuestionLister);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QuestionLister->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuQuestion_Lister->menuAction());
        menuQuestion_Lister->addAction(actionNew);
        menuQuestion_Lister->addAction(actionOpen);
        menuQuestion_Lister->addAction(actionSave_As);

        retranslateUi(QuestionLister);

        QMetaObject::connectSlotsByName(QuestionLister);
    } // setupUi

    void retranslateUi(QMainWindow *QuestionLister)
    {
        QuestionLister->setWindowTitle(QApplication::translate("QuestionLister", "QuestionLister", nullptr));
        actionNew->setText(QApplication::translate("QuestionLister", "New", nullptr));
        actionOpen->setText(QApplication::translate("QuestionLister", "Open", nullptr));
        actionSave_As->setText(QApplication::translate("QuestionLister", "Save As...", nullptr));
        questionLabel->setText(QApplication::translate("QuestionLister", "Questions", nullptr));
        addQuestionButton->setText(QApplication::translate("QuestionLister", "Add", nullptr));
        removeQuestionButton->setText(QApplication::translate("QuestionLister", "Remove", nullptr));
        correctLabel->setText(QApplication::translate("QuestionLister", "Correct Answers", nullptr));
        removeCorrectButton->setText(QApplication::translate("QuestionLister", "Remove", nullptr));
        addCorrectButton->setText(QApplication::translate("QuestionLister", "Add", nullptr));
        addIncorrectButton->setText(QApplication::translate("QuestionLister", "Add", nullptr));
        incorrectLabel->setText(QApplication::translate("QuestionLister", "Incorrect Answers", nullptr));
        remooveIncorrectButton->setText(QApplication::translate("QuestionLister", "Remove", nullptr));
        menuQuestion_Lister->setTitle(QApplication::translate("QuestionLister", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuestionLister: public Ui_QuestionLister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONLISTER_H
