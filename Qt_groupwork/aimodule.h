#ifndef AIMODULE_H
#define AIMODULE_H

#include <QBoxLayout>
#include <QCloseEvent>
#include <QJsonArray>
#include <QJsonObject>
#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QLayoutItem>
#include <QLineEdit>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextEdit>
#include "qwidget.h"

enum Mode {TreeMode,ChatMode};

class AImodule : public QWidget
{
    Q_OBJECT
private:
    bool modeChanged;
    Mode mode;
    QLineEdit* createLineEditForItem(const QString &initialText);
    QTreeWidget *treeWidget;
    // QLineEdit *nodeNameEdit;
    QTextEdit *outputTextEdit;
    QNetworkAccessManager *networkManager;

    QVBoxLayout* mainLayout;
    QLabel* text1;
    QTextEdit *inputTextEdit;
    QLabel* text2;
    QStackedWidget* output;
    QHBoxLayout* buttonLayout;
    QPushButton* clear_PB;
    QPushButton* commit_PB;
    QPushButton* modeSwitch_PB;

    void show_treeMode();
    void show_chatMode();
public:
    explicit AImodule(QWidget *parent = nullptr);
    void show_ui();
    void closeEvent(QCloseEvent *event) override; 
signals:
    void close();
public slots:
    void toggle_clear_PB();
    void toggle_commit_PB();
    void toggle_modeSwitch_PB();
    void apiReplyFinished(QNetworkReply *reply);
};

#endif // AIMODULE_H
