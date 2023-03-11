#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

//------------------------------------------------------------------------------------
// Ponto de entrada principal do programa
//------------------------------------------------------------------------------------
typedef struct Canhao{
    Vector2 canhao;
    Texture2D textura;
}Canhao;

typedef struct Espirito{
    int cor;
    Texture2D textura;
    Rectangle posicaoEspirito;
    bool ativo;
}Espirito;

typedef struct Estrela{
    int cor;
    Rectangle posicaoEstrela;
    bool ativado;
    bool atirar;
}Estrela;

//----------------------------------------------------------
//Pilha
//----------------------------------------------------------
typedef struct contador{
    int valor;
    struct contador *proximo;
}Contador;
typedef struct{
    Contador *topo;
    int tam;
}Pilha;
//----------------------------------------------------------
//Pilha
//----------------------------------------------------------
void guardarEstrela(Pilha *p,int i){
    Contador *contador = malloc(sizeof(Contador));
    contador->valor = i;
    contador->proximo = p->topo;
    p->topo = contador;
}

Contador* pegarEstrela(Pilha *p){
    Contador *contador = NULL;
    if(p->topo){
        contador = p->topo;
        p->topo = contador->proximo;
    }
    return contador;
}

int main(void)
{
    // inicialização
    const int screenWidth = 492;
    const int screenHeight = 900;
    int i, j;
    
    Estrela estrela[50];
    
    /*
    Cria um retanglo que permite que o ojeto em cena tenha massa,
    movimentação, colisoes
    retangulo = {posicao x, posicao y, largura , altura};
    */
    Rectangle posicaoEstrela = {225, 600, 47, 50}; 
    
    Espirito espirito[6][6];
    
    Canhao canhao;
    /*
    Cria um vetor 2d que permite que o ojeto em cena tenha massa,
    movimentação, colisoes
    vetor2D = {posicao x, posicao y};
    */
    Vector2 posicaoCanhao = {206, 625};
    //--------------------------------------------------------------------------------------
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Image icone = LoadImage("Sprites/Icone.png");
    SetWindowIcon(icone);
    
    // TODO: Carrega imagens que serao usadas / Inicializa as variaveis
    Image image = LoadImage("Sprites/Fundo.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    
    Image layout = LoadImage("Sprites/Layout_png.png");
    Texture2D texture1 = LoadTextureFromImage(layout);
    UnloadImage(layout);
    
    Image lagarto = LoadImage("Sprites/Largato.png");
    Texture2D texture3 = LoadTextureFromImage(lagarto);
    UnloadImage(lagarto);
    
    Image canhaoImg = LoadImage("Sprites/Canhao.png");
    canhao.textura = LoadTextureFromImage(canhaoImg);
    UnloadImage(canhaoImg);
    
    Image layoutTutorial = LoadImage("Sprites/Layout_Como_Jogar.png");
    Texture2D texturaLayout = LoadTextureFromImage(layoutTutorial);
    UnloadImage(layoutTutorial);
    
    Image inicial = LoadImage("Sprites/Layout_Como_Jogar.png");
    Texture2D texturaInicial = LoadTextureFromImage(inicial);
    UnloadImage(inicial);
    
    Image botao = LoadImage("Sprites/BotaoJogar.png");
    Texture2D texturaBotao = LoadTextureFromImage(botao);
    UnloadImage(botao);
    
    Texture estrelaTextura[50];
    for(i = 0; i < 50; i++){
        estrela[i].cor = GetRandomValue(1,4);
        if(estrela[i].cor == 1){
            Image estrela1 = LoadImage("Sprites/Estrela1.png");
            estrelaTextura[i] = LoadTextureFromImage(estrela1);
            UnloadImage(estrela1); 
        }
        if(estrela[i].cor == 2){
            Image estrela2 = LoadImage("Sprites/Estrela2.png");
            estrelaTextura[i] = LoadTextureFromImage(estrela2);
            UnloadImage(estrela2); 
        }
        if(estrela[i].cor == 3){
            Image estrela3 = LoadImage("Sprites/Estrela3.png");
            estrelaTextura[i] = LoadTextureFromImage(estrela3);
            UnloadImage(estrela3); 
        }
        if(estrela[i].cor == 4){
            Image estrela4 = LoadImage("Sprites/Estrela4.png");
            estrelaTextura[i] = LoadTextureFromImage(estrela4);
            UnloadImage(estrela4); 
        }
    }
    
    for(i=0;i<6;i++){
        for(j =0; j<6; j++){
            espirito[i][j].cor=GetRandomValue(1,4);
            if(espirito[i][j].cor == 1){
                espirito[i][j].ativo = true;
                Image espirito1 = LoadImage("Sprites/Espirito1.png");
                espirito[i][j].textura = LoadTextureFromImage(espirito1);
                UnloadImage(espirito1);
            }
            if(espirito[i][j].cor == 2){
                espirito[i][j].ativo = true;
                Image espirito2 = LoadImage("Sprites/Espirito2.png");
                espirito[i][j].textura = LoadTextureFromImage(espirito2);
                UnloadImage(espirito2);
            }
            if(espirito[i][j].cor == 3){
                espirito[i][j].ativo = true;
                Image espirito3 = LoadImage("Sprites/Espirito3.png");
                espirito[i][j].textura = LoadTextureFromImage(espirito3);
                UnloadImage(espirito3);
            }
           if(espirito[i][j].cor == 4){
                espirito[i][j].ativo = true;
                Image espirito4 = LoadImage("Sprites/Espirito4.png");
                espirito[i][j].textura = LoadTextureFromImage(espirito4);
                UnloadImage(espirito4);
           }
        }
    }
    
    bool colisao = false;
    bool tiro = false;
    bool jogar = false;

    SetTargetFPS(30); // determina o FPS do jogo
    //--------------------------------------------------------------------------------------
    Contador *contador;
    Pilha p;
    p.tam = 0;
    p.topo = NULL;
    int cont;
    int texturaAntiga;
    // Game loop: toda ação do jogo deve ser colocada dentro do loop
    while (!WindowShouldClose())    // Detecta se a tela fechou ou apertou ESC
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Atualizar variáveis ​​/ Implementar lógica de exemplo neste ponto
        
        //Tecla W faz o push da pilha
        if(IsKeyDown(KEY_W)){
            guardarEstrela(&p,cont);
            UnloadTexture(estrelaTextura[cont]);
            cont++;
        }
        //Tecla D move para a direita
        if(IsKeyDown(KEY_D)){
            posicaoEstrela.x += 5;
            posicaoCanhao.x += 5;
        }
        //Tecla A: move para a esquerda
        if(IsKeyDown(KEY_A)){
            posicaoEstrela.x -= 5;
            posicaoCanhao.x -= 5;
        }
        //Tecla SPACE: faz o disparo da estrela
        if(IsKeyDown(KEY_SPACE)){
            tiro = true;
        }
        if(tiro){
            posicaoEstrela.y -=10;
        }
        //Tecla Q: faz o pop da pilha
        if(IsKeyDown(KEY_Q)){
            UnloadTexture(estrelaTextura[cont]);
            cont++;
            contador = pegarEstrela(&p);
            if(contador){
                texturaAntiga = contador->valor;            
            }
            
        }
        //Se a estrela chegar á 50 pixels de altura ela some e aparece outra
        if(posicaoEstrela.y < 50){
            UnloadTexture(estrelaTextura[cont]);
            cont++;
            estrela[cont].ativado = false;
            tiro = false;
            espirito[i][j].ativo = false;
            posicaoEstrela.y = 600;
        }
        //Verifica a colisao entre o espirito e a estrela de acordo com a cor
        for(i = 0; i<6; i++){
            for(j = 0; j<6; j++){
               colisao = CheckCollisionRecs(posicaoEstrela, espirito[i][j].posicaoEspirito); 
                if(colisao){
                    if(estrela[cont].cor == espirito[i][j].cor){
                        UnloadTexture(estrelaTextura[cont]);
                        UnloadTexture(espirito[i][j].textura);
                        espirito[i][j].posicaoEspirito.x = 0;
                        espirito[i][j].posicaoEspirito.y = 0;
                        cont++;
                        estrela[cont].ativado = false;
                        tiro = false;
                        espirito[i][j].ativo = false;
                        posicaoEstrela.y = 600;
                    }
                }      
            }
        }
        
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // TODO: Desenhe tudo o que precisa ser desenhado neste ponto:
            ClearBackground(RAYWHITE);
            //Fundo
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
            //Layout
            DrawTexture(texture1, 50, 50, WHITE);
            //Canhão
            DrawTexture(canhao.textura, posicaoCanhao.x, posicaoCanhao.y, WHITE);
            //Lagarto
            DrawTexture(texture3, 80, 750, WHITE);
            //Estrela
            if(texturaAntiga != NULL){
                DrawTexture(estrelaTextura[texturaAntiga], posicaoEstrela.x, posicaoEstrela.y, WHITE);
                texturaAntiga = NULL;
            }else{
                DrawTexture(estrelaTextura[cont], posicaoEstrela.x, posicaoEstrela.y, WHITE);
            }
            
            //Espirito
            for(i = 0; i < 6; i++){
                for( j = 0; j <6; j++){
                    if(espirito[i][j].ativo){
                        espirito[i][j].posicaoEspirito.x = 80+55*i;
                        espirito[i][j].posicaoEspirito.y = 85+47*j;
                        DrawTexture(espirito[i][j].textura, espirito[i][j].posicaoEspirito.x, espirito[i][j].posicaoEspirito.y,WHITE);
                    }
                }   
            }
            if(jogar == false){
               DrawTexture(texturaLayout, 0,0,WHITE); 
            }
            
            if(IsKeyDown(KEY_P)){
                UnloadTexture(texturaLayout);
                jogar = true;
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    //--------------------------------------------------------------------------------------
    // Desinicialização
    //--------------------------------------------------------------------------------------

    // TODO: descarregar as inforrmaçoes do jogo
    UnloadTexture(texture); 
    UnloadTexture(texture1); 
    UnloadTexture(canhao.textura); 
    UnloadTexture(texture3);
    for(i=0;i<6;i++){
        for(j =0; j<6; j++){ 
            UnloadTexture(espirito[i][i].textura);
        }
    }
    
    UnloadTexture(estrelaTextura[cont]);
    fflush(stdin);

    CloseWindow();        // Fecha a janela e o OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}