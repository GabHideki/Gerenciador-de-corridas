#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NOME 51
#define PAIS 36
#define TEMPO 7
#define ANOLIM 2024
#define MESLIM 7
#define COMP 8
#define TESTE 100
#define LINHA puts(" --------------------------------")

int controle = 0;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Atleta {
    char nome[NOME];
    char pais[PAIS];
    char sexo;
    Data nascimento;
} Atleta;

typedef struct Competidor {
    Atleta atleta;
    int tempo[TEMPO];
} Competidor;

typedef struct Competicao {
    char nome[NOME];
    Data data;
    Competidor corredor[COMP];
} Competicao;

int ValidarNome(char a[]);
int ValidarPais(char pais[]);
Atleta CadastrarAtleta(void);
int ValidarData(Data dt);
Data ReceberData();
int ValidarIdade(Data dt);
int Treinamento(Competidor a);
Atleta CadastrarAtletaAutomatico(void);
void Melhores(Competidor a[], int b[], int c[], Competidor aux2[]);
int SomarTempo(Competidor a, int b, int c);
void MenuPrincipal(void);
void Modal(void);
int TreinamentoAutomatico(void);
Atleta EscolhaModalRegistro(int a);
void SubMenu(void);
void GerenciarCompeticao(void);
Competicao NomearCompeticao(Competicao a);
Competicao DataCompeticao(Competicao a);
void MenuPais(void);
void ListarCompetidores(void);
void MelhorPais(int a, Competidor b[], int menores[]);
void PrintCompetidor(Competidor a[], int i, int c[]);
void MelhorporSexo(int a, Competidor b[], int menores[]);
void MenuSexo(void);
void MostrarRanking(Competicao a, Competidor b[], int c[]);
void Cadastro(Competidor corredor[]);
void Treinos(Competidor corredor[], int menores[], int controletreinamento);
void SCompetidor(Competidor a[], int c[], int escolha);
void PrintCompetidorSigno(Competidor a[], int i, int c[], int s);
void MenuSigno(Competidor a[], int c[]);
int VerificarSexo(char a);

int ValidarNome(char a[]) {
    int tam = strlen(a), i;

    for(i = 0; i < tam; i++){
        if(tam < 3 || a[0] == ' ' || (a[i] >= '0' && a[i] <= '9')){
            return 0;
        }
    }

    return 1;
}

int VerificarSexo(char a){

    if(a == 'M'){
        return 0;
    }else if(a == 'F'){
        return 0;
    }
    return 1;

}

int ValidarPais(char pais[]) {
    int i;
    char paises[5][20] = {"Brasil", "EUA", "Inglaterra", "Jamaica", "Arabia Saudita"};

    if(!ValidarNome(pais)){
        return 0;
    }

    for(i = 0 ; i < 5 ; i++){
        if(!strcmp(pais, paises[i])){
            return 1;
        }
    }

    return 0;
}

Data ReceberData() {
    Data dt;

    scanf("%d/%d/%d", &dt.dia, &dt.mes, &dt.ano);

    return dt;
}

int ValidarData(Data dt) {
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(dt.ano % 4 == 0){
        dias[1] = 29;
        if(dt.ano % 100 == 0 && (dt.ano / 100) % 4 != 0){
            dias[1] = 28;
        }
    }

    if(dt.dia <= dias[dt.mes - 1] && dt.dia > 0 && dt.mes > 0 && dt.mes < 13){
        return 1;
    }

    return 0;
}

int ValidarIdade(Data dt) {
    if((ANOLIM - dt.ano) > 45){
        return 1;
    }

    if((ANOLIM - dt.ano == 45) && dt.mes <= MESLIM){
        return 1;
    }

    return 0;
}

