#ifndef GOTOCELLEIALOG
#define GOTOCELLEIALOG

#include <QDialog>
#include "ui_gotocelldialog.h"

namespace Ui {
class gotocelldialog;
}

class gotocelldialog : public QDialog, public Ui::gotocelldialog
{
    Q_OBJECT

public:
    explicit gotocelldialog(QWidget *parent = 0);

private slots:
    void on_lineEdit_textChanged();

};

#endif // GOTOCELLEIALOG

