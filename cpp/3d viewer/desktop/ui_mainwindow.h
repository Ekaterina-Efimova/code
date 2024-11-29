/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *MainStackedWidget;
    QWidget *MainStackedWidgetPage;
    QPushButton *ScreenButton;
    QLabel *label;
    QPushButton *OpenFileButton;
    QLabel *InfoLabel;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_2;
    QPushButton *SaveButton;
    QLabel *label_3;
    QLabel *label_6;
    QPushButton *GifButton;
    QPushButton *BackgroundColorButton;
    QPushButton *VertexButton;
    QPushButton *EdgesButton;
    QPushButton *CenterButton;
    QPushButton *ParallelButton;
    QOpenGLWidget *openGLWidget;
    QLineEdit *TransposeLineEdit_x;
    QLineEdit *TransposeLineEdit_y;
    QLineEdit *TransposeLineEdit_z;
    QLineEdit *ScaleLineEdit;
    QLineEdit *RotateLineEdit_z;
    QLineEdit *RotateLineEdit_y;
    QLineEdit *RotateLineEdit_x;
    QScrollBar *TransposeScrollBar_x;
    QScrollBar *TransposeScrollBar_y;
    QScrollBar *TransposeScrollBar_z;
    QScrollBar *ScaleScrollBar;
    QScrollBar *RotateScrollBar_z;
    QScrollBar *RotateScrollBar_y;
    QScrollBar *RotateScrollBar_x;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QWidget *EdgesSettingsPage;
    QWidget *EdgesSettings;
    QRadioButton *DishedEdgesRadioButton;
    QScrollBar *SizeEdgesScrollBar;
    QRadioButton *SolidEdgesRadioButton;
    QDialogButtonBox *CancelEdgesButton;
    QLabel *label_10;
    QPushButton *ColorEdgesButton;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *EdgesLineEdit;
    QWidget *SettingVertexPage;
    QWidget *SettingVertex;
    QRadioButton *CercleVertexRadioButton;
    QRadioButton *SquareVertexRadioButton;
    QScrollBar *SizeVertexScrollBar;
    QRadioButton *NoneVertexRadioButton;
    QDialogButtonBox *CancelVertexButton;
    QLabel *label_7;
    QPushButton *ColorVertexButton;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *VertexLineEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(852, 689);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        MainStackedWidget = new QStackedWidget(centralwidget);
        MainStackedWidget->setObjectName(QString::fromUtf8("MainStackedWidget"));
        MainStackedWidget->setLineWidth(0);
        MainStackedWidgetPage = new QWidget();
        MainStackedWidgetPage->setObjectName(QString::fromUtf8("MainStackedWidgetPage"));
        ScreenButton = new QPushButton(MainStackedWidgetPage);
        ScreenButton->setObjectName(QString::fromUtf8("ScreenButton"));
        ScreenButton->setGeometry(QRect(0, 100, 91, 41));
        label = new QLabel(MainStackedWidgetPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 550, 16, 16));
        OpenFileButton = new QPushButton(MainStackedWidgetPage);
        OpenFileButton->setObjectName(QString::fromUtf8("OpenFileButton"));
        OpenFileButton->setGeometry(QRect(-1, 6, 181, 41));
        InfoLabel = new QLabel(MainStackedWidgetPage);
        InfoLabel->setObjectName(QString::fromUtf8("InfoLabel"));
        InfoLabel->setGeometry(QRect(0, 150, 181, 261));
        InfoLabel->setToolTipDuration(5);
        InfoLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        InfoLabel->setWordWrap(false);
        label_4 = new QLabel(MainStackedWidgetPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(590, 590, 16, 16));
        label_5 = new QLabel(MainStackedWidgetPage);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(191, 634, 16, 16));
        label_2 = new QLabel(MainStackedWidgetPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 550, 16, 16));
        SaveButton = new QPushButton(MainStackedWidgetPage);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));
        SaveButton->setGeometry(QRect(0, 50, 181, 41));
        label_3 = new QLabel(MainStackedWidgetPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 590, 16, 16));
        label_6 = new QLabel(MainStackedWidgetPage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(590, 630, 20, 20));
        GifButton = new QPushButton(MainStackedWidgetPage);
        GifButton->setObjectName(QString::fromUtf8("GifButton"));
        GifButton->setGeometry(QRect(90, 100, 91, 41));
        BackgroundColorButton = new QPushButton(MainStackedWidgetPage);
        BackgroundColorButton->setObjectName(QString::fromUtf8("BackgroundColorButton"));
        BackgroundColorButton->setGeometry(QRect(0, 520, 171, 41));
        VertexButton = new QPushButton(MainStackedWidgetPage);
        VertexButton->setObjectName(QString::fromUtf8("VertexButton"));
        VertexButton->setGeometry(QRect(0, 570, 171, 41));
        EdgesButton = new QPushButton(MainStackedWidgetPage);
        EdgesButton->setObjectName(QString::fromUtf8("EdgesButton"));
        EdgesButton->setGeometry(QRect(0, 620, 171, 41));
        CenterButton = new QPushButton(MainStackedWidgetPage);
        CenterButton->setObjectName(QString::fromUtf8("CenterButton"));
        CenterButton->setGeometry(QRect(0, 470, 171, 41));
        ParallelButton = new QPushButton(MainStackedWidgetPage);
        ParallelButton->setObjectName(QString::fromUtf8("ParallelButton"));
        ParallelButton->setGeometry(QRect(0, 420, 171, 41));
        openGLWidget = new QOpenGLWidget(MainStackedWidgetPage);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setEnabled(false);
        openGLWidget->setGeometry(QRect(190, 10, 640, 480));
        TransposeLineEdit_x = new QLineEdit(MainStackedWidgetPage);
        TransposeLineEdit_x->setObjectName(QString::fromUtf8("TransposeLineEdit_x"));
        TransposeLineEdit_x->setGeometry(QRect(360, 540, 41, 28));
        TransposeLineEdit_x->setClearButtonEnabled(false);
        TransposeLineEdit_y = new QLineEdit(MainStackedWidgetPage);
        TransposeLineEdit_y->setObjectName(QString::fromUtf8("TransposeLineEdit_y"));
        TransposeLineEdit_y->setGeometry(QRect(360, 580, 41, 28));
        TransposeLineEdit_z = new QLineEdit(MainStackedWidgetPage);
        TransposeLineEdit_z->setObjectName(QString::fromUtf8("TransposeLineEdit_z"));
        TransposeLineEdit_z->setGeometry(QRect(360, 620, 41, 28));
        ScaleLineEdit = new QLineEdit(MainStackedWidgetPage);
        ScaleLineEdit->setObjectName(QString::fromUtf8("ScaleLineEdit"));
        ScaleLineEdit->setGeometry(QRect(460, 550, 71, 28));
        RotateLineEdit_z = new QLineEdit(MainStackedWidgetPage);
        RotateLineEdit_z->setObjectName(QString::fromUtf8("RotateLineEdit_z"));
        RotateLineEdit_z->setGeometry(QRect(770, 620, 41, 28));
        RotateLineEdit_y = new QLineEdit(MainStackedWidgetPage);
        RotateLineEdit_y->setObjectName(QString::fromUtf8("RotateLineEdit_y"));
        RotateLineEdit_y->setGeometry(QRect(770, 580, 41, 28));
        RotateLineEdit_x = new QLineEdit(MainStackedWidgetPage);
        RotateLineEdit_x->setObjectName(QString::fromUtf8("RotateLineEdit_x"));
        RotateLineEdit_x->setGeometry(QRect(770, 540, 41, 28));
        TransposeScrollBar_x = new QScrollBar(MainStackedWidgetPage);
        TransposeScrollBar_x->setObjectName(QString::fromUtf8("TransposeScrollBar_x"));
        TransposeScrollBar_x->setGeometry(QRect(220, 550, 131, 16));
        TransposeScrollBar_x->setMaximum(100);
        TransposeScrollBar_x->setPageStep(1);
        TransposeScrollBar_x->setValue(50);
        TransposeScrollBar_x->setOrientation(Qt::Horizontal);
        TransposeScrollBar_y = new QScrollBar(MainStackedWidgetPage);
        TransposeScrollBar_y->setObjectName(QString::fromUtf8("TransposeScrollBar_y"));
        TransposeScrollBar_y->setGeometry(QRect(220, 590, 131, 16));
        TransposeScrollBar_y->setMaximum(100);
        TransposeScrollBar_y->setPageStep(1);
        TransposeScrollBar_y->setValue(50);
        TransposeScrollBar_y->setOrientation(Qt::Horizontal);
        TransposeScrollBar_z = new QScrollBar(MainStackedWidgetPage);
        TransposeScrollBar_z->setObjectName(QString::fromUtf8("TransposeScrollBar_z"));
        TransposeScrollBar_z->setGeometry(QRect(220, 630, 131, 16));
        TransposeScrollBar_z->setMaximum(100);
        TransposeScrollBar_z->setPageStep(1);
        TransposeScrollBar_z->setValue(50);
        TransposeScrollBar_z->setOrientation(Qt::Horizontal);
        ScaleScrollBar = new QScrollBar(MainStackedWidgetPage);
        ScaleScrollBar->setObjectName(QString::fromUtf8("ScaleScrollBar"));
        ScaleScrollBar->setGeometry(QRect(430, 590, 131, 16));
        ScaleScrollBar->setMaximum(100);
        ScaleScrollBar->setPageStep(1);
        ScaleScrollBar->setValue(50);
        ScaleScrollBar->setOrientation(Qt::Horizontal);
        RotateScrollBar_z = new QScrollBar(MainStackedWidgetPage);
        RotateScrollBar_z->setObjectName(QString::fromUtf8("RotateScrollBar_z"));
        RotateScrollBar_z->setGeometry(QRect(630, 630, 131, 16));
        RotateScrollBar_z->setMaximum(360);
        RotateScrollBar_z->setPageStep(1);
        RotateScrollBar_z->setValue(180);
        RotateScrollBar_z->setOrientation(Qt::Horizontal);
        RotateScrollBar_y = new QScrollBar(MainStackedWidgetPage);
        RotateScrollBar_y->setObjectName(QString::fromUtf8("RotateScrollBar_y"));
        RotateScrollBar_y->setGeometry(QRect(630, 590, 131, 16));
        RotateScrollBar_y->setMaximum(360);
        RotateScrollBar_y->setPageStep(1);
        RotateScrollBar_y->setValue(180);
        RotateScrollBar_y->setOrientation(Qt::Horizontal);
        RotateScrollBar_x = new QScrollBar(MainStackedWidgetPage);
        RotateScrollBar_x->setObjectName(QString::fromUtf8("RotateScrollBar_x"));
        RotateScrollBar_x->setGeometry(QRect(630, 550, 131, 16));
        RotateScrollBar_x->setMaximum(360);
        RotateScrollBar_x->setPageStep(1);
        RotateScrollBar_x->setValue(180);
        RotateScrollBar_x->setTracking(true);
        RotateScrollBar_x->setOrientation(Qt::Horizontal);
        label_13 = new QLabel(MainStackedWidgetPage);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(240, 520, 111, 20));
        label_14 = new QLabel(MainStackedWidgetPage);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(467, 520, 61, 20));
        label_15 = new QLabel(MainStackedWidgetPage);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(667, 520, 61, 20));
        MainStackedWidget->addWidget(MainStackedWidgetPage);
        EdgesSettingsPage = new QWidget();
        EdgesSettingsPage->setObjectName(QString::fromUtf8("EdgesSettingsPage"));
        EdgesSettings = new QWidget(EdgesSettingsPage);
        EdgesSettings->setObjectName(QString::fromUtf8("EdgesSettings"));
        EdgesSettings->setGeometry(QRect(270, 150, 261, 241));
        EdgesSettings->setMouseTracking(false);
        EdgesSettings->setFocusPolicy(Qt::NoFocus);
        EdgesSettings->setAutoFillBackground(true);
        EdgesSettings->setInputMethodHints(Qt::ImhNone);
        DishedEdgesRadioButton = new QRadioButton(EdgesSettings);
        DishedEdgesRadioButton->setObjectName(QString::fromUtf8("DishedEdgesRadioButton"));
        DishedEdgesRadioButton->setGeometry(QRect(140, 70, 101, 21));
        SizeEdgesScrollBar = new QScrollBar(EdgesSettings);
        SizeEdgesScrollBar->setObjectName(QString::fromUtf8("SizeEdgesScrollBar"));
        SizeEdgesScrollBar->setGeometry(QRect(10, 170, 251, 16));
        SizeEdgesScrollBar->setCursor(QCursor(Qt::UpArrowCursor));
        SizeEdgesScrollBar->setContextMenuPolicy(Qt::PreventContextMenu);
        SizeEdgesScrollBar->setLayoutDirection(Qt::LeftToRight);
        SizeEdgesScrollBar->setMinimum(1);
        SizeEdgesScrollBar->setMaximum(10);
        SizeEdgesScrollBar->setSingleStep(1);
        SizeEdgesScrollBar->setPageStep(1);
        SizeEdgesScrollBar->setValue(5);
        SizeEdgesScrollBar->setOrientation(Qt::Horizontal);
        SizeEdgesScrollBar->setInvertedControls(false);
        SolidEdgesRadioButton = new QRadioButton(EdgesSettings);
        SolidEdgesRadioButton->setObjectName(QString::fromUtf8("SolidEdgesRadioButton"));
        SolidEdgesRadioButton->setGeometry(QRect(140, 40, 101, 21));
        CancelEdgesButton = new QDialogButtonBox(EdgesSettings);
        CancelEdgesButton->setObjectName(QString::fromUtf8("CancelEdgesButton"));
        CancelEdgesButton->setGeometry(QRect(50, 200, 176, 28));
        CancelEdgesButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_10 = new QLabel(EdgesSettings);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(50, 130, 61, 20));
        ColorEdgesButton = new QPushButton(EdgesSettings);
        ColorEdgesButton->setObjectName(QString::fromUtf8("ColorEdgesButton"));
        ColorEdgesButton->setGeometry(QRect(9, 93, 251, 28));
        label_11 = new QLabel(EdgesSettings);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 60, 101, 16));
        label_12 = new QLabel(EdgesSettings);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(60, 10, 118, 16));
        EdgesLineEdit = new QLineEdit(EdgesSettings);
        EdgesLineEdit->setObjectName(QString::fromUtf8("EdgesLineEdit"));
        EdgesLineEdit->setGeometry(QRect(120, 130, 113, 28));
        MainStackedWidget->addWidget(EdgesSettingsPage);
        SettingVertexPage = new QWidget();
        SettingVertexPage->setObjectName(QString::fromUtf8("SettingVertexPage"));
        SettingVertex = new QWidget(SettingVertexPage);
        SettingVertex->setObjectName(QString::fromUtf8("SettingVertex"));
        SettingVertex->setGeometry(QRect(270, 150, 261, 241));
        SettingVertex->setMouseTracking(false);
        SettingVertex->setFocusPolicy(Qt::NoFocus);
        SettingVertex->setAutoFillBackground(true);
        SettingVertex->setInputMethodHints(Qt::ImhNone);
        CercleVertexRadioButton = new QRadioButton(SettingVertex);
        CercleVertexRadioButton->setObjectName(QString::fromUtf8("CercleVertexRadioButton"));
        CercleVertexRadioButton->setGeometry(QRect(90, 66, 58, 21));
        SquareVertexRadioButton = new QRadioButton(SettingVertex);
        SquareVertexRadioButton->setObjectName(QString::fromUtf8("SquareVertexRadioButton"));
        SquareVertexRadioButton->setGeometry(QRect(172, 66, 80, 21));
        SizeVertexScrollBar = new QScrollBar(SettingVertex);
        SizeVertexScrollBar->setObjectName(QString::fromUtf8("SizeVertexScrollBar"));
        SizeVertexScrollBar->setGeometry(QRect(10, 170, 251, 16));
        SizeVertexScrollBar->setContextMenuPolicy(Qt::PreventContextMenu);
        SizeVertexScrollBar->setLayoutDirection(Qt::LeftToRight);
        SizeVertexScrollBar->setInputMethodHints(Qt::ImhNone);
        SizeVertexScrollBar->setMinimum(1);
        SizeVertexScrollBar->setMaximum(100);
        SizeVertexScrollBar->setSingleStep(1);
        SizeVertexScrollBar->setPageStep(1);
        SizeVertexScrollBar->setValue(5);
        SizeVertexScrollBar->setOrientation(Qt::Horizontal);
        NoneVertexRadioButton = new QRadioButton(SettingVertex);
        NoneVertexRadioButton->setObjectName(QString::fromUtf8("NoneVertexRadioButton"));
        NoneVertexRadioButton->setGeometry(QRect(9, 66, 52, 21));
        CancelVertexButton = new QDialogButtonBox(SettingVertex);
        CancelVertexButton->setObjectName(QString::fromUtf8("CancelVertexButton"));
        CancelVertexButton->setGeometry(QRect(50, 200, 176, 28));
        CancelVertexButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_7 = new QLabel(SettingVertex);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 140, 46, 16));
        ColorVertexButton = new QPushButton(SettingVertex);
        ColorVertexButton->setObjectName(QString::fromUtf8("ColorVertexButton"));
        ColorVertexButton->setGeometry(QRect(9, 93, 241, 28));
        label_9 = new QLabel(SettingVertex);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(90, 37, 76, 16));
        label_8 = new QLabel(SettingVertex);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 10, 118, 16));
        VertexLineEdit = new QLineEdit(SettingVertex);
        VertexLineEdit->setObjectName(QString::fromUtf8("VertexLineEdit"));
        VertexLineEdit->setGeometry(QRect(120, 130, 113, 28));
        MainStackedWidget->addWidget(SettingVertexPage);

        gridLayout_2->addWidget(MainStackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(SizeEdgesScrollBar, SIGNAL(valueChanged(int)), EdgesLineEdit, SLOT(show()));
        QObject::connect(SizeVertexScrollBar, SIGNAL(valueChanged(int)), VertexLineEdit, SLOT(show()));
        QObject::connect(VertexLineEdit, SIGNAL(textEdited(QString)), SizeVertexScrollBar, SLOT(show()));
        QObject::connect(EdgesLineEdit, SIGNAL(textEdited(QString)), SizeEdgesScrollBar, SLOT(show()));
        QObject::connect(RotateScrollBar_x, SIGNAL(valueChanged(int)), RotateLineEdit_x, SLOT(show()));
        QObject::connect(RotateScrollBar_y, SIGNAL(valueChanged(int)), RotateLineEdit_y, SLOT(show()));
        QObject::connect(RotateScrollBar_z, SIGNAL(valueChanged(int)), RotateLineEdit_z, SLOT(show()));
        QObject::connect(TransposeScrollBar_x, SIGNAL(valueChanged(int)), TransposeLineEdit_x, SLOT(show()));
        QObject::connect(TransposeScrollBar_y, SIGNAL(valueChanged(int)), TransposeLineEdit_y, SLOT(show()));
        QObject::connect(TransposeScrollBar_z, SIGNAL(valueChanged(int)), TransposeLineEdit_z, SLOT(show()));
        QObject::connect(RotateLineEdit_x, SIGNAL(textEdited(QString)), RotateLineEdit_x, SLOT(show()));
        QObject::connect(RotateLineEdit_y, SIGNAL(textEdited(QString)), RotateScrollBar_y, SLOT(show()));
        QObject::connect(RotateLineEdit_z, SIGNAL(textEdited(QString)), RotateScrollBar_z, SLOT(show()));
        QObject::connect(TransposeLineEdit_x, SIGNAL(textEdited(QString)), TransposeScrollBar_x, SLOT(show()));
        QObject::connect(TransposeLineEdit_y, SIGNAL(textEdited(QString)), TransposeScrollBar_y, SLOT(show()));
        QObject::connect(TransposeLineEdit_z, SIGNAL(textEdited(QString)), TransposeScrollBar_z, SLOT(show()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ScreenButton->setText(QCoreApplication::translate("MainWindow", "Screen", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        OpenFileButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        InfoLabel->setText(QCoreApplication::translate("MainWindow", "       \320\244\320\260\320\271\320\273 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        SaveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        GifButton->setText(QCoreApplication::translate("MainWindow", "Gif", nullptr));
        BackgroundColorButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202 \321\204\320\276\320\275\320\260", nullptr));
        VertexButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\262\320\265\321\200\321\210\320\270\320\275", nullptr));
        EdgesButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\200\320\265\320\261\320\265\321\200", nullptr));
        CenterButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\260\321\217 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\321\217", nullptr));
        ParallelButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\260\321\217 \320\277\321\200\320\276\320\265\320\272\321\206\320\270\321\217", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\260\321\211\320\265\320\275\320\270\320\265", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        DishedEdgesRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\250\321\202\321\200\320\270\321\205\320\276\320\262\320\260\321\217", nullptr));
        SolidEdgesRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\273\320\276\321\210\320\275\320\260\321\217", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\211\320\270\320\275\320\260", nullptr));
        ColorEdgesButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\276\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\270:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \321\200\320\265\320\261\320\265\321\200", nullptr));
        CercleVertexRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\321\203\320\263", nullptr));
        SquareVertexRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\262\320\260\320\264\321\200\320\260\321\202", nullptr));
        NoneVertexRadioButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        ColorVertexButton->setText(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\262\320\265\321\200\321\210\320\270\320\275:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\262\320\265\321\200\321\210\320\270\320\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