Atleta CadastrarAtleta(void) {
    Atleta cadastro;

    do{
        printf("Nome.: ");
        fgets(cadastro.nome, NOME, stdin);
        cadastro.nome[strlen(cadastro.nome) - 1] = '\0';
    } while(!ValidarNome(cadastro.nome));

    do{
        printf("Pais (Arabia Saudita / Brasil / EUA / Inglaterra / Jamaica).: ");
        fgets(cadastro.pais, PAIS, stdin);
        cadastro.pais[strlen(cadastro.pais) - 1] = '\0';
    } while(!ValidarPais(cadastro.pais));

    do{
        printf("Sexo (M / F).: ");
        scanf("%c", &cadastro.sexo);
        getchar();
    }while(VerificarSexo(cadastro.sexo));

    do{
        printf("Nascimento (DD/MM/AAAA).: ");
        cadastro.nascimento = ReceberData();
    } while(!ValidarData(cadastro.nascimento) || !ValidarIdade(cadastro.nascimento));

    return cadastro;
}

int Treinamento(Competidor a) {
    int i, menor = 0;

    for(i = 0; i < TEMPO; i++){
        do {
            printf("Tempo %d: ", i + 1);
            scanf("%d", &a.tempo[i]);
            if(a.tempo[i] < 0) {
                printf("Tempo invalido, insira outro valor.:");
            }
        } while (a.tempo[i] < 0);
    }

    for(i = 0; i < TEMPO; i++){
        if(i == 0){
            menor = a.tempo[i];
        }
        if(a.tempo[i] < menor){
            menor = a.tempo[i];
        }
    }

    return menor;
}

void Melhores(Competidor a[], int b[], int c[], Competidor aux2[]) {
    int i;
    int j;
    int menor;
    Competidor aux;

    for(i = 0; i < controle ; i++) {
        aux2[i] = a[i];
        c[i] = b[i];
    }

    for(i = 0; i < controle - 1; i++){
        for(j = i + 1; j < controle; j++){
            if(c[i] > c[j]) {
                menor = c[j];
                c[j] = c[i];
                c[i] = menor;
                aux = aux2[j];
                aux2[j] = aux2[i];
                aux2[i] = aux;
            }
        }
    }
}

Atleta CadastrarAtletaAutomatico(void) {
    Atleta cadastro;
    char paises[5][PAIS] = {"Brasil", "EUA", "Inglaterra", "Jamaica", "Arabia Saudita"};
    char nomes[40][NOME] = {"Gabriel", "Lucas", "Rafael", "Joao", "Pedro", "Matheus", "Gustavo", "Felipe", "Thiago", "Ricardo",
    "Andre", "Bruno", "Leonardo", "Daniel", "Eduardo", "Marcelo", "Vinicius", "Hugo", "Arthur", "Carlos",
    "Mariana", "Isabela", "Amanda", "Ana", "Carolina", "Fernanda", "Beatriz", "Larissa", "Camila", "Juliana",
    "Gabriela", "Juliana", "Natalia", "Rafaela", "Luana", "Sofia", "Tatiane", "Priscila", "Jessica", "Leticia"};
    char sobrenomes[30][NOME] = {" Silva", " Souza", " Rocha", " Lima", " Costa", " Moraes", " Santos", " Almeida", " Fernandes",
   " Martins", " Oliveira", " Andrade", " Pinto", " Reis", " Duarte", " Gomes", " Silva", " Costa", " Pereira", " Mendes",
   " Cardoso", " Barbosa", " Nogueira", " Campos", " Vieira", " Moreira", " Freitas", " Teixeira", " Silveira", " Macedo"};

    int i = rand() % 40;

    strcpy(cadastro.nome, nomes[i]);
    strcat(cadastro.nome, sobrenomes[rand() % 30]);
    strcpy(cadastro.pais, paises[rand() % 5]);
    cadastro.sexo = (i < 20) ? 'M' : 'F';
    cadastro.nascimento.dia = rand() % 28 + 1;
    cadastro.nascimento.mes = rand() % 12 + 1;
    cadastro.nascimento.ano = rand() % 50 + 1920;

    return cadastro;
}

