#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    secendaryGroupBox->hide();
    tertiaryGroupBox->hide();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setColumnRange('A', 'Z');
}


void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryCloumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryCloumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryCloumnCombo->addItem(tr("None"));
    primaryCloumnCombo->setMinimumSize(
                secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        primaryCloumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryCloumnCombo->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
}

