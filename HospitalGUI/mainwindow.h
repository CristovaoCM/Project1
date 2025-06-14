#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hospital.h" // Include the Hospital class header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnCadastrarPaciente_clicked();
    void on_btnCadastrarMedico_clicked();
    void on_btnCadastrarLeito_clicked();
    void on_btnAlocar_clicked();
    void on_btnLiberarLeito_clicked();
    void on_btnListarPacientes_clicked();
    void on_btnListarMedicos_clicked();
    void on_btnConsultarLeitos_clicked();

private:
    Ui::MainWindow *ui;
    Hospital hospital;
};
#endif // MAINWINDOW_H