int SomarTempo(Competidor a, int b, int c) {
    int i, j, cont, res = 0;

    if(b == 1) {
        printf("Insira os tempos do atleta %d.:\n", c + 1);
        for(i = 0; i < 5 ; i++){
            printf("Tempo %d: ", i + 1);
            scanf("%d", &a.tempo[i]);
        }
    } else {
        for(i = 0; i < 5 ; i++){
            a.tempo[i] = rand() % 180 + 1;
        }
    }

    for(i = 0; i < 5 ; i++){
        for(j = i + 1; j < 5 ; j++){
            if(a.tempo[i] < a.tempo[j]){
                cont = a.tempo[j];
                a.tempo[j] = a.tempo[i];
                a.tempo[i] = cont;
            }
        }
    }

    for(i = 1; i < 4 ; i++){
        res += a.tempo[i];
    }

    return res;
}

void MenuPrincipal(void) {
    puts("");
    LINHA;
    printf("|\t       %s \t\t |\n", "MENU");
    printf("| 1 - %-26s |\n", "Cadastrar atletas");
    printf("| 2 - %-26s |\n", "Treinamento");
    printf("| 3 - %-26s |\n", "Atletas mais velhos");
    printf("| 4 - %-26s |\n", "Signos dos Atletas");
    printf("| 5 - %-26s |\n", "Atletas cadastrados");
    printf("| 6 - %-26s |\n", "Classificados");
    printf("| 7 - %-26s |\n", "Competicao final");
    printf("| 8 - %-26s |\n", "Sair");
    LINHA;
}

Atleta EscolhaModalRegistro(int a) {
    Atleta b;

    switch(a){
        case 1:
            b = CadastrarAtleta();
            getchar();
            return b;
        default:
            return CadastrarAtletaAutomatico();
    }
}

int TreinamentoAutomatico(void) {
    int a[7], menor = 0, i, j;

    for(j = 0; j < TEMPO; j++) {
        a[j] = rand() % 180 + 60;
    }

    for(i = 0; i < TEMPO; i++){
        if(i == 0){
            menor = a[i];
        }
        if(a[i] < menor){
            menor = a[i];
        }
    }

    return menor;
}

void Modal(void) {
    puts("");
    LINHA;
    printf("| %-30s |\n", "Forma de preenchimento");
    printf("| 1 - %-26s |\n", "Manualmente");
    printf("| 2 - %-26s |\n", "Automaticamente");
    LINHA;
}

void SubMenu(void) {
    puts("");
    LINHA;
    printf("|\t  %s  \t |\n", "COMPETICAO FINAL");
    printf("| 1 - %-26s |\n", "Gerenciar Competicao");
    printf("| 2 - %-26s |\n", "Listar Competidores");
    printf("| 3 - %-26s |\n", "Ranking");
    printf("| 4 - %-26s |\n", "Retornar ao menu");
    LINHA;
}

void GerenciarCompeticao(void) {
    puts("");
    LINHA;
    printf("|      %s      |\n", "GERENCIAR COMPETICAO");
    printf("| 1 - %-26s |\n", "Dados da Competicao");
    printf("| 2 - %-26s |\n", "Inserir tempos");
    printf("| 3 - %-26s |\n", "Voltar");
    LINHA;
}

Competicao NomearCompeticao(Competicao a) {
    int i;

    printf("Qual a competicao (modalidade)?\n");
    fgets(a.nome, NOME, stdin);
    i = strlen(a.nome);
    a.nome[i - 1] = '\0';

    return a;
}

Competicao DataCompeticao(Competicao a) {
    do {
        printf("\nInforme a data em que ocorrera a competicao (DD/MM/AAAA).: ");
        a.data = ReceberData();
    } while (!ValidarData(a.data));

    return a;
}

