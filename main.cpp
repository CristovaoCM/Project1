#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mysql.h>
#include <iomanip>

using namespace std;

class Pessoa { // CLASSE PESSOA É A SUPERCLASSE DAS CLASSES PACIENTE E MEDICO
protected:
    string nome;

public:
    Pessoa(const string& nome) : nome(nome) {}
    virtual void exibirDados() const = 0;
	virtual ~Pessoa() {} // destrutor virtual para permitir polimorfismo
};

class Paciente : public Pessoa { // CLASSE PACIENTE
private:
    char genero;
    int idade;
    int cpf;

public:
    Paciente(const string& nome, char genero, int idade, int cpf)
        : Pessoa(nome), genero(genero), idade(idade), cpf(cpf) {
    }

    void exibirDados() const override {
        cout << "Paciente: " << nome << ", Idade: " << idade << ", CPF: " << cpf << endl;
    }

    int getCpf() const { return cpf; }
};


class Medico : public Pessoa { // CLASSE MEDICO
private:
    int crm;
    string especialidade;

public:
    Medico(const string& nome, const string& esp, int crm)
        : Pessoa(nome), crm(crm), especialidade(esp) {
    }

    void exibirDados() const override {
        cout << "Medico: " << nome << " (" << especialidade << ") - CRM: " << crm << endl;
    }

    int getCrm() const { return crm; }

    void consultarLeitos(MYSQL* conn) {
        if (mysql_query(conn, "SELECT l.id, l.status, p.nome FROM Leito l LEFT JOIN Paciente p ON l.cpf_paciente = p.cpf")) {
            cerr << "Erro ao consultar leitos: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        cout << left << setw(10) << "Leito" << setw(15) << "Status" << setw(20) << "Paciente" << endl;
        cout << string(45, '-') << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << setw(10) << row[0]
                << setw(15) << row[1]
                << setw(20) << (row[2] ? row[2] : "Nenhum") << endl;
        }

        mysql_free_result(res);
    }

    void consultarLeitos(MYSQL* conn, int leito_id) { // VOU MUDAR PARA "consultarLeitos" também 
        string query = "SELECT L.id, L.status, P.nome AS paciente_nome, "
            "M.nome AS medico_nome, M.especialidade "
            "FROM Leito L "
            "LEFT JOIN Paciente P ON L.cpf_paciente = P.cpf "
            "LEFT JOIN Medico M ON L.crm_medico = M.crm "
            "WHERE L.id = " + to_string(leito_id);

        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao executar consulta: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* resultado = mysql_store_result(conn);
        if (!resultado) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW linha;
        if ((linha = mysql_fetch_row(resultado)) != nullptr) {
            cout << "Informacoes do Leito (ID: " << linha[0] << ")\n";
            cout << "Status: " << linha[1] << endl;
            cout << "Paciente: " << (linha[2] ? linha[2] : "Nao associado") << endl;
            cout << "Medico: " << (linha[3] ? linha[3] : "Nao associado");
            if (linha[3]) cout << " (Especialidade: " << linha[4] << ")";
            cout << endl;
        }
        else {
            cout << "Leito com ID " << leito_id << " nao encontrado." << endl;
        }

        mysql_free_result(resultado);
    }
};

class Leito { // ADICIONEI UMA CLASSE LEITO
private:
    int id;
    string status;
    shared_ptr<Paciente> paciente;
    shared_ptr<Medico> medico;

public:
    Leito(int id) : id(id), status("disponivel") {}

    void associarPaciente(shared_ptr<Paciente> p) {
        paciente = p;
        status = "ocupado";
    }

    void associarMedico(shared_ptr<Medico> m) {
        medico = m;
    }

    void liberar(MYSQL* conn) {
        paciente = nullptr;
        medico = nullptr;
        status = "disponivel";

        string query = "UPDATE Leito SET cpf_paciente = NULL, crm_medico = NULL, status = 'disponivel' WHERE id = " + to_string(id);
        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao atualizar banco de dados: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Leito " << id << " liberado com sucesso.\n";
        }
    }

    int getId() const { return id; }
    string getStatus() const { return status; }
};


class Hospital { // ADICIONEI UMA CLASSE HOSPITAL
private:
    vector<shared_ptr<Paciente>> pacientes; //vetor de tipos para poder fazer a manipulação dos atributos dentro de dessa classe
    vector<shared_ptr<Medico>> medicos;
    vector<shared_ptr<Leito>> leitos;
    MYSQL* conn;

public:
    Hospital() {
        conectarAoBanco();
        carregarLeitosDoBanco();
    }

