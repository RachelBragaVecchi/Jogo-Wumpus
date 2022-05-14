#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
int posicaoXJ=0;
int posicaoYJ=0;
int tempoMov = 25;
int redesenhar = 1;
int xW, yW, xB, yB, xA,  yA, xP = -500, yP = -500, xB2, yB2, xP2, yP2;
int quantFlechas = 4;
char matrizJogador [6][6];
char matrizWumpus [6][6];
void gerarPortalSemMagia(void);
void exibirMatrizWumpus(void);
void musicaMatriz(void);
void musicaRegraDeJ(void);
void jogadoFoiDeBase(void);//Coloquei
void wumpusMatouJ(void);//Coloquei
void moverWumpus(void);//Coloquei
void gerarPortal(void);
void timeMatriz(void); //ipc
void atirarFlecha(char direcao); //IPC
void colocarVariaveis(void);
void sextoSentido(void); //IPC
void exibirComandosDoJogador(void);
void iniciarMatrizWumpus(void);
void moverJogador(void); //IPC
void iniciarMatrizJogador(void);
void printMatrizJogador(void);
void regraDoJogo(void);
void inicioJogo(void); //IPC2

int main()

{
    posicaoXJ=0;
    posicaoYJ=0;
    tempoMov = 25;
    redesenhar = 1;
    xW = -500;
    yW = -500;
    xB = -500;
    yB = -500;
    xA = -500;
    yA = -500;
    xP = -500;         // assim as variaveis vao reiniciar toda vez q o jogador voltar para o menu do jogo
    yP = -500;
    xB2 = -500;
    yB2 = -500;

    quantFlechas = 4;

    PlaySound (TEXT("Relaxing Celtic Music - Autumn Forest.wav"), NULL, SND_ASYNC|SND_LOOP);
    system("MODE con cols=60 lines=40");
    system("color 06");
    setlocale(LC_ALL,"portuguese");
    char R;

    while(1)
    {

        HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 3);

        printf("\n\n\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t----------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t+                           *\n");
        printf("\t\t\t\t\t\t\t\t\t\t*   THE LEGEND OF WUMPUS    *\n");
        printf("\t\t\t\t\t\t\t\t\t\t*                           +\n");
        printf("\t\t\t\t\t\t\t\t\t\t----------------------------\n\n\n\n");
        printf("\t\t\t\t\t \n\n\n");
        SetConsoleTextAttribute(h, 11);
        printf("\t\t\t\t\t\t\t\t\t\t      1 - REGRAS\n");
        printf("\t\t\t\t\t\t\t\t\t\t      2 - INICIAR O JOGO\n");
        printf("\t\t\t\t\t\t\t\t\t\t      3 - SAIR\n");
        printf("\n\n\n\n");
        SetConsoleTextAttribute(h, 3);
        printf("\t\t\t\t\t\t\t\t\t\tDÍGITE UM  NÚMERO: ");
        fflush(stdin);
        R = getchar();

        switch (R)
        {
        case '1':
            system("CLS");
            regraDoJogo();
            break;
        case '2':
            system("CLS");
            inicioJogo();
            break;
        case '3':
            exit(0);

            break;

        default:
            printf("\t\t\t\tOPÇÃO INVÁLIDA.\n\n");
        }
        system("pause");
        system("CLS");
    }
}
void iniciarMatrizJogador()
{
    int i;
    int j;
    for(i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            matrizJogador[j][i] = ' ';
        }
    }
}
void iniciarMatrizWumpus()
{
    int i;
    int j;
    for(i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            matrizWumpus[j][i] = ' ';
        }
    }
}
void exibirComandosDoJogador()
{

    if (posicaoXJ==0 && posicaoYJ==0)
    {
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';
        matrizJogador [posicaoXJ ][posicaoYJ + 1] = 's';
    }
    else if (posicaoXJ==0 && posicaoYJ==5)
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1] = 'w';
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';

    }
    else if (posicaoXJ==5 && posicaoYJ==0)
    {
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
        matrizJogador [posicaoXJ][posicaoYJ + 1] = 's';
    }
    else if (posicaoXJ==5 && posicaoYJ==5)
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1 ] = 'w';
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
    }
    else if (posicaoXJ==0 && (posicaoYJ==1||posicaoYJ ==2||posicaoYJ==3||posicaoYJ==4))
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1] = 'w';
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';
        matrizJogador [posicaoXJ][posicaoYJ + 1] = 's';
    }
    else if (posicaoXJ==5 && (posicaoYJ==1||posicaoYJ ==2||posicaoYJ==3||posicaoYJ==4))
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1] = 'w';
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
        matrizJogador [posicaoXJ][posicaoYJ + 1] = 's';
    }
    else if (posicaoYJ==0 &&(posicaoXJ==1||posicaoXJ ==2||posicaoXJ==3||posicaoXJ==4))
    {
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
        matrizJogador [posicaoXJ][posicaoYJ + 1] = 's';
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';
    }
    else if (posicaoYJ==5 &&(posicaoXJ==1||posicaoXJ ==2||posicaoXJ==3||posicaoXJ==4))
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1 ] = 'w';
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';
    }
    else
    {
        matrizJogador [posicaoXJ][posicaoYJ - 1] = 'w';
        matrizJogador [posicaoXJ - 1][posicaoYJ] = 'a';
        matrizJogador [posicaoXJ][posicaoYJ + 1] = 's';
        matrizJogador [posicaoXJ + 1][posicaoYJ] = 'd';
    }

}