void MenuPais(void) {
    puts("");
    LINHA;
    printf("|         %s        |\n", "FILTRO POR PAIS");
    printf("| 1 - %-26s |\n", "Atletas da Arabia Saudita");
    printf("| 2 - %-26s |\n", "Atletas do Brasil");
    printf("| 3 - %-26s |\n", "Atletas dos EUA");
    printf("| 4 - %-26s |\n", "Atletas da Inglaterra");
    printf("| 5 - %-26s |\n", "Atletas da Jamaica");
    printf("| 6 - %-26s |\n", "Voltar a Listar");
    LINHA;
}

void ListarCompetidores(void) {
    puts("");
    LINHA;
    printf("|       %s      |\n", "LISTAR COMPETIDORES");
    printf("| 1 - %-26s |\n", "Todos os Competidores");
    printf("| 2 - %-26s |\n", "Filtrar por Pais");
    printf("| 3 - %-26s |\n", "Filtrar por Sexo");
    printf("| 4 - %-26s |\n", "Voltar");
    LINHA;
}

void PrintCompetidor(Competidor a[], int i, int c[]) {
    printf("| %-50s | %-20s | %c | %02d/%02d/%04d | %02d:%02d |\n", a[i].atleta.nome, a[i].atleta.pais, a[i].atleta.sexo, a[i].atleta.nascimento.dia, a[i].atleta.nascimento.mes, a[i].atleta.nascimento.ano, c[i] / 60, c[i] % 60);
}

void MelhorPais(int a, Competidor b[], int menores[]) {
    int i,j = 0;

    puts("");

    switch (a) {
        case 1:
            for (i = 0; i < COMP; i++) {
                if(strcmp(b[i].atleta.pais, "Arabia Saudita") == 0) {
                    PrintCompetidor(b, i, menores);
                } else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste pais\n");
            }
            break;
        case 2:
            for (i = 0; i < COMP; i++) {
                if(strcmp(b[i].atleta.pais, "Brasil") == 0) {
                    PrintCompetidor(b, i, menores);
                } else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste pais\n");
            }
            break;
        case 3:
            for (i = 0; i < COMP; i++) {
                if(strcmp(b[i].atleta.pais, "EUA") == 0) {
                    PrintCompetidor(b, i, menores);
                } else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Não existem competidores deste pais\n");
            }
            break;
        case 4:
            for (i = 0; i < COMP; i++) {
                if(strcmp(b[i].atleta.pais, "Inglaterra") == 0) {
                    PrintCompetidor(b, i, menores);
                } else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste pais\n");
            }
            break;
        case 5:
            for (i = 0; i < COMP; i++) {
                if(strcmp(b[i].atleta.pais, "Jamaica") == 0) {
                    PrintCompetidor(b, i, menores);
                } else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste pais\n");
            }
            break;
        default:
            break;
    }
}

void MenuSexo(void) {
    puts("");
    LINHA;
    printf("|          %s       |\n", "FILTRO POR SEXO");
    printf("| 1 - %-26s |\n", "Masculino");
    printf("| 2 - %-26s |\n", "Feminino");
    printf("| 3 - %-26s |\n", "Voltar a Listar");
    LINHA;
}

void MelhorporSexo(int a, Competidor b[], int menores[]) {
    int i, j = 0;

    switch (a) {
        case 1:
            puts("");
            for (i = 0; i < COMP; i++) {
                if(b[i].atleta.sexo == 'M') {
                    PrintCompetidor(b, i, menores);
                }else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste sexo\n");
            }
            break;
        case 2:
            puts("");
            for (i = 0; i < COMP; i++) {
                if(b[i].atleta.sexo == 'F') {
                    PrintCompetidor(b, i, menores);
                }else {
                    j++;
                }
            }
            if(j == COMP) {
                printf("Nao existem competidores deste sexo\n");
            }
            break;
        default:
            break;
    }
}

