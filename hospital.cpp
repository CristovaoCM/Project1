#include "hospital.h"

Hospital::Hospital() {
    conectarAoBanco();
    carregarLeitosDoBanco();
}

Hospital::~Hospital() {
    mysql_close(conn);
}

void Hospital::conectarAoBanco() {
    conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "127.0.0.1", "root", "cris11", "Hosp", 0, nullptr, 0)) {
        std::cerr << "Erro ao conectar ao MySQL: " << mysql_error(conn) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Hospital::carregarLeitosDoBanco() {
    if (mysql_query(conn, "SELECT id, status, cpf_paciente, crm_medico FROM Leito")) {
        std::cerr << "Erro ao carregar leitos: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado dos leitos: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        int id = std::stoi(row[0]);
        std::string status = row[1] ? row[1] : "disponivel";
        int cpf = row[2] ? std::stoi(row[2]) : -1;
        int crm = row[3] ? std::stoi(row[3]) : -1;

        auto leito = std::make_shared<Leito>(id);

        if (cpf != -1) {
            auto paciente = buscarPacientePorCpf(cpf);
            if (paciente) leito->associarPaciente(paciente);
        }

        if (crm != -1) {
            auto medico = buscarMedicoPorCrm(crm);
            if (medico) leito->associarMedico(medico);
        }

        leitos.push_back(leito);
    }

    mysql_free_result(res);
    std::cout << "Leitos carregados do banco de dados com sucesso.\n";
}

void Hospital::cadastrarLeito(int id) {
    auto leito = std::make_shared<Leito>(id);
    leitos.push_back(leito);

    std::string query = "INSERT INTO Leito (id, status) VALUES (" + std::to_string(id) + ", 'disponivel')";
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao cadastrar leito no banco de dados: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Leito " << id << " cadastrado com sucesso.\n";
    }
}

void Hospital::cadastrarPaciente(const std::string& nome, char genero, int idade, int cpf) {
    auto p = std::make_shared<Paciente>(nome, genero, idade, cpf);
    pacientes.push_back(p);

    std::string query = "INSERT INTO Paciente (cpf, nome, idade, genero, data_admissao) VALUES (" +
                        std::to_string(cpf) + ", '" + nome + "', " + std::to_string(idade) + ", '" + genero + "', CURDATE())";

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao cadastrar paciente no banco de dados: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Paciente " << nome << " cadastrado com sucesso.\n";
    }
}

void Hospital::cadastrarMedico(const std::string& nome, const std::string& esp, int crm) {
    auto m = std::make_shared<Medico>(nome, esp, crm);
    medicos.push_back(m);

    std::string query = "INSERT INTO Medico (nome, crm, especialidade) VALUES ('" + nome + "', " + std::to_string(crm) + ", '" + esp + "')";

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao cadastrar medico no banco de dados: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Medico " << nome << " cadastrado com sucesso.\n";
    }
}

void Hospital::listarPacientes() {
    if (mysql_query(conn, "SELECT nome, cpf, idade, genero FROM Paciente")) {
        std::cerr << "Erro ao listar pacientes: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW row;
    std::cout << std::left << std::setw(25) << "Nome"
              << std::setw(15) << "CPF"
              << std::setw(10) << "Idade"
              << std::setw(10) << "Genero" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    while ((row = mysql_fetch_row(res))) {
        std::cout << std::setw(25) << row[0]
                  << std::setw(15) << row[1]
                  << std::setw(10) << row[2]
                  << std::setw(10) << row[3] << std::endl;
    }

    mysql_free_result(res);
}

void Hospital::listarMedicos() {
    if (mysql_query(conn, "SELECT nome, crm, especialidade FROM Medico")) {
        std::cerr << "Erro ao listar medicos: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW row;
    std::cout << std::left << std::setw(25) << "Nome"
              << std::setw(15) << "CRM"
              << std::setw(25) << "Especialidade" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    while ((row = mysql_fetch_row(res))) {
        std::cout << std::setw(25) << row[0]
                  << std::setw(15) << row[1]
                  << std::setw(25) << row[2] << std::endl;
    }

    mysql_free_result(res);
}

std::shared_ptr<Medico> Hospital::buscarMedicoPorCrm(int crm) {
    std::string query = "SELECT nome, especialidade FROM Medico WHERE crm = " + std::to_string(crm);
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao buscar medico no banco de dados: " << mysql_error(conn) << std::endl;
        return nullptr;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return nullptr;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        std::string nome = row[0];
        std::string especialidade = row[1];
        mysql_free_result(res);
        return std::make_shared<Medico>(nome, especialidade, crm);
    }

    mysql_free_result(res);
    return nullptr;
}

std::shared_ptr<Paciente> Hospital::buscarPacientePorCpf(int cpf) {
    std::string query = "SELECT nome, idade, genero FROM Paciente WHERE cpf = " + std::to_string(cpf);
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao buscar paciente no banco de dados: " << mysql_error(conn) << std::endl;
        return nullptr;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        std::cerr << "Erro ao obter resultado: " << mysql_error(conn) << std::endl;
        return nullptr;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        std::string nome = row[0];
        int idade = std::stoi(row[1]);
        char genero = row[2][0];
        mysql_free_result(res);
        return std::make_shared<Paciente>(nome, genero, idade, cpf);
    }

    mysql_free_result(res);
    return nullptr;
}

std::shared_ptr<Leito> Hospital::buscarLeitoDisponivel() {
    for (auto& l : leitos) {
        if (l->getStatus() == "disponivel") return l;
    }
    return nullptr;
}

std::shared_ptr<Leito> Hospital::buscarLeitoPorId(int id) {
    for (auto& l : leitos) {
        if (l->getId() == id) return l;
    }
    return nullptr;
}

void Hospital::alocarPacienteMedico() {
    int cpf, crm;
    std::cout << "Digite o CPF do paciente: ";
    std::cin >> cpf;
    std::cout << "Digite o CRM do medico: ";
    std::cin >> crm;

    auto paciente = buscarPacientePorCpf(cpf);
    auto medico = buscarMedicoPorCrm(crm);
    auto leito = buscarLeitoDisponivel();

    if (!paciente || !medico || !leito) {
        std::cout << "Paciente, medico ou leito disponivel nao encontrado.\n";
        return;
    }

    leito->associarPaciente(paciente);
    leito->associarMedico(medico);

    std::string query = "UPDATE Leito SET cpf_paciente = " + std::to_string(paciente->getCpf()) +
                        ", crm_medico = " + std::to_string(medico->getCrm()) + ", status = 'ocupado' WHERE id = " + std::to_string(leito->getId());

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Erro ao atualizar banco de dados: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Paciente e medico alocados ao leito " << leito->getId() << ".\n";
    }
}

void Hospital::liberarLeito() {
    int id;
    std::cout << "Digite o ID do leito a liberar: ";
    std::cin >> id;
    auto leito = buscarLeitoPorId(id);
    if (leito) {
        leito->liberar(conn);
    } else {
        std::cout << "Leito nao encontrado.\n";
    }
}
