/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabHome;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelWelcome;
    QLabel *labelInstructions;
    QWidget *tabCadastrarPaciente;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayoutPaciente;
    QLabel *labelNomePaciente;
    QLineEdit *inputNomePaciente;
    QLabel *labelCpfPaciente;
    QLineEdit *inputCpfPaciente;
    QLabel *labelIdadePaciente;
    QLineEdit *inputIdadePaciente;
    QLabel *labelGeneroPaciente;
    QComboBox *comboGeneroPaciente;
    QPushButton *btnCadastrarPaciente;
    QSpacerItem *verticalSpacerPaciente;
    QWidget *tabCadastrarMedico;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayoutMedico;
    QLabel *labelNomeMedico;
    QLineEdit *inputNomeMedico;
    QLabel *labelCrmMedico;
    QLineEdit *inputCrmMedico;
    QLabel *labelEspecialidadeMedico;
    QLineEdit *inputEspecialidadeMedico;
    QPushButton *btnCadastrarMedico;
    QSpacerItem *verticalSpacerMedico;
    QWidget *tabCadastrarLeito;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayoutLeito;
    QLabel *labelIdLeito;
    QLineEdit *inputIdLeito;
    QPushButton *btnCadastrarLeito;
    QSpacerItem *verticalSpacerLeito;
    QWidget *tabListar;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayoutListar;
    QPushButton *btnListarPacientes;
    QPushButton *btnListarMedicos;
    QPushButton *btnConsultarLeitos;
    QTextEdit *outputListar;
    QWidget *tabAlocarLiberar;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayoutAlocar;
    QLabel *labelCpfAlocar;
    QLineEdit *inputCpfAlocar;
    QLabel *labelCrmAlocar;
    QLineEdit *inputCrmAlocar;
    QPushButton *btnAlocar;
    QSpacerItem *verticalSpacerAlocar;
    QFrame *line;
    QFormLayout *formLayoutLiberar;
    QLabel *labelIdLiberar;
    QLineEdit *inputIdLiberar;
    QPushButton *btnLiberarLeito;
    QSpacerItem *verticalSpacerLiberar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabHome = new QWidget();
        tabHome->setObjectName("tabHome");
        verticalLayout_2 = new QVBoxLayout(tabHome);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelWelcome = new QLabel(tabHome);
        labelWelcome->setObjectName("labelWelcome");
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        labelWelcome->setFont(font);
        labelWelcome->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelWelcome);

        labelInstructions = new QLabel(tabHome);
        labelInstructions->setObjectName("labelInstructions");
        labelInstructions->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelInstructions);

        tabWidget->addTab(tabHome, QString());
        tabCadastrarPaciente = new QWidget();
        tabCadastrarPaciente->setObjectName("tabCadastrarPaciente");
        verticalLayout_3 = new QVBoxLayout(tabCadastrarPaciente);
        verticalLayout_3->setObjectName("verticalLayout_3");
        formLayoutPaciente = new QFormLayout();
        formLayoutPaciente->setObjectName("formLayoutPaciente");
        formLayoutPaciente->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelNomePaciente = new QLabel(tabCadastrarPaciente);
        labelNomePaciente->setObjectName("labelNomePaciente");

        formLayoutPaciente->setWidget(0, QFormLayout::ItemRole::LabelRole, labelNomePaciente);

        inputNomePaciente = new QLineEdit(tabCadastrarPaciente);
        inputNomePaciente->setObjectName("inputNomePaciente");

        formLayoutPaciente->setWidget(0, QFormLayout::ItemRole::FieldRole, inputNomePaciente);

        labelCpfPaciente = new QLabel(tabCadastrarPaciente);
        labelCpfPaciente->setObjectName("labelCpfPaciente");

        formLayoutPaciente->setWidget(1, QFormLayout::ItemRole::LabelRole, labelCpfPaciente);

        inputCpfPaciente = new QLineEdit(tabCadastrarPaciente);
        inputCpfPaciente->setObjectName("inputCpfPaciente");

        formLayoutPaciente->setWidget(1, QFormLayout::ItemRole::FieldRole, inputCpfPaciente);

        labelIdadePaciente = new QLabel(tabCadastrarPaciente);
        labelIdadePaciente->setObjectName("labelIdadePaciente");

        formLayoutPaciente->setWidget(2, QFormLayout::ItemRole::LabelRole, labelIdadePaciente);

        inputIdadePaciente = new QLineEdit(tabCadastrarPaciente);
        inputIdadePaciente->setObjectName("inputIdadePaciente");

        formLayoutPaciente->setWidget(2, QFormLayout::ItemRole::FieldRole, inputIdadePaciente);

        labelGeneroPaciente = new QLabel(tabCadastrarPaciente);
        labelGeneroPaciente->setObjectName("labelGeneroPaciente");

        formLayoutPaciente->setWidget(3, QFormLayout::ItemRole::LabelRole, labelGeneroPaciente);

        comboGeneroPaciente = new QComboBox(tabCadastrarPaciente);
        comboGeneroPaciente->addItem(QString());
        comboGeneroPaciente->addItem(QString());
        comboGeneroPaciente->setObjectName("comboGeneroPaciente");

        formLayoutPaciente->setWidget(3, QFormLayout::ItemRole::FieldRole, comboGeneroPaciente);


        verticalLayout_3->addLayout(formLayoutPaciente);

        btnCadastrarPaciente = new QPushButton(tabCadastrarPaciente);
        btnCadastrarPaciente->setObjectName("btnCadastrarPaciente");

        verticalLayout_3->addWidget(btnCadastrarPaciente);

        verticalSpacerPaciente = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacerPaciente);

        tabWidget->addTab(tabCadastrarPaciente, QString());
        tabCadastrarMedico = new QWidget();
        tabCadastrarMedico->setObjectName("tabCadastrarMedico");
        verticalLayout_4 = new QVBoxLayout(tabCadastrarMedico);
        verticalLayout_4->setObjectName("verticalLayout_4");
        formLayoutMedico = new QFormLayout();
        formLayoutMedico->setObjectName("formLayoutMedico");
        formLayoutMedico->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelNomeMedico = new QLabel(tabCadastrarMedico);
        labelNomeMedico->setObjectName("labelNomeMedico");

        formLayoutMedico->setWidget(0, QFormLayout::ItemRole::LabelRole, labelNomeMedico);

        inputNomeMedico = new QLineEdit(tabCadastrarMedico);
        inputNomeMedico->setObjectName("inputNomeMedico");

        formLayoutMedico->setWidget(0, QFormLayout::ItemRole::FieldRole, inputNomeMedico);

        labelCrmMedico = new QLabel(tabCadastrarMedico);
        labelCrmMedico->setObjectName("labelCrmMedico");

        formLayoutMedico->setWidget(1, QFormLayout::ItemRole::LabelRole, labelCrmMedico);

        inputCrmMedico = new QLineEdit(tabCadastrarMedico);
        inputCrmMedico->setObjectName("inputCrmMedico");

        formLayoutMedico->setWidget(1, QFormLayout::ItemRole::FieldRole, inputCrmMedico);

        labelEspecialidadeMedico = new QLabel(tabCadastrarMedico);
        labelEspecialidadeMedico->setObjectName("labelEspecialidadeMedico");

        formLayoutMedico->setWidget(2, QFormLayout::ItemRole::LabelRole, labelEspecialidadeMedico);

        inputEspecialidadeMedico = new QLineEdit(tabCadastrarMedico);
        inputEspecialidadeMedico->setObjectName("inputEspecialidadeMedico");

        formLayoutMedico->setWidget(2, QFormLayout::ItemRole::FieldRole, inputEspecialidadeMedico);


        verticalLayout_4->addLayout(formLayoutMedico);

        btnCadastrarMedico = new QPushButton(tabCadastrarMedico);
        btnCadastrarMedico->setObjectName("btnCadastrarMedico");

        verticalLayout_4->addWidget(btnCadastrarMedico);

        verticalSpacerMedico = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacerMedico);

        tabWidget->addTab(tabCadastrarMedico, QString());
        tabCadastrarLeito = new QWidget();
        tabCadastrarLeito->setObjectName("tabCadastrarLeito");
        verticalLayout_5 = new QVBoxLayout(tabCadastrarLeito);
        verticalLayout_5->setObjectName("verticalLayout_5");
        formLayoutLeito = new QFormLayout();
        formLayoutLeito->setObjectName("formLayoutLeito");
        formLayoutLeito->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelIdLeito = new QLabel(tabCadastrarLeito);
        labelIdLeito->setObjectName("labelIdLeito");

        formLayoutLeito->setWidget(0, QFormLayout::ItemRole::LabelRole, labelIdLeito);

        inputIdLeito = new QLineEdit(tabCadastrarLeito);
        inputIdLeito->setObjectName("inputIdLeito");

        formLayoutLeito->setWidget(0, QFormLayout::ItemRole::FieldRole, inputIdLeito);


        verticalLayout_5->addLayout(formLayoutLeito);

        btnCadastrarLeito = new QPushButton(tabCadastrarLeito);
        btnCadastrarLeito->setObjectName("btnCadastrarLeito");

        verticalLayout_5->addWidget(btnCadastrarLeito);

        verticalSpacerLeito = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacerLeito);

        tabWidget->addTab(tabCadastrarLeito, QString());
        tabListar = new QWidget();
        tabListar->setObjectName("tabListar");
        verticalLayout_6 = new QVBoxLayout(tabListar);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayoutListar = new QHBoxLayout();
        horizontalLayoutListar->setObjectName("horizontalLayoutListar");
        btnListarPacientes = new QPushButton(tabListar);
        btnListarPacientes->setObjectName("btnListarPacientes");

        horizontalLayoutListar->addWidget(btnListarPacientes);

        btnListarMedicos = new QPushButton(tabListar);
        btnListarMedicos->setObjectName("btnListarMedicos");

        horizontalLayoutListar->addWidget(btnListarMedicos);

        btnConsultarLeitos = new QPushButton(tabListar);
        btnConsultarLeitos->setObjectName("btnConsultarLeitos");

        horizontalLayoutListar->addWidget(btnConsultarLeitos);


        verticalLayout_6->addLayout(horizontalLayoutListar);

        outputListar = new QTextEdit(tabListar);
        outputListar->setObjectName("outputListar");
        outputListar->setReadOnly(true);

        verticalLayout_6->addWidget(outputListar);

        tabWidget->addTab(tabListar, QString());
        tabAlocarLiberar = new QWidget();
        tabAlocarLiberar->setObjectName("tabAlocarLiberar");
        verticalLayout_7 = new QVBoxLayout(tabAlocarLiberar);
        verticalLayout_7->setObjectName("verticalLayout_7");
        formLayoutAlocar = new QFormLayout();
        formLayoutAlocar->setObjectName("formLayoutAlocar");
        formLayoutAlocar->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelCpfAlocar = new QLabel(tabAlocarLiberar);
        labelCpfAlocar->setObjectName("labelCpfAlocar");

        formLayoutAlocar->setWidget(0, QFormLayout::ItemRole::LabelRole, labelCpfAlocar);

        inputCpfAlocar = new QLineEdit(tabAlocarLiberar);
        inputCpfAlocar->setObjectName("inputCpfAlocar");

        formLayoutAlocar->setWidget(0, QFormLayout::ItemRole::FieldRole, inputCpfAlocar);

        labelCrmAlocar = new QLabel(tabAlocarLiberar);
        labelCrmAlocar->setObjectName("labelCrmAlocar");

        formLayoutAlocar->setWidget(1, QFormLayout::ItemRole::LabelRole, labelCrmAlocar);

        inputCrmAlocar = new QLineEdit(tabAlocarLiberar);
        inputCrmAlocar->setObjectName("inputCrmAlocar");

        formLayoutAlocar->setWidget(1, QFormLayout::ItemRole::FieldRole, inputCrmAlocar);


        verticalLayout_7->addLayout(formLayoutAlocar);

        btnAlocar = new QPushButton(tabAlocarLiberar);
        btnAlocar->setObjectName("btnAlocar");

        verticalLayout_7->addWidget(btnAlocar);

        verticalSpacerAlocar = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacerAlocar);

        line = new QFrame(tabAlocarLiberar);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_7->addWidget(line);

        formLayoutLiberar = new QFormLayout();
        formLayoutLiberar->setObjectName("formLayoutLiberar");
        formLayoutLiberar->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelIdLiberar = new QLabel(tabAlocarLiberar);
        labelIdLiberar->setObjectName("labelIdLiberar");

        formLayoutLiberar->setWidget(0, QFormLayout::ItemRole::LabelRole, labelIdLiberar);

        inputIdLiberar = new QLineEdit(tabAlocarLiberar);
        inputIdLiberar->setObjectName("inputIdLiberar");

        formLayoutLiberar->setWidget(0, QFormLayout::ItemRole::FieldRole, inputIdLiberar);


        verticalLayout_7->addLayout(formLayoutLiberar);

        btnLiberarLeito = new QPushButton(tabAlocarLiberar);
        btnLiberarLeito->setObjectName("btnLiberarLeito");

        verticalLayout_7->addWidget(btnLiberarLeito);

        verticalSpacerLiberar = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_7->addItem(verticalSpacerLiberar);

        tabWidget->addTab(tabAlocarLiberar, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sistema de Gerenciamento Hospitalar", nullptr));
        labelWelcome->setText(QCoreApplication::translate("MainWindow", "Bem-vindo ao Sistema Hospitalar", nullptr));
        labelInstructions->setText(QCoreApplication::translate("MainWindow", "Selecione uma op\303\247\303\243o no menu acima para come\303\247ar.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabHome), QCoreApplication::translate("MainWindow", "In\303\255cio", nullptr));
        labelNomePaciente->setText(QCoreApplication::translate("MainWindow", "Nome:", nullptr));
        labelCpfPaciente->setText(QCoreApplication::translate("MainWindow", "CPF:", nullptr));
        labelIdadePaciente->setText(QCoreApplication::translate("MainWindow", "Idade:", nullptr));
        labelGeneroPaciente->setText(QCoreApplication::translate("MainWindow", "G\303\252nero:", nullptr));
        comboGeneroPaciente->setItemText(0, QCoreApplication::translate("MainWindow", "M", nullptr));
        comboGeneroPaciente->setItemText(1, QCoreApplication::translate("MainWindow", "F", nullptr));

        btnCadastrarPaciente->setText(QCoreApplication::translate("MainWindow", "Cadastrar Paciente", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCadastrarPaciente), QCoreApplication::translate("MainWindow", "Cadastrar Paciente", nullptr));
        labelNomeMedico->setText(QCoreApplication::translate("MainWindow", "Nome:", nullptr));
        labelCrmMedico->setText(QCoreApplication::translate("MainWindow", "CRM:", nullptr));
        labelEspecialidadeMedico->setText(QCoreApplication::translate("MainWindow", "Especialidade:", nullptr));
        btnCadastrarMedico->setText(QCoreApplication::translate("MainWindow", "Cadastrar M\303\251dico", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCadastrarMedico), QCoreApplication::translate("MainWindow", "Cadastrar M\303\251dico", nullptr));
        labelIdLeito->setText(QCoreApplication::translate("MainWindow", "ID do Leito:", nullptr));
        btnCadastrarLeito->setText(QCoreApplication::translate("MainWindow", "Cadastrar Leito", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCadastrarLeito), QCoreApplication::translate("MainWindow", "Cadastrar Leito", nullptr));
        btnListarPacientes->setText(QCoreApplication::translate("MainWindow", "Listar Pacientes", nullptr));
        btnListarMedicos->setText(QCoreApplication::translate("MainWindow", "Listar M\303\251dicos", nullptr));
        btnConsultarLeitos->setText(QCoreApplication::translate("MainWindow", "Consultar Leitos", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabListar), QCoreApplication::translate("MainWindow", "Listar Dados", nullptr));
        labelCpfAlocar->setText(QCoreApplication::translate("MainWindow", "CPF do Paciente:", nullptr));
        labelCrmAlocar->setText(QCoreApplication::translate("MainWindow", "CRM do M\303\251dico:", nullptr));
        btnAlocar->setText(QCoreApplication::translate("MainWindow", "Alocar Paciente/M\303\251dico", nullptr));
        labelIdLiberar->setText(QCoreApplication::translate("MainWindow", "ID do Leito a Liberar:", nullptr));
        btnLiberarLeito->setText(QCoreApplication::translate("MainWindow", "Liberar Leito", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAlocarLiberar), QCoreApplication::translate("MainWindow", "Alocar/Liberar Leito", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
