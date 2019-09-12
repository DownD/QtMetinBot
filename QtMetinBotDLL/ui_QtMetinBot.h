/********************************************************************************
** Form generated from reading UI file 'QtMetinBot.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMETINBOT_H
#define UI_QTMETINBOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtMetinBotClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *metinsKilledLabel;
    QLabel *numMetinsKilled;
    QLabel *tangLabel;
    QLabel *numYangMade;
    QLabel *currYangLabel;
    QLabel *currYang;
    QLabel *deathLabel;
    QLabel *deathCounter;
    QSpacerItem *horizontalSpacer;
    QToolButton *startButton;
    QGroupBox *botModesBox;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *expButton;
    QRadioButton *farmButton;
    QRadioButton *fishingButton;
    QTabWidget *tabWidget;
    QWidget *generalTab;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_4;
    QCheckBox *activateSkillBotCheckBox;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *suraSkillsRadioButton;
    QRadioButton *warriorSkillsRadioButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *activatePickupCheckBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *rangePickupCheckBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *itemUserCheckBox;
    QPushButton *runPythonButton;
    QWidget *damageTab;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *waitDamageCheckBox;
    QCheckBox *selectedDamageCheckBox;
    QWidget *securityTab;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *disableSilentButton;
    QPushButton *enableSilentButton;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *pickupSilentCheckBox;
    QCheckBox *dmgHackSilentCheckBox;
    QCheckBox *waitHackSilentCheckBox;
    QWidget *expTab;
    QWidget *farmTab;
    QWidget *fishingTab;

    void setupUi(QMainWindow *QtMetinBotClass)
    {
        if (QtMetinBotClass->objectName().isEmpty())
            QtMetinBotClass->setObjectName(QString::fromUtf8("QtMetinBotClass"));
        QtMetinBotClass->resize(529, 233);
        QtMetinBotClass->setMinimumSize(QSize(529, 233));
        QtMetinBotClass->setMaximumSize(QSize(529, 238));
        centralWidget = new QWidget(QtMetinBotClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        metinsKilledLabel = new QLabel(centralWidget);
        metinsKilledLabel->setObjectName(QString::fromUtf8("metinsKilledLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, metinsKilledLabel);

        numMetinsKilled = new QLabel(centralWidget);
        numMetinsKilled->setObjectName(QString::fromUtf8("numMetinsKilled"));

        formLayout->setWidget(0, QFormLayout::FieldRole, numMetinsKilled);

        tangLabel = new QLabel(centralWidget);
        tangLabel->setObjectName(QString::fromUtf8("tangLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, tangLabel);

        numYangMade = new QLabel(centralWidget);
        numYangMade->setObjectName(QString::fromUtf8("numYangMade"));

        formLayout->setWidget(1, QFormLayout::FieldRole, numYangMade);

        currYangLabel = new QLabel(centralWidget);
        currYangLabel->setObjectName(QString::fromUtf8("currYangLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, currYangLabel);

        currYang = new QLabel(centralWidget);
        currYang->setObjectName(QString::fromUtf8("currYang"));

        formLayout->setWidget(2, QFormLayout::FieldRole, currYang);

        deathLabel = new QLabel(centralWidget);
        deathLabel->setObjectName(QString::fromUtf8("deathLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, deathLabel);

        deathCounter = new QLabel(centralWidget);
        deathCounter->setObjectName(QString::fromUtf8("deathCounter"));

        formLayout->setWidget(3, QFormLayout::FieldRole, deathCounter);


        verticalLayout->addLayout(formLayout);

        horizontalSpacer = new QSpacerItem(89, 13, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        startButton = new QToolButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        startButton->setMinimumSize(QSize(92, 0));
        startButton->setMaximumSize(QSize(16777215, 16777214));
        startButton->setCheckable(true);
        startButton->setChecked(false);

        verticalLayout->addWidget(startButton);

        botModesBox = new QGroupBox(centralWidget);
        botModesBox->setObjectName(QString::fromUtf8("botModesBox"));
        verticalLayout_6 = new QVBoxLayout(botModesBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        expButton = new QRadioButton(botModesBox);
        expButton->setObjectName(QString::fromUtf8("expButton"));

        verticalLayout_6->addWidget(expButton);

        farmButton = new QRadioButton(botModesBox);
        farmButton->setObjectName(QString::fromUtf8("farmButton"));

        verticalLayout_6->addWidget(farmButton);

        fishingButton = new QRadioButton(botModesBox);
        fishingButton->setObjectName(QString::fromUtf8("fishingButton"));

        verticalLayout_6->addWidget(fishingButton);


        verticalLayout->addWidget(botModesBox);


        horizontalLayout->addLayout(verticalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        generalTab = new QWidget();
        generalTab->setObjectName(QString::fromUtf8("generalTab"));
        layoutWidget = new QWidget(generalTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(150, 10, 231, 131));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(layoutWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        activateSkillBotCheckBox = new QCheckBox(groupBox_4);
        activateSkillBotCheckBox->setObjectName(QString::fromUtf8("activateSkillBotCheckBox"));
        activateSkillBotCheckBox->setGeometry(QRect(10, 23, 59, 17));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 46, 79, 73));
        verticalLayout_9 = new QVBoxLayout(groupBox_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        suraSkillsRadioButton = new QRadioButton(groupBox_5);
        suraSkillsRadioButton->setObjectName(QString::fromUtf8("suraSkillsRadioButton"));

        verticalLayout_9->addWidget(suraSkillsRadioButton);

        warriorSkillsRadioButton = new QRadioButton(groupBox_5);
        warriorSkillsRadioButton->setObjectName(QString::fromUtf8("warriorSkillsRadioButton"));

        verticalLayout_9->addWidget(warriorSkillsRadioButton);


        horizontalLayout_6->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        activatePickupCheckBox = new QCheckBox(groupBox_2);
        activatePickupCheckBox->setObjectName(QString::fromUtf8("activatePickupCheckBox"));

        verticalLayout_4->addWidget(activatePickupCheckBox);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        rangePickupCheckBox = new QCheckBox(groupBox_3);
        rangePickupCheckBox->setObjectName(QString::fromUtf8("rangePickupCheckBox"));

        verticalLayout_7->addWidget(rangePickupCheckBox);


        verticalLayout_4->addWidget(groupBox_3);


        horizontalLayout_6->addWidget(groupBox_2);

        layoutWidget1 = new QWidget(generalTab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 105, 48));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        itemUserCheckBox = new QCheckBox(layoutWidget1);
        itemUserCheckBox->setObjectName(QString::fromUtf8("itemUserCheckBox"));

        verticalLayout_5->addWidget(itemUserCheckBox);

        runPythonButton = new QPushButton(layoutWidget1);
        runPythonButton->setObjectName(QString::fromUtf8("runPythonButton"));

        verticalLayout_5->addWidget(runPythonButton);

        tabWidget->addTab(generalTab, QString());
        damageTab = new QWidget();
        damageTab->setObjectName(QString::fromUtf8("damageTab"));
        horizontalLayout_4 = new QHBoxLayout(damageTab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        waitDamageCheckBox = new QCheckBox(damageTab);
        waitDamageCheckBox->setObjectName(QString::fromUtf8("waitDamageCheckBox"));

        horizontalLayout_3->addWidget(waitDamageCheckBox);

        selectedDamageCheckBox = new QCheckBox(damageTab);
        selectedDamageCheckBox->setObjectName(QString::fromUtf8("selectedDamageCheckBox"));

        horizontalLayout_3->addWidget(selectedDamageCheckBox);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        tabWidget->addTab(damageTab, QString());
        securityTab = new QWidget();
        securityTab->setObjectName(QString::fromUtf8("securityTab"));
        groupBox = new QGroupBox(securityTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(70, 30, 242, 100));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        disableSilentButton = new QPushButton(groupBox);
        disableSilentButton->setObjectName(QString::fromUtf8("disableSilentButton"));

        verticalLayout_3->addWidget(disableSilentButton);

        enableSilentButton = new QPushButton(groupBox);
        enableSilentButton->setObjectName(QString::fromUtf8("enableSilentButton"));

        verticalLayout_3->addWidget(enableSilentButton);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pickupSilentCheckBox = new QCheckBox(groupBox);
        pickupSilentCheckBox->setObjectName(QString::fromUtf8("pickupSilentCheckBox"));

        verticalLayout_2->addWidget(pickupSilentCheckBox);

        dmgHackSilentCheckBox = new QCheckBox(groupBox);
        dmgHackSilentCheckBox->setObjectName(QString::fromUtf8("dmgHackSilentCheckBox"));

        verticalLayout_2->addWidget(dmgHackSilentCheckBox);

        waitHackSilentCheckBox = new QCheckBox(groupBox);
        waitHackSilentCheckBox->setObjectName(QString::fromUtf8("waitHackSilentCheckBox"));

        verticalLayout_2->addWidget(waitHackSilentCheckBox);


        horizontalLayout_2->addLayout(verticalLayout_2);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        tabWidget->addTab(securityTab, QString());
        expTab = new QWidget();
        expTab->setObjectName(QString::fromUtf8("expTab"));
        tabWidget->addTab(expTab, QString());
        farmTab = new QWidget();
        farmTab->setObjectName(QString::fromUtf8("farmTab"));
        tabWidget->addTab(farmTab, QString());
        fishingTab = new QWidget();
        fishingTab->setObjectName(QString::fromUtf8("fishingTab"));
        tabWidget->addTab(fishingTab, QString());

        horizontalLayout->addWidget(tabWidget);

        QtMetinBotClass->setCentralWidget(centralWidget);

        retranslateUi(QtMetinBotClass);
        QObject::connect(activateSkillBotCheckBox, SIGNAL(toggled(bool)), groupBox_5, SLOT(setDisabled(bool)));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(QtMetinBotClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtMetinBotClass)
    {
        QtMetinBotClass->setWindowTitle(QCoreApplication::translate("QtMetinBotClass", "MetinBot", nullptr));
        metinsKilledLabel->setText(QCoreApplication::translate("QtMetinBotClass", "Metins killed:", nullptr));
        numMetinsKilled->setText(QCoreApplication::translate("QtMetinBotClass", "0", nullptr));
        tangLabel->setText(QCoreApplication::translate("QtMetinBotClass", "Yang Made:", nullptr));
        numYangMade->setText(QCoreApplication::translate("QtMetinBotClass", "0", nullptr));
        currYangLabel->setText(QCoreApplication::translate("QtMetinBotClass", "Current Yang:", nullptr));
        currYang->setText(QCoreApplication::translate("QtMetinBotClass", "0", nullptr));
        deathLabel->setText(QCoreApplication::translate("QtMetinBotClass", "Death Count:", nullptr));
        deathCounter->setText(QCoreApplication::translate("QtMetinBotClass", "0", nullptr));
        startButton->setText(QCoreApplication::translate("QtMetinBotClass", "Start", nullptr));
        botModesBox->setTitle(QCoreApplication::translate("QtMetinBotClass", "Modes", nullptr));
        expButton->setText(QCoreApplication::translate("QtMetinBotClass", "ExpBot", nullptr));
        farmButton->setText(QCoreApplication::translate("QtMetinBotClass", "FarmBot", nullptr));
        fishingButton->setText(QCoreApplication::translate("QtMetinBotClass", "FishingBot", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("QtMetinBotClass", "Skill Bot", nullptr));
        activateSkillBotCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Skill Bot", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("QtMetinBotClass", "Options", nullptr));
        suraSkillsRadioButton->setText(QCoreApplication::translate("QtMetinBotClass", "Sura", nullptr));
        warriorSkillsRadioButton->setText(QCoreApplication::translate("QtMetinBotClass", "Warrior", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QtMetinBotClass", "Pickup", nullptr));
        activatePickupCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Pickup", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("QtMetinBotClass", "Options", nullptr));
        rangePickupCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Range Pickup", nullptr));
        itemUserCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Item User", nullptr));
        runPythonButton->setText(QCoreApplication::translate("QtMetinBotClass", "Execute Python File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(generalTab), QCoreApplication::translate("QtMetinBotClass", "General", nullptr));
        waitDamageCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Wait Damage", nullptr));
        selectedDamageCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Damage Selected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(damageTab), QCoreApplication::translate("QtMetinBotClass", "DamageHacks", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QtMetinBotClass", "Silent Options", nullptr));
        disableSilentButton->setText(QCoreApplication::translate("QtMetinBotClass", "DisableAll", nullptr));
        enableSilentButton->setText(QCoreApplication::translate("QtMetinBotClass", "Enable All", nullptr));
        pickupSilentCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Range Pickup Silent", nullptr));
        dmgHackSilentCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Damage Selected Silent", nullptr));
        waitHackSilentCheckBox->setText(QCoreApplication::translate("QtMetinBotClass", "Wait Hack Silent", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(securityTab), QCoreApplication::translate("QtMetinBotClass", "Security", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(expTab), QCoreApplication::translate("QtMetinBotClass", "ExpBot", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(farmTab), QCoreApplication::translate("QtMetinBotClass", "FarmBot", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(fishingTab), QCoreApplication::translate("QtMetinBotClass", "FishingBot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtMetinBotClass: public Ui_QtMetinBotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMETINBOT_H
