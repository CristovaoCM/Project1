#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCadastrarPaciente_clicked() {
    QString nome = ui->inputNomePaciente->text();
    int idade = ui->inputIdadePaciente->text().toInt();
    char genero = ui->comboGeneroPaciente->currentText().at(0).toLatin1();
    int cpf = ui->inputCpfPaciente->text().toInt();

    hospital.cadastrarPaciente(nome.toStdString(), genero, idade, cpf);

    QMessageBox::information(this, "Sucesso", "Paciente cadastrado com sucesso.");
    ui->inputNomePaciente->clear();
    ui->inputIdadePaciente->clear();
    ui->inputCpfPaciente->clear();
}

void MainWindow::on_btnCadastrarMedico_clicked() {
    QString nome = ui->inputNomeMedico->text();
    int crm = ui->inputCrmMedico->text().toInt();
    QString especialidade = ui->inputEspecialidadeMedico->text();

    hospital.cadastrarMedico(nome.toStdString(), especialidade.toStdString(), crm);

    QMessageBox::information(this, "Sucesso", "Médico cadastrado com sucesso.");
    ui->inputNomeMedico->clear();
    ui->inputCrmMedico->clear();
    ui->inputEspecialidadeMedico->clear();
}

void MainWindow::on_btnCadastrarLeito_clicked() {
    int id = ui->inputIdLeito->text().toInt();

    hospital.cadastrarLeito(id);

    QMessageBox::information(this, "Sucesso", "Leito cadastrado com sucesso.");
    ui->inputIdLeito->clear();
}

void MainWindow::on_btnListarPacientes_clicked() {

    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    hospital.listarPacientes();


    std::cout.rdbuf(oldCout);
    ui->outputListar->setText(QString::fromStdString(ss.str()));
}

void MainWindow::on_btnListarMedicos_clicked() {

    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    hospital.listarMedicos();

    // Restore cout
    std::cout.rdbuf(oldCout);
    ui->outputListar->setText(QString::fromStdString(ss.str()));
}

void MainWindow::on_btnAlocar_clicked() {
    int cpf = ui->inputCpfAlocar->text().toInt();
    int crm = ui->inputCrmAlocar->text().toInt();

    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    std::cerr.rdbuf(ss.rdbuf());

    hospital.alocarPacienteMedico();

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    QMessageBox::information(this, "Alocação", QString::fromStdString(ss.str()));
    ui->inputCpfAlocar->clear();
    ui->inputCrmAlocar->clear();
}

void MainWindow::on_btnLiberarLeito_clicked() {
    int id = ui->inputIdLiberar->text().toInt();

    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::streambuf* oldCerr = std::cerr.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    std::cerr.rdbuf(ss.rdbuf());

    hospital.liberarLeito();

    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    QMessageBox::information(this, "Liberação", QString::fromStdString(ss.str()));
    ui->inputIdLiberar->clear();
}

void MainWindow::on_btnConsultarLeitos_clicked() {
    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    if (mysql_query(hospital.getConexao(), "SELECT l.id, l.status, p.nome, m.nome FROM Leito l LEFT JOIN Paciente p ON l.cpf_paciente = p.cpf LEFT JOIN Medico m ON l.crm_medico = m.crm")) {
        std::cerr << "Erro ao consultar leitos: " << mysql_error(hospital.getConexao()) << std::endl;
        ss << "Erro ao consultar leitos: " << mysql_error(hospital.getConexao()) << std::endl;
    } else {
        MYSQL_RES* res = mysql_store_result(hospital.getConexao());
        if (res) {
            MYSQL_ROW row;
            ss << std::left << std::setw(10) << "ID Leito"
               << std::setw(15) << "Status"
               << std::setw(20) << "Paciente"
               << std::setw(20) << "Médico" << std::endl;
            ss << std::string(65, '-') << std::endl;
            while ((row = mysql_fetch_row(res))) {
                ss << std::setw(10) << row[0]
                   << std::setw(15) << row[1]
                   << std::setw(20) << (row[2] ? row[2] : "Nenhum")
                   << std::setw(20) << (row[3] ? row[3] : "Nenhum") << std::endl;
            }
            mysql_free_result(res);
        } else {
            ss << "Erro ao obter resultado dos leitos: " << mysql_error(hospital.getConexao()) << std::endl;
        }
    }

    std::cout.rdbuf(oldCout);
    ui->outputListar->setText(QString::fromStdString(ss.str()));
}