void MostrarRanking(Competicao a, Competidor b[], int c[]) {
    int i;

    printf("\nCompeticao: %s\n", a.nome);
    printf("Data: %02d/%02d/%04d\n", a.data.dia, a.data.mes, a.data.ano);
    printf("Classificacao Final:\n");

    for(i = 0; i < COMP; i++) {
        if(i == 0) {
            printf("%d %-7s: ", i + 1, "OURO");
        } else if(i == 1) {
            printf("%d %-7s: ", i + 1, "PRATA");
        } else if(i == 2) {
            printf("%d %-7s: ", i + 1, "BRONZE");
        } else {
            printf("%d        : ", i + 1);
        }
        printf("| %-20s | %-20s | %02d:%02d |\n", b[i].atleta.nome, b[i].atleta.pais, c[i] / 60, c[i] % 60);
    }
}

void Cadastro(Competidor corredor[]) {
    int registros, modo, i;

    if(controle == 100) {
        printf("\nVoce chegou ao limite de atletas.\n");
    } else {
        printf("\nInsira a quantidade de atletas que voce deseja cadastrar.: ");
        do {
            scanf("%d", &registros);
            if(registros + controle > 100 || registros <= 0) {
                printf("\nO Numero de atletas escolhido e invalido, insira outra quantidade.: ");
            }
        } while(registros + controle > 100 || registros <= 0);

        Modal();
        scanf("%d", &modo);
        getchar();
        puts("");

        for(i = controle; i < (registros + controle); i++){
            if(modo == 2) {
                printf("Gerando %d/%d\n", i+1, registros+controle);
            } else {
                printf("Insira os dados do %d atleta\n", i+1);
            }
            corredor[i].atleta = EscolhaModalRegistro(modo);
        }

        controle = i;
    }
}

void Treinos(Competidor corredor[], int menores[], int controletreinamento) {
    int modo, i;
    Modal();
    scanf("%d", &modo);
    puts("");

    for(i = controletreinamento; i < controle ; i++) {
        if(modo == 1) {
            printf("Tempos do atleta %d.:\n", i + 1);
            menores[i] = Treinamento(corredor[i]);
        } else {
            menores[i] = TreinamentoAutomatico();
        }
        printf("Menor tempo do atleta %d.: %02d:%02d\n", i + 1, menores[i] / 60, menores[i] % 60);
    }
}

void ListarTodosCompetidores(Competidor corredor[], int menores[]) {
    int i;

    for(i = 0; i < controle; i++) {
        PrintCompetidor(corredor, i, menores);
    }
}

void CompeticaoFinal(Competidor corredor[], int menores[], Competicao corrida) {
    int escolhasub, escolhagerenciar, escolhatempo, i, escolhalista, escolhapais, escolhasexo, tempo = 0, ordenado[TESTE], armazenar;
    Competidor aux[TESTE];

    do {
        SubMenu();
        scanf("%d", &escolhasub);
        switch(escolhasub) {
            case 1:
                do {
                    GerenciarCompeticao();
                    scanf("%d", &escolhagerenciar);
                    getchar();
                    switch(escolhagerenciar) {
                        case 1:
                            printf("\nModalidade.: %s\n", corrida.nome);
                            printf("Data da competicao.: %02d/%02d/%04d\n", corrida.data.dia, corrida.data.mes, corrida.data.ano);
                            break;
                        case 2:
                            if(tempo) {
                                puts("\nVoce ja inseriu os tempos dos atletas!");
                                break;
                            } else {
                                Modal();
                                scanf("%d", &escolhatempo);
                                puts("");
                                for(i = 0; i < COMP; i++) {
                                    menores[i] = SomarTempo(corredor[i], escolhatempo, i);
                                    printf("Somatoria dos tempos do atleta %d (%s).: ", i + 1, corredor[i].atleta.nome);
                                    printf("%02d:%02d\n", menores[i] / 60, menores[i] % 60);
                                    if(i < 7){
                                        puts("");
                                    }
                                }
                                tempo = 1;
                            }
                            break;
                        default:
                            break;
                    }
                } while(escolhagerenciar != 3);
                break;
            case 2:
                do {
                    ListarCompetidores();
                    scanf("%d", &escolhalista);
                    getchar();
                    switch(escolhalista) {
                        case 1:
                            puts("");
                            for(i = 0; i < COMP; i++) {
                                PrintCompetidor(corredor, i, menores);
                            }
                            break;
                        case 2:
                            do {
                                MenuPais();
                                scanf("%d", &escolhapais);
                                getchar();
                                MelhorPais(escolhapais, corredor, menores);
                            } while (escolhapais != 6);
                            break;
                        case 3:
                            do {
                                MenuSexo();
                                scanf("%d", &escolhasexo);
                                getchar();
                                MelhorporSexo(escolhasexo, corredor, menores);
                            } while (escolhasexo != 3);
                            break;
                        default:
                            break;
                    }
                } while (escolhalista != 4);
                break;
            case 3:
                if(tempo) {
                    armazenar = controle;
                    controle = 8;
                    Melhores(corredor, menores, ordenado, aux);
                    MostrarRanking(corrida, aux, ordenado);
                    controle = armazenar;
                } else {
                    puts("\nVoce ainda nao adicionou os tempos da competicao!");
                    puts("Selecione a opcao \"Gerenciar Competicao\" e, em seguida, a opcao \"Inserir Tempos\"");
                }
                break;
            default:
                break;
        }
    } while(escolhasub != 4);
}