void printMatrizJogador()
{
    int i, j;
    for (i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            matrizJogador [j][i]=' ';
        }
    }
    exibirComandosDoJogador();
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 11);
    matrizJogador [posicaoXJ][posicaoYJ]='J';
    printf("FLECHAS:%d",quantFlechas);
    SetConsoleTextAttribute(h, 15);

    printf("\n\n\n");
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][0], matrizJogador[1][0], matrizJogador[2][0], matrizJogador[3][0], matrizJogador[4][0], matrizJogador[5][0]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][1], matrizJogador[1][1], matrizJogador[2][1], matrizJogador[3][1], matrizJogador[4][1], matrizJogador[5][1]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][2], matrizJogador[1][2], matrizJogador[2][2], matrizJogador[3][2], matrizJogador[4][2], matrizJogador[5][2]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][3], matrizJogador[1][3], matrizJogador[2][3], matrizJogador[3][3], matrizJogador[4][3], matrizJogador[5][3]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][4], matrizJogador[1][4], matrizJogador[2][4], matrizJogador[3][4], matrizJogador[4][4], matrizJogador[5][4]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizJogador[0][5], matrizJogador[1][5], matrizJogador[2][5], matrizJogador[3][5], matrizJogador[4][5], matrizJogador[5][5]);
    printf("\t\t -------------------------\n");
