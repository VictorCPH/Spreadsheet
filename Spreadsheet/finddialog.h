#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog: public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    void lineEditClear();
signals:
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);//从当前单元格开始向前搜索字符串（可设置大小写敏感）
    void findNext(const QString &str, Qt::CaseSensitivity cs);//从当前单元格开始向后搜索字符串（可设置大小写敏感）
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
    void findFail();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;

};
#endif // FINDDIALOG_H