void MaisVelhos(Competidor a[], int c[]) {
    int i, j, tempo[controle], auxtempo;
    Competidor velhos[controle], aux;

    for(i = 0; i < controle; i++){
        velhos[i] = a[i];
        tempo[i] = c[i];
    }

    for(i = 0 ; i < controle - 1; i++){
        for(j = i + 1 ; j < controle ; j++){
            if(velhos[i].atleta.nascimento.ano > velhos[j].atleta.nascimento.ano){
                aux = velhos[i];
                velhos[i] = velhos[j];
                velhos[j] = aux;
                auxtempo = tempo[i];
                tempo[i] = tempo[j];
                tempo[j] = auxtempo;
            } else if(velhos[i].atleta.nascimento.ano == velhos[j].atleta.nascimento.ano && velhos[i].atleta.nascimento.mes > velhos[j].atleta.nascimento.mes) {
                aux = velhos[i];
                velhos[i] = velhos[j];
                velhos[j] = aux;
                auxtempo = tempo[i];
                tempo[i] = tempo[j];
                tempo[j] = auxtempo;
            } else if(velhos[i].atleta.nascimento.ano == velhos[j].atleta.nascimento.ano && velhos[i].atleta.nascimento.mes == velhos[j].atleta.nascimento.mes && velhos[i].atleta.nascimento.dia > velhos[j].atleta.nascimento.dia) {
                aux = velhos[i];
                velhos[i] = velhos[j];
                velhos[j] = aux;
                auxtempo = tempo[i];
                tempo[i] = tempo[j];
                tempo[j] = auxtempo;
            }
        }
    }
    puts("");
    for(i = 0; i < 5 ; i++){
        PrintCompetidor(velhos, i, tempo);
    }
}

void PrintCompetidorSigno(Competidor a[], int i, int c[], int s) {
    char signo[12][12] = {"Aries", "Touro", "Gemeos", "Cancer", "Leao", "Virgem", "Libra", "Escorpiao", "Sagitario", "Capricornio", "Aquario", "Peixes"};
    printf("| %-50s | %-20s | %c | %02d/%02d/%04d | %02d:%02d | %-11s |\n", a[i].atleta.nome, a[i].atleta.pais, a[i].atleta.sexo, a[i].atleta.nascimento.dia, a[i].atleta.nascimento.mes, a[i].atleta.nascimento.ano, c[i] / 60, c[i] % 60, signo[s]);
}

