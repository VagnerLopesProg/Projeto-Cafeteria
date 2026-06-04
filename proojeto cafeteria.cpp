#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct produto {
    int codigo;
    string nome;
    float preco;
    string categoria;
};

struct itempedido
{
    string nome;
    float preco;
};

produto produtos[100];
int totalprodutos = 0;

void cadastrarProduto()
{
    string entrada;
    string continuar;

    do
    {
        cout << "\n ======= CADASTRO DE PRODUTOS =======\n";
         
        cout << "\nCodigo do produto: \n";
        getline(cin, entrada);
        produtos[totalprodutos].codigo = stoi(entrada);

        cout << "\nNome do produto: \n";
        getline(cin, produtos[totalprodutos].nome);

        cout << "\nPreco de venda: \n";
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
            system("cls");
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
                cout << "Opcao invalida! Escolha entre 1 e 3. \n";
            }

        } while (!categoriaValida);

        totalprodutos++;
        cout << "\nProduto cadastrado com sucesso!\n";

        cout << "Deseja cadastrar outro produto? (S/N): ";
        getline(cin, continuar); 
        system ("cls");
            
    } while (continuar == "S" || continuar == "s");
}

void listarProdutos()
{
    cout << "\n======= CARDAPIO DO DIA =======\n"; 

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
            cout << "\nValor: R$ " << produtos[i].preco << "\n";
            cout << "------------------------------------------\n";
        }
    }
}

void fazerPedido()
{
    if (totalprodutos == 0) {
        cout << "\nNao e possivel fazer um pedido porque nao ha produtos no cardapio!\n";
        return;
    }

    itempedido itensDoPedido[100]; 
    int totalItensPedido = 0;      
    string entrada, continuar;
    float totalConta = 0;

    do {
        listarProdutos();

        cout << "\nDigite o CODIGO do produto que deseja pedir: ";
        getline(cin, entrada);
        int codigoEscolhido = stoi(entrada);

        bool produtoEncontrado = false;

        // 1. O loop APENAS procura e adiciona se achar
        for (int i = 0; i < totalprodutos; i++) {
            if (produtos[i].codigo == codigoEscolhido) {
                itensDoPedido[totalItensPedido].nome = produtos[i].nome;
                itensDoPedido[totalItensPedido].preco = produtos[i].preco;
                totalItensPedido++;
                
                totalConta += produtos[i].preco; 
                cout << "\n-> " << produtos[i].nome << " adicionado ao seu pedido!\n";
                produtoEncontrado = true;
                break; // Achou? Para o "for" na hora!
            }
        }

        // 2. SÓ DEPOIS do loop terminar avaliamos se ele passou por lá sem achar nada
        if (!produtoEncontrado) {
            cout << "\nCodigo invalido! Produto nao encontrado.\n";
        }

        cout << "\nDeseja adicionar mais algum produto ao seu pedido? (S/N): ";
        getline(cin, continuar);

    } while (continuar == "S" || continuar == "s");

    cout << "\n======= RESUMO DO SEU PEDIDO =======\n";
    for (int i = 0; i < totalItensPedido; i++) {
        cout << "- " << itensDoPedido[i].nome << " : R$ " << itensDoPedido[i].preco << "\n";
    }
    cout << "------------------------------------\n";
    cout << "TOTAL A PAGAR: R$ " << totalConta << "\n";
    cout << "====================================\n";
};

int main()
{
    string entradaOpcao;
    int opcao;

    do {
        // CORRIGIDO: Adicionado \n ao final de cada linha para o menu ficar na vertical
        cout << "\n======= CAFETERIA =======\n";
        cout << "1 - Cadastrar produto\n";
        cout << "2 - Listar produtos\n";
        cout << "3 - Fazer novo pedido\n";
        cout << "4 - Sair\n";
        cout << "Opcao: ";

        getline(cin, entradaOpcao);
        opcao = stoi(entradaOpcao);

        switch (opcao)
        {
        case 1:
            cadastrarProduto();
            break;
        
        case 2: 
            listarProdutos();
            break; 
        case 3:
            fazerPedido();
            break;
        
        case 4:
            cout <<"\n Encerrando.......";
            break;

        default: 
            cout << "Opcao invalida!\n"; 
            break;
        }
        
    } while (opcao != 4);
    
    return 0;
}