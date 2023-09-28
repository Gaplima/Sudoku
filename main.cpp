#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include "text_color.h"
using namespace std;

int menuPrincipal(int opc); //Menu com as opções do jogo, como escolher puzzle e ler as regras
void exibirPuzzle(int sdk[]); //Função para mostrar o Sudoku na tela
void jogar(int vet[], int sol[]); //Função com os comandos que o jogador utiliza durante uma partida
int verifica(int vet[], int sol[], int valor); //Função para verificar se uma jogada é válida, inválida, certeira, etc
void check(int sdk[], int sol[]); //Função que verifica se as jogadas inseridas até então são certas ou erradas. Diferente de um trecho da função exibirPuzzle, esta aqui compara diretamente os valores de cada célula do vetor jogável com a correspondente célula no vetor solução
void digitos(int vet[]); //Verificar quais dígitos aparecem menos de 9 vezes no tabuleiro
bool endGame(int vet[]); //Função para conferir se o jogo acabou
bool venceu(int vet[], int sol[]);//Função para conferir se o jogador venceu ou perdeu

//Duas variáveis globais cujos valores se alteram a cada jogada. Embora não seja a solução mais adequada, achei mais prática para meu código do que criar variáveis a cada função ou criar na main e ir passando como parâmetro em cada função.
int lin = 0;
int col = 0;
//Outras duas Variáveis globais, uma para limitar a quantidade de checks e a outra para que haja rotatividade dos puzzles
int checks = 0;
int puz = 1;

int main(){
  int ini;
  int opc;
  cout << "============================================\nBem vindo à uma versão teste do jogo Sudoku\nCopyright (C) 2021, Gabriel Alves P. Lima\n============================================\n\nDigite 1 para iniciar, ou insira outro valor para sair do programa: ";
  cin >> ini;
  if (ini == 1){
    opc = 0;
  }
  else{
    opc = 87;
  }
  while (opc != 87){//Esse 87 é um valor genérico alto para que o programa só encerre em situações bem específicas
    opc = menuPrincipal(opc);
  }
  cout << "Programa encerrado!";
  return 0;
}

