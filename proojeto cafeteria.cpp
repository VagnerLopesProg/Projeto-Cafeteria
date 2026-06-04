#include <iostream>
#include <cstdlib>
#include <string>
#include "cabecalho.h"

using namespace std;

struct produto
{
    int codigo;
    string nome;
    float preco;
    string categoria;
};

struct itemPedido
{
    string nome;
    float preco;
};

struct registromesa
{
    itemPedido itens[100];
    int totalitens = 0;
    float totalconta = 0;
};

// =========================== PRIMEIRO BANCO DE DADOS GLOBAL ================================

produto produtos [100];
int totalprodutos = 0;

registromesa mesas[26];

void cadastrarProduto()
{
    string entrada;
    string continuar;

    do
    {
        system("cls"); // Limpa a tela para iniciar o cadastro do zero
        exibircabecalho("CADASTRO DE PRODUTOS");

        cout <<"Codigo do produto: \n";
        getline(cin,entrada);
        produtos[totalprodutos].codigo = stoi (entrada);

        cout <<"\nNome do produto: ";
        getline(cin,produtos[totalprodutos].nome);

        cout<<"\nPreco de venda: ";
        getline(cin,entrada);
        produtos[totalprodutos].preco = stof (entrada); // Ajustado para stof (aceitar centavos)
        
        int opcaoCategoria;
        bool categoriaValida = false;
        do
        {
            cout <<"\nSelecione a categoria do produto:\n";
            cout <<"1 - Bebida\n";
            cout <<"2 - Comida\n";
            cout <<"3 - Sobremesa\n";
            cout <<"Opcao: ";

            getline(cin, entrada);
            opcaoCategoria = stoi (entrada);

            switch (opcaoCategoria)
            {
            case 1:
                produtos[totalprodutos].categoria = "Bebida";
                categoriaValida = true;
                break;
            
            case 2:
                produtos[totalprodutos].categoria = "Comida";
                categoriaValida = true;
                break;

            case 3:
                produtos[totalprodutos].categoria = "Sobremesa";
                categoriaValida = true;
                break;

            default:
                cout <<"\nOpcao invalida! Tente novamente escolhendo de 1 a 3!\n";  
                break;
            }
        } while (!categoriaValida);

        totalprodutos ++;

        cout << "\nProduto cadastrado com sucesso!\n";

        cout << "Deseja cadastrar outro produto? (S/N) ";
        getline(cin,continuar);
        

    } while (continuar == "S" || continuar == "s");
    
}

void Listarprodutos()
{
    // Removido o limpador daqui de dentro para não apagar a tela no meio de um pedido
    exibircabecalho("CARDAPIO DO DIA");

    if (totalprodutos == 0 )
    {
        cout << "Nao ha produtos cadastrados no momento.\n";
    } else
    {
        for (int i = 0; i < totalprodutos; i++)
        {
            cout <<"\nCodigo: " << produtos[i].codigo;
            cout <<"\nProduto: " << produtos[i].nome;
            cout <<"\nCategoria: " << produtos[i].categoria;
            cout <<"\nValor: R$ " << produtos[i].preco;
            cout <<"\n----------------------------------\n";
        }
    }
}

