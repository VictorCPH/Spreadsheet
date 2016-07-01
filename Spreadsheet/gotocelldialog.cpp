#include "gotocelldialog.h"
#include <QPushButton>

gotocelldialog::gotocelldialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");//设置输入格式，因为表格列从A~Z，行从1~999
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

void gotocelldialog::on_lineEdit_textChanged()
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
                lineEdit->hasAcceptableInput());
}