int menuPrincipal(int opc){
  int vet[81]; //Vetor que será modificado ao longo do jogo

  //Não consegui fazer essa rotatividade por função, tive que deixar na do menuPrincipal
  int pzum[81] = {1, -3, 4, 6, 7, 8, 5, 9, 2, 6, 7, 2, 1, 9, 5, 3, 4, 8, 5, -9, 8, 3, 4, 2, 1, 6, 7, 8, 5, 9, 7, 6, 1, 4, 2, 3, 4, 2, 6, -8, 5, 3, 9, 7, 1, 7, 1, 3, 4, 2, 9, 8, 5, 6, 9, 6, 1, 5, 3, 7, 2, 8, 4, 2, 8, 7, 9, 1, 4, 6, 3, 5, 3, 4, 5, 2, 8, 6, -7, 1, 9};
  int pzdois[81] = {4, -3, -5, 8, -7, 1, -9, -6, -2, -2, -7, 6, 3, 4, -9, 8, -1, -5, 9, 8, 1, 2, -5, -6, -4, 3, -7, 7, 4, -9, 1, -3, 2, -6, 5, 8, -6, -1, 2, -5, 9, -8, -7, 4, 3, 3, -5, 8, 7, -6, 4, 2, -9, 1, 1, -9, 3, 4, -2, -7, 5, -8, -6, 8, 6, -7, -9, -1, 5, -3, -2, 4, 5, -2, -4, -6, 8, -3, -1, -7, -9};
  int pztres[81] = {4, -7, -9, -2, 3, -1, -5, 8, -6, 1, 6, -2, -8, 9, -5, -4, -3, 7, -5, -3, -8, -4, -6, -7, -9, -1, -2, -9, -1, 3, 7, -2, 4, -8, -6, 5, 6, 8, -7, -5, -1, 9, 2, 4, -3, -2, -5, -4, -3, -8, 6, -7, 9, -1, -3, 4, 5, -1, -7, 8, -6, -2, -9, 7, -2, -6, -9, 4, 3, 1, 5, -8, -8, -9, 1, -6, 5, 2, 3, -7, -4};
  int pzquatro[81] = {3, -4, -9, -7, 2, -6, -8, -5, 1, -8, -7, -1, -3, 4, -5, -9, -2, -6, -2, 5, -6, 8, -9, -1, 4, -7, -3, -1, 3, -2, -4, 7, -9, 6, -8, 5, -7, 6, -4, -5, -3, 8, 2, -1, 9, 5, -9, 8, 1, -6, -2, -7, -3, -4, -6, -8, -3, -2, -5, -4, -1, 9, -7, -9, 1, 5, -6, -8, 7, -3, -4, -2, -4, -2, 7, 9, -1, -3, 5, -6, -8};
  int pzcinco[81] = {5, 3, -4, -6, 7, -8, -9, -1, -2, 6, -7, -2, 1, 9, 5, -3, -4, -8, -1, 9, 8, -3, -4, -2, -5, 6, -7, 8, -5, -9, -7, 6, -1, -4, -2, 3, 4, -2, -6, 8, -5, 3, -7, -9, 1, 7, -1, -3, -9, 2, -4, -8, -5, 6, -9, 6, -1, -5, -3, -7, 2, 8, -4, -2, -8, -7, 4, 1, 9, -6, -3, 5, -3, -4, -5, -2, 8, -6, -1, 7, 9};
  int pzseis[81] = {-9, 6, -3, 1, -7, 4, -2, 5, -8, -1, -7, 8, 3, -2, 5, 6, -4, -9, 2, -5, -4, -6, -8, -9, -7, -3, 1, 8, -2, -1, 4, -3, 7, -5, -9, 6, -4, -9, 6, -8, -5, -2, 3, -1, -7, 7, -3, -5, 9, -6, 1, -8, -2, 4, 5, -8, -9, -7, -1, -3, -4, -6, 2, -3, -1, 7, 2, -4, 6, 9, -8, -5, -6, 4, -2, 5, -9, 8, -1, 7, -3};
  
  if (puz % 6 == 1){//Nestes próximos if/else definimos qual puzzle será utilizado, a partir da escolha do jogador
    for (int i = 0; i < 81; i++){
      vet[i] = pzum[i];
    }
  }
  else if (puz % 6 == 2){
    for (int i = 0; i < 81; i++){
      vet[i] = pzdois[i];
    }
  }
  else if (puz % 6 == 3){
    for (int i = 0; i < 81; i++){
      vet[i] = pztres[i];
    }
  }
  else if (puz % 6 == 4){
    for (int i = 0; i < 81; i++){
      vet[i] = pzquatro[i];
    }
  }
  else if (puz % 6 == 5){
    for (int i = 0; i < 81; i++){
      vet[i] = pzcinco[i];
    }
  }
  else if (puz % 6 == 0){
    for (int i = 0; i < 81; i++){
      vet[i] = pzseis[i];
    }
  }

  int sol[81];//Aqui fazemos um vetor solução em que todos os valores são negativos, utilizado em algumas comparações ao longo da execução
  for (int i = 0; i < 81; i++){
    if (vet[i] >= 0){
      sol[i] = vet[i] * -1;
    }
    else{
      sol[i] = vet[i];
    }
  }

  cout <<  Color::tcolor( "\n   -----Menu  Principal-----", Color::BRIGHT_BLUE );
  exibirPuzzle(vet);
  cout <<   Color::tcolor( "\n\n1) Jogar este Puzzle\n2) Escolher outro Puzzle\n3) Sair do Jogo\n4) Ler as regras\n\nSelecione uma opção [1,4] > ", Color::BRIGHT_YELLOW );
  cin >> opc; //recebemos opc para que o código execute a opção escolhida
  if (opc == 1){
    checks = 3;
    cout << "Jogar este Puzzle\n\n";
    jogar(vet, sol);
  }
  else if (opc == 2){
    cout << "Escolher outro Puzzle\n";
    puz++; //É neste puz++ que fazemos a rotatividade dos puzzles, lá em cima fazemos a divisão deste valor por 6 (quantidade de puzzles) e vemos qual será exibido através do resto da divisão
  }
  else if (opc == 3 || opc == 87){
    cout << "\nVocê escolheu sair do jogo.\n";
    opc = 87; //Nosso valor de segurança
  }
  else if (opc == 4){
    cout << Color::tcolor("\n====================================================\nO objetivo do Sudoku é preencher uma tabela 9x9 com\nnúmeros de forma que cada linha, coluna e quadrante\n(3x3) contenha todos os dígitos entre 1 e 9.\n\nAs regras do Sudoku são:\n1) Cada linha, coluna e quadrante deve conter cada\nnúmero exatamente uma vez.\n2) A soma de todos os números em qualquer linha,\ncoluna ou quadrante deve ser igual a 45.\n====================================================\n\n", Color::BRIGHT_GREEN );
  }
  else{
    cout << 
  Color::tcolor("\nVocê escolheu uma opção inválida. Por favor, tente novamente.\n", Color::BRIGHT_YELLOW );
  }
  return opc;
}

