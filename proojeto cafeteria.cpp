#include <iostream>
#include <cstdlib>
#include <string>
#include <limits> // Necessário para o numeric_limits

using namespace std;

struct produto {
    int codigo;
    string nome;
    float preco;
};

produto produtos[100];
int totalprodutos = 0;

void cadastrarProduto()


{
    cout << "\n======= Cadastro de produtos =======\n";

    cout << "Codigo do produto: ";
    cin >> produtos[totalprodutos].codigo;

    // Limpa o '\n' que ficou do código para não pular o nome
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nome do produto: ";
    getline(cin, produtos[totalprodutos].nome);

    cout << "Preço de venda: ";
    cin >> produtos[totalprodutos].preco;

    // AQUI ESTAVA O SEGREDO: Limpa o '\n' que ficou do preço para não quebrar o menu principal!
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    totalprodutos++;
    
    cout << "\nProduto cadastrado com sucesso!\n";
}

void listarProdutos()
{
    cout << "\n======= CARDAPIO DO DIA =======\n";

    if(totalprodutos == 0)
    {
        cout << "Infelizmente nao ha produtos cadastrados no momento.\n";
    }
    else 
    {
        for(int i = 0; i < totalprodutos; i++)
        {
            cout << "\nCodigo: " << produtos[i].codigo;
            cout << "\nProduto: " << produtos[i].nome;
            cout << "\nValor: R$ " << produtos[i].preco << "\n";
            cout << "--------------------------------";
        } 
        cout << "\n";
    }
}

int main()
{
    int opcao;

    do
    {
        cout << "\n======= CAFETERIA =======\n";
        cout << "1 - Cadastrar produtos\n";
        cout << "2 - Listar produtos\n";
        cout << "3 - Sair\n";
        cout << "Opcao:  ";
        
        // Se o usuário digitar uma letra no menu, isso evita o travamento
        if (!(cin >> opcao)) {
            cout << "\nErro: Digite apenas numeros!\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = 0; 
        }

        switch (opcao)
        {
        case 1:
            cadastrarProduto();
            
            break;

        case 2:
            listarProdutos();
            break;
        
        case 3: 
            cout << "\nEncerrando...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }
    }
    while (opcao != 3);

    return 0;
}