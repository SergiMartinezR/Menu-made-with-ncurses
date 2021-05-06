#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h> //Librería ncurses, necesaria para las funciones.
#include <string.h>

//DECLARACIÓN DE FUNCIONES
void funcionWaddch(WINDOW *otraven); //Función que hace uso de la función "waddch".
void funcionMvwprintwYwattronYwrefresh(WINDOW *otraven); //Función que hace uso de las funciones "mvwprintw", "wattron", "wrefresh", entre otras.
void funcionWborderYwmove(WINDOW *otraven); //Función que hace uso de las funciones "wborder", "wmove", entre otras.

//Inicia la función main.
int main(){

	initscr(); //Función que inicializa la pantalla.
	raw(); //Función que deshabilita el line buffer.

	while (1){ //Loop infinito.

		int y_max, x_max; //Declaración de variables enteras que servirán para guardar las medidas de la terminal.
		getmaxyx(stdscr, y_max, x_max); //Función que obtiene las medidas de la terminal y las guarda en las variables antes mencionadas.

		WINDOW * menu = newwin(y_max-1, x_max-1, 0, 0); //Inicialización de una nueva ventana con dimensiones 1 pixel más puequeñas que la terminal.
		box(menu, 0, 0); //Dibuja una caja con bordes definidos al rededor de la venta menu.
		refresh(); //Redibuja la pantalla estandar.
		wrefresh(menu); //Redibuja la ventana menu.

		keypad(menu, true); //Función que activa el keypad de la terminal
		wattron(menu, A_BOLD); //Función que activa el atributo "Negritas" en la ventana menu.
		mvwprintw(menu, 1, 1, "ELIGE UNA OPCION:"); //Imprime un texto en las coordenadas (1, 1) de la ventana menu.
		wattroff(menu, A_BOLD); //Desactiva el atributo "Negritas" en la ventana menu.
		wattron(menu, A_UNDERLINE); //Activa el atributo "Subrayado" en la ventana menu.
		mvwprintw(menu, 1, x_max-41, "Mover arriba/abajo: flecha arriba/abajo"); //Imprime un texto en la esquina sup. der. de la ventana menu.
		mvwprintw(menu, y_max-3, 1, "Selecciona: 'enter'"); //Imprime un texto en la esquina inf. izq. de la ventana menu.
		mvwprintw(menu, y_max-3, x_max-12, "Salir: 's'"); ////Imprime un texto en la esquina inf. der. de la ventana menu.
		wattroff(menu, A_UNDERLINE); //Desactiva el atributo "Subrayado" en la ventana menu.

		char *opciones[] = {"Opcion 1", "Opcion 2", "Opcion 3"}; //Declaración de un arreglo de strings que serviran para crear el menu.
		int opcion, sombrear = 0; //Declaración de dos variables enteras que servirán para la selección y sombreado de la opción respectivamente.

		while(1){ //Loop infinito.

			for(int i = 0; i < 3; i++){ //For que recorre del 0 al 2, el número de elementos en el arreglo de strings.

				if(i == sombrear){ //Condicional que checa si la opción i está seleccionada.

					wattron(menu, A_REVERSE | A_BLINK); //Si es así la sombrea y hace que parpadee.

				}
				mvwprintw(menu, i+3, 1, opciones[i]); //Imprime las opciones a partir de las coordenadas (3, 1) en adelante.
				wattroff(menu, A_REVERSE | A_BLINK); //Desactiva los atributos de sombreado y parpadeo

			}

			opcion = wgetch(menu); //Espera a que el usuario presione una tecla del keypad y guarda el valor en la variable opción.

			switch(opcion){ //Switch case que sombrea la opcion que está seleccionada.

				case KEY_UP: //En caso de que la tecla "Flecha arriba" sea seleccionada.
					sombrear--; //Disminuye la variable "sombrear".
					if(sombrear == -1){ //Condicional que checa si la variable sombrear tiene el valor de -1.

						sombrear = 0; //Si es así regresa la variable a cero.

					} //Esto sirve para que no se pueda sombrear valores que no están dentro del arreglo de strings.
					break;

				case KEY_DOWN: //En caso de que la tecla "Flecha abajo" sea seleccionada.
					sombrear++; //Aumenta en uno la variable "sombrear".
					if(sombrear == 3){ //Condicional que checa si la variable sombrear tiene valor de 3.

						sombrear = 2; //Si es así regresa la variable a 2.

					} //Esto sirve para que no se pueda sombrear valores que no están dentro del arreglo de strings.
					break;

				default: //En otro caso, se rompe el switch.
					break;

			}

			if(opcion == 10){ //Condicional que checa si se presiono la tecla "enter".

				break; //Si es así, rompe el loop infinto.

			} else if (opcion == 115){ //En otro caso checa si se presionó la tecla "s".
				return 0; //Si es así, termina el programa.
			}

		}

		wrefresh(menu); //Redibuja la ventana menu.

		WINDOW * otraven = newwin(y_max-3, x_max-3, 1, 1); //Crea otra ventana llamada "otraven".
		wrefresh(otraven); //Redibuja la venta otraven.

		box(otraven, (int)' ', (int)' '); //Dibuja una caja sin bordes alrededor de la venta otraven.


		switch(sombrear){ //Switch case que sirve para ejecutar el código de la opción seleccionada.

			case 0: //En caso de que se haya elegido la primer opción.
				mvwprintw(otraven, 1, 1, "Tu eleccion fue: %s", opciones[sombrear]); //Imprime el texto en las coordenas (1, 1) de otraven.
				funcionWaddch(otraven); //Ejecuta el código de la función y le pasa como parametro la ventana "otraven".
				break;

			case 1: //En caso de que se haya elegido la segunda opción.
				mvwprintw(otraven, 1, 1, "Tu eleccion fueo: %s", opciones[sombrear]); //Imprime el texto en las coordenas (1, 1) de otraven.
				funcionWborderYwmove(otraven); //Ejecuta el código de la función y le pasa como parametro la ventana "otraven".			
				break;

			case 2: //En caso de que se haya elegido la tercer opción.
				mvwprintw(otraven, 1, 1, "Tu eleccion fue: %s", opciones[sombrear]); //Imprime el texto en las coordenas (1, 1) de otraven.
				funcionMvwprintwYwattronYwrefresh(otraven); //Ejecuta el código de la función y le pasa como parametro la ventana "otraven".
				break;

			default: //En caso de que no se haya elegido ninguna opción.
				mvwprintw(otraven, 1, 1, "Ocurrio un error"); //Imprime un mensaje de error en las coordenadas (1, 1) de otraven.
				break;

		}

		wrefresh(otraven); //Redibuja la ventana otraven.
	}
	getch(); //Redibuja la pantalla principal.
	endwin(); //Termina la pantalla principal.

	return 0; //termina el programa.
}