void exibirPuzzle(int sdk[]){
  string str;
  cout << "\n";
  //Posição da coluna em que o último valor foi inserido, para indicar com a setinha. Utilizo uns padrões de identação e um pequeno for para garantir que será a posição certa
  if (col >= 1 && col <= 3){
    cout << "   ";
  }
  else if (col >= 4 && col <= 6){
    cout << "     ";
  }
  else if (col >= 7 && col <= 9){
    cout << "       ";
  }
  for (int a = 1; a <= col; a++){
    cout << "  ";
  }
  cout << "v \n";
  cout << Color::tcolor( "     1 2 3   4 5 6   7 8 9  \n", Color::CYAN ) << "   +-------+-------+-------+\n";
  for (int i = 1; i <= 9; i++){
    if ((i % 3) == 1 && i>1){
      cout << "   |-------+-------+-------|\n";
    }
    str = to_string(i);
    if (lin == i){  //Posição da linha em que o último valor foi inserido, para indicar com a setinha
      cout << ">" << Color::tcolor( str, Color::CYAN ) << " | ";   
    }
    else{
      cout << " " << Color::tcolor( str, Color::CYAN ) << " | ";
    }
    for (int j = 1; j <= 9; j++){
      int x = ((i-1) * 9) + (j-1); //Fórmula para converter a posição desejada para um vetor unitário (ao invés de usar um v[9][9] uso um v[81])
      //sdk[x] = 1;
      if (sdk[x] <= 0){
        //Nada inserido
        cout << "  ";
      }
      else if (sdk[x] > 0 && sdk[x] < 10){
        //Celula padrão
        cout << sdk[x] << " ";
      }
      else if (sdk[x] >= 10 && sdk[x] < 20){
        //Valor válido e certo
        str = to_string(sdk[x]%10);
        cout << Color::tcolor( str, Color::CYAN) << " ";
      }
      else if (sdk[x] >= 20 && sdk[x] < 30){
        //Valor válido, mas errado
        str = to_string(sdk[x]%20);
        cout << Color::tcolor( str, Color::CYAN) << " ";
      }
      else if (sdk[x] >= 30 && sdk[x] < 40){
        //Valor inválido
        str = to_string(sdk[x]%30);
        cout << Color::tcolor( str, Color::BRIGHT_RED) << " ";
      }
      if ((j % 3) == 0){
        cout << "| ";
      }
    }
    cout << "\n";
  }
  cout << "   +-------+-------+-------+\n";
}

