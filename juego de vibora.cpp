#include <windows.h>/*incluye gran cantidad de cabeceras, ya que nuchas lineas no pueden inluirse por si mismas por dependencia */
#include <iostream>/*nos permite organizar el codigo en grpos logicos, asi para evitar conflintos en nombres */
#include <stdlib.h>/*nos permte un entero a una cadena de caracteristicas */
#include <conio.h>/*nos incluye funciones especificas para el control de entrada*/
 /*librerias que se usan es c++ para diferentes funciones, cada libreria tiene como fin hacer algo en especifico */


/*FUNCION DEFINE es la asociacion de un identificador que parametiza con una cadena token */
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
/*Estas constantes permiten utilizar nombres más intuitivos en lugar de valores numéricos directos, lo que facilita la comprensión y el mantenimiento del código. */
 
int cuerpo[200][2];/*se están declarando variables y un arreglo para ser utilizados*/
int n = 1, tam = 10, dir = 3;
int x = 10, y = 12;
int xc = 30, yc = 15;
int velocidad = 60;
char tecla;


 /*FUNCION VOID GOTOXY*/
 /*Mueve el cursor de la ventana de texto a la posición según las coordenadas especificadas*/
void gotoxy(int x, int y) 
{ 
    HANDLE hCon; 
    COORD dwPos; 
 
    dwPos.X = x; 
    dwPos.Y = y; 
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hCon,dwPos); /*Obtiene el manejador de la salida estándar (consola) y lo almacena en la variable hCon. Esto permite interactuar con la consola.*/
}
void OcultaCursor() /*configura la información del cursor de la consola para que tenga un tamaño grande y lo oculta, de manera que no sea visible durante la ejecución del programa en la consola. Esto puede mejorar la presentación de la interfaz de usuario y la visualización de la información en la pantalla.*/
 {
    CONSOLE_CURSOR_INFO cci = {100, FALSE};
 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void pintar()/*se encarga de dibujar un marco rectangular en la consola de texto, lo que puede ser útil para mejorar la presentación visual de la interfaz de usuario en una aplicación de consola.*/
{  
     for(int i=2; i < 78; i++){
        gotoxy (i, 3); printf ("%c", 205);
        gotoxy(i, 23); printf ("%c", 205); 
        }
     for(int v=4; v < 23; v++){
        gotoxy (2,v);  printf ("%c", 186);
        gotoxy(77,v);  printf ("%c", 186); 
        }
     gotoxy  (2,3);    printf ("%c", 201);
     gotoxy (2,23);    printf ("%c", 200);
     gotoxy (77,3);    printf ("%c", 187);
     gotoxy(77,23);    printf ("%c", 188); 
     } 

void guardar_posicion()/*se encarga de almacenar la posición actual de un elemento en el juego. A medida que se almacenan nuevas posiciones, se avanza en el índice del arreglo, y cuando se llega al límite, se comienza a sobrescribir las posiciones más antiguas. Esto puede ser útil para llevar un registro de los movimientos pasados en juegos o aplicaciones que requieren un historial de posiciones.*/
{
     cuerpo[n][0] = x;
     cuerpo[n][1] = y;
     n++;
     if(n == tam) n = 1;
}
void dibujar_cuerpo()/*se encarga de dibujar el cuerpo y ademas el bucle for hace incrementar al cuerpo a medida que se va ganando puntos */
{
      for(int i = 1; i < tam; i++){
      gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("+");
     }
}
void borrar_cuerpo()/*se encarga de borrar la posición actual del cuerpo de la. Esto se logra posicionando el cursor en la ubicación actual del cuerpo y reemplazando ese espacio con un espacio en blanco, lo que simula el borrado del contenido en esa ubicación en la pantalla.*/
{
     gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");
    }
void teclear()/*se utiliza para cambiar la dirección de la vibora en función de las teclas presionadas por el usuario. Cuando se presionan las teclas de dirección (ARRIBA, ABAJO, DERECHA o IZQUIERDA), la dirección de la vibora se ajusta según las reglas establecidas, lo que permite qe la viborita  se mueva en la dirección deseada en el juego FULL SNAKE */
{
     if(kbhit()){
            tecla = getch();
            switch(tecla){
                case ARRIBA : if(dir != 2) dir = 1; break;
                case ABAJO : if(dir != 1) dir = 2; break;
                case DERECHA : if(dir != 4) dir = 3; break;
                case IZQUIERDA : if(dir != 3) dir = 4; break;
           }
     }
}
void comida()/*se encarga de gestionar la aparición y el consumo de comida en del juego,lo que esto llega a aumentar el tamaño de la serpiente en el juego . La comida se coloca en una ubicación aleatoria dentro de la pantalla del juego después de ser comida.*/
{
     if(x == xc && y == yc)
     {
          xc = (rand() % 73) + 4;
          yc = (rand() % 19) + 4;
 
          tam++;
          gotoxy(xc, yc); printf("%c", 4);
     }
}
bool game_over()/*verifica si el juego ha llegado a su fin, ya sea debido a una colisión con los bordes de la pantalla o una colisión con el propio cuerpo del elemento.*/
{
     if(y == 3 || y == 23 || x == 2 || x == 77) return false;
     for(int j = tam - 1; j > 0; j--){
             if(cuerpo[j][0] == x &&  cuerpo[j][1] == y)
             return false;
     }
    return true;
}
int main()/*controla el flujo principal del juego FULL SNAKE en la consola, incluyendo la gestión del cursor, el dibujo de elementos en la pantalla, la detección de teclas presionadas y la lógica del juego. El juego continúa hasta que se presiona la tecla "ESC" o se cumple una condición de finalización definida por la función game_over().*/
{
    OcultaCursor();
 
    pintar();
   gotoxy(xc, yc); printf("%c", 4);
 
    while(tecla != ESC && game_over())
    {
         borrar_cuerpo();
         guardar_posicion();
         dibujar_cuerpo();
         comida();
         teclear();
         teclear();
 
         if(dir == 1) y--;
         if(dir == 2) y++;
         if(dir == 3) x++;
         if(dir == 4) x--;
 
         Sleep(velocidad);
         }
    pintar();
    return 0;
}