    ~Hospital() {
        mysql_close(conn);
    }

    void conectarAoBanco() {
        conn = mysql_init(nullptr);
        if (!mysql_real_connect(conn, "127.0.0.1", "root", "cris11", "Hosp", 0, nullptr, 0)) {
            cerr << "Erro ao conectar ao MySQL: " << mysql_error(conn) << endl;
            exit(EXIT_FAILURE);
        }
    }
	void carregarLeitosDoBanco() {   // coloquei essa função para carregar os leitos do banco em objeto assim que o programa inicia
        if (mysql_query(conn, "SELECT id, status, cpf_paciente, crm_medico FROM Leito")) {
            cerr << "Erro ao carregar leitos: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado dos leitos: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            int id = stoi(row[0]);
            string status = row[1] ? row[1] : "disponivel";
            int cpf = row[2] ? stoi(row[2]) : -1;
            int crm = row[3] ? stoi(row[3]) : -1;

            auto leito = make_shared<Leito>(id);

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
        cout << "Leitos carregados do banco de dados com sucesso.\n";
    }

    void cadastrarLeito(int id) {
        auto leito = make_shared<Leito>(id);
        leitos.push_back(leito);

        string query = "INSERT INTO Leito (id, status) VALUES (" + to_string(id) + ", 'disponivel')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao cadastrar leito no banco de dados: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Leito " << id << " cadastrado com sucesso.\n";
        }
    }

    void cadastrarPaciente(const string& nome, char genero, int idade, int cpf) {
        auto p = make_shared<Paciente>(nome, genero, idade, cpf);
        pacientes.push_back(p);

        string query = "INSERT INTO Paciente (cpf, nome, idade, genero, data_admissao) VALUES (" +
            to_string(cpf) + ", '" + nome + "', " + to_string(idade) + ", '" + genero + "', CURDATE())";

        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao cadastrar paciente no banco de dados: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Paciente " << nome << " cadastrado com sucesso.\n";
        }
    }

    void cadastrarMedico(const string& nome, const string& esp, int crm) {
        auto m = make_shared<Medico>(nome, esp, crm);
        medicos.push_back(m);

        string query = "INSERT INTO Medico (nome, crm, especialidade) VALUES ('" + nome + "', " + to_string(crm) + ", '" + esp + "')";

        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao cadastrar medico no banco de dados: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Medico " << nome << " cadastrado com sucesso.\n";
        }
    }


    void listarPacientes() {
        if (mysql_query(conn, "SELECT nome, cpf, idade, genero FROM Paciente")) {
            cerr << "Erro ao listar pacientes: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        cout << left << setw(25) << "Nome" << setw(15) << "CPF" << setw(10) << "Idade" << setw(10) << "Genero" << endl;
        cout << string(60, '-') << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << setw(25) << row[0]
                << setw(15) << row[1]
                << setw(10) << row[2]
                << setw(10) << row[3] << endl;
        }

        mysql_free_result(res);
    }

    void listarMedicos() {
        if (mysql_query(conn, "SELECT nome, crm, especialidade FROM Medico")) {
            cerr << "Erro ao listar medicos: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        cout << left << setw(25) << "Nome" << setw(15) << "CRM" << setw(25) << "Especialidade" << endl;
        cout << string(65, '-') << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << setw(25) << row[0]
                << setw(15) << row[1]
                << setw(25) << row[2] << endl;
        }

        mysql_free_result(res);
    }

    shared_ptr<Medico> buscarMedicoPorCrm(int crm) {
        string query = "SELECT nome, especialidade FROM Medico WHERE crm = " + to_string(crm);
        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao buscar medico no banco de dados: " << mysql_error(conn) << endl;
            return nullptr;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return nullptr;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            string nome = row[0];
            string especialidade = row[1];
            mysql_free_result(res);
            return make_shared<Medico>(nome, especialidade, crm);
        }

        mysql_free_result(res);
        return nullptr;
    }

    shared_ptr<Paciente> buscarPacientePorCpf(int cpf) {
        string query = "SELECT nome, idade, genero FROM Paciente WHERE cpf = " + to_string(cpf);
        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao buscar paciente no banco de dados: " << mysql_error(conn) << endl;
            return nullptr;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Erro ao obter resultado: " << mysql_error(conn) << endl;
            return nullptr;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            string nome = row[0];
            int idade = stoi(row[1]);
            char genero = row[2][0];
            mysql_free_result(res);
            return make_shared<Paciente>(nome, genero, idade, cpf);
        }

        mysql_free_result(res);
        return nullptr;
    }

    shared_ptr<Leito> buscarLeitoDisponivel() {
        for (auto& l : leitos) {
            if (l->getStatus() == "disponivel") return l;
        }
        return nullptr;
    }

    shared_ptr<Leito> buscarLeitoPorId(int id) {
        for (auto& l : leitos) {
            if (l->getId() == id) return l;
        }
        return nullptr;
    }

    void alocarPacienteMedico() {
        int cpf, crm;
        cout << "Digite o CPF do paciente: "; cin >> cpf;
        cout << "Digite o CRM do medico: "; cin >> crm;

        auto paciente = buscarPacientePorCpf(cpf);
        auto medico = buscarMedicoPorCrm(crm);
        auto leito = buscarLeitoDisponivel();

        if (!paciente || !medico || !leito) {
            cout << "Paciente, medico ou leito disponivel nao encontrado.\n";
            return;
        }

        leito->associarPaciente(paciente);
        leito->associarMedico(medico);

        string query = "UPDATE Leito SET cpf_paciente = " + to_string(paciente->getCpf()) +
            ", crm_medico = " + to_string(medico->getCrm()) + ", status = 'ocupado' WHERE id = " + to_string(leito->getId());
        if (mysql_query(conn, query.c_str())) {
            cerr << "Erro ao atualizar banco de dados: " << mysql_error(conn) << endl;
        }
        else {
            cout << "Paciente e medico alocados ao leito " << leito->getId() << ".\n";
        }
    }

    void liberarLeito() {
        int id;
        cout << "Digite o ID do leito a liberar: ";
        cin >> id;
        auto leito = buscarLeitoPorId(id);
        if (leito) {
            leito->liberar(conn);
        }
        else {
            cout << "Leito nao encontrado.\n";
        }
    }

    MYSQL* getConexao() const { return conn; }
};