void jogar(int vet[], int sol[]){
  string str;
  int op = 0;
  cout <<  Color::tcolor( "\n   ------Menu de Ações------", Color::BRIGHT_BLUE );
  exibirPuzzle(vet);
  digitos(vet);
  str = to_string(checks);//Usei este to_string para printar alguns valores coloridos, aparece múltiplas vezes no código
  cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
  int addrem = 0; //Variável para verificar se houve uma última jogada e se ela foi para inserir ou remover valor
  int val = 0; //Variável onde será o input
  int aux = 0; //Variável que recebe a fórmula para converter matriz em um vetor único

  // 3 variáveis que receberão o último valor a ser colocado e sua posição, para facilitar na hora de desfazer a última jogada. Iria colocar dentro do if de remover, mas o fiquei receoso de ocorrerem alguns erros
  int ultval = 0; 
  int ultlin = 0;
  int ultcol = 0;

  while (op != 87){
    cout << Color::tcolor( "\n\nOpções\n1) Inserir valor ao puzzle\n2) Desfazer última jogada\n3) Remover valor do puzzle\n4) Verificar se suas jogadas estão certas\n5) Retornar ao menu principal", Color::BRIGHT_GREEN ) << Color::tcolor( "\n\nSelecione uma opção [1,5] > ", Color::BRIGHT_YELLOW );
    cin >> op;
    if (op == 1){ //Inserir valor

      cout << "\nInforme linha, coluna e valor que deseja inserir: ";
      cin >> lin >> col >> val;
      if (lin > 9 || lin < 1 || col > 9 || col < 1 || val > 9 || val < 1){//Confere se nenhum valor inserido está fora do range [1,9]
        cout <<  Color::tcolor("\n\nMSG: [ Por favor, insira valores inteiros no intervalo [1,9] ]\n", Color::BRIGHT_YELLOW );
      }
      else{
        aux = ((lin-1) * 9) + (col-1); //Fórmula para converter as posições de uma matriz[9][9] na de um vetor[81]

        if (vet[aux] > 0 && vet[aux] < 10){ //Valor neste intervalo é uma posição padrão do puzzle, nada é modificado
          exibirPuzzle(vet);
          digitos(vet);
          str = to_string(checks);
          cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
          cout << Color::tcolor( "\nMSG: [ Você não pode sobrescrever uma posição padrão do puzzle. ]\n", Color::BRIGHT_YELLOW );
        }
        else if (vet[aux] > 10 && vet[aux] < 40){//Valor neste intervalo é uma posição já preenchida pelo jogador, nada é modificado
          exibirPuzzle(vet);
          digitos(vet);
          str = to_string(checks);
          cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
          cout << Color::tcolor( "\nMSG: [ Você já preencheu esta célula com um valor. Caso deseja substituir o valor atual selecione a opção 3, remova o valor da posição e só então volte a esta opção para adicionar o novo valor. ]\n", Color::BRIGHT_YELLOW );
        }
        else if (vet[aux] <= 0){//Esta posição não está ocupada, agora verificamos alguns detalhes antes de inserir o valor
          if (verifica(vet, sol, val) == 3){//Conferimos se é uma posição inválida de acordo com as regras. Se for, perguntamos ao jogador se ele deseja manter sua jogada
            int inserir = 0;
            cout << Color::tcolor("\nMSG: [ Sua jogada é contra as regras do Sudoku, deseja inserir mesmo assim? ]\n", Color::BRIGHT_YELLOW );
            cout << Color::tcolor("\nSe deseja manter a jogada digite 1, caso contrário digite qualquer outro valor e pressione Enter. > ", Color::BRIGHT_YELLOW );
            cin >> inserir;
            if (inserir == 1){//Aqui o jogador desejou manter, logo ocorre uma jogada aceita pelo sistema
              vet[aux] = val + (10 * verifica(vet, sol, val));
              addrem = 1;
              ultlin = lin; //As 3 próximas linhas são das variáveis ult recebendo os valores inseridos
              ultcol = col;
              ultval = vet[aux];
              exibirPuzzle(vet);
              digitos(vet);
              str = to_string(checks);
              cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
              cout << Color::tcolor("\nMSG: [ Sua jogada, mesmo inválida, foi computada com sucesso! ]\n", Color::BRIGHT_YELLOW );
            }
            else{//Aqui o jogador desejou não manter, logo nada no puzzle é modificado
              exibirPuzzle(vet);
              digitos(vet);
              str = to_string(checks);
              cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
              cout << Color::tcolor("\nMSG: [ Sua jogada não foi computada! ]\n", Color::BRIGHT_YELLOW );
            }
          }
          else{ //Aqui ocorre uma jogada válida
            vet[aux] = val + (10 * verifica(vet, sol, val));//Embora no cout não haja diferença entre uma jogada válida errada e uma válida certeira, essa função verifica é útil para a hora do check
            addrem = 1;
            ultlin = lin;
            ultcol = col;
            ultval = vet[aux];
            exibirPuzzle(vet);
            digitos(vet);
            str = to_string(checks);
            cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
            cout << Color::tcolor("\nMSG: [ Jogada válida e computada com sucesso! ]\n", Color::BRIGHT_YELLOW );
          }
        }
      }
    }

    else if (op == 2){//Última jogada
      if (addrem == 1){ //Última jogada foi inserir um valor, logo este valor é removido do puzzle
        aux = ((ultlin-1) * 9) + (ultcol-1);
        vet[aux] = 0;
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor("\nMSG: [ Sua última jogada foi desfeita com sucesso! ]\n", Color::BRIGHT_YELLOW );
        addrem = 3;
      }
      else if (addrem == 2){ //Última jogada foi remover um valor, logo este valor é reinserido ao puzzle
        aux = ((ultlin-1) * 9) + (ultcol-1);  
        vet[aux] = ultval;
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor("\nMSG: [ Sua última jogada foi desfeita com sucesso! ]\n", Color::BRIGHT_YELLOW );
        addrem = 3;
      }
      else if (addrem == 3){ //Como eu só consegui desfazer uma jogada, coloquei este addrem == 3 para que não dê outros problemas no executável
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor( "\nMSG: [ Sua última jogada já foi desfeita ]\n", Color::BRIGHT_YELLOW );
      }
      else if (addrem == 0){ //Caso o jogador ainda não tenha feito nenhuma jogada
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor( "\nMSG: [ Você ainda não fez nenhuma jogada! ]\n", Color::BRIGHT_YELLOW );
      }
    }
    else if (op == 3){//Remover valor
      cout << "\nInforme linha e coluna do valor que deseja remover: ";
      cin >> lin >> col;
      if (lin > 9 || lin < 1 || col > 9 || col < 1){//Confere se os valores inseridos estão no intervalo [1,9]
        cout <<  Color::tcolor("\n\nMSG: [ Por favor, insira valores inteiros no intervalo [1,9] ]\n", Color::BRIGHT_YELLOW );
      }
      else{
        aux = ((lin-1) * 9) + (col-1);
        if (vet[aux] == 0){ //Célula vazia, nada é feito
          exibirPuzzle(vet);
          digitos(vet);
          str = to_string(checks);
          cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
          cout << Color::tcolor( "\nMSG: [ A célula já está vazia ]\n", Color::BRIGHT_YELLOW );
        }
        else if (vet[aux] > 0 && vet[aux] < 10){ //Célula padrão do puzzle, nada é feito
          exibirPuzzle(vet);
          digitos(vet);
          str = to_string(checks);
          cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
          cout << Color::tcolor("\nMSG: [ Você não pode remover uma posição padrão do puzzle ]\n", Color::BRIGHT_YELLOW );
         }
        else if (vet[aux] > 10){//Aqui remove independente se o valor é válido ou inválido, certeiro ou errado
          ultlin = lin;
          ultcol = col;
          ultval = vet[aux];
          vet[aux] = 0;
          addrem = 2;
          exibirPuzzle(vet);
          digitos(vet);
          str = to_string(checks);
          cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
          cout << Color::tcolor("\nMSG: [ Você removeu um valor do puzzle! ]\n", Color::BRIGHT_YELLOW );
        }
      }
    }
    else if (op == 4){//Check
      if(checks > 0){ //Confere se o jogador ainda tem checks disponíveis, se sim executa a função check
        check (vet, sol);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor("\nMSG: [ Você pediu uma verificação das posições do jogo. ]\n", Color::BRIGHT_YELLOW );
      }
      else{
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor("\nMSG: [ Você não tem mais checks disponíveis! ]\n", Color::BRIGHT_YELLOW );
      }
    }
    else if (op == 5 || op == 87){//Retornar ao menu
      int inserir = 0;
      cout << Color::tcolor( "\nMSG: [ Tem certeza que deseja retornar ao menu principal? Seu jogo não será salvo. ]\nSe deseja sair digite 1, caso contrário digite qualquer outro valor e pressione Enter. > ", Color::BRIGHT_YELLOW );
      cin >> inserir; //Pergunta ao jogador se ele realmente deseja retornar ao menu
      if (inserir == 1){
        cout << Color::tcolor( "\nMSG: [ Retornando ao menu principal! }\n", Color::BRIGHT_YELLOW );
        op = 87;
      }
      else{
        exibirPuzzle(vet);
        digitos(vet);
        str = to_string(checks);
        cout << Color::tcolor("\nChecks Restantes: ", Color::BRIGHT_YELLOW ) << Color::tcolor(str, Color::BRIGHT_YELLOW );
        cout << Color::tcolor( "\nMSG: [ Continuando o jogo! ]\n", Color::BRIGHT_YELLOW );        
      }
    }
    else{
      cout << Color::tcolor( "\nVocê escolheu uma opção inválida. Por favor, tente novamente.\n", Color::BRIGHT_YELLOW );
    }
    if (endGame(vet)){ //Confere se todos os elementos da tabela foram preenchidos
      char menu;
      cout << Color::tcolor("\nMSG: [ O jogo terminou!", Color::BRIGHT_YELLOW );
      if(venceu(vet, sol)){ //Confere se todos os elementos estão certos
        cout << Color::tcolor(" PARABÉNS, você conseguiu completar este puzzle do Sudoku. Pressione qualquer tecla e aperte Enter para retornar ao menu principal ]", Color::BRIGHT_YELLOW );
        cin >> menu;
        op = 87;
      }
      else{
        cout << Color::tcolor(" Que pena, não foi dessa vez que você conseguiu vencer o Sudoku. Pressione qualquer tecla e aperte Enter para retornar ao menu principal ]", Color::BRIGHT_YELLOW );
        cin >> menu;
        op = 87;
      }
    }
  }
}

