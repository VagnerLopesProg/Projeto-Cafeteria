#include <iostream>
#include <cstdlib>
#include <string>
#include "cabecalho.h"
#include "BancoDeDados.h" // <-- ADICIONADO: Importa as structs, variáveis e o cardápio fixo

using namespace std;

// Repare que as structs 'produto', 'itemPedido', 'registroMesa' 
// e as variáveis globais NÃO estão mais aqui. O 'database.h' cuida delas!

// =========================== FUNÇÕES DO SISTEMA ================================

void cadastrarProduto()
{
    string entrada;
    string continuar;

    do
    {
        system("cls"); 
        exibircabecalho("CADASTRAR NOVO PRODUTO (ATUALIZACAO)");

        cout << "Digite o codigo para o novo produto: \n";
        getline(cin, entrada);
        produtos[totalprodutos].codigo = stoi(entrada);

        cout << "\nNome do produto: ";
        getline(cin, produtos[totalprodutos].nome);

        cout << "\nPreco de venda: ";
        getline(cin, entrada);
        produtos[totalprodutos].preco = stof(entrada); 
        
        int opcaoCategoria;
        bool categoriaValida = false;
        do
        {
            cout << "\nSelecione a categoria do produto:\n";
            cout << "1 - Bebida\n";
            cout << "2 - Comida\n";
            cout << "3 - Sobremesa\n";
            cout << "Opcao: ";

            getline(cin, entrada);
            opcaoCategoria = stoi(entrada);

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
                cout << "\nOpcao invalida! Tente novamente escolhendo de 1 a 3!\n";  
                break;
            }
        } while (!categoriaValida);

        totalprodutos++;

        cout << "\nProduto cadastrado e adicionado ao cardapio com sucesso!\n";

        cout << "Deseja cadastrar mais algum produto extra? (S/N) ";
        getline(cin, continuar);
        
    } while (continuar == "S" || continuar == "s");
}

void Listarprodutos()
{
    exibircabecalho("CARDAPIO ATUALIZADO");

    if (totalprodutos == 0)
    {
        cout << "Nao ha produtos cadastrados no momento.\n";
    } 
    else
    {
        for (int i = 0; i < totalprodutos; i++)
        {
            cout << "\nCodigo: " << produtos[i].codigo;
            cout << "\nProduto: " << produtos[i].nome;
            cout << "\nCategoria: " << produtos[i].categoria;
            cout << "\nValor: R$ " << produtos[i].preco;
            cout << "\n----------------------------------\n";
        }
    }
}

