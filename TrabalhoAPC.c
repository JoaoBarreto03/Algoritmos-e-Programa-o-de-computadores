#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define CHAR_VOO 9
#define CHAR_RESERVA 10
#define QUANT_CPF 15
#define MAX_NOME 1000

void menu(); // Protótipo de apresentação do menu;
void cadastrar_voo(); // Cadastro do voo;
void cadastrar_reserva(); // Cadastro da reserva;
void consultar_voo(); // Consulta do voo;
void consultar_reserva(); // Consulta de reserva;
void consultar_passageiro(); // Consulta de passageiro;
void cancelar_voo(); // Cancelar um voo;
void cancelar_reserva(); // Cancelamento de reserva;
void excluir_voo(); // Exclusão de um voo;
char cadastrar_numVoo(char numVoo[CHAR_VOO]); // Função de cadastro do número do voo (JEB-XXXX);
int valida_data(int dia, int mes, int ano); // Função para validar a data no formato (DD/MM/AAAA);
int valida_hora(int hora, int minuto); // Função para validar a hora (HH:MM);
char status_voo(char status); // Função para validar o status do voo ('A' = Ativo; 'C' = Cancelado);
char cadastrar_numReserva(char numReserva[CHAR_RESERVA]); // Função para o cadastro do número da reserva (GB-XXXXXX);
char validarCPF(char numCPF[QUANT_CPF]); // Função para validar o CPF;
int valida_data_nascimento(int diaNascimento, int mesNascimento, int anoNascimento); // Função para validar a data de nascimento;
char sexo_do_passageiro(char caracter_sexo); // Função para validar o sexo do passageiro (M = Masculino/ F = Feminino/ O = Outro);
char status_reserva(char atividade_da_reserva); // Função para mostrar se a reserva está ativa ou cancelada (A = Ativa/ C = Cancelada);

struct Voo{ // Struct para declaração de variáveis correspondentes ao cadastro do voo;
    char numVoo[CHAR_VOO]; // Número do voo;
    char status; // Status do voo 
    int dia, mes, ano, hora, minuto; // Variáveis de data e hora;
    int quant_passageiros; // Quantidade de passageiros do voo;
};

struct Reserva{
    char numReserva[CHAR_RESERVA]; // Número da reserva;
    char numVoo[CHAR_VOO]; // Número do voo;
    char numCPF[QUANT_CPF]; // CPF do passageiro;
    char nomeCompleto[MAX_NOME]; // Nome completo;
    char caracter_sexo; // Sexo;
    char atividade_da_reserva; // Indicar se a reserva está ativa ou cancelada;
    int diaNascimento, mesNascimento, anoNascimento; // Data de nascimento do passageiro;
};

struct ConsultarVoo{ // Struct para consulta de voo
    char numVoo[CHAR_VOO]; // Leitura do voo que deverá ser consultado
};

int main()
{
   int escolhaOpcao; // Escolha de opções do menu;
   
    do { // Repetir o menu, enquanto o número inserido for diferente de 9;
        menu(); // Impressão de Menu
        printf("\n");
        printf("\nEscolha a opção desejada: \n");
        scanf("%d", &escolhaOpcao);
    
        switch(escolhaOpcao){ // Escolha das opções do menu;
        case 1: // Cadastrar voo;
            cadastrar_voo();
            break;
            
        case 2: // Cadastrar reserva;
            cadastrar_reserva();
            break;
        
        case 3: // Consultar voo;
            consultar_voo();
            break;
        
        case 4: // Consultar reserva;
            consultar_reserva();
            break;
            
        case 5: // Consultar passageiro;
            consultar_passageiro();
            break;
        
        case 6: // Cancelar voo;
            cancelar_voo();
            break;
            
        case 7: // Cancelar reserva;
            cancelar_reserva();
            break;
            
        case 8: // Excluir voo;
            excluir_voo();
            break;
            
        case 9: // Sair do programa;
            printf("\nOperação finalizada!\n");
        }
        
    } while(escolhaOpcao != 9);


}



void menu(){
    printf("-------GALATIC BIRDS-------\n");
    printf("--O ESPAÇO AO SEU ALCANCE--\n\n");
    printf("1) Cadastrar voo\n");
    printf("2) Cadastrar reserva\n");
    printf("3) Consultar voo\n");
    printf("4) Consultar reserva\n");
    printf("5) Consultar passageiro\n");
    printf("6) Cancelar voo\n");
    printf("7) Cancelar reserva\n");
    printf("8) Excluir voo\n");
    printf("9) Sair do programa\n");
}