int main() {
    Hospital hospital;

    int opcao;
    do {
        cout << "\n1. Cadastrar Leito\n2. Cadastrar Paciente\n3. Cadastrar Medico\n4. Consultar Todos os Leitos\n5. Consultar Leito por ID\n6. Alocar Paciente e Medico a um Leito\n7. Liberar Leito\n8. Listar Pacientes\n9. Listar Medicos\n0. Sair\nEscolha: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {
            int id;
            cout << "ID do leito: ";
            cin >> id;
            hospital.cadastrarLeito(id);
            break;
        }
        case 2: {
            string nome;
            char genero;
            int idade, cpf;
            cout << "Nome: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Genero (M/F): "; cin >> genero;
            cout << "Idade: "; cin >> idade;
            cout << "CPF: "; cin >> cpf;
            hospital.cadastrarPaciente(nome, genero, idade, cpf);
            break;
        }
        case 3: {
            string nome, esp;
            int crm;
            cout << "Nome: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Especialidade: "; getline(cin, esp);
            cout << "CRM: "; cin >> crm;
            hospital.cadastrarMedico(nome, esp, crm);
            break;
        }
        case 4: {
            int crm;
            cout << "CRM do medico: "; cin >> crm;
            auto medico = hospital.buscarMedicoPorCrm(crm);
            if (medico) {
                medico->consultarLeitos(hospital.getConexao());
            }
            else {
                cout << "Medico nao encontrado.\n";
            }
            break;
        }
        case 5: {
            int crm, id;
            cout << "CRM do medico: "; cin >> crm;
            auto medico = hospital.buscarMedicoPorCrm(crm);
            if (medico) {
                cout << "ID do Leito: "; cin >> id;
                medico->consultarLeitos(hospital.getConexao(), id);
            }
            else {
                cout << "Medico nao encontrado.\n";
            }
            break;
        }
        case 6:
            hospital.alocarPacienteMedico();
            break;
        case 7:
            hospital.liberarLeito();
            break;
        case 8:
            hospital.listarPacientes();
            break;
        case 9:
            hospital.listarMedicos();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);

    return 0;
}