/*/
    printf("\n\n\n");
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][0], matrizWumpus[1][0], matrizWumpus[2][0], matrizWumpus[3][0], matrizWumpus[4][0], matrizWumpus[5][0]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][1], matrizWumpus[1][1], matrizWumpus[2][1], matrizWumpus[3][1], matrizWumpus[4][1], matrizWumpus[5][1]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][2], matrizWumpus[1][2], matrizWumpus[2][2], matrizWumpus[3][2], matrizWumpus[4][2], matrizWumpus[5][2]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][3], matrizWumpus[1][3], matrizWumpus[2][3], matrizWumpus[3][3], matrizWumpus[4][3], matrizWumpus[5][3]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][4], matrizWumpus[1][4], matrizWumpus[2][4], matrizWumpus[3][4], matrizWumpus[4][4], matrizWumpus[5][4]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][5], matrizWumpus[1][5], matrizWumpus[2][5], matrizWumpus[3][5], matrizWumpus[4][5], matrizWumpus[5][5]);
    printf("\t\t -------------------------\n");/*/
}
void moverJogador()
{
    if(kbhit())  //keyboard hit
    {
        char direcao;
        HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 11);
        direcao = getch();  //include <conio.h> direcao= getch();//

        switch(direcao)
        {
        case 'w':
            Beep(1350,300);
            if(posicaoYJ > 0 )
            {
                posicaoYJ --;
            }
            jogadoFoiDeBase();
            wumpusMatouJ();
            moverWumpus();
            redesenhar = 1;
            break;

        case 'a':
            Beep(1350,300);
            if(posicaoXJ > 0)
            {
                posicaoXJ --;
            }
            jogadoFoiDeBase();
            wumpusMatouJ();
            moverWumpus();
            redesenhar = 1;
            break;

        case 'd':
            Beep(1350,300);
            if(posicaoXJ < 5)
            {
                posicaoXJ ++;
            }
            jogadoFoiDeBase();
            wumpusMatouJ();
            moverWumpus();
            redesenhar = 1;
            break;

        case 's':
            Beep(1350,300);   // a função redesenhar ganha 1 para redesenhar a matriz sempre que o jogador anda
            if(posicaoYJ < 5)  // wumpus matou jogador porque na matriz n estava funcionando quando o wumpus ou o jogador se encontrassem.
            {
                posicaoYJ ++;
            }
            jogadoFoiDeBase();
            wumpusMatouJ();
            moverWumpus();
            redesenhar = 1;
            break;

        case 'f':
            printf("escolha a direção para atirar.\n");
            fflush(stdin);
            direcao = getchar();
            if(quantFlechas > -1)
            {
                atirarFlecha(direcao);
            }
            if (quantFlechas == 0)  // quando a flecha for igual a 0 a função gerar portal e ativada
            {
                gerarPortalSemMagia();

            }

            if (quantFlechas== -1)
            {

                system("cls");
                PlaySound (TEXT("SOM DE ALERTA VERMELHO (ALARME DE EMERGÊNCIA) Efeito Sonoro HQ + DOWNLOAD.WAV"), NULL, SND_ASYNC);
                printf("\n\nSUAS FLECHAS ACABARAM.\n\n\n\n\n\n");
                system("pause");
                system("cls");
                exibirMatrizWumpus();
            }
            break;
        }
        if(quantFlechas == 0)
        {
            if(xP2==posicaoXJ && yP2==posicaoYJ)
            {
                system("cls");
                PlaySound (TEXT("Tema da Vitória - Ayrton Senna.WAV"), NULL, SND_ASYNC|SND_FILENAME);
                printf("O CAÇADOR CUMPRIU SEU OBJETIVO.\n");
                printf("\tOBRIGADA POR JOGAR ^^\n\n");
                system("pause");
                system("cls");
                exibirMatrizWumpus();

            }

        }

        if(xB==posicaoXJ && yB==posicaoYJ)
        {
            system("cls");
            PlaySound (TEXT("[Sound Effect Source] - Grito do Pateta (Saiu Voando).WAV"), NULL, SND_ASYNC|SND_FILENAME);
            printf("O CAÇADOR MORREU EM UM BURACO.\n");
            system("pause");
            system("cls");
            exibirMatrizWumpus();

        }
        if(xB2==posicaoXJ && yB2==posicaoYJ)
        {
            system("cls");
            PlaySound (TEXT("[Sound Effect Source] - Grito do Pateta (Saiu Voando).WAV"), NULL, SND_ASYNC|SND_FILENAME);
            printf("O CAÇADOR MORREU EM UM BURACO.\n");
            system("pause");
            system("cls");
            exibirMatrizWumpus();
        }
        if(xA==posicaoXJ && yA==posicaoYJ)
        {
            srand((unsigned) time(NULL));
            posicaoXJ = rand() %6;
            posicaoYJ = rand() %6;
            printf("O CAÇADOR ENTROU UMA CAVERNA COM MORCEGOS E FOI LEVADO PARA OUTRA CAVERNA.\n");
            system("pause");
        }
        if(xP==posicaoXJ && yP==posicaoYJ)
        {
            system("cls");
            PlaySound (TEXT("Tema da Vitória - Ayrton Senna.WAV"), NULL, SND_ASYNC|SND_FILENAME);
            printf("O CAÇADOR CUMPRIU SEU OBJETIVO.\n");
            printf("\tOBRIGADA POR JOGAR ^^ \n\n");
            system("pause");
            system("cls");

            exibirMatrizWumpus();
        }

    }
}
void gerarPortal()
{
    /*gerando uma posicao aleatoria para o portal*/
    srand((unsigned) time(NULL));
    do
    {
        xP = 1 + (rand() % 4);
        yP = 1 + (rand() % 4);
    }
    while((xP==posicaoXJ&&yP==posicaoYJ) || (xP==xB2||yP==yB2) || (xP==xB||yP==yB) || (xP==xA||yP==yA));
    // printf("(%d,%d)",xP,yP);
    matrizWumpus [xP][yP] = 'Q';
    PlaySound (TEXT("Portal 2 in Real life.WAV"), NULL, SND_ASYNC|SND_FILENAME);

    /*gerando magia do portal*/

    if(!((xP==posicaoXJ||(yP+1)==posicaoYJ)&&(xP==xB2||(yP+1)==yB2)&&(xP==xB||(yP+1)==yB)&&(xP==xA||(yP+1)==yA)))
        matrizWumpus[xP][yP + 1] = '~';

    if(!((xP==posicaoXJ||(yP-1)==posicaoYJ)&&(xP==xB2||(yP-1)==yB2)&&(xP==xB||(yP-1)==yB)&&(xP==xA||(yP-1)==yA)))
        matrizWumpus[xP][yP -1] = '~';

    if(!(((xP+1)==posicaoXJ||yP==posicaoYJ)&&((xP+1)==yB2||yP==yB2)&&((xP+1)==xB||yP==yB)&&((xP+1)==xA||yP==yA)))
        matrizWumpus[xP + 1][yP] = '~';

    if(!(((xP+1)==posicaoXJ||yP==posicaoYJ)&&((xP+1)==xB2||yP==yB2)&&((xP+1)==xB||yP==yB)&&((xP+1)==xA||yP==yA)))
        matrizWumpus[xP - 1][yP] = '~';
}
void atirarFlecha(char direcao)
{
    switch(direcao)
    {
    case 'w':
        quantFlechas --;
        if(matrizWumpus[posicaoXJ][posicaoYJ-1]=='W')
        {

            printf("O CAÇADOR MATOU O WUMPUS!!!\nENCONTRE O PORTAL PARA COMPLETAR O OBJETIVO.\n\n");
            matrizWumpus[xW][yW]=' ';
            xW = -1;
            yW = -1;
            system("pause");
            gerarPortal();
        }

        else
        {
            printf("O CAÇADOR NÃO ACERTOU O WUMPUS.");
            system("pause");
        }

        break;

    case 'a':
        quantFlechas --;
        if(matrizWumpus[posicaoXJ-1][posicaoYJ]=='W')
        {
            printf("O CAÇADOR MATOU O WUMPUS!!!\nENCONTRE O PORTAL PARA COMPLETAR O OBJETIVO.\n\n");
            matrizWumpus[xW][yW]=' ';
            xW = -1;
            yW = -1;
            system("pause");
            gerarPortal();
        }

        else
        {
            printf("O CAÇADOR NÃO ACERTOU O WUMPUS.");
            system("pause");
        }

        break;

    case 'd':
        quantFlechas --;
        if(matrizWumpus[posicaoXJ+1][posicaoYJ]=='W')
        {
            printf("O CAÇADOR MATOU O WUMPUS!!!\nENCONTRE O PORTAL PARA COMPLETAR O OBJETIVO.\n\n");
            matrizWumpus[xW][yW]=' ';
            xW = -1;
            yW = -1;
            system("pause");
            gerarPortal();
        }
        else
        {
            printf("O CAÇADOR NÃO ACERTOU O WUMPUS.");
            system("pause");
        }

        break;

    case 's':
        quantFlechas --;
        if(matrizWumpus[posicaoXJ][posicaoYJ+1]=='W')
        {
            printf("O CAÇADOR MATOU O WUMPUS!!!\nENCONTRE O PORTAL PARA COMPLETAR O OBJETIVO.\n\n");
            matrizWumpus[xW][yW]=' ';
            xW = -1;
            yW = -1;
            system("pause");
            gerarPortal();
        }
        else
        {
            printf("O CAÇADOR NÃO ACERTOU O WUMPUS.");
            system("pause");
        }
        break;
    }
}
void regraDoJogo()
{
    system("cls");
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 3);
    system("MODE con cols=80 lines=40");
    musicaRegraDeJ();

    printf("\t\t #################\n");
    printf("\t\t # REGRA DO JOGO #\n");
    printf("\t\t #################\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    printf("=> O JOGO FUNCIONA COMO UM JOGO DA MEMÓRIA.\n=> O JOGADOR DEVERÁ TOMAR CUIDADO E LEMBRAR BEM A POSIÇÃO DAS ARMADILHAS NA MATRIZ.\n=> DEVE TOMAR CUIDADO COM O WUMPUS, POIS O MESMO GOSTA DE BRINCAR DE ESCONDER.\n");
    printf("=> O CAÇADOR TEM O OBJETIVO DE MATAR O WUMPUS E DEPOIS ENTRAR NO PORTAL.\n");
    printf("=> CAÇADOR TERÁ 4 FLECHAS PARA FINALIZAR O WUMPUS, CASO SUAS FLECHAS ACABEM O JOGADOR AINDA TERÁ UMA SEGUNDA OPÇÃO.\n");
    printf("=> O PORTAL COM A MAGIA SÓ APARECERÁ NO MAPA DEPOIS QUE O CAÇADOR FINALIZAR O WUMPUS.\n");
    printf("=> IRÁ APARECER UMA MENSAGEM PARA O JOGADOR QUANDO O CAÇADOR ESTIVER SENTINDO A MAGIA DE UM PORTAL POR PERTO.\n");
    printf("=> O CAÇADOR DEVERÁ TOMAR CUIDADO COM AS ARMADILHAS DAS CAVERNAS.\n");
    printf("=> NO MAPA TERÁ DOIS BURACOS QUE CASO O CAÇADOR ENTRE O MESMO MORRERÁ, CASO ENCONTRE UMA CAVERNA COM MORCEGO, O CAÇADOR SERÁ LEVADO PARA UMA CAVERNA ALEATÓRIA, NO MAPA SÓ TERÁ UMA ARMADILHA COM MORCEGO.\n");
    printf("=> CASO CAÇADOR ENTRE NA MESMA CAVERNA DO WUMPUS O MESMO MORRERÁ.\t");
    printf("=> O CAÇADOR SÓ PODERÁ ACERTAR O WUMPUS A UMA CAVERNA DE DISTÂNCIA.\n");
    printf("=> SEMPRE IRÁ APARECER UMA MENSAGEM PARA O JOGADOR QUANDO O PERIGO ESTIVER PRÓXIMO.\n\n");
    printf("=> BASTA CLICAR NA TECLA (f) PARA ESCOLHER EM QUAL DIREÇÃO ATIRAR.\n\n");
    system("pause");
    system("cls");
    SetConsoleTextAttribute(h, 3);
    printf("\t\t ########################\n");
    printf("\t\t # MOVIMENTO DO CAÇADOR #\n");
    printf("\t\t ########################\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    printf("\t=> NO MAPA O JOGADOR TERÁ QUATRO MANEIRAS DE MOVIMENTAR O CAÇADOR E UMA TECLA PARA ATIRAR A FLECHA.\n\n");
    puts("\t ==>  CIMA (w) BAIXO (s)");
    puts("\t ==> DIREITA (d) ESQUERDA (a)");
    puts("\t==> TECLA PARA ATIVAR A FLECHA (f)\n\n");
    system("pause");
    system("cls");
    SetConsoleTextAttribute(h, 3);
    printf("\t\t #######################\n");
    printf("\t\t #SÍMBOLO DAS VARIÁVEIS#\n");
    printf("\t\t #######################\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    puts("\t==> CAÇADOR (J)");
    puts("\t==> BURACO (O)");
    puts("\t==> WUMPUS (W)");
    puts("\t==> MORCEGO (A)");
    puts("\t==> MAGIA DO PORTAL (~)");
    puts("\t==>  PORTAL (Q) \n\n");
    system("pause");
    system("cls");
    SetConsoleTextAttribute(h, 3);
    printf("\t\t #######\n");
    printf("\t\t #TURNO#\n");
    printf("\t\t #######\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    puts("==> O JOGADOR TERÁ UM TURNO DE 25 SEGUNDOS PARA ATIRAR A FLECHA.\n==> SE O JOGADOR SE MOVER OU O TEMPO ACABAR PASSA PARA O TURNO DO WUMPUS.\n==> DEPOIS QUE O WUMPUS SE MOVER O TURNO DO JOGADOR COMEÇA NOVAMENTE.");
    printf("==> O TEMPO DO TURNO PARA DE CONTAR QUANDO O WUMPUS MORRE.");
    printf("\n\n\n");
    system("pause");
    system("cls");
    SetConsoleTextAttribute(h, 3);
    printf("\t\t ###################\n");
    printf("\t\t #WUMPUS SE ESCONDE#\n");
    printf("\t\t ###################\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    puts("\t==> ATENÇÃO POIS O WUMPUS SE ESCONDE EM ALGUMAS ARMADILHAS E QUANDO ESTIVER ESCONDIDO A FLECHA NÃO FUNCIONARÁ.");
    printf("\n\n\n");
    SetConsoleTextAttribute(h, 9);
    printf("\t>-------->\n");
    printf("\t [FLECHA]\n");
    printf("\t \n\n\n\n");
    SetConsoleTextAttribute(h, 12);
    puts("\t==> O TEMPO IRÁ PARAR SEMPRE QUE O JOGADOR APERTAR A TECHA(f)PARA ATIRAR\nE IRÁ VOLTAR QUANDO O JOGADOR ATIRAR A FLECHA OU CANCELAR.");
    puts("\t==> PARA CANCELAR A FLECHA BASTA APERTAR A TECLA ENTER.  \n\n");
    system("pause");
    system("cls");

    SetConsoleTextAttribute(h, 3);
    printf("\t\t ###############\n");
    printf("\t\t #SEGUNDA OPÇÃO#\n");
    printf("\t\t ###############\n\n\n\n");
    SetConsoleTextAttribute(h, 12);
    printf("=> CASO O CAÇADOR FIQUE COM ZERO DE FLECHAS UM PORTAL IRÁ APARECER NA MATRIZ.\n");
    printf("=> SE O JOGADOR TENTAR USAR A FLECHA MESMO A QUANTIDADE SENDO ZERO, O JOGO IRÁ ACABAR.\n");
    printf("=> ESSE PORTAL NÃO TERÁ MAGIA ENTÃO NÃO PODERÁ SER IDENTIFICADO FACILMENTE.");
    printf("\n\n\n");
    system("pause");
    system("cls");

    SetConsoleTextAttribute(h, 12);
    printf("\t\t\t\t#########\n");
    printf("\t\t\t\t#ATENÇÃO#\n");
    printf("\t\t\t\t#########\n\n\n\n");
    SetConsoleTextAttribute(h, 11);
    printf("\t==> VERIFIQUE SE SEU TECLADO ESTÁ COM O CAPS LOCK DESATIVADO, CASO CONTRARIO O AS TECLAS NÃO IRAM FUNCIONAR.\n\n");
    system("pause");
    system("cls");

    system("MODE con cols=60 lines=40");

    system("MODE con cols=60 lines=40");
    main();
}
void sextoSentido()
{
    if (posicaoXJ==0 && posicaoYJ==0)
    {
        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }

    }
    else if (posicaoXJ==0 && posicaoYJ==5)
    {
        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }
    }
    else if (posicaoXJ==5 && posicaoYJ==0)
    {
        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }
    }
    else if (posicaoXJ==5 && posicaoYJ==5)
    {
        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }
        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }
    }
    else if (posicaoXJ==0 && (posicaoYJ==1||posicaoYJ ==2||posicaoYJ==3||posicaoYJ==4))
    {
        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }
        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }
        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }

    }
    else if (posicaoXJ==5 && (posicaoYJ==1||posicaoYJ ==2||posicaoYJ==3||posicaoYJ==4))
    {
        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }
        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }
        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }

    }
    else if (posicaoYJ==0 &&(posicaoXJ==1||posicaoXJ ==2||posicaoXJ==3||posicaoXJ==4))
    {
        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }
        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }

    }
    else if (posicaoYJ==5 &&(posicaoXJ==1||posicaoXJ ==2||posicaoXJ==3||posicaoXJ==4))
    {
        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }

        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }

    }
    else
    {

        if (matrizWumpus[posicaoXJ+1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua direita\n\n\n");
        }

        if(matrizWumpus[posicaoXJ-1][posicaoYJ] != ' ')
        {
            printf("tem algo a sua esquerda\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ -1] != ' ')
        {
            printf("tem algo em cima\n\n\n");
        }

        if (matrizWumpus[posicaoXJ][posicaoYJ +1] != ' ')
        {
            printf("tem algo em baixo\n\n\n");
        }

    }

    //
    if(matrizWumpus[posicaoXJ][posicaoYJ +1]== '~')
    {
        printf("O CAÇADOR ESTÁ SENTINDO O PORTAL A BAIXO.\n\n");
    }

    if(matrizWumpus[posicaoXJ][posicaoYJ -1]== '~')
    {
        printf("O CAÇADOR ESTÁ SENTINDO O PORTAL A CIMA.\n\n");
    }
    if(matrizWumpus[posicaoXJ+1][posicaoYJ]== '~')
    {
        printf("O CAÇADOR ESTÁ SENTINDO O PORTAL A DIREITA.\n\n");
    }
    if(matrizWumpus[posicaoXJ-1][posicaoYJ]== '~')
    {
        printf("O CAÇADOR ESTÁ SENTINDO O PORTAL A ESQUERDA.\n\n");
    }


    if(matrizWumpus[xW][yW]== 'A')
    {
        printf("O WUMPUS SE ESCONDEU COM MORCEGOS.\n\n");                                         // quando a posicao do x y do wumpus for igual  A O Q o a mensagem irá alerta o jogador que o wumpus se escondeu
    }
    if(matrizWumpus[xW][yW]== 'O')
    {
        printf("O WUMPUS SE ESCONDEU.\n\n");
    }
    if(matrizWumpus[xW][yW]== 'Q')
    {
        printf("O WUMPUS SE ESCONDEU NO PORTAL.\n\n");
    }







    /*/ som do wumpus

    if(matrizWumpus[posicaoXJ][posicaoYJ +1]== 'W')
    {
        printf("O CAÇADOR ESTÁ OUVINDO O WUMPUS.\n\n");
    }

    if(matrizWumpus[posicaoXJ][posicaoYJ -1]== 'W')
    {
        printf("O CAÇADOR ESTÁ OUVINDO O WUMPUS.\n\n");
    }
    if(matrizWumpus[posicaoXJ+1][posicaoYJ]== 'W')
    {
        printf("O CAÇADOR ESTÁ OUVINDO O WUMPUS.\n\n");
    }
    if(matrizWumpus[posicaoXJ-1][posicaoYJ]== 'W')
    {
        printf("O CAÇADOR ESTÁ OUVINDO O WUMPUS.\n\n");
    }
    /*/

    if( matrizWumpus[xW][yW]>0 )
    {
        if( tempoMov <=10)
        {
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);                 // quando tempo chegar a 10 segundo o mesmo ficara vermelho e começa a fazer beep
            SetConsoleTextAttribute(h, 12);
            Beep(1200,100);

        }

    }
}
void colocarVariaveis()
{

    /*gerando uma posicao aleatoria para o wumpus*/
    do
    {
        srand((unsigned) time(NULL));
        xW = 1+ (rand() % 5);
        yW = 1+ (rand() % 5);
    }
    while(xW==posicaoXJ && yW==posicaoYJ);
    // printf("(%d,%d)",xW,yW);
    matrizWumpus [xW][yW] = 'W';


    /*gerando uma posicao aleatoria para o buraco*/
    srand((unsigned) time(NULL));
    do
    {
        xB = 1+ rand() % 5;
        yB = 1+ rand() % 5;
    }
    while((xB==posicaoXJ&&xB==posicaoYJ) || (xB==xW||yB==yW));
    // printf("(%d,%d)",xB,yB);
    matrizWumpus [xB][yB] = 'O';

    /*gerando uma posicao aleatoria para o morcego*/
    srand((unsigned) time(NULL));
    do
    {
        xA =  rand() % 6;
        yA = rand() % 6;
    }
    while((xA==posicaoXJ&&xA==posicaoYJ) || (xA==xW||yA==yW) || (xA==xB||yA==yB));
    // printf("(%d,%d)",xA,yA);
    matrizWumpus [xA][yA] = 'A';

    /*gerando uma posicao aleatoria para o buraco2*/
    srand((unsigned) time(NULL));
    do
    {
        xB2 = 1+ rand() % 5;
        yB2 = 1+ rand() % 5;
    }
    while((xB2==posicaoXJ&&xB2==posicaoYJ) || (xB2==xW||yB2==yW) || (xB2==xB||yB2==yB) || (xB2==xA||yB2==yA));
    // printf("(%d,%d)",xB2,yB2);
    matrizWumpus [xB2][yB2] = 'O';
}
void inicioJogo()
{
    quantFlechas = 4;
    posicaoXJ=0;
    posicaoYJ=0;
    matrizJogador [0][0]='J';
    iniciarMatrizJogador();
    iniciarMatrizWumpus();
    colocarVariaveis();
    musicaMatriz();
    {

        time_t p1 = (time_t) 1;

        time_t t = time(NULL) + p1;                                                               //recebendo tempo do sistema + 1
        do
        {
            if(redesenhar != 0)                                                            //so entra no if quando passa um segundo ou jogador ou wumpus se mover
            {
                if( matrizWumpus[xW][yW]>0)
                {
                    printf("\t\t\tTEMPO=[%d]\n", tempoMov);


                }
                else if( matrizWumpus[xW][yW]== -1)
                {

                    printf("\t\t\tTEMPO=[%d]\n", tempoMov);
                }
                printMatrizJogador();
                sextoSentido();
                redesenhar = 0;
            }
            if(t <= time(NULL))
            {
                tempoMov--;
                redesenhar = 1;
                t = time(NULL) + p1;
            }
            if(tempoMov > 0)
            {
                moverJogador();
            }
            else
            {
                moverWumpus();
            }
            if(redesenhar != 0)
            {
                system("cls");
            }
        }
        while(1);
    }
}

void musicaMatriz()
{
    PlaySound (TEXT("Hunt the Wumpus [ 1975 ] [ BASIC ].WAV"), NULL, SND_ASYNC|SND_LOOP|SND_FILENAME);
}
void musicaRegraDeJ()
{
    PlaySound (TEXT("Barulho de Água na Gruta.WAV"), NULL, SND_ASYNC|SND_LOOP|SND_FILENAME);
}
void moverWumpus()
{
    int x, i, j;
    redesenhar = 1;
    srand((unsigned) time(NULL));
    x = rand() % 4 + 1;
    switch(x)
    {
    case 1:

        if(xW < 0)
        {
            break;
        }
        else if(xW<5)
        {
            for(i=0; i<6; i++)
            {
                for(j=0; j<6; j++)
                {
                    matrizWumpus[j][i] = ' ';
                }
            }
            xW=xW+1;
            yW=yW;

            //printf("(%d,%d)",xW,yW);
            matrizWumpus[xW][yW] = 'W';
            matrizWumpus[xA][yA] = 'A';
            matrizWumpus[xB][yB] = 'O';
            matrizWumpus [xB2][yB2] = 'O';
            if(quantFlechas == 0)
            {
                matrizWumpus [xP2][yP2] = 'Q';
            }
        }
        wumpusMatouJ();
        break;
    case 2:

        if(xW < 0)
        {
            break;
        }
        else if(xW>0)
        {
            for(i=0; i<6; i++)
            {
                for(j=0; j<6; j++)
                {
                    matrizWumpus[j][i] = ' ';
                }
            }
            xW=xW-1;
            yW=yW;

            //printf("(%d,%d)",xW,yW);
            matrizWumpus[xW][yW] = 'W';
            matrizWumpus[xA][yA] = 'A';
            matrizWumpus[xB][yB] = 'O';
            matrizWumpus[xB2][yB2] = 'O';
            if(quantFlechas == 0)
            {
                matrizWumpus [xP2][yP2] = 'Q';
            }
        }

        wumpusMatouJ();

        break;
    case 3:

        if(yW < 0)
        {
            break;
        }

        else if(yW<5)
        {
            for(i=0; i<6; i++)
            {
                for(j=0; j<6; j++)
                {
                    matrizWumpus[j][i] = ' ';
                }
            }
            xW=xW;
            yW=yW+1;


            //printf("(%d,%d)",xW,yW);
            matrizWumpus[xW][yW] = 'W';
            matrizWumpus[xA][yA] = 'A';
            matrizWumpus[xB][yB] = 'O';
            matrizWumpus[xB2][yB2] = 'O';

            if(quantFlechas == 0)
            {
                matrizWumpus [xP2][yP2] = 'Q';
            }
        }
        wumpusMatouJ();
        break;
    case 4:

        if(yW < 0) // para não limpar a matriz para o portal não sumir e evitar ele n ser redesenhado
        {
            break;
        }

        if(yW>0)
        {
            for(i=0; i<6; i++)
            {
                for(j=0; j<6; j++)
                {
                    matrizWumpus[j][i] = ' ';
                }
            }

            xW=xW;
            yW=yW-1;

            //printf("(%d,%d)",xW,yW);
            matrizWumpus[xW][yW] = 'W';
            matrizWumpus[xA][yA] = 'A';
            matrizWumpus[xB][yB] = 'O';
            matrizWumpus[xB2][yB2] = 'O';
            if(quantFlechas == 0)
            {
                matrizWumpus [xP2][yP2] = 'Q';
            }
        }
        wumpusMatouJ();
        break;
    }
    tempoMov = 25;
}
void gerarPortalSemMagia()
{
    if( matrizWumpus[xW][yW]== - 1)
    {

        xP2= - 1;                                                          // o p2 so irá aparecer quando o jogador nao tiver mais flechas
        yP2= - 1;                                                          // para evitar os dois aparecerem no mesmo tempo o p2 irá para fora da matriz se o wumpus tbam for

    }
    srand((unsigned) time(NULL));
    do
    {
        xP2 = 1 + (rand() % 4);
        yP2 = 1 + (rand() % 4);
    }
    while((xP2==posicaoXJ&&yP2==posicaoYJ) || (xP2==xB2||yP2==yB2) || (xP2==xB||yP2==yB) || (xP2==xA||yP2==yA));
    PlaySound (TEXT("Portal 2 in Real life.WAV"), NULL, SND_ASYNC|SND_FILENAME);

}
void jogadoFoiDeBase()
{

    if(xW==posicaoXJ && yW==posicaoYJ)
    {

        system("cls");
        PlaySound (TEXT("AAAAAAAAAAAAAAAAAAAAAAAAA (Marmota Gritando).WAV"), NULL, SND_ASYNC|SND_FILENAME);
        printf("O CAÇADOR FOI CANTAR COM JESUIZ!!!\n\n");
        printf("caçador foi lanchado pelo wumpus.\n\n\n");
        system("pause");
        system("cls");
        exibirMatrizWumpus();
    }
}
void wumpusMatouJ()
{
    if(posicaoXJ==xW && posicaoYJ==yW)
    {

        system("cls");
        PlaySound (TEXT("AAAAAAAAAAAAAAAAAAAAAAAAA (Marmota Gritando).WAV"), NULL, SND_ASYNC|SND_FILENAME);
        printf("O CAÇADOR FOI CANTAR COM JESUIZ!!!\n\n");
        printf("caçador foi lanchado pelo wumpus.\n\n\n");
        system("pause");
        system("cls");
        exibirMatrizWumpus();

    }
}
void exibirMatrizWumpus()
{

    printf("\n\n\n");
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][0], matrizWumpus[1][0], matrizWumpus[2][0], matrizWumpus[3][0], matrizWumpus[4][0], matrizWumpus[5][0]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][1], matrizWumpus[1][1], matrizWumpus[2][1], matrizWumpus[3][1], matrizWumpus[4][1], matrizWumpus[5][1]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][2], matrizWumpus[1][2], matrizWumpus[2][2], matrizWumpus[3][2], matrizWumpus[4][2], matrizWumpus[5][2]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][3], matrizWumpus[1][3], matrizWumpus[2][3], matrizWumpus[3][3], matrizWumpus[4][3], matrizWumpus[5][3]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][4], matrizWumpus[1][4], matrizWumpus[2][4], matrizWumpus[3][4], matrizWumpus[4][4], matrizWumpus[5][4]);
    printf("\t\t -------------------------\n");
    printf("\t\t | %c | %c | %c | %c | %c | %c | \n", matrizWumpus[0][5], matrizWumpus[1][5], matrizWumpus[2][5], matrizWumpus[3][5], matrizWumpus[4][5], matrizWumpus[5][5]);
    printf("\t\t -------------------------\n");
    system("pause");
    main();

}