void cadastrar_voo(){
    char statusVoo; // Variáveis para substituição da função status_voo no int main;
    int i; // Contador;
    int erro = 0; // Variável de erro;
    int data, horario; // Variável de substituição das funções valida_data e valida_hora no int main, respectivamente;
    FILE *cadastro_voo; // Arquivo que armazenará os voos cadastrados;
    char voo; // Variável de substituição da função cadastrarVoo no int main;
    struct Voo vw; // Declaração do struct Voo para escrita em arquivo (vw = voo write);
    struct Voo vr; // Declaração do struct Voo para leitura no arquivo (vr = voo read);

    struct tm *data_hora_atual; // Declaração do struct para ler os voos a partir da data atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    
    cadastro_voo = fopen("Voos.bin","ab"); // Abertura do arquivo de armazenamento de voos cadastrados;
    if (cadastro_voo == NULL){
        printf("Erro ao tentar abrir o arquivo!");
    }else{
        printf("Digite o número do voo que deverá ser cadastrado: \n");
        scanf("%s", vw.numVoo);
        voo = cadastrar_numVoo(vw.numVoo);
        
        if(voo == 1){ // Se o voo for incorreto;
            printf("\nFalha no cadastro\n");
        } else { // Se for correto;
        
            printf("Informe a data do voo: \n");
            scanf("%02d/%02d/%04d", &vw.dia,&vw.mes,&vw.ano);
            
            if((data_hora_atual->tm_mday == vw.dia) && (data_hora_atual->tm_mon+1 == vw.mes) && (data_hora_atual->tm_year+1900 == vw.ano)){ // Condição para que a data inserida não seja a atual
                printf("\nData inválida\n");
            }else{
        
                data = valida_data(vw.dia, vw.mes, vw.ano);
        
                if(data == 1){ // Se a data for inválida;
                    printf("\nData inválida\n");
                } else { // Se a data for válida;
                    printf("Informe o horário do voo: \n");
                    scanf("%d:%d", &vw.hora,&vw.minuto);

                    horario = valida_hora(vw.hora, vw.minuto);
        
                    if(horario == 1){ //Se o horário for inválido;
                        printf("\nHoras ou minutos inválidos\n");
                    }else{ // Se o horário for válido;
                        printf("Informe a quantidade de passageiros do voo: \n");
                        scanf("%d", &vw.quant_passageiros);
                        
                        if(vw.quant_passageiros <= 0){ // Se a capacidade de passageiros for nula ou negativa;
                            printf("Capacidade de voo negativa ou nula!\n\n");
                        }else{
                    
                            printf("Informe o status do voo: \n");
                            scanf("%s", &vw.status);
                    
                            statusVoo = status_voo(vw.status);
                    
                            if(statusVoo == 1){
                                printf("\nStatus inválido\n");
                            }else{
                                fclose(cadastro_voo);
                                cadastro_voo = fopen("Voos.bin","rb");
                                fread(&vr, sizeof(struct Voo), 1, cadastro_voo);
                                if(strcmp(vw.numVoo, vr.numVoo) == 0){
                                    printf("\nVoo já cadastrado!\n");
                                }else{
                            // Saída do cadastro de voo;
                                    fclose(cadastro_voo);
                                    cadastro_voo = fopen("Voos.bin","ab"); // Abertura do arquivo de armazenamento de voos cadastrados;
                                    if(cadastro_voo == NULL){
                                        printf("\nErro ao tentar abrir o arquivo!\n");
                                    }else{
                                        fseek(cadastro_voo, 1, SEEK_SET);
                                        fwrite(&vw, 1, sizeof(struct Voo), cadastro_voo);
                                        fclose(cadastro_voo); // Fechamento do arquivo
                                        printf("\nVoo cadastrado!\n\n"); // Mensagem de saída para o usuário;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void cadastrar_reserva(){
    int i; // Contador;
    int erro = 0; // Variável de erro;
    char voo; // Variável de substituição da função cadastrarVoo no int main;
    char status; // Variável de substituição da função status_voo no int main;
    FILE *cadastro_voo; // Arquivo que armazenará os voos cadastrados;
    FILE *cadastro_reserva; // Arquivo que armazenará resevas cadastradas;
    char reserva; // Variável de substituição da função numReserva;
    char CPF; // Variável de substituição da função validarCPF no int main;
    char statusReserva; // Variável de substituição da função status_reserva no int main;
    char sexo; // Variável de substituição da função sexo_do_passageiro no int main;
    int data_nascimento; // Variável de substituição da função valida_data_nascimento no int main;
    struct Voo vw; // Declaração do struct Voo para escrita em arquivo (vw = voo write);
    struct Voo vr; // Declaração do struct Voo para leitura no arquivo (vr = voo read);
    struct Reserva rw; // Declaração do struct Reserva para escrita em arquivo (rw = reserva write);
    struct Reserva rr; // Declaração do struct Reserva para leitura no arquivo (rr = reserva read);

    
    cadastro_reserva = fopen("Reservas.bin", "ab");
    if (cadastro_reserva == NULL){
        printf("Erro ao tentar abrir o arquivo!");
    }else{
        printf("Digite o número da reserva: \n");
        scanf("%s", rw.numReserva);

        reserva = cadastrar_numReserva(rw.numReserva);
        
        if(reserva == 1){ // Se a reserva não for válida;
            printf("\nReserva inválida!\n");
        }else{ // Se a reserva for válida
        
            printf("Digite o número do voo: \n");
            scanf("%s", rw.numVoo);
            cadastro_voo = fopen("Voos.bin","rb");
            fread(&vr, sizeof(struct Voo), 1, cadastro_voo);
            if(strcmp(rw.numVoo, vr.numVoo) == 1){
                printf("\nVoo não cadastrado!\n");
            }else{
                if(vr.status == 'C'){
                    printf("Este voo está cancelado!\n");
                }else{
                    fclose(cadastro_voo);
                
                    voo = cadastrar_numVoo(rw.numVoo);
            
                    if(voo == 1){ // Se o voo não for válido;
                        printf("\nNúmero de voo inválido\n");
                    }else{ // Se o voo for válido;
                        printf("Digite o seu CPF: \n");
                        scanf("%s", rw.numCPF);
                        cadastro_reserva = fopen("Reservas.bin", "rb");
                        fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva);
                        if(strcmp(rw.numCPF, rr.numCPF) == 1){
                            printf("\nCPF já cadastrado!\n");
                        }else{
                
                        CPF = validarCPF(rw.numCPF);
                
                            if(CPF == 1){ // Se o CPF não for válido;
                                printf("\nCPF inválido!\n");
                            }else{ // Se o CPF for válido;
                
                                printf("Digite o nome completo:\n");
                                for(i = 0; i < 2; i++){ // Leitura do nome da pessoa;
                                    fgets(rw.nomeCompleto, MAX_NOME, stdin);
                                }
                                printf("Informe o seu sexo:  (M = Masculino; F = Feminino; O = Outros)\n");
                                scanf("%s", &rw.caracter_sexo);
                        
                                sexo = sexo_do_passageiro(rw.caracter_sexo);
            
                                if(sexo == 1){ // Se o sexo não for válido;
                                    printf("\ncaracter inválido!\n");
                                }else{ // Se o sexo for válido
                        
                                    printf("Digite a data de nascimento:\n");
                                    scanf("%02d/%02d/%04d", &rw.diaNascimento, &rw.mesNascimento, &rw.anoNascimento);
                        
                                    data_nascimento = valida_data_nascimento(rw.diaNascimento, rw.mesNascimento, rw.anoNascimento);
                        
                                    if(data_nascimento == 1){ // Se a data de nascimento da pessoa não for válida;
                                        printf("\nData de nascimento inválida!\n");
                                    }else{ // Se a data de nascimento for válida;
                        
                                        printf("Informe o status da reserva: (A = Ativa; C = cancelada)\n");
                                        scanf("%s", &rw.atividade_da_reserva);
                            
                                        statusReserva = status_reserva(rw.atividade_da_reserva);
                            
                                        if(statusReserva == 1){ // Se a reserva não for válida;
                                            printf("\nStatus inválido!\n");
                                        }else{ // Se a reserva for válida;
                                            cadastro_reserva = fopen("Reservas.bin","rb");
                                            fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva);
                                
                                            if(strcmp(rw.numReserva, rr.numReserva) == 0){
                                                printf("\nReserva já cadastrada!\n");
                                                fclose(cadastro_reserva);
                                            } else {
                                                cadastro_reserva = fopen("Reservas.bin","ab"); // Abertura do arquivo para o cadastro das reservas
                                                if (cadastro_reserva == NULL){ // Se o arquivo estiver com problemas e não for criado, aparecer uma mensagem de erro;
                                                    printf("Erro ao tentar abrir o arquivo!");
                                                }else{
                                                    fseek(cadastro_reserva, 1, SEEK_SET); // Cadastro da struct em binário no arquivo Reservas;
                                                    fwrite(&rw, 1, sizeof(struct Reserva), cadastro_reserva);
                                                    fclose(cadastro_reserva);
                                                    printf("\nReserva cadastrada!\n\n");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void consultar_voo(){
    char statusVoo; // Variáveis para substituição da função status_voo no int main;
    int i; // Contador;
    int erro = 0; // Variável de erro;
    FILE *cadastro_voo; // Arquivo que armazenará os voos cadastrados;
    FILE *cadastro_reserva; // Arquivo que armazenará resevas cadastradas;
    char statusReserva; // Variável de substituição da função status_reserva no int main;
    struct Voo vw; // Declaração do struct Voo para escrita em arquivo (vw = voo write);
    struct Voo vr; // Declaração do struct Voo para leitura no arquivo (vr = voo read);
    struct Reserva rw; // Declaração do struct Reserva para escrita em arquivo (rw = reserva write);
    struct Reserva rr; // Declaração do struct Reserva para leitura no arquivo (rr = reserva read);
    struct ConsultarVoo cv; // Declaração do struct para ler o voo que deverá ser consultado (cv = consultar voo);
    int contador; // contador de reservas;
    float result; // Resultado do percentual de ocupação do voo;
    
    printf("Digite o voo que deseja consultar: \n");
    scanf("%s", cv.numVoo); // Leitura do número do voo que deverá ser consultado;
    cadastro_voo = fopen("Voos.bin","rb");
       
    contador = -1;
    result = 0;
    while(fread(&vr, sizeof(struct Voo), 1, cadastro_voo)){
        if(strcmp(cv.numVoo, vr.numVoo) == 0){ // Comparação para confirmar se o número digitado está no arquivo;
            cadastro_reserva = fopen("Reservas.bin", "rb");
            contador = 0;
            printf("\nReservas ativas:\n");
            while(fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){
                if(strcmp(rr.numVoo, vr.numVoo) == 0){
                    if(rr.atividade_da_reserva == 'A'){ // Se o status da reserva for ativo, apresente-a na tela;
                        printf("\t%s\n", rr.numReserva);
                        contador++; // Soma das reservas efetuadas para o voo inserido;
                    }
                }
                
            }
            result = (contador*100)/vr.quant_passageiros; // Cálculo do percentual de passageiros com reservas ativas para aquele voo;
            break;
        } 
    }
    if(contador > 0){ // Saída se o voo tiver reservas;
        printf("\nPercentual de ocupação: %.3f%%\n", result);
        printf("DATA: %02d/%02d/%04d\nHORA: %02d:%02d\nQUANTIDADE DE PASSAGEIROS: %d\nSTATUS DO VOO-%c\n\n", vr.dia, vr.mes, vr.ano, vr.hora, vr.minuto, vr.quant_passageiros, vr.status);
    }else{
        if(contador == 0){ // Se o voo não tiver nenhuma reserva ativa;
            printf("\nNão há reservas ativas\n\n");
        }else{
            printf("\nVoo não encontrado\n\n");
        }
    }
    
    // Fechamento dos arquivos
    
    fclose(cadastro_reserva);
    fclose(cadastro_voo);
    
}

void consultar_reserva(){
    struct Reserva rr; // Declaração do struct Reserva para leitura no arquivo (rr = reserva read);
    struct Reserva cr; // Declaração do struct Reserva para consulta (cr = consultar reserva);
    FILE *cadastro_reserva;
    int contador;
    
    printf("Digite o número da reserva que deseja consultar:\n");
    scanf("%s", cr.numReserva); // Leitura do número da reserva que deseja ser consultada;
    cadastro_reserva = fopen("Reservas.bin", "rb"); // Abertura do arquivo para leitura;
    
    while(fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){ // Leitura das structs de reserva no arquivo;
        if(strcmp(cr.numReserva, rr.numReserva) == 0){ // Verificar se o número da reserva inserido é igual a um número de reserva existente no arquivo;
            printf("\n%s\nCPF-%s\nRESERVA: %s\nVOO: %s\nDATA DE NASCIMENTO: %02d/%02d/%04d \nSEXO-%c\nSTATUS DA RESERVA-%c\n\n", rr.nomeCompleto, rr.numCPF, rr.numReserva, rr.numVoo, rr.diaNascimento, rr.mesNascimento, rr.anoNascimento, rr.caracter_sexo, rr.atividade_da_reserva);
            break;
        }
    }
    if(strcmp(cr.numReserva, rr.numReserva) == 1){ // Se um número de reserva não for encontrado, mostre uma mensagem de reserva não encontrada;
        printf("\nReserva não encontrada!\n");  
    }
    fclose(cadastro_reserva); // Fechamento do arquivo;
}

void consultar_passageiro(){
    struct Reserva rr; // Declaração do struct Reserva para leitura no arquivo (rr = reserva read);
    struct Reserva cp; // Declaração do struct Reserva para consulta de passageiros (cp = consulta passageiro);
    FILE *cadastro_reserva;
    
    printf("Digite o número do CPF do passageiro que deseja consultar:\n");
    scanf("%s", cp.numCPF); // Leitura do número de CPF que deseja consultar;
    cadastro_reserva = fopen("Reservas.bin", "rb"); // Abertura do arquivo para leitura
    
    printf("\nReservas ativas:\n");
    while(fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){ // Leitura dos structs presentes no arquivo;
        if(strcmp(cp.numCPF, rr.numCPF) == 0){ // Verificar se o CPF inserido é igual a um CPF presente no arquivo;
            printf("%s\n", rr.numReserva); // Print para mostrar o número de reservas ativas para aquele CPF;  
        }
        printf("\n");
        if(strcmp(cp.numCPF, rr.numCPF) == 1){ // Se o CPF inserido não estiver no arquivo, mostre uma mensagem de que não há reservas
            printf("\nNão há reservas com esse CPF\n");
        }
    }
    
    fclose(cadastro_reserva);
}

void cancelar_voo(){
    
    struct Voo vr; // Struct voo para leitura (vr = voo read);
    struct Voo vw; // Struct voo para escrita (vw = voo write);
    struct Voo cancelVoo; // Struct voo para cancelamento de voo;
    struct Reserva rw; // Struct da Reserva para escrita (rw = reserva write);
    struct Reserva rr; // Struct da Reserva para leitura (rr = reserva read);
    struct Reserva cancelReserva; // Struct da Reserva para cancelamento;
    int encontrar;
    int encontrar2;
    fpos_t position; // Armazenar uma posicao no arquivo 
    

    FILE *cadastro_voo;
    cadastro_voo = fopen ("Voos.bin", "r+b"); // Abertura do arquivo que contem os voos cadastrados para leitura e edicao; 
    if (cadastro_voo == NULL){
        printf ("Erro ao tentar abrir o arquivo\n");
        printf ("Pressione qualquer tecla para sair do programa\n");
        getchar ();
        exit (0);
    }
    FILE *cadastro_reserva;
    cadastro_reserva = fopen ("Reservas.bin", "r+b"); // Abertura do arquivo que contem as reservas para leitura e edicao;
    if (cadastro_reserva == NULL){
        printf ("Erro ao tentar abrir o arquivo\n");
        printf ("Pressione qualquer tecla para sair do programa\n");
        getchar ();
        exit (0);
    }
    printf("Digite o número do voo a ser cancelado:\n");
    scanf("%s", cancelVoo.numVoo); // Leitura do voo que deve ser cancelado juntamento com suas reservas
    
    encontrar = 0; // Variável com valor zero, pois o arquivo ainda não foi percorrido;
    fgetpos(cadastro_voo, &position); // Armazena a posicao atual do arquivo;
    while(fread(&vr, sizeof(struct Voo), 1, cadastro_voo)){ // Enquanto as structs de voo forem lidas, faça;
        if(strcmp(cancelVoo.numVoo, vr.numVoo) == 0){ // Se o voo digitado for igual a um voo cadastrado no arquivo, encontrar passa a ser 1; 
            encontrar = 1; // Quando o encontrar assume o valor 1, o Voo foi encontrado;
            break;
        }
        fgetpos(cadastro_voo, &position); // Armazena a posicao onde o voo foi encontrado;
    }
    if(encontrar){ // Se o voo foi encontrado, realize as seguintes modificações;
        struct Voo vc; // Struct de voos cancelados (vc = voos cancelados);
        vc = vr; // O struct de voos cancelados assume os mesmos dados dos voos armazenados para leitura;
        vc.status = 'C'; // Alteração do Status do Voo para C = cancelado;
        fsetpos(cadastro_voo, &position); // Aplicação da posição armazenada anteriormente; 
        fwrite(&vc, sizeof(struct Voo), 1, cadastro_voo); // Escreva no arquivo a nova struct na posição em que o voo foi encontrado;
                                                          // Isso permite que apenas o voo que foi digitado seja alterado;
    }else{
        printf("\nVoo não encontrado!\n");
        getchar();
    }
    encontrar2 = 0; // Variável com valor zero, pois o arquivo ainda não foi percorrido;
    fgetpos(cadastro_reserva, &position); // Armazena a posição atual do arquivo;
    while(fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){ // Enquanto as structs de reserva forem lidas, faça;
        if(rr.atividade_da_reserva == 'A'){ // Se a reserva correspondente ao voo for ativa, então encontrar2 passa a ser igual a 1; 
            encontrar2 = 1; // Quando o encontrar2 assume o valor 1, significa que a reserva ativa foi encontrada
            break;
        }
        fgetpos(cadastro_reserva, &position); // Armazene a posição da reserva encontrada;
    }
    
    if(encontrar2){ // Se a reserva foi encontrada, faça as seguintes modificações;
        struct Reserva rc; // Struct de reservas canceladas (rc = reservas canceladas);
        rc = rr; // O struct de reservas cancelados assume os mesmos dados das reservas armazenadas para leitura;
        rc.atividade_da_reserva = 'C'; // Alteração do status da reserva para cancelado;
        fsetpos(cadastro_reserva, &position); // Aplicação da posição onde a reserva foi encontrada
        fwrite(&rc, sizeof(struct Reserva), 1, cadastro_reserva); // Escrita da nova struct no arquivo, significando que as reservas também foram canceladas
        printf("\nVoo cancelado com sucesso!\n\n");
    }else{
        printf("\nVoo não encontrado!\n\n");
        getchar();
    }

// Fechamento dos arquivos;
    fclose(cadastro_voo);
    fclose(cadastro_reserva);
}

void cancelar_reserva(){
    FILE *cadastro_reserva; // Arquivo com as reservas cadastradas;
    struct Reserva cancelReserva; // Struct de reservas para cancelamento;
    struct Reserva rr; // Struct de reservas para leitura em arquivo (rr = reservas read);
    int encontrar;
    fpos_t position; // Função para o armazenamento da posição do arquivo;
    int encontrar2; 
    
    printf("Digite o número da reserva que deseja cancelar:\n");
    scanf("%s", cancelReserva.numReserva); // Leitura do número da reserva que deve ser cancelada;
    cadastro_reserva = fopen("Reservas.bin", "r+b"); // Abertura do arquivo das reservas cadastradas para leitura e escrita;
    encontrar = 0; // Variável com valor zero, pois o arquivo ainda não foi percorrido;
    fgetpos(cadastro_reserva, &position); // Armazena a posição atual do arquivo;
    while(fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){ // Enquanto as structs do arquivo forem lidas, faça;
        if(strcmp(cancelReserva.numReserva, rr.numReserva) == 0){ // Se a reserva digitada for igual a uma reserva cadastrada do arquivo, continue;
            if(rr.atividade_da_reserva == 'A'){ // Se o status da reserva dor ativo, então encontrar passa a ser igual a 1;
                encontrar = 1; // Quando a reserva é encontrada, encontrar assume o valor de 1;
                break;
            }
        }
        fgetpos(cadastro_reserva, &position); // Armazenamento da posição em que se encontra a reserva a ser cancelada;
    }
    
    if(encontrar){
        struct Reserva rc; // Struct para reservas canceladas (rc = reservas canceladas);
        rc = rr; // O struct de reservas cancelados assume os mesmos dados das reservas armazenadas para leitura;
        rc.atividade_da_reserva = 'C'; // Alteração do status da reserva para cancelado;
        fsetpos(cadastro_reserva, &position); // Aplicação da posição onde a reserva foi encontrada
        fwrite(&rc, sizeof(struct Reserva), 1, cadastro_reserva); // Escrita da nova struct no arquivo;
        printf("\nReserva cancelada com sucesso!\n");
    }else{
        printf("\nReserva não encontrada!\n");
        getchar();
    }
    fclose(cadastro_reserva);
}

void excluir_voo(){
    FILE *cadastro_voo; // Arquivo com os voos cadastrados;
    FILE *cadastro_reserva; // Arquivo com as reservas cadastradas;
    FILE *arq_aux; // Arquivo auxiliar;
    FILE *arq_aux2; // Arquivo auxiliar;
    struct Voo ev; // Struct de voo para exclusão (ev = excluir voo);
    struct Voo vr; // Struct de voo para leitura (vr = voos read);
    struct Reserva rr; // Struct de reserva para leitura (rr = reservas read);
    char confirmacao; // Confirmação da exclusão;
    
    printf("Digite o número do Voo que deseja excluir:\n");
    scanf("%s", ev.numVoo); // Leitura do número do voo que deverá ser cancelado;
    cadastro_voo = fopen("Voos.bin", "rb"); // Abertura do arquivo de voos cadastrados para leitura;
    cadastro_reserva = fopen("Reservas.bin", "rb"); // Abertura do arquivo de reservas cadastradas para leitura;

    if(cadastro_voo == NULL){ // Conferir se o arquivo está sendo aberto corretamente;
        printf("\nFalha na abertura do arquivo!\n ");
    }
    if(cadastro_reserva == NULL){ // Conferir se o arquivo está sendo aberto corretamente;
        printf("\nFalha na abertura do arquivo!\n ");
    }
    while(fread(&vr, sizeof(struct Voo), 1, cadastro_voo)){ // Enquanto as structs de voos forem lidas, faça; 
        if(strcmp(ev.numVoo, vr.numVoo) == 0){ // Se o número do voo digitado for igual a um voo armazenado no arquivo,
                                               // retorne uma mensagem, para confirmação da exclusão;
            printf("Deseja realmente excluir esse voo?   (S/N)\n");
            fflush(stdin);
            scanf(" %c", &confirmacao); // Confirmação da exclusão do voo; 
            if ((confirmacao == 'S')){ // Se a confirmação for igual a S (S = Sim), então continue;
                arq_aux = fopen("VoosAuxiliar.bin", "wb"); // Abra um arquivo auxiliar para escrita dos voos;
                arq_aux2 = fopen("ReservasAuxiliar.bin", "wb"); // Abra um arquivo auxiliar para escrita das reservas;
                if (arq_aux == NULL){ // Conferir se o arquivo está sendo aberto corretamente;
                    printf("\nFalha na abertura do arquivo!\n");
                }else{
            // Copia os registros para o arquivo auxiliar, menos o registro a ser excluído
                    rewind(cadastro_voo); // Posiciona o apontador de arquivo para o início;
                    while (fread(&vr, sizeof(struct Voo), 1, cadastro_voo)){ // Enquanto os structs de voos forem lidos, faça; 
                        if(strcmp(ev.numVoo, vr.numVoo) != 0){ // Seleciona todos os voos, menos o digitado e escreva-os no arquivo de voos auxiliares;
                            fwrite(&vr, sizeof(struct Voo), 1, arq_aux); // Escrita dos voos, menos o digitado, no arquivo auxiliar;
                        }
                        fread(&vr, sizeof(struct Voo), 1, arq_aux); // Leitura do arquivo auxiliar já alterado;
                    }
                    rewind(cadastro_reserva); // Posiciona o apontador de arquivo para o início;
                    while (fread(&rr, sizeof(struct Reserva), 1, cadastro_reserva)){ // Enquanto os structs de reserva forem lidos, faça; 
                        if(strcmp(ev.numVoo, rr.numVoo) != 0){ // Seleciona todas as reservas, menos as que foram feitas no voo digitado e escreve-as no arquivo de reservas auxiliares;
                            fwrite(&rr, sizeof(struct Reserva), 1, arq_aux2); // Escrita das reservas que não correspondem ao voo digitado;
                        }
                        fread(&rr, sizeof(struct Reserva), 1, arq_aux2); // Leitura do arquivo auxiliar já alterado;
                    }
                    
                    // Fechamento dos arquivos;
                    
                    fclose(cadastro_voo);
                    fclose(arq_aux);
                    fclose(cadastro_reserva);
                    fclose(arq_aux2);
                    
                    // Substituição dos arquivos originais pelos auxiliares;
                    
                    remove("Voos.bin"); // Remove o arquivo de voos cadastrados;
                    rename("VoosAuxiliar.bin", "Voos.bin"); // Renomeia o arquivo auxiliar com o mesmo nome do arquivo original;
                    remove("Reservas.bin"); // Remove o arquivo de reseras cadastrados;
                    rename("ReservasAuxiliar.bin", "Reservas.bin"); // Renomeia o arquivo auxiliar com o mesmo nome do arquivo original;
                    printf("\nVoo excluído com sucesso!\n");
                
                }
            }
        }
    }
}

char cadastrar_numVoo(char numVoo[CHAR_VOO]){
    int erro = 0;
    int i;
        if(strlen(numVoo) == CHAR_VOO-1){ // Condições para as posições dos caracteres e números do voo;
            for(i = 0; i < CHAR_VOO-1; i++){
            // Condições para que o número do voo não seja diferente de (JEB-XXXX), sendo X = número inteiro;
                if(i == 0 && numVoo[i] != 'J'){
                    erro = 1;
                    break;
                }else{
                    if(i == 1 && numVoo[i] != 'E'){
                        erro = 1;
                        break;
                    }else{
                        if(i == 2 && numVoo[i] != 'B'){
                            erro = 1;
                            break;
                        }else{
                            if(i == 3 && numVoo[i] != '-'){
                                erro = 1;
                                break;
                            }else{
                                if(i > 3 && !isdigit(numVoo[i])){ // Função isdigit para comprovar que os últimos 4 caracteres sejam números;
                                    erro = 1;
                                }
                            }
                        }
                    }
                }
            }
        }else{
            erro = 1;
        }   
    return erro;
}

int valida_data(int dia, int mes, int ano){
    int erro = 0;
	// Validação de dias;
	if(dia < 1 || dia > 31){
	    erro = 1;
    }
	// Validação de meses;
	if(mes < 1 || mes > 12){
        erro = 1;
	} else {
		if((mes == 4 && dia > 30) || (mes == 6 && dia > 30) || (mes == 9 && dia > 30) || (mes == 11 && dia > 30)){
		    erro = 1;
		} else {
	// Condição para o mês de fevereiro;
		    if(mes == 2 && dia > 29){
			    erro = 1;
			}
		}
	}
	// Contagem do ano a partir de 2030;
    if(ano < 2021){
        erro = 1;		
	} else {
	// Condição para anos bissextos;
		if((ano % 4 != 0 || (ano % 100 == 0 && ano % 400 != 0)) && mes == 2 && dia > 28){
		    erro = 1;
		}
	}
	return erro;
}

int valida_hora(int hora, int minuto){
    int erro = 0;
    // Condição para que as horas e os minutos sejam válidos
    if(hora < 0 || hora > 23 || minuto < 0 || minuto > 59){
        erro = 1;
    }
    return erro;
}

char status_voo(char status){
    int erro = 0;
    // Condição para que o status seja apenas 'C' para Cancelado e 'A' para ativo; 
    if(status != 'A' && status != 'C'){
        erro = 1;
    }
    return erro;
}

char cadastrar_numReserva(char numReserva[CHAR_RESERVA]){
    int erro = 0;
    int i;
    
    // Condições para que a reserva tenha o formato GB-XXXXXX
    
        if(strlen(numReserva) == CHAR_RESERVA-1){
            for(i = 0; i < CHAR_RESERVA-1; i++){
                if(i == 0 && numReserva[i] != 'G'){
                    erro = 1;
                    break;
                }else{
                    if(i == 1 && numReserva[i] != 'B'){
                        erro = 1;
                        break;
                    }else{
                        if(i == 2 && numReserva[i] != '-'){
                            erro =1;
                            break;
                        }else{
                            if(i > 2 && !isdigit (numReserva[i])){ // Condição para que os 6 últimos caracteres da reserva sejam números;
                                erro = 1;
                                break;
                            }
                        }
                    }
                }  
            }    
        }else{
            erro = 1;
        }
    return erro;
}

char validarCPF(char numCPF[QUANT_CPF]){
    
    int CPF_novo[11], Total_d1 = 0, Total_d2 = 0, digito_calculado, i = 0, j = 0, tam, digito_inserido;
    int erro = 0;
    
    
        tam = strlen(numCPF); 
        while( i <= tam){ // Enquanto o tamanho do CPF for menor ou igual a 14, faça:
            if(numCPF[i] != '.' && numCPF[i] != '-'){ // Se o CPF for diferente de ponto e de hífen, então ele precisa ser número;
                CPF_novo[j] = numCPF[i]-48; // Utilização da tabela ascii para que os demais dígitos sejam números;
                j++; // Verificação de cada número;
            }
        i++; // Verificação de cada CPF;
        }
    i = 0; // Reinicialização da variável;
    
    while(i < 9){
        Total_d1 = Total_d1 + ((CPF_novo[i]) * (10 - i)); /* Multiplicação dos 9 primeiros números do CPF pela sequência: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
                                                            sendo o primeiro número multiplicado por 10, o segundo por 9 e assim sucessivamente, para encontrar o primeiro dígito verificador */
                                                            
        Total_d2 = Total_d2 + ((CPF_novo[i]) * (11 - i)); /* Multiplicação dos 9 primeiros números do CPF pela sequência: 11, 10, 9, 8, 7, 6, 5, 4, 3, 2
                                                            sendo o primeiro número multiplicado por 10, o segundo por 9 e assim sucessivamente, para encontrar o segundo dígito verificador
                                                            OBS: O número 2 é multiplicado pelo primeiro dígito verificador */
        i++; // Somatório dessas multiplicações;
    }
    
    Total_d1 = (Total_d1 * 10) % 11; /* A soma da multiplicação feita anteriormente, agora é multiplicada por 10 e divida por 11.
                                        O resto dessa divisão é o primeiro dígito verificador. */
                                        
    if(Total_d1 > 9){ // Se o resto da divisão for maior que 9, o dígito verficador será 0;
        Total_d1 = 0;
    }
    
    Total_d2 = (Total_d2 + (Total_d1 * 2)) * 10 % 11; /* A soma da multiplicação feita para descobrir o segundo dígito, agora é somada com o primeiro dígito * 2
                                                        e novamente multiplicada por 10 e divida por 11. O resto dessa divisão é o segundo dígito verificador. */
                                                        
    if(Total_d2 > 9){ // Se o resto da divisão for maior que 9, o dígito verficador será 0;
        Total_d2 = 0;
    }
    
    digito_calculado = (Total_d1 * 10) + Total_d2; // Cálculo do dígito realizado anteriormente;

    i = CPF_novo[9];
    j = CPF_novo[10];
    
    digito_inserido = ((i)*10)+(j); // O dígito inserido pelo usuário deve equivaler a esse cálculo, que é o cálculo anterior de forma simplificada;
    
    /* Condição para que o CPF não tenha todos os números iguais, pois apesar de atender todos os cálculos propostos,
    os CPFs com números iguais não são válidos; */
    
    if(CPF_novo[0] == CPF_novo[1]&&
       CPF_novo[0] == CPF_novo[2]&&
       CPF_novo[0] == CPF_novo[3]&&
       CPF_novo[0] == CPF_novo[4]&&
       CPF_novo[0] == CPF_novo[5]&&
       CPF_novo[0] == CPF_novo[6]&&
       CPF_novo[0] == CPF_novo[7]&&
       CPF_novo[0] == CPF_novo[8]&&
       CPF_novo[0] == CPF_novo[9]){
           erro = 1;
    }
    
    if(digito_calculado != digito_inserido){ // Se o dígito inserido pelo usuário, for diferente do cálculo realizado, o CPF é inválido;
        erro = 1;
    }

    return erro;
}
char sexo_do_passageiro(char caracter_sexo){
    int erro = 0;

// Condição para que o sexo do passageiro seja representado apenas por: (M = Masculino/ F = Feminino/ O = Outros;

    if(caracter_sexo != 'M' && caracter_sexo != 'F' && caracter_sexo != 'O'){
        erro = 1;
    }    
    return erro;
}

int valida_data_nascimento(int diaNascimento, int mesNascimento, int anoNascimento){
    int erro = 0;
	// Validação de dias;
	if(diaNascimento < 1 || diaNascimento > 31){
	    erro = 1;
    }
	// Validação de meses;
	if(mesNascimento < 1 || mesNascimento > 12){
        erro = 1;
	}else{
	    if((mesNascimento == 4 && diaNascimento > 30) || (mesNascimento == 6 && diaNascimento > 30) || (mesNascimento == 9 && diaNascimento > 30) || (mesNascimento == 11 && diaNascimento > 30)){
		    erro = 1;
		}else{
	// Condição para o mês de fevereiro;
		    if(mesNascimento == 2 && diaNascimento > 29){
			    erro = 1;
			}
		}
	}
	// Contagem dos anos d.C;
    if(anoNascimento < 1895 || anoNascimento > 2021){
        erro = 1;		
	} else {
	// Condição para anos bissextos;
		if((anoNascimento % 4 != 0 || (anoNascimento % 100 == 0 && anoNascimento % 400 != 0)) && mesNascimento == 2 && diaNascimento > 28){
		    erro = 1;
		}
	}
	return erro;
}
char status_reserva(char atividade_da_reserva){
    int erro = 0;
    
    // Condição para que o status da reserva seja apenas 'C' para cancelado e 'A' para ativo;
    if(atividade_da_reserva != 'A' && atividade_da_reserva != 'C'){
        erro = 1;
    }
    return erro;
}
