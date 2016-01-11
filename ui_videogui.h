/********************************************************************************
** Form generated from reading UI file 'videogui.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOGUI_H
#define UI_VIDEOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videoGUI
{
public:
    QAction *fileOpenAction;
    QAction *exitAction;
    QAction *setOutputAction;
    QAction *displayAction;
    QAction *versionAction;
    QAction *frameDifAlgAction;
    QAction *multiThrhldFramedifAction;
    QAction *vibeAlgAction;
    QAction *usedToolAction;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *fileNameLabel;
    QLineEdit *fileNameEdit;
    QPushButton *fileOpenBtn;
    QSpacerItem *verticalSpacer_2;
    QLabel *imageLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *splitProcessBtn;
    QPushButton *cancelBtn;
    QPushButton *closeBtn;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *messageLabel;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *messageTextBrowser;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *videoGUI)
    {
        if (videoGUI->objectName().isEmpty())
            videoGUI->setObjectName(QStringLiteral("videoGUI"));
        videoGUI->resize(520, 369);
        fileOpenAction = new QAction(videoGUI);
        fileOpenAction->setObjectName(QStringLiteral("fileOpenAction"));
        exitAction = new QAction(videoGUI);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        setOutputAction = new QAction(videoGUI);
        setOutputAction->setObjectName(QStringLiteral("setOutputAction"));
        displayAction = new QAction(videoGUI);
        displayAction->setObjectName(QStringLiteral("displayAction"));
        displayAction->setCheckable(true);
        versionAction = new QAction(videoGUI);
        versionAction->setObjectName(QStringLiteral("versionAction"));
        frameDifAlgAction = new QAction(videoGUI);
        frameDifAlgAction->setObjectName(QStringLiteral("frameDifAlgAction"));
        frameDifAlgAction->setCheckable(true);
        multiThrhldFramedifAction = new QAction(videoGUI);
        multiThrhldFramedifAction->setObjectName(QStringLiteral("multiThrhldFramedifAction"));
        multiThrhldFramedifAction->setCheckable(true);
        vibeAlgAction = new QAction(videoGUI);
        vibeAlgAction->setObjectName(QStringLiteral("vibeAlgAction"));
        vibeAlgAction->setCheckable(true);
        usedToolAction = new QAction(videoGUI);
        usedToolAction->setObjectName(QStringLiteral("usedToolAction"));
        centralWidget = new QWidget(videoGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fileNameLabel = new QLabel(centralWidget);
        fileNameLabel->setObjectName(QStringLiteral("fileNameLabel"));

        horizontalLayout->addWidget(fileNameLabel);

        fileNameEdit = new QLineEdit(centralWidget);
        fileNameEdit->setObjectName(QStringLiteral("fileNameEdit"));

        horizontalLayout->addWidget(fileNameEdit);

        fileOpenBtn = new QPushButton(centralWidget);
        fileOpenBtn->setObjectName(QStringLiteral("fileOpenBtn"));

        horizontalLayout->addWidget(fileOpenBtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));

        verticalLayout->addWidget(imageLabel);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitProcessBtn = new QPushButton(centralWidget);
        splitProcessBtn->setObjectName(QStringLiteral("splitProcessBtn"));

        horizontalLayout_2->addWidget(splitProcessBtn);

        cancelBtn = new QPushButton(centralWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout_2->addWidget(cancelBtn);

        closeBtn = new QPushButton(centralWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));

        horizontalLayout_2->addWidget(closeBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        messageLabel = new QLabel(centralWidget);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));

        horizontalLayout_3->addWidget(messageLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        messageTextBrowser = new QTextBrowser(centralWidget);
        messageTextBrowser->setObjectName(QStringLiteral("messageTextBrowser"));

        verticalLayout_2->addWidget(messageTextBrowser);


        horizontalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        videoGUI->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(videoGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 520, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        videoGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(videoGUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        videoGUI->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(videoGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        videoGUI->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(fileOpenAction);
        menu->addAction(exitAction);
        menu_2->addAction(setOutputAction);
        menu_2->addAction(displayAction);
        menu_2->addAction(menu_4->menuAction());
        menu_4->addAction(frameDifAlgAction);
        menu_4->addAction(multiThrhldFramedifAction);
        menu_4->addAction(vibeAlgAction);
        menu_3->addAction(versionAction);
        menu_3->addAction(usedToolAction);

        retranslateUi(videoGUI);

        QMetaObject::connectSlotsByName(videoGUI);
    } // setupUi

    void retranslateUi(QMainWindow *videoGUI)
    {
        videoGUI->setWindowTitle(QApplication::translate("videoGUI", "videoGUI", 0));
        fileOpenAction->setText(QApplication::translate("videoGUI", "\346\211\223\345\274\200", 0));
        exitAction->setText(QApplication::translate("videoGUI", "\351\200\200\345\207\272", 0));
        setOutputAction->setText(QApplication::translate("videoGUI", "\350\276\223\345\207\272", 0));
        displayAction->setText(QApplication::translate("videoGUI", "\346\230\276\347\244\272", 0));
        versionAction->setText(QApplication::translate("videoGUI", "\347\211\210\346\234\254", 0));
        frameDifAlgAction->setText(QApplication::translate("videoGUI", "\345\270\247\351\227\264\345\267\256\345\210\206\347\256\227\346\263\225", 0));
        multiThrhldFramedifAction->setText(QApplication::translate("videoGUI", "\345\244\232\351\230\200\345\200\274\345\270\247\351\227\264\345\267\256\345\210\206\347\256\227\346\263\225", 0));
        vibeAlgAction->setText(QApplication::translate("videoGUI", "VIBE\347\256\227\346\263\225", 0));
        usedToolAction->setText(QApplication::translate("videoGUI", "\345\274\200\345\217\221\345\267\245\345\205\267", 0));
        fileNameLabel->setText(QApplication::translate("videoGUI", "\346\226\207\344\273\266\345\220\215\357\274\232", 0));
        fileOpenBtn->setText(QApplication::translate("videoGUI", "\346\211\223\345\274\200", 0));
        imageLabel->setText(QString());
        splitProcessBtn->setText(QApplication::translate("videoGUI", "\345\210\207\345\210\206", 0));
        cancelBtn->setText(QApplication::translate("videoGUI", "\345\217\226\346\266\210", 0));
        closeBtn->setText(QApplication::translate("videoGUI", "\345\205\263\351\227\255", 0));
        messageLabel->setText(QApplication::translate("videoGUI", "\346\266\210\346\201\257", 0));
        menu->setTitle(QApplication::translate("videoGUI", "\350\217\234\345\215\225", 0));
        menu_2->setTitle(QApplication::translate("videoGUI", "\350\256\276\347\275\256", 0));
        menu_4->setTitle(QApplication::translate("videoGUI", "\345\212\250\351\235\231\346\200\201\347\256\227\346\263\225", 0));
        menu_3->setTitle(QApplication::translate("videoGUI", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class videoGUI: public Ui_videoGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOGUI_H
