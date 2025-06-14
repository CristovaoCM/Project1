#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <mysql.h>

class Pessoa {
protected:
    std::string nome;

public:
    Pessoa(const std::string& nome) : nome(nome) {}
    virtual void exibirDados() const = 0;
    virtual ~Pessoa() {}
    std::string getNome() const { return nome; }
};

class Paciente : public Pessoa {
private:
    char genero;
    int idade;
    int cpf;

public:
    Paciente(const std::string& nome, char genero, int idade, int cpf)
        : Pessoa(nome), genero(genero), idade(idade), cpf(cpf) {}

    void exibirDados() const override {
        std::cout << "Paciente: " << nome << ", Idade: " << idade << ", CPF: " << cpf << std::endl;
    }

    int getCpf() const { return cpf; }
};

class Medico : public Pessoa {
private:
    int crm;
    std::string especialidade;

public:
    Medico(const std::string& nome, const std::string& esp, int crm)
        : Pessoa(nome), crm(crm), especialidade(esp) {}

    void exibirDados() const override {
        std::cout << "Medico: " << nome << " (" << especialidade << ") - CRM: " << crm << std::endl;
    }

    int getCrm() const { return crm; }

    void consultarLeitos(MYSQL* conn);
    void consultarLeitos(MYSQL* conn, int leito_id);
};

class Leito {
private:
    int id;
    std::string status;
    std::shared_ptr<Paciente> paciente;
    std::shared_ptr<Medico> medico;

public:
    Leito(int id) : id(id), status("disponivel") {}

    void associarPaciente(std::shared_ptr<Paciente> p) {
        paciente = p;
        status = "ocupado";
    }

    void associarMedico(std::shared_ptr<Medico> m) {
        medico = m;
    }

    void liberar(MYSQL* conn) {
        paciente = nullptr;
        medico = nullptr;
        status = "disponivel";

        std::string query = "UPDATE Leito SET cpf_paciente = NULL, crm_medico = NULL, status = 'disponivel' WHERE id = " + std::to_string(id);
        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Erro ao atualizar banco de dados: " << mysql_error(conn) << std::endl;
        } else {
            std::cout << "Leito " << id << " liberado com sucesso.\n";
        }
    }

    int getId() const { return id; }
    std::string getStatus() const { return status; }
};

class Hospital {
private:
    std::vector<std::shared_ptr<Paciente>> pacientes;
    std::vector<std::shared_ptr<Medico>> medicos;
    std::vector<std::shared_ptr<Leito>> leitos;
    MYSQL* conn;

public:
    Hospital();
    ~Hospital();

    void conectarAoBanco();
    void carregarLeitosDoBanco();

    void cadastrarLeito(int id);
    void cadastrarPaciente(const std::string& nome, char genero, int idade, int cpf);
    void cadastrarMedico(const std::string& nome, const std::string& esp, int crm);

    void listarPacientes();
    void listarMedicos();

    std::shared_ptr<Medico> buscarMedicoPorCrm(int crm);
    std::shared_ptr<Paciente> buscarPacientePorCpf(int cpf);
    std::shared_ptr<Leito> buscarLeitoDisponivel();
    std::shared_ptr<Leito> buscarLeitoPorId(int id);

    void alocarPacienteMedico();
    void liberarLeito();

    MYSQL* getConexao() const { return conn; }
};

// Implementações de métodos do Medico
inline void Medico::consultarLeitos(MYSQL* conn) {
    if (mysql_query(conn, "SELECT l.id, l.status, p.nome FROM Leito l LEFT JOIN Paciente p ON l.cpf_paciente = p.cpf")) {
        std::cerr << "Erro ao consultar leitos: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW row;
    std::cout << std::left << std::setw(10) << "Leito"
              << std::setw(15) << "Status"
              << std::setw(20) << "Paciente" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    while ((row = mysql_fetch_row(res))) {
        std::cout << std::setw(10) << row[0]
                  << std::setw(15) << row[1]
                  << std::setw(20) << (row[2] ? row[2] : "Nenhum") << std::endl;
    }

    mysql_free_result(res);
}

inline void Medico::consultarLeitos(MYSQL* conn, int leito_id) {
    std::string query = "SELECT L.id, L.status, P.nome AS paciente_nome, "
                        "M.nome AS medico_nome, M.especialidade "
                        "FROM Leito L "
                        "LEFT JOIN Paciente P ON L.cpf_paciente = P.cpf "
                        "LEFT JOIN Medico M ON L.crm_medico = M.crm "
                        "WHERE L.id = " + std::to_string(leito_id);

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao executar consulta: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* resultado = mysql_store_result(conn);
    if (!resultado) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW linha;
    if ((linha = mysql_fetch_row(resultado)) != nullptr) {
        std::cout << "Informacoes do Leito (ID: " << linha[0] << ")\n";
        std::cout << "Status: " << linha[1] << std::endl;
        std::cout << "Paciente: " << (linha[2] ? linha[2] : "Nao associado") << std::endl;
        std::cout << "Medico: " << (linha[3] ? linha[3] : "Nao associado");
        if (linha[3]) std::cout << " (Especialidade: " << linha[4] << ")";
        std::cout << std::endl;
    } else {
        std::cout << "Leito com ID " << leito_id << " nao encontrado." << std::endl;
    }

    mysql_free_result(resultado);
}

#endif // HOSPITAL_H
