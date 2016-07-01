/********************************************************************************
** Form generated from reading UI file 'sortdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
//此.h由设计器生成
#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SortDialog
{
public:
    QGridLayout *mainLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;
    QPushButton *moreButton;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *primaryOrdercombo;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QComboBox *primaryCloumnCombo;
    QGroupBox *secendaryGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *secondaryColumnCombo;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QComboBox *secondaryOrderCombo;
    QGroupBox *tertiaryGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QComboBox *tertiaryCloumnCombo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QComboBox *tertiaryOrderCombo;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *SortDialog)
    {
        if (SortDialog->objectName().isEmpty())
            SortDialog->setObjectName(QStringLiteral("SortDialog"));
        SortDialog->resize(400, 319);
        mainLayout = new QGridLayout(SortDialog);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        okButton = new QPushButton(SortDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setAutoDefault(false);
        okButton->setDefault(true);

        verticalLayout->addWidget(okButton);

        cancelButton = new QPushButton(SortDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setAutoDefault(false);

        verticalLayout->addWidget(cancelButton);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        moreButton = new QPushButton(SortDialog);
        moreButton->setObjectName(QStringLiteral("moreButton"));
        moreButton->setCheckable(true);

        verticalLayout->addWidget(moreButton);


        mainLayout->addLayout(verticalLayout, 0, 1, 2, 1);

        primaryGroupBox = new QGroupBox(SortDialog);
        primaryGroupBox->setObjectName(QStringLiteral("primaryGroupBox"));
        gridLayout = new QGridLayout(primaryGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(primaryGroupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        primaryOrdercombo = new QComboBox(primaryGroupBox);
        primaryOrdercombo->setObjectName(QStringLiteral("primaryOrdercombo"));

        gridLayout->addWidget(primaryOrdercombo, 1, 1, 1, 2);

        label_2 = new QLabel(primaryGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(125, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        primaryCloumnCombo = new QComboBox(primaryGroupBox);
        primaryCloumnCombo->setObjectName(QStringLiteral("primaryCloumnCombo"));

        gridLayout->addWidget(primaryCloumnCombo, 0, 1, 1, 1);


        mainLayout->addWidget(primaryGroupBox, 0, 0, 1, 1);

        secendaryGroupBox = new QGroupBox(SortDialog);
        secendaryGroupBox->setObjectName(QStringLiteral("secendaryGroupBox"));
        gridLayout_3 = new QGridLayout(secendaryGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(secendaryGroupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        secondaryColumnCombo = new QComboBox(secendaryGroupBox);
        secondaryColumnCombo->setObjectName(QStringLiteral("secondaryColumnCombo"));

        gridLayout_3->addWidget(secondaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_6 = new QLabel(secendaryGroupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        secondaryOrderCombo = new QComboBox(secendaryGroupBox);
        secondaryOrderCombo->setObjectName(QStringLiteral("secondaryOrderCombo"));

        gridLayout_3->addWidget(secondaryOrderCombo, 1, 1, 1, 2);


        mainLayout->addWidget(secendaryGroupBox, 2, 0, 1, 1);

        tertiaryGroupBox = new QGroupBox(SortDialog);
        tertiaryGroupBox->setObjectName(QStringLiteral("tertiaryGroupBox"));
        gridLayout_2 = new QGridLayout(tertiaryGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(tertiaryGroupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        tertiaryCloumnCombo = new QComboBox(tertiaryGroupBox);
        tertiaryCloumnCombo->setObjectName(QStringLiteral("tertiaryCloumnCombo"));

        gridLayout_2->addWidget(tertiaryCloumnCombo, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_4 = new QLabel(tertiaryGroupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        tertiaryOrderCombo = new QComboBox(tertiaryGroupBox);
        tertiaryOrderCombo->setObjectName(QStringLiteral("tertiaryOrderCombo"));

        gridLayout_2->addWidget(tertiaryOrderCombo, 1, 1, 1, 2);


        mainLayout->addWidget(tertiaryGroupBox, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mainLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        QWidget::setTabOrder(primaryCloumnCombo, primaryOrdercombo);
        QWidget::setTabOrder(primaryOrdercombo, secondaryColumnCombo);
        QWidget::setTabOrder(secondaryColumnCombo, secondaryOrderCombo);
        QWidget::setTabOrder(secondaryOrderCombo, tertiaryCloumnCombo);
        QWidget::setTabOrder(tertiaryCloumnCombo, tertiaryOrderCombo);
        QWidget::setTabOrder(tertiaryOrderCombo, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, moreButton);

        retranslateUi(SortDialog);
        QObject::connect(okButton, SIGNAL(clicked()), SortDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SortDialog, SLOT(reject()));
        QObject::connect(moreButton, SIGNAL(toggled(bool)), secendaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(moreButton, SIGNAL(toggled(bool)), tertiaryGroupBox, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(SortDialog);
    } // setupUi

    void retranslateUi(QDialog *SortDialog)
    {
        SortDialog->setWindowTitle(QApplication::translate("SortDialog", "Sort", 0));
        okButton->setText(QApplication::translate("SortDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("SortDialog", "Cancel", 0));
        moreButton->setText(QApplication::translate("SortDialog", "&More", 0));
        primaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Primary Key", 0));
        label->setText(QApplication::translate("SortDialog", "Column", 0));
        primaryOrdercombo->clear();
        primaryOrdercombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
        label_2->setText(QApplication::translate("SortDialog", "Order", 0));
        primaryCloumnCombo->clear();
        primaryCloumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        secendaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Secondary Key", 0));
        label_5->setText(QApplication::translate("SortDialog", "Column", 0));
        secondaryColumnCombo->clear();
        secondaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        label_6->setText(QApplication::translate("SortDialog", "Order", 0));
        secondaryOrderCombo->clear();
        secondaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
        tertiaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Tertiary Key", 0));
        label_3->setText(QApplication::translate("SortDialog", "Column", 0));
        tertiaryCloumnCombo->clear();
        tertiaryCloumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        label_4->setText(QApplication::translate("SortDialog", "Order", 0));
        tertiaryOrderCombo->clear();
        tertiaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class SortDialog: public Ui_SortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