void funcionWaddch(WINDOW *otraven){ //Función que recibe como parámetro una variable de tipo WINDOW.

	mvwprintw(otraven, 2, 1, "Escribe un caracter para que este se repita con la funcion 'waddch':"); //Imprime el texto en las coordenadas (1, 2) de la ventana otraven.
	int car = mvwgetch(otraven, 2, 70); //Guarda el carácter ingresado por el usuario en la variable "car".
	mvwprintw(otraven, 3, 1,"Caracter repetido: "); //Imprime el texto en las coordenadas (1, 3) de la ventana otraven.
	waddch(otraven, car); //Añade el carácter ingresado por el usuario con la función "waddch".
	mvwprintw(otraven, (otraven->_maxy), (otraven->_maxx)-44, "Presiona cualquier tecla para continuar..."); //Imprime el texto en la esquina inf. der. de la pantalla.
	wgetch(otraven); //Espera a que el usuario ingrese un carácter.

}

void funcionWborderYwmove(WINDOW *otraven){ //Función que recibe como parámetro una variable de tipo WINDOW.

	char b = 'b', o = 'o', x = 'x'; //Declaración de variables de tipo carácter con los valores 'b', 'o' y 'x'.

	wmove(otraven, 4, 4); //Mueve el cursor de la ventana otraven a las coordenadas (4, 4).
	wrefresh(otraven); //Redibuja la ventana otraven.
	wprintw(otraven, "El borde de esta ventana ha sido cambiado con la funcion 'wborder' y el cursor fue desplazado con 'wmove'"); //Imprime el texto en la ventana otraven.
	wborder(otraven, 0, (int)o, (int)b, (int)x, 0, 0, 0, 0); //Modifica el borde de la ventana por los caracteres antes mencionados y las esquinas las deja por default.
	mvwprintw(otraven, (otraven->_maxy)-1, (otraven->_maxx)-44, "Presiona cualquier tecla para continuar..."); //Imprime el texto en la esquina inf. der. de la pantalla.
	wgetch(otraven); //Espera a que el usuario ingrese un carácter.

}

void funcionMvwprintwYwattronYwrefresh(WINDOW *otraven){ //Función que recibe como parámetro una variable del tipo WINDOW.

	wattron(otraven, A_REVERSE); //Activa el atributo "Invertir colores" en la ventana otraven.
	mvwprintw(otraven, 1, 1, "Este texto fue escrito con el atributo 'A_REVERSE' y con la funcion 'mvwprintw'"); //Imprime un texto en las coordenadas (1, 1) de la ventana otraven.
	wattroff(otraven, A_REVERSE); //Desactiva el atributo "Invertir colores" en la ventana otraven.
	mvwprintw(otraven, (otraven->_maxy), (otraven->_maxx)-44, "Presiona cualquier tecla para continuar..."); //Imprime el texto en la esquina inf. der. de la pantalla.
	wgetch(otraven); //Espera a que el usuario ingrese un carácter.

}