void fazerPedido()
{
    system("cls"); 
    if (totalprodutos == 0) {
        cout << "Nao e possivel fazer pedidos porque nao ha produtos no cardapio.\n";
        cout << "\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }

    string entrada, continuar;
    int numeroMesa = 0;

    exibircabecalho("NOVO PEDIDO / ADICIONAR ITEM");

    while (true)
    {
        cout << "Digite o numero da mesa (1 a 25): ";
        getline(cin, entrada);
        numeroMesa = stoi(entrada);
        
        if (numeroMesa >= 1 && numeroMesa <= 25) {
            break;
        } else {
            cout << "Mesa invalida! Temos somente 25 mesas no salao.\n\n";
        }
    }
    
    // ATUALIZADO: Usando 'registroMesa' com M maiúsculo
    registroMesa &mesaAtual = mesas[numeroMesa]; 

    do {
        system("cls"); 
        Listarprodutos();

        cout << "\nDigite o codigo do produto que a mesa " << numeroMesa << " deseja pedir: ";
        getline(cin, entrada);
        int codigoEscolhido = stoi(entrada);

        bool produtoEncontrado = false;

        for (int i = 0; i < totalprodutos; i++)
        {
            if (produtos[i].codigo == codigoEscolhido) {
                int posicaoLivre = mesaAtual.totalitens;

                mesaAtual.itens[posicaoLivre].nome = produtos[i].nome;
                mesaAtual.itens[posicaoLivre].preco = produtos[i].preco;

                mesaAtual.totalitens++;
                mesaAtual.totalconta += produtos[i].preco;

                cout << "\n-> " << produtos[i].nome << " adicionado com sucesso a mesa " << numeroMesa << "!\n";

                produtoEncontrado = true;
                break;
            }
        }
        if (!produtoEncontrado) 
        {
            cout << "\nCodigo invalido! Produto nao encontrado no cardapio.\n";
        }
        
        cout << "\nDeseja adicionar mais algum produto para a mesa " << numeroMesa << "? (S/N): ";
        getline(cin, continuar);
    } while (continuar == "S" || continuar == "s");

    system("cls"); 
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
    system("cls"); 
    if (totalprodutos == 0)
    {
        cout << "Nao ha pedidos registrados no sistema no momento.\n";
        cout << "\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }

    string entrada; 
    int numeromesa = 0;

    exibircabecalho("CONTA DA MESA / FECHAMENTO");

    while (true)
    {
        cout << "Digite o numero da mesa para consultar (1 a 25): ";
        getline(cin, entrada);
        numeromesa = stoi(entrada);

        if (numeromesa >= 1 && numeromesa <= 25) {
            break;
        } else {
            cout << "Mesa invalida! digite um numero de 1 a 25.\n\n";
        }
    }
    
    // ATUALIZADO: Usando 'registroMesa' com M maiúsculo
    registroMesa &mesaatual = mesas[numeromesa]; 

    if (mesaatual.totalitens == 0)
    {
        cout << "\nA mesa " << numeromesa << " nao possui itens lancados na conta.\n";
        cout << "\nPressione ENTER para voltar...";
        string pausa;
        getline(cin, pausa);
        return;
    }
    
    system("cls"); 
    cout << "\n========== EXTRATO MESA " << numeromesa << " ===========\n";
    for (int i = 0; i < mesaatual.totalitens; i++) 
    {
        cout << "- " << mesaatual.itens[i].nome << " : R$ " << mesaatual.itens[i].preco << "\n";
    }
    cout << "------------------------------------------\n";
    cout << "TOTAL ACUMULADO: R$ " << mesaatual.totalconta << "\n";
    cout << "==========================================\n\n";

    cout << "O que deseja fazer com a Mesa " << numeromesa << "?\n";
    cout << "1 - Apenas consultar e voltar ao menu (Manter Mesa Aberta)\n";
    cout << "2 - Finalizar conta e registrar pagamento\n";
    cout << "Opcao: ";
    getline(cin, entrada);
    int acaoMesa = stoi(entrada);

    if (acaoMesa == 2) {
        system("cls");
        exibircabecalho("FORMA DE PAGAMENTO");
        cout << "Valor da Conta: R$ " << mesaatual.totalconta << "\n\n";
        cout << "Selecione a forma de pagamento:\n";
        cout << "1 - Dinheiro\n";
        cout << "2 - Cartao de Credito/Debito\n";
        cout << "3 - Pix\n";
        cout << "Opcao: ";
        
        getline(cin, entrada);
        int formaPagamento = stoi(entrada);
        string stringForma = "";

        switch (formaPagamento) {
            case 1: stringForma = "Dinheiro"; break;
            case 2: stringForma = "Cartao"; break;
            case 3: stringForma = "Pix"; break;
            default: stringForma = "Nao Informada"; break;
        }

        faturamentoDiario += mesaatual.totalconta; 

        cout << "\n========================================\n";
        cout << " Pagamento de R$ " << mesaatual.totalconta << " recebido via " << stringForma << "!\n";
        cout << "========================================\n";

        mesaatual.totalitens = 0;
        mesaatual.totalconta = 0;
        cout << "\nConta encerrada com sucesso! Mesa " << numeromesa << " agora esta LIVRE.\n";

    } else {
        cout << "\nMesa " << numeromesa << " permanece ABERTA. Nenhum valor foi alterado.\n";
    }
    
    cout << "\nPressione ENTER para voltar ao menu principal...";
    string pausa;
    getline(cin, pausa);
}

void visualizarMesasAtivas()
{
    system("cls");
    exibircabecalho("MESAS COM PEDIDOS ATIVOS");

    bool exibirMesaOcupada = false;

    for (int i = 1; i <= 25; i++) 
    {
        if (mesas[i].totalitens > 0)
        {
            cout << "[ MESA " << i << " ] -> STATUS: OCUPADA\n";
            cout << "  - Itens pedidos: " << mesas[i].totalitens << "\n";
            cout << "  - Valor atual da conta: R$ " << mesas[i].totalconta << "\n";
            cout << " -----------------------------------------\n";

            exibirMesaOcupada = true;
        }
    }
    
    if (!exibirMesaOcupada) {
        cout << "\n No momento, todas as 25 mesas estao LIVRES!\n";
        cout << "Nao ha nenhum cliente consumindo no salao.\n";
    }

    cout << "\nPressione ENTER para voltar ao menu principal.....";
    string pausa;
    getline(cin, pausa);
}                                                                                  

void exibirRelatorioVendas()
{
    system("cls");
    exibircabecalho("FECHAMENTO DE CAIXA / RELATORIO DO DIA");

    cout << "================================================\n";
    cout << "          RESUMO FINANCEIRO DA CAFETERIA        \n";
    cout << "================================================\n\n";
    
    cout << "  (+) FATURAMENTO TOTAL BRUTO: R$ " << faturamentoDiario << "\n";
    cout << "------------------------------------------------\n";
    
    if (faturamentoDiario == 0) {
        cout << "  Status do Caixa: Nenhuma venda realizada ate o momento.\n";
    } else if (faturamentoDiario > 0 && faturamentoDiario < 100) {
        cout << "  Status do Caixa: Movimento inicial/calmo.\n";
    } else {
        cout << "  Status do Caixa: Dia produtivo! Parabens pelas vendas.\n";
    }
    
    cout << "================================================\n";

    cout << "\nPressione ENTER para voltar ao menu principal...";
    string pausa;
    getline(cin, pausa);
}

// ================= FUNÇÃO PRINCIPAL (MAIN) =================

int main()
{
    // Roda a função do database.h para colocar os 5 produtos fixos antes do menu abrir
    inicializarCardapio(); 

    string entradaOpcao;
    int opcao;

    do
    {
        system("cls"); 
        exibircabecalho("MENU PRINCIPAL - CAFETERIA");

        cout << "1 - Cadastrar produtos\n"; 
        cout << "2 - Listar produtos (Cardapio)\n";
        cout << "3 - Fazer / atualizar pedido de uma mesa\n";
        cout << "4 - Exibir conta de uma mesa\n";
        cout << "5 - Visualizar mesas ocupadas (Com clientes)\n";
        cout << "6 - Relatorio de faturamento do dia\n";
        cout << "7 - Sair\n";
        cout << "Opcao: ";
        getline(cin, entradaOpcao);
        opcao = stoi(entradaOpcao);

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
            visualizarMesasAtivas();
            break;

        case 6:
            exibirRelatorioVendas();
            break;

        case 7:
            system("cls");
            cout << "Encerrando o sistema...\n";
            break;

        default: 
            cout << "\nOpcao invalida! Tente novamente!\n";
            cout << "Pressione ENTER para continuar...";
            getline(cin, entradaOpcao);
            break;
        }
    } while (opcao != 7);

    return 0;    
}