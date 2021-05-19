#include "Lista.h"
#include "Menu.h"
#include "leitorDeArquivos.h"
#include "NodeSeq.h"
#include "MenuSeq.h"
#include "LeitorSeq.h"

void quicksort (NodeSeq myVector[], int inicial, int listLength, int *c, int *m)
{
    int i, j, pivo, auxRG;
    string auxName;
    i = inicial;
    j = listLength-1;
    pivo = myVector[(inicial + listLength) / 2].rg;
    *m += 8;
    while(i <= j)
    {
        while(myVector[i].rg < pivo && i < listLength)
        {
            i++;
            *c += 1;
        }
        while(myVector[j].rg > pivo && j > inicial)
        {
            j--;
            *c += 1;
        }
        if(i <= j)
        {
            auxRG = myVector[i].rg;
            auxName = myVector[i].name;
            myVector[i].rg = myVector[j].rg;
            myVector[i].name = myVector[j].name;
            myVector[j].rg = auxRG;
            myVector[j].name = auxName;
            i++;
            j--;
            *c += 1;
            *m += 3;
        }
        *c += 1;
    }
    if(j > inicial)
        quicksort(myVector, inicial, j+1, c, m);
    if(i < listLength)
        quicksort(myVector, i, listLength, c, m);
}

int main()
{
    int listType;
    cout << "Escolha o tipo de lista:" << endl
         << "1. Sequencial" << endl
         << "2. Encadeada" << endl
         << "Digite sua escolha: ";
    cin >> listType;

    if(listType == 1)
    {
        MenuSeq myMenu;
        ReaderSeq myReader;
        clock_t clockStarted, clockFinished;
        int listLength, userOption;
        double executionTime;
        int comparisons = 0, moves = 0;
        string fileName;

        cout << (listLength = myReader.lineCounter(fileName = myMenu.whichFile(userOption = myMenu.showFirstMenu())))
        << " linhas nesse arquivo" << endl;

        clockStarted = clock();
        NodeSeq *myVector = (NodeSeq*) malloc (listLength * sizeof(NodeSeq));
        myReader.geradorSeq(fileName, myVector);
        clockFinished = clock();
        executionTime = (clockFinished - clockStarted) / (double)CLOCKS_PER_SEC;
        cout << endl << "Tempo gerando lista: " << executionTime << "(seg)" << endl << endl;

        if(myVector == NULL)
        {
            cout << "Erro de alocação de memoria" << endl;
            system("pause");
            exit(1);
        }

        cout << endl;

            while(userOption != 99)
        {
            myMenu.showSecondMenu();
            userOption = myMenu.getUserOption();
            switch (userOption){

            case 1:{
                string newName = myMenu.getNewName();
                int newRg = myMenu.getNewRg();
                clockStarted = clock();
                listLength += 1;

                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));
                myVector[listLength-1].name = newName;
                myVector[listLength-1].rg = newRg;

                cout << endl << "Pos: "<< listLength << " Nome: "<< myVector[listLength-1].name
                << " Rg: " << myVector[listLength-1].rg << endl;

                moves += 1;

                break;
            }
            case 2:{
                string newName = myMenu.getNewName();
                int i, newRg = myMenu.getNewRg();
                clockStarted = clock();
                listLength += 1;

                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));
                for(int i = listLength-1; i > 0; i--)
                {
                    myVector[i] = myVector[i-1];
                    moves += 1;
                    comparisons += 1;
                }


                myVector[0].name = newName;
                myVector[0].rg = newRg;

                cout << endl << "Pos: 1"<< " Nome: "<< myVector[0].name
                << " Rg: " << myVector[0].rg << endl;

                break;
            }
            case 3:{
                string newName = myMenu.getNewName();
                int newRg = myMenu.getNewRg();
                int posK = myMenu.getPosition();
                clockStarted = clock();
                listLength += 1;
                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));

                for(int i = listLength-1; i > posK-1; i--)
                {
                    myVector[i] = myVector[i-1];
                    comparisons += 1;
                    moves += 1;
                }

                myVector[posK-1].name = newName;
                myVector[posK-1].rg = newRg;

                cout <<"Pos: " << posK << " Nome: " << myVector[posK-1].name
                << " Rg: " << myVector[posK-1].rg << endl;

                break;
            }
            case 4:{
                cout << "Removendo pos 1: " << myVector[0].name << " " << myVector[listLength-1].rg << endl;
                clockStarted = clock();
                listLength -= 1;

                for(int i = 0; i < listLength; i++)
                {
                    myVector[i] = myVector[i+1];
                    comparisons += 1;
                    moves += 1;
                }

                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));

                cout << endl << "Pos 1 Atual:"<< " Nome: "<< myVector[0].name
                << " Rg: " << myVector[0].rg << " Tam Lista: "<< listLength << endl;

                break;
            }
            case 5:{
                int posK = myMenu.getPosition();
                clockStarted = clock();
                listLength -= 1;

                cout <<"Removendo pos " << posK << " Nome: " << myVector[posK-1].name
                << " Rg: " << myVector[posK-1].rg << endl;

                for(int i = posK-1; i < listLength; i++)
                {
                    myVector[i] = myVector[i+1];
                    comparisons += 1;
                    moves += 1;
                }

                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));

                cout <<"Pos " << posK << " atual >> Nome: " << myVector[posK-1].name
                << " Rg: " << myVector[posK-1].rg << endl;

                break;
            }
            case 6:{
                clockStarted = clock();
                listLength -= 1;

                cout <<"Removendo pos " << listLength+1 << ">> Nome: " << myVector[listLength].name
                << " Rg: " << myVector[listLength].rg << endl;

                myVector = (NodeSeq*) realloc (myVector, listLength * sizeof(NodeSeq));
                moves += 1;

                cout <<"Pos " << listLength << " atual >> Nome: " << myVector[listLength-1].name
                << " Rg: " << myVector[listLength-1].rg << endl;

                break;
            }
            case 7:{
                int i, aux = 0, searchRg = myMenu.getNewRg();
                clockStarted = clock();

                i = myVector[aux].rg;

                while(i != searchRg)
                {
                    aux++;
                    i = myVector[aux].rg;
                    comparisons += 1;
                }

                cout << "Pos: " << aux+1 << " Nome: " << myVector[aux].name << " Rg: " << myVector[aux].rg << endl;

                break;

            }
            case 8:{
                clockStarted = clock();
                int inf =0, sup = listLength - 1, searchRg = myMenu.getNewRg(), flag = 0, meio;

                while (inf <= sup)
                {
                    meio = (inf + sup)/2;
                    moves += 1;
                    if (searchRg == myVector[meio].rg)
                    {
                        cout << "Pos: " << meio+1 << " Nome: " << myVector[meio].name << " Rg: " << myVector[meio].rg << endl;
                        flag = 1;
                        break;
                    }
                    if (searchRg < myVector[meio].rg){
                        sup = meio-1;
                        moves += 1;
                    }

                    else{
                        inf = meio+1;
                        moves += 1;
                    }


                    comparisons += 4;
                }

                if(flag == 0)
                    cout << "Nao encontrado" << endl;
                break;
            }
            case 9:{
                for (int i = 0; i < listLength; i++) {
                    int indiceMenor = i;
                    for (int indiceSeguinte = i+1; indiceSeguinte < listLength; indiceSeguinte++) {
                        comparisons += 1;
                        if (myVector[indiceSeguinte].rg < myVector[indiceMenor].rg) {
                            indiceMenor = indiceSeguinte;
                        }
                    }
                    int auxRg = myVector[i].rg;
                    string auxName = myVector[i].name;
                    myVector[i].rg = myVector[indiceMenor].rg;
                    myVector[i].name = myVector[indiceMenor].name;
                    myVector[indiceMenor].rg = auxRg;
                    myVector[indiceMenor].name = auxName;
                    moves += 3;
                    //cout << ".";
                }
                cout << "Reordenado via selection-sort com sucesso!" << endl;
                break;
            }
            case 10:{
                for (int i = 1; i < listLength; i++) {
                    int escolhido = myVector[i].rg;
                    string escolhidoName = myVector[i].name;
                    int j = i - 1;

                    while ((j >= 0) && (myVector[j].rg > escolhido)) {
                        myVector[j + 1].rg = myVector[j].rg;
                        myVector[j + 1].name = myVector[j].name;
                        j--;
                    }

                    myVector[j + 1].rg = escolhido;
                    myVector[j + 1].name = escolhidoName;
                }
                cout << "Reordenado via insertion-sort com sucesso!" << endl;
                break;
            }
            case 11:{

                break;
            }
            case 12:{
                clockStarted = clock();
                int h = 1, rep = 0, i, j;

                while (h < listLength) {
                   h = h*3+1;
                   comparisons += 1;
                   moves += 1;
                }

                while (h > 1) {
                    h /= 3;
                    comparisons += 1;

                    for (i = h; i < listLength; i++) {
                        int auxRG = myVector[i].rg;
                        string auxName = myVector[i].name;
                        j = i;
                        moves += 2;

                        while (j >= h && auxRG < myVector[j-h].rg) {
                            myVector[j].rg = myVector[j-h].rg;
                            myVector[j].name = myVector[j-h].name;
                            j -= h;
                            rep++;
                            comparisons += 1;
                            moves += 2;
                        }

                        myVector[j].rg = auxRG;
                        myVector[j].name = auxName;
                        comparisons += 1;
                        moves += 1;

                    }
                }
                break;
            }
            case 13:{
                clockStarted = clock();
                quicksort(myVector,0,listLength, &comparisons, &moves);

                break;
            }
            case 14:{

                break;
            }
            case 15:{
                clockStarted = clock();
                for(int i = 0; i < listLength; i++)
                {
                    cout << i+1 << " " << myVector[i].name << " " << myVector[i].rg << endl;
                    comparisons += 1;
                }

                break;
            }
            case 16:{
                clockStarted = clock();
                ofstream savingFile ("NomeRGSave.txt");

                if (savingFile.is_open())
                {
                    for (int i = 0; i < listLength; i++){
                        savingFile << myVector[i].name << "," << myVector[i].rg << endl;
                        comparisons += 1;
                        moves += 1;
                        }

                    savingFile.close();
                    cout << "Arquivo salvo com sucesso!" << endl;
                }
                else cout << "Unable to open file";
                break;
            }
            case 17:{
                free(myVector);
                exit (0);
            }
            default:{
                cout << endl << "-> Opçao invalida" << endl;
                break;
            }
        }
            clockFinished = clock();
            executionTime = (clockFinished - clockStarted) / (double)CLOCKS_PER_SEC;
            cout << endl << "Tempo de execucao: " << executionTime << "(seg)" << endl
            << "Comparacoes: " << comparisons << "  Atribuicoes: " << moves << endl << endl;
            comparisons = 0;
            moves = 0;

        }

        free(myVector);
    }

    else if(listType == 2)
    {
        Menu myMenu;
        Reader myReader;
        Lista myList;
        clock_t clockStarted, clockFinished;
        int userOption;
        double executionTime;
        int comparisons = 0, moves = 0;

        cout << myReader.lineCounter(myMenu.whichFile(userOption = myMenu.showFirstMenu()))
        << " linhas nesse arquivo" << endl;
        clockStarted = clock();
        myReader.geradorEncadeada(myMenu.whichFile(userOption), &myList);
        clockFinished = clock();
        executionTime = (clockFinished - clockStarted) / (double)CLOCKS_PER_SEC;
        cout << "Tempo gerando lista: " << executionTime << "(seg)" << endl << endl;
        myList.updatePositions();

        while(userOption != 99)
        {
            myMenu.showSecondMenu();
            myMenu.loopingMenu(userOption = myMenu.getUserOption(), &myList,
                               &comparisons, &moves, clockStarted, clockFinished, &executionTime);
            cout << endl << "Tempo de execucao: " << executionTime << "(seg)" << endl
            << "Comparacoes: " << comparisons << "  Atribuicoes: " << moves << endl << endl;
            comparisons = 0;
            moves = 0;
        }
    }

    else
    {
        cout << "Opcao invalida!" << endl;
        main();
    }

    return 0;
};
