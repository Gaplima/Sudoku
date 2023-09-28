Linguagem de Programação I - T01
Projeto de Programação #1

Aluno: Gabriel Alves Pinheiro Lima
Professor: Selan Rodrigues dos Santos

Comando de compilação: gpp -Wall main.cpp -o main
Comando de execução: ./main
Link do git: https://projetos.imd.ufrn.br/bydebil00/projeto-de-programacao-1-sudoku

Sudoku Interativo

   Este trabalho consiste de desenvolver em c++ um Sudoku que o usuário
possa jogar e resolver os puzzles com uma série de comandos fornecidos.
   O código foi feito inteiramente por mim, Gabriel Alves, utilizando de
alguns conceitos aprendidos nos encontros do Zoom e/ou em disciplinas
anteriores. Este código desenvolvido é composto de um arquivo main.cpp e um
arquivo text_color.h (fornecido pelo professor) para auxiliar na identificação
dos textos com diferentes cores. O arquivo principal consiste de uma várias
funções dos tipos void, bool ou int que facilitaram a dinamizar o
desenvolvimento do trabalho.

   Algumas partes solicitadas no arquivo .pdf eu não consegui fazer por motivos como
erro de compilação ou simplesmente por eu não saber como aplicá-las da maneira
requisitada, são elas:
   -Ler e armazenar os puzzles em um arquivo de entrada. Como eu não entendo de leitura
e gravação de arquivo, apenas deixei uns puzzles padrões no main.cpp, eles estão dentro
da função menuPrincipal;
   -Opção de retomar uma partida suspensa. Pelo mesmo motivo da anterior eu não sei
como poderia salvar o progresso do jogador em um arquivo para numa próxima execução ler
e executar o jogo salvo.

   Já outros detalhes do código foram feitos de maneira diferente da solicitada no .pdf
do projeto, alguns para adaptar melhor ao resto do código, outros por serem dependentes
das partes que eu não consegui fazer. Estes detalhes são:
   -Permitir a escolha dos puzzles lidos do arquivo: Como não há leitura de arquivo,
essa escolha é feita dentro da função menuPrincipal, através de alguns puzzles já defi-
nidos no código.
   -Executar o comando de desfazer ação: Minha ideia era criar uma struct que armaze-
nasse cada jogada e o jogador ia desfazendo quantas jogadas fosse possível, contudo eu
não consegui aplicar essa teoria no meu código e deixei apenas algumas variáveis que
salvam a jogada mais recente, sendo que esta é a única que pode ser desfeita.
   -Tratar corretamente os argumentos da linha de comando: Eu não entendo muito bem
de leitura de strings, logo fiz um menu numérico com as opções do jogo e salvei essas
opções em variáveis int. Desta forma, caso o jogador deseje inserir um valor na tabela,
ele primeiro deve escolher esta opção e no cin seguinte informar linha, coluna e valor.