void fazerPedido()
{
    system("cls"); // Limpa a tela para focar no pedido
    if (totalprodutos == 0){
        cout <<"Nao e possivel fazer pedidos porque nao ha produtos no cardapio.\n";
        cout <<"\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }

    string entrada, continuar;
    int numeroMesa = 0;

    exibircabecalho("NOVO PEDIDO / ADICIONAR ITEM");

    while (true)
    {
        cout <<"Digite o numero da mesa (1 a 25): ";
        getline(cin, entrada);
        numeroMesa = stoi(entrada);
        
        if (numeroMesa >= 1 && numeroMesa <=25) {
            break;
        }else{
            cout <<"Mesa invalida! Temos somente 25 mesas no salao.\n\n";
        }
        
    }
    
    registromesa &mesaAtual = mesas[numeroMesa];

    do{
        system("cls"); // Limpa para mostrar o cardápio atualizado e o pedido atual
        Listarprodutos();

        cout<< "\nDigite o codigo do produto que a mesa " << numeroMesa << " deseja pedir: ";
        getline(cin,entrada);
        int codigoEscolhido = stoi(entrada);

        bool produtoEncontrado = false;

        for (int i = 0; i < totalprodutos; i++)
        {
            if (produtos[i].codigo == codigoEscolhido) {
                int posicaoLivre = mesaAtual.totalitens;

                mesaAtual.itens[posicaoLivre].nome = produtos[i].nome;
                mesaAtual.itens[posicaoLivre].preco = produtos[i].preco;

                mesaAtual.totalitens ++;
                mesaAtual.totalconta += produtos[i].preco;

                cout << "\n-> " << produtos[i].nome << " adicionado com sucesso a mesa " << numeroMesa << "!\n";

                produtoEncontrado = true;
                break;
            }
        }
        if (!produtoEncontrado) 
        {
            cout <<"\nCodigo invalido! Produto nao encontrado no cardapio.\n";
        }
        
        cout <<"\nDeseja adicionar mais algum produto para a mesa " << numeroMesa << "? (S/N): ";
        getline (cin, continuar);
    }while (continuar == "S" || continuar == "s");

    system("cls"); // Limpa para exibir o resumo limpo no final do atendimento
    cout << "========================================\n";
    cout << " STATUS ATUALIZADO - MESA " << numeroMesa << "\n";
    cout << " Itens pedidos ate agora: " << mesaAtual.totalitens << "\n";
    cout << " Valor acumulado ate agora: R$ " << mesaAtual.totalconta << "\n";
    cout << "========================================\n";
    
    cout << "\nPressione ENTER para voltar ao menu principal...";
    string pausa;
    getline(cin, pausa);
}

void exibircontamesa()
{
    system("cls"); // Limpa a tela para focar na conta
    if (totalprodutos == 0 )
    {
        cout <<"Nao ha pedidos registrados no sistema no momento.\n";
        cout <<"\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }

    string entrada, continuar;
    int numeromesa = 0;

    exibircabecalho("CONTA DA MESA / FECHAMENTO");

    while (true)
    {
        cout <<"Digite o numero da mesa para continuar: ";
        getline(cin, entrada);
        numeromesa = stoi(entrada);

        if (numeromesa >= 1 && numeromesa <=25) {
            break;
        }else{
            cout <<"Mesa invalida! digite um numero de 1 a 25.\n\n";
        }
    }
    
    registromesa &mesaatual = mesas[numeromesa];

    if (mesaatual.totalitens == 0 )
    {
        cout << "\nA mesa " << numeromesa << " nao possui item lancado na conta.\n";
        cout << "\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }
    
    system("cls"); // Limpa para mostrar o extrato isolado
    cout << "\n========== EXTRATO MESA " << numeromesa << " ===========\n";
    for (int i = 0; i < mesaatual.totalitens; i++) 
    {
        cout << "- " << mesaatual.itens[i].nome << " : R$ " << mesaatual.itens[i].preco << "\n";
    }
    cout << "------------------------------------------\n";
    cout << "TOTAL ACUMULADO: R$ " << mesaatual.totalconta << "\n";
    cout << "==========================================\n";

    cout << "\nDeseja fechar a conta da Mesa " << numeromesa << " e liberar a mesa? (S/N): ";
    getline(cin, continuar);

    if (continuar == "S" || continuar == "s") {
        mesaatual.totalitens = 0;
        mesaatual.totalconta = 0;
        cout << "\nConta encerrada! Mesa " << numeromesa << " agora esta LIVRE.\n";
    } else {
        cout << "\nMesa continua aberta.\n";
    }
    
    cout << "\nPressione ENTER para voltar ao menu principal...";
    string pausa;
    getline(cin, pausa);
}

int main()
{
    string entradaOpcao;
    int opcao;

    do
    {
        system("cls"); // Garante que o menu principal sempre reapareça em uma tela limpa
        exibircabecalho("MENU PRINCIPAL - CAFETERIA");

        cout << "1 - Cadastrar produto\n";
        cout << "2 - Listar produtos (Cardapio)\n";
        cout << "3 - Fazer / atualizar pedido de uma mesa\n";
        cout << "4 - Exibir conta de uma mesa\n";
        cout << "5 - Sair\n";
        cout << "Opcao: ";
        getline (cin, entradaOpcao);
        opcao = stoi (entradaOpcao);

        switch (opcao)
        {
        case 1:
            cadastrarProduto(); 
            break;

        case 2:
            system("cls");
            Listarprodutos(); 
            cout << "\nPressione ENTER para voltar ao menu...";
            getline(cin, entradaOpcao); 
            break;
            
        case 3:
            fazerPedido(); 
            break;

        case 4:
            exibircontamesa(); 
            break;

        case 5:
            system("cls");
            cout << "Encerrando o sistema...\n";
            break;

        default: 
            cout <<"\nOpcao invalida! Tente novamente!\n";
            cout <<"Pressione ENTER para continuar...";
            getline(cin, entradaOpcao);
            break;
        }
    } while (opcao != 5);

    return 0;    
}