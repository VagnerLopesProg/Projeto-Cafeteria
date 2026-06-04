#ifndef DATABASE_H
#define DATABASE_H

#include <string>

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

struct registroMesa
{
    itemPedido itens[100];
    int totalitens = 0;
    float totalconta = 0.0; 
};

// === VARIÁVEIS GLOBAIS ===
inline produto produtos[100]; 
inline int totalprodutos = 0;

inline registroMesa mesas[26];
inline float faturamentoDiario = 0.0;  

// === INICIALIZAÇÃO DO BANCO DE DADOS ===
inline void inicializarCardapio()
{
    // CORRIGIDO: Era 'rodutos', mudado para 'produtos'
    produtos[totalprodutos].codigo = 10;
    produtos[totalprodutos].nome = "Cafe";
    produtos[totalprodutos].preco = 2.00;
    produtos[totalprodutos].categoria = "Bebida";
    totalprodutos++;

    produtos[totalprodutos].codigo = 11;
    produtos[totalprodutos].nome = "Cafe Expresso";
    produtos[totalprodutos].preco = 5.00;
    produtos[totalprodutos].categoria = "Bebida";
    totalprodutos++;

    // CORRIGIDO: O código era 11 (duplicado), mudado para 12
    produtos[totalprodutos].codigo = 12;
    produtos[totalprodutos].nome = "Cappuccino";
    produtos[totalprodutos].preco = 8.50;
    produtos[totalprodutos].categoria = "Bebida";
    totalprodutos++;

    // AJUSTADO: Código mudado para 13 para seguir a sequência
    produtos[totalprodutos].codigo = 13;
    produtos[totalprodutos].nome = "Pao de Queijo";
    produtos[totalprodutos].preco = 4.00;
    produtos[totalprodutos].categoria = "Comida";
    totalprodutos++;

    // AJUSTADO: Código mudado para 14
    produtos[totalprodutos].codigo = 14;
    produtos[totalprodutos].nome = "Coxinha de Frango";
    produtos[totalprodutos].preco = 7.00;
    produtos[totalprodutos].categoria = "Comida";
    totalprodutos++;

    // AJUSTADO: Código mudado para 15
    produtos[totalprodutos].codigo = 15;
    produtos[totalprodutos].nome = "Fatia de Bolo de Cenoura";
    produtos[totalprodutos].preco = 6.50;
    produtos[totalprodutos].categoria = "Sobremesa";
    totalprodutos++;

    // CORRIGIDO: Era 'rodutos', mudado para 'produtos' e código para 16
    produtos[totalprodutos].codigo = 16;
    produtos[totalprodutos].nome = "Misto quente";
    produtos[totalprodutos].preco = 5.50;
    produtos[totalprodutos].categoria = "Comida";
    totalprodutos++;
}

#endif