void SCompetidor(Competidor a[], int c[], int escolha) {

    int i, b[TESTE];
    float porcentagem, signos[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char signo[12][12] = {"Aries", "Touro", "Gemeos", "Cancer", "Leao", "Virgem", "Libra", "Escorpiao", "Sagitario", "Capricornio", "Aquario", "Peixes"};

    for(i = 0; i < controle; i++) {
        if ((a[i].atleta.nascimento.dia >= 21 && a[i].atleta.nascimento.mes == 3) || (a[i].atleta.nascimento.dia <= 20 && a[i].atleta.nascimento.mes == 4)) {
            signos[0]++;
            b[i] = 0;
        }else if((a[i].atleta.nascimento.dia >= 21 && a[i].atleta.nascimento.mes == 4) || (a[i].atleta.nascimento.dia <= 20 && a[i].atleta.nascimento.mes == 5)) {
            signos[1]++;
            b[i] = 1;
        }else if((a[i].atleta.nascimento.dia >= 21 && a[i].atleta.nascimento.mes == 5) || (a[i].atleta.nascimento.dia <= 20 && a[i].atleta.nascimento.mes == 6)) {
            signos[2]++;
            b[i] = 2;
        }else if((a[i].atleta.nascimento.dia >= 21 && a[i].atleta.nascimento.mes == 6) || (a[i].atleta.nascimento.dia <= 22 && a[i].atleta.nascimento.mes == 7)) {
            signos[3]++;
            b[i] = 3;
        }else if((a[i].atleta.nascimento.dia >= 23 && a[i].atleta.nascimento.mes == 7) || (a[i].atleta.nascimento.dia <= 22 && a[i].atleta.nascimento.mes == 8)) {
            signos[4]++;
            b[i] = 4;
        }else if((a[i].atleta.nascimento.dia >= 23 && a[i].atleta.nascimento.mes == 8) || (a[i].atleta.nascimento.dia <= 22 && a[i].atleta.nascimento.mes == 9)) {
            signos[5]++;
            b[i] = 5;
        }else if((a[i].atleta.nascimento.dia >= 23 && a[i].atleta.nascimento.mes == 9) || (a[i].atleta.nascimento.dia <= 22 && a[i].atleta.nascimento.mes == 10)) {
            signos[6]++;
            b[i] = 6;
        }else if((a[i].atleta.nascimento.dia >= 23 && a[i].atleta.nascimento.mes == 10) || (a[i].atleta.nascimento.dia <= 21 && a[i].atleta.nascimento.mes == 11)) {
            signos[7]++;
            b[i] = 7;
        }else if((a[i].atleta.nascimento.dia >= 22 && a[i].atleta.nascimento.mes == 11) || (a[i].atleta.nascimento.dia <= 21 && a[i].atleta.nascimento.mes == 12)) {
            signos[8]++;
            b[i] = 8;
        }else if((a[i].atleta.nascimento.dia >= 22 && a[i].atleta.nascimento.mes == 12) || (a[i].atleta.nascimento.dia <= 20 && a[i].atleta.nascimento.mes == 1)) {
            signos[9]++;
            b[i] = 9;
        }else if((a[i].atleta.nascimento.dia >= 21 && a[i].atleta.nascimento.mes == 1) || (a[i].atleta.nascimento.dia <= 18 && a[i].atleta.nascimento.mes == 2)) {
            signos[10]++;
            b[i] = 10;
        }else if((a[i].atleta.nascimento.dia >= 19 && a[i].atleta.nascimento.mes == 2) || (a[i].atleta.nascimento.dia <= 20 && a[i].atleta.nascimento.mes == 3)) {
            signos[11]++;
            b[i] = 11;
        }
    }

    switch(escolha){
        case 1:
            puts("");
            for(i = 0; i < controle; i++){
                PrintCompetidorSigno(a, i, c, b[i]);
            }
            break;
        case 2:
            puts("");
            for(i = 0; i < 12 ; i++){
                porcentagem = (signos[i] / controle) * 100;
                printf("| %-11s | %05.2f %% | ",signo[i], porcentagem);
                while(porcentagem >= 1){
                    printf("*");
                    porcentagem -= 1;
                }
                if(i < 11){
                    puts("");
                }
            }
            puts("");
            break;
        default:
            break;
    }

}

void MenuSigno(Competidor a[], int c[]) {
    int escolhasigno;

    do{
        puts("");
        LINHA;
        printf("|        %s      |\n", "SIGNOS DOS ATLETAS");
        printf("| 1 - %-26s |\n", "Listar todos");
        printf("| 2 - %-26s |\n", "Porcentagem dos signos");
        printf("| 3 - %-26s |\n", "Voltar ao menu");
        LINHA;
        scanf("%d", &escolhasigno);
        SCompetidor(a, c, escolhasigno);
    }while(escolhasigno != 3);
}

void Historia(Competicao a){
    puts("\nSeja bem vindo ao sistema de gerenciamento de competicoes!");
    printf("A competicao %s sera realizada no dia %02d/%02d/%04d contara com no maximo 100\n", a.nome, a.data.dia, a.data.mes, a.data.ano);
    puts("atletas na fase de treinamento, onde somente atletas com 45 anos ou mais,");
    puts("completados ate 31 de julho de 2024, poderao participar. Alem disso,");
    puts("participarao apenas atletas dos paises: Arabia Saudita, Brasil, EUA,");
    puts("Inglaterra e Jamaica. Apos a fase de treinamento serao selecionados 8");
    puts("atletas para a Grande Final. Atencao, o tempo deve estar em segundos.");
}

int main(void) {
    Competidor corredor[TESTE], coraux[TESTE];
    int i, escolha, menores[TESTE], ordenado[TESTE], controletreinamento = 0, contcad = 0, conttreino = 0, contclas = 0;
    Competicao corrida;

    srand(time(NULL));

    corrida = NomearCompeticao(corrida);
    corrida = DataCompeticao(corrida);
    Historia(corrida);

    while(1){
        MenuPrincipal();
        scanf("%d", &escolha);
        getchar();
        switch(escolha) {
            case 1:
                Cadastro(corredor);
                contcad = 1;
                break;
            case 2:
                if(contcad){
                    Treinos(corredor, menores, controletreinamento);
                    controletreinamento = controle;
                } else {
                    puts("\nPara acessar \"Treinamento\" cadastre algum atleta antes.");
                }
                conttreino = 1;
                break;
            case 3:
                if(controle < 5){
                    puts("\nPara acessar \"Atletas mais velhos\" cadastre no minino 5 atletas.");
                }else{
                    MaisVelhos(corredor, menores);
                }

                break;
            case 4:
                if(contcad){
                    MenuSigno(corredor, menores);
                } else {
                    puts("\nPara acessar \"Signos dos atletas\" cadastre algum atleta antes.");
                }
                break;
            case 5:
                if(contcad){
                    puts("");
                    ListarTodosCompetidores(corredor, menores);
                } else {
                    puts("\nPara acessar \"Atletas cadastrados\" cadastre algum atleta antes.");
                }
                break;
            case 6:
                if(controle >= 8){
                    if(conttreino){
                        if(controletreinamento == controle) {
                            Melhores(corredor, menores, ordenado, coraux);
                            puts("");
                            for(i = 0; i < COMP; i++) {
                                PrintCompetidor(coraux, i, ordenado);
                            }
                            contclas = 1;
                        } else {
                            puts("\nPara acessar \"Classificados\" realize o treinamento de todos os atletas antes.");
                        }
                    } else {
                        puts("\nPara acessar \"Classificados\" realize o treinamento de atletas antes.");
                    }
                } else {
                    puts("\nPara acessar \"Classificados\" cadastre no minino 8 atletas.");
                }
                break;
            case 7:
                if(contclas){
                    CompeticaoFinal(coraux, menores, corrida);
                } else {
                    puts("\nPara acessar \"Competicao final\" faca a classificacao de atletas antes.");
                }
                break;
            default:
                return 0;
        }
    }
}
