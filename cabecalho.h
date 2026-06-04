#ifndef CABECALHO_H
#define CABECALHO_H

#include <iostream>
#include <string>

using namespace std;

// Função que desenha o cabeçalho dinâmico
void exibircabecalho(string texto)
{
    cout << "\n===============================================\n";
    cout << "               " << texto << "\n";
    cout << "===============================================\n";
}

#endif // CABECALHO_H