int verifica(int vet[], int sol[], int valor){
  int ver = 2;
  int aux = ((lin-1) * 9) + (col-1);
  for (int i = 1; i <=9; i++){//Verificando se já há um valor igual na mesma linha
    int x = ((i-1) * 9) + (col-1);
    if (vet[x]%10 == valor && i != lin){
      return ver = 3;
    }
  }
  for (int j = 1; j <=9; j++){//Verificando se já há um valor igual na mesma coluna
    int x = ((lin-1) * 9) + (j-1);
    if (vet[x]%10 == valor && j != col){
      return ver = 3;
    }
  }
  //Agora comparando os quadrantes
  if (lin >= 1 && lin <= 3){//Os 3 quadrantes de cima
    if (col >= 1 && col <= 3){
      for (int i = 1; i <= 3; i++){
        for(int j = 1; j <= 3; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }
        }
      }
    }
    else if (col >= 4 && col <= 6){
      for (int i = 1; i <= 3; i++){
        for(int j = 4; j <= 6; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
    else if (col >= 7 && col <= 9){
      for (int i = 1; i <= 3; i++){
        for(int j = 7; j <= 9; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
  }
  else if(lin >= 4 && lin <= 6){//Os 3 quadrantes do meio
    if (col >= 1 && col <= 3){
      for (int i = 4; i <= 6; i++){
        for(int j = 1; j <= 3; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
    else if (col >= 4 && col <= 6){
      for (int i = 4; i <= 6; i++){
        for(int j = 4; j <= 6; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
    else if (col >= 7 && col <= 9){
      for (int i = 4; i <= 6; i++){
        for(int j = 7; j <= 9; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }    
    }
  }
  else if(lin >= 7 && lin <= 9){//Os 3 quadrantes de baixo
    if (col >= 1 && col <= 3){
      for (int i = 7; i <= 9; i++){
        for(int j = 1; j <= 3; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
    else if (col >= 4 && col <= 6){
      for (int i = 7; i <= 9; i++){
        for(int j = 4; j <= 6; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }
    }
    else if (col >= 7 && col <= 9){
      for (int i = 7; i <= 9; i++){
        for(int j = 7; j <= 9; j++){
          int x = ((i-1) * 9) + (j-1);
          if (vet[x]%10 == valor && i != lin && j != col){
            return ver = 3;
          }          
        }
      }    
    }
  }
  if (valor * -1 == sol[aux]){
    return ver = 1;
  }
  return ver;
}

void check(int sdk[], int sol[]){
  //Nesta função a parte de printar o tabuleiro é muito semelhante à da função exibirPuzzle, mas aqui a comparação é direta com o vetor solução
  string str;
  cout << "\n";
  //Posição da coluna em que o último valor foi inserido, para indicar com a setinha
  if (col >= 1 && col <= 3){
    cout << "   ";
  }
  else if (col >= 4 && col <= 6){
    cout << "     ";
  }
  else if (col >= 7 && col <= 9){
    cout << "       ";
  }
  for (int a = 1; a <= col; a++){
    cout << "  ";
  }
  cout << "v \n";

  cout << "     1 2 3   4 5 6   7 8 9  \n   +-------+-------+-------+\n";
  for (int i = 1; i <= 9; i++){
    if ((i % 3) == 1 && i>1){
      cout << "   |-------+-------+-------|\n";
    }

    if (lin == i){
      cout << ">" << i << " | ";     //Posição da linha em que o último valor foi inserido, para indicar com a setinha
    }
    else{
      cout << " " << i << " | ";
    }

    for (int j = 1; j <= 9; j++){
      int x = ((i-1) * 9) + (j-1); //Fórmula para converter a posição desejada para um vetor unitário (ao invés de usar um v[9][9] uso um v[81])
      //sdk[x] = 1;

      if (sdk[x] * -1 == sol[x]){ //Celula padrão
        cout << sdk[x] << " ";
      }
      else if (sdk[x] <= 0){ //Nada inserido
          cout << "  ";
        }
      else if ((sdk[x] -10) * -1 == sol[x]){ //Valor válido e certo
        str = to_string(sdk[x]%10);
        cout << Color::tcolor( str, Color::BRIGHT_GREEN) << " ";
      }
      else if ((sdk[x] -10) * -1 != sol[x]){
        if (sdk[x] >= 20 && sdk[x] < 30){ //Valor válido, mas errado
        str = to_string(sdk[x]%20);
        cout << Color::tcolor( str, Color::BRIGHT_RED) << " ";
        }
        else if (sdk[x] >= 30 && sdk[x] < 40){ //Valor inválido
        str = to_string(sdk[x]%20);
        cout << Color::tcolor( str, Color::RED) << " ";
        }      
      }
      if ((j % 3) == 0){
        cout << "| ";
      }
    }
    cout << "\n";
  }
  cout << "   +-------+-------+-------+\n";
  checks--;
}

void digitos(int vet[]){
  string str;
  int v[9];//Utilizo um vetor auxiliar e reduzido para contar quantas vezes cada valor (de 1 a 9) aparece no tabuleiro
  for (int a = 0; a < 9; a++){
    v[a] = 0;
  }
  for (int x = 0; x < 81; x++){
    for (int y = 0; y < 9; y++){
      if (vet[x]%10 == y + 1){ //Como o vetor vai de 0 a 8, somo 1 para equivaler
        v[y]++;
      }
    }
  }
  cout << Color::tcolor("\nDígitos restantes: [ ", Color::BRIGHT_YELLOW ); //Cout simples, se o número aparecer 9 vezes no vetor do tabuleiro então no lugar do número sera printado um espaço vazio
  for (int b = 0; b < 9; b++){
    if (v[b] >= 9){ //Este >= evita que o número seja printado nos restantes caso um jogador coloque mais de 9 vezes um valor
      cout << "  ";
    }
    else{
      str = to_string(b+1);
      cout << Color::tcolor( str, Color::BRIGHT_YELLOW ) << " ";
    }
  }
  cout << Color::tcolor("]", Color::BRIGHT_YELLOW );
}

bool endGame(int vet[]){
  for (int i = 0; i < 81; i++){//Percorre todos os elementos do vetor, se tiver algum que seja igual (ou menor) a zero significa que aquela posição não está preenchida. Logo ainda falta inserir pelo menos um elemento no Sudoku
    if (vet[i] <= 0){
      return false;
    }
  }
  return true;
}

bool venceu(int vet[], int sol[]){
  for (int i = 0; i < 81; i++){//Percorre todos os elementos do vetor "jogável" e compara cada um com o respectivo do vetor solução, se nenhum valor for diferente o jogador venceu.
    if (vet[i]%10 != sol[i] * -1){
      return false;
    }
  }
  return true;
}