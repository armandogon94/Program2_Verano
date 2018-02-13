#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>

struct sucursal {
	char nombre[30];
	sucursal *prox;
};

struct subrubros {
	char nombre[30];
	subrubros *abajo;
};

struct rubros {
	char nombre[30];
	rubros *prox;
	subrubros *abajo;
};

struct lote {
	char codigo[30];
	char sucursal[30];
	char rubro[30];
	char subcategoria[30];
	long int unidades;
	long int existencia;
	float peso;
	long double costo;
	lote *prox;
};

struct cliente {
	char nombre[30];
	cliente *prox;
};

struct subfactura {
	char codigo_lote[30];
	long int unidades;
	long double precio;
	long double venta;
	subfactura *abajo;
};

struct factura {
	char codigo[30];
	char sucursal[30];
	int dia;
	int mes;
	int year;
	char cliente[30];
	long int total;
	factura *prox;
	subfactura *abajo;
};

int buscar_rubro(rubros **r, char palabra[30]) {
	if (*r) {
		rubros *t = *r;
		if (strcmp(t->nombre,palabra)==0) return 1;
		while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
		if (t->prox) return 1;
	}
	return 0;
}

int buscar_subrubro(rubros **r, char rub[30], char subrub[30]) {
	if (*r) {
		rubros *t = *r;
		subrubros *s;
		while (t){
			if (t->abajo && strcmp(t->nombre,rub)==0) {
				s = t->abajo;
				while (s && strcmp(s->nombre,subrub)!=0) s = s->abajo;
				if (s) { return 1; } else return 0;
			}
			t = t->prox;
		}
	}
	return 0;
}

int buscar_cliente(cliente **c, char palabra[30]) {
	if (*c) {
		cliente *t = *c;
		if (strcmp(t->nombre,palabra)==0) return 1;
		while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
		if (t->prox) return 1;
	}
	return 0;
}

int buscar_lote(lote **l, char palabra[30]) {
	if (*l) {
		lote *t = *l;
		if (strcmp(t->codigo,palabra)==0) return 1;
		while (t && t->prox && strcmp(t->prox->codigo,palabra)!=0) t = t->prox;
		if (t->prox) return 1;
	}
	return 0;
}

int buscar_sucursal(sucursal **s, char palabra[30]) {
	if (*s) {
		sucursal *t = *s;
		if (strcmp(t->nombre,palabra)==0) return 1;
		while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
		if (t->prox) return 1;
	}
	return 0;
}

int buscar_factura(factura **f, char palabra[30]) {
	if (*f) {
		factura *t = *f;
		if (strcmp(t->codigo,palabra)==0) return 1;
		while (t && t->prox && strcmp(t->prox->codigo,palabra)!=0) t = t->prox;
		if (t->prox) return 1;
	}
	return 0;
}

long int obtener_existentes_lote(lote **l, char palabra[30]) {
	if (*l) {
		lote *t = *l;
		while (t) {
			if (strcmp(t->codigo,palabra)==0) return (t->existencia);
			t = t->prox;
		}
	}
	return 0;
}

long double obtener_precio_lote(lote **l, char palabra[30]) {
	if (*l) {
		lote *t = *l;
		while (t) {
			if (strcmp(t->codigo, palabra) == 0) return (t->costo);
			t = t->prox;
		}
	}
	return 0;
}

void agregar_rubro(rubros **r, char palabra[30]) {
	rubros *p = new rubros;
	rubros *t = *r;
	strcpy(p->nombre, palabra);
	p->prox = NULL;
	p->abajo = NULL;
	if (*r) {
		while ((t) && (t->prox)) {
			t = t->prox;
		}
		t->prox = p;
	}
	else
		*r = p;
}

void agregar_subrubro(rubros **r, char palabra[30], char palabra2[30]) {
	rubros *t = *r;
	subrubros *s;
	while (t) {
		if (strcmp(t->nombre,palabra)==0) {
			if (t->abajo) {
				s = t->abajo;
				while (s && s->abajo) s = s->abajo;
				subrubros *nuevo = new subrubros;
				strcpy(nuevo->nombre, palabra2);
				nuevo->abajo = NULL;
				s->abajo = nuevo;
			}
			else {
				s = new subrubros;
				strcpy(s->nombre, palabra2);
				s->abajo = NULL;
				t->abajo = s;
			}
		}
		t = t->prox;
	}
}

void agregar_cliente(cliente **c,char palabra[30]) {
	cliente *t = *c,*p = new cliente;
	strcpy(p->nombre, palabra);
	p->prox = NULL;
	if (*c) {
		while ((t) && (t->prox)) t = t->prox;
		t->prox = p;
	}
	else
		*c = p;
}

void agregar_lote(lote **l, char codigo[30], char sucur[30], char rub[30], char subrub[30], long int unidades, long int existencia, float peso, long double costo) {
	lote *t = *l, *aux = new lote;
	strcpy(aux->codigo, codigo);
	strcpy(aux->sucursal, sucur);
	strcpy(aux->rubro, rub);
	strcpy(aux->subcategoria, subrub);
	aux->unidades = unidades;
	aux->existencia = existencia;
	aux->peso = peso;
	aux->costo = costo;
	aux->prox = NULL;
	if (t) {
		while (t && t->prox) t = t->prox;
		t->prox = aux;
	}
	else {
		*l = aux;
	}
}

void agregar_sucursal(sucursal **s, char palabra[30]) {
	sucursal *t = *s, *p = new sucursal;
	strcpy(p->nombre, palabra);
	p->prox = NULL;
	if (*s) {
		while ((t) && (t->prox)) {
			t = t->prox;
		}
		t->prox = p;
	}
	else
		*s = p;

}

void agregar_factura(factura **f,char codigo[30], char sucursal[30], int dia, int mes, int year, char cliente[30], long int total) {
	factura *t = *f, *aux = new factura;
	strcpy(aux->codigo,codigo);
	strcpy(aux->sucursal, sucursal);
	strcpy(aux->cliente, cliente);
	aux->dia = dia;
	aux->mes = mes;
	aux->year = year;
	aux->total = total;
	aux->prox = NULL;
	aux->abajo = NULL;
	if (*f) {
		while (t && t->prox) t = t->prox;
		t->prox = aux;
	}
	else {
		*f = aux;
	}
}

void agregar_subfactura(factura **f, char codigo[30], char codigo_lote[30], long int unidades, long double precio, long double venta) {
	if (*f) {
		factura *t = *f;
		subfactura *s = new subfactura;
		strcpy(s->codigo_lote,codigo_lote);
		s->unidades = unidades;
		s->precio = precio;
		s->venta = venta;
		s->abajo = NULL;
		while (t){
			if (strcmp(t->codigo, codigo) == 0) {
				if (t->abajo) {
					subfactura *aux = t->abajo;
					while (aux && aux->abajo) aux = aux->abajo;
					aux->abajo = s;
				}
				else {
					t->abajo = s;
				}
			}
			t = t->prox;
		}
	}
}

void agregar_rubro_principal(rubros **r) {
	int op = -1, cont;
	char palabra[30];
	char palabra2[30];
	while (op) {
		system("cls");
		printf("\n\tMENU AGREGAR RUBRO\n\n");
		printf("1.\tRubro\n");
		printf("2.\tSubcategoria de Rubro\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1:cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que no exista!\n");
				printf("Ingrese el nombre del rubro: ");
				scanf("%s", &palabra);
				cont++;
			} while (buscar_rubro(r, palabra));
			agregar_rubro(r, palabra);
			printf("Rubro agregado satisfactoriamente!\n");
			system("pause");
			break;
		case 2: cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que exista!\n");
				printf("Ingrese el nombre del rubro: ");
				scanf("%s", &palabra);
				cont++;
			} while (!buscar_rubro(r, palabra));
			printf("Ingrese el nombre de la subcategoria: ");
			scanf("%s", &palabra2);
			agregar_subrubro(r, palabra, palabra2);
			printf("Subcategoria de rubro agregada satisfactoriamente!\n");
			system("pause");
			break;
		}
	}
}

void agregar_factura_principal(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {//TERMINAR DE ACOMODAR COMO DICE EL PROFE
	system("cls");
	printf("\n\tAGREGAR FACTURA\n\n");
	int cont = 0,aux;
	char cliente[30];
	do {
		printf("Ingrese el nombre del cliente: ");
		scanf("%s", &cliente);
		//fflush(stdin);
		if (!(buscar_cliente(c, cliente))) {
			printf("\nEl cliente que ingreso no existe desea agregarlo?\nPresione 1 para si y 0 para no: ");
			//fflush(stdin);
			scanf_s("%d", &aux);
			if (aux) {
				agregar_cliente(c, cliente);
				printf("\nCliente agregado satisfactoriamente!");
				cont = 1;
			}
		}
		else {
			cont = 1;
		}
	} while (!cont);
	printf("\n");
	cont = 0;
	char codigo[30];
	do {
		if (cont) printf("\nError! Ingrese un codigo de factura que no exista!\n");
		printf("Ingrese el codigo de factura: ");
		scanf("%s", &codigo);
		cont++;
	} while (buscar_factura(f, codigo));
	printf("\n");
	cont = 0;
	char sucur[30];
	do {
		if (cont) printf("\nError! Ingrese una sucursal que exista!\n");
		printf("Ingrese la sucursal: ");
		scanf("%s", &sucur);
		cont++;
	} while (!(buscar_sucursal(s, sucur)));
	printf("\n");
	cont = 0;
	int dia;
	do {
		if (cont) printf("\nError! Ingrese un dia que exista!\n");
		printf("Ingrese el dia: ");
		scanf("%i", &dia);
		cont++;
	} while (dia<1||dia>31);
	printf("\n");
	cont = 0;
	int mes;
	do {
		if (cont) printf("\nError! Ingrese un mes entre 1 y 12!\n");
		printf("Ingrese el mes: ");
		scanf("%i", &mes);
		cont++;
	} while (mes<1||mes>12);
	printf("\n");
	cont = 0;
	int year;
	do {
		if (cont) printf("\nError! Ingrese un numero mayor a 0!\n");
		printf("Ingrese el anho: ");
		scanf("%i", &year);
		cont++;
	} while (year <= 0);
	printf("\n");
	agregar_factura(f, codigo, sucur, dia, mes, year, cliente,0);
	printf("\nAhora se procedera a incorporar los lotes a comprar.\n");
	int cont2;
	cont = 0;
	char codigo_lote[30]; 
	long int unidades;
	long double precio, venta;
	do {
		do {
			if (cont) printf("\nError! Ingrese un lote existente!\n");
			printf("Ingrese el codigo de lote a comprar: ");
			scanf("%s",&codigo_lote);
			cont++;
		} while (!(buscar_lote(l,codigo_lote)));
		printf("\n");
		cont = 0;
		do {
			if (cont) printf("\nError! Ingrese un numero entre 0 y %i!\n",obtener_existentes_lote(l,codigo_lote));
			printf("Ingrese la cantidad de unidades a comprar: ");
			scanf("%i", &unidades);
			cont++;
		} while (unidades>0 && (unidades<obtener_existentes_lote(l, codigo_lote)));
		precio = (obtener_precio_lote(l,codigo_lote))*2;
		venta = precio * unidades;
		agregar_subfactura(f,codigo,codigo_lote,unidades,precio,venta);
		printf("\nCompra realizada, desea agregar elementos de otro lote a la factura?\nPresione 1 para si y 0 para no: ");
		scanf("%i",&cont2);
	} while (!cont2);
	printf("Factura agregada satisfactoriamente!");
	//MODIFICAR LOTES
	system("pause");
}

void agregar_cliente_principal(cliente **c) {
	system("cls");
	printf("\n\tAGREGAR CLIENTE\n\n");
	int cont = 0;
	char palabra[30];
	do {
		if (cont) printf("\nError! Ingrese un cliente que no exista!\n");
		printf("Ingrese el nombre del cliente: ");
		scanf("%s", &palabra);
		cont++;
	} while (buscar_cliente(c, palabra));
	agregar_cliente(c, palabra);
	printf("Cliente agregado satisfactoriamente!");
	system("pause");
}

void agregar_lote_principal(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	system("cls");
	printf("\n\tAGREGAR LOTE\n\n");
	int cont = 0;
	char codigo[30];
	do {
		if (cont) printf("\nError! Ingrese un lote que no exista!\n");
		printf("Ingrese el codigo del lote: ");
		scanf("%s", &codigo);
		cont++;
	} while (buscar_lote(l, codigo));
	printf("\n");
	cont = 0;
	char sucur[30];
	do {
		if (cont) printf("\nError! Ingrese una sucursal que exista!\n");
		printf("Ingrese la sucursal: ");
		scanf("%s", &sucur);
		cont++;
	} while (!(buscar_sucursal(s, sucur)));
	printf("\n");
	cont = 0;
	char rub[30];
	do {
		if (cont) printf("\nError! Ingrese un rubro que exista!\n");
		printf("Ingrese el rubro: ");
		scanf("%s", &rub);
		cont++;
	} while (!(buscar_rubro(r, rub)));
	printf("\n");
	cont = 0;
	char subrub[30];
	do {
		if (cont) printf("\nError! Ingrese una subcategoria de rubro que exista en el rubro indicado!\n");
		printf("Ingrese la subcategoria de rubro: ");
		scanf("%s", &subrub);
		cont++;
	} while (!(buscar_subrubro(r, rub, subrub)));
	printf("\n");
	cont = 0;
	long int unidades;
	do {
		if (cont) printf("\nError! Ingrese mas de 0 unidades!\n");
		printf("Ingrese las unidades: ");
		scanf("%i", &unidades);
		cont++;
	} while (unidades<=0);
	printf("\n");
	cont = 0;
	float peso;
	do {
		if (cont) printf("\nError! Ingrese un peso positivo!\n");
		printf("Ingrese el peso en Kg por unidad: ");
		scanf("%f", &peso);
		cont++;
	} while (peso<=0);
	printf("\n");
	cont = 0;
	long double costo;
	do {
		if (cont) printf("\nError! Ingrese un costo positivo!\n");
		printf("Ingrese el costo en BsF por unidad: ");
		scanf("%lf", &costo);
		cont++;
	} while (costo <= 0);
	agregar_lote(l, codigo,sucur,rub,subrub,unidades,unidades,peso,costo);
	printf("Lote agregado satisfactoriamente!");
	system("pause");
}

void agregar_sucursal_principal(sucursal **s) {
	system("cls");
	printf("\n\tAGREGAR SUCURSAL\n\n");
	int cont = 0;
	char palabra[30];
	do {
		if (cont) printf("\nError! Ingrese una sucursal que no exista!\n");
		printf("Ingrese la sucursal: ");
		scanf("%s", &palabra);
		cont++;
	} while (buscar_sucursal(s, palabra));
	agregar_sucursal(s, palabra);
	printf("Sucursal agregado satisfactoriamente!");
	system("pause");
}


void agregar(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU AGREGAR\n\n");
		printf("1.\tRubro\n");
		printf("2.\tFactura\n");
		printf("3.\tCliente\n");
		printf("4.\tLote\n");
		printf("5.\tSucursal\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: agregar_rubro_principal(r);
			break;
		case 2: agregar_factura_principal(r,f,c,l,s);
			break;
		case 3: agregar_cliente_principal(c);
			break;
		case 4: agregar_lote_principal(r,f,c,l,s);
			break;
		case 5: agregar_sucursal_principal(s);
			break;
		}
	}
}


/*
void modificar(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU MODIFICAR\n\n");
		printf("1.\tRubro\n");
		printf("2.\tFactura\n");
		printf("3.\tCliente\n");
		printf("4.\tLote\n");
		printf("5.\tSucursal\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: modificar_rubro(r);
			break;
		case 2: modificar_factura(f);
			break;
		case 3: modificar_cliente(c);
			break;
		case 4: modificar_lote(l);
			break;
		case 5: modificar_sucursal(s);
			break;
		}
	}
}
*/

void mostrar_rubros(rubros **r) {
	printf("\n\t\tRUBROS\tSUBCATEGORIAS\n\n");
	rubros *t = *r;
	subrubros *s;
	while (t) {
		printf("\t%s:\t",t->nombre);
		if (t->abajo) {
			s = t->abajo;
			while (s) {
				if (s->abajo) {
					printf("%s,",s->nombre);
				}
				else {
					printf("%s.",s->nombre);
				}
				s = s->abajo;
			}
		}
		else {
			printf("No hay.");
		}
		printf("\n\n");
		t = t->prox;
	}
	if (!(*r)) printf("\tNo hay Rubros");
	printf("\n");
}

void mostrar_facturas(factura **f) {
	factura *t = *f;
	subfactura *s;
	printf("\n\tFacturas\n");
	printf("-----------------------------------------\n");
	printf("-----------------------------------------\n\n");
	while (t) {
		printf("\tCodigo:%s\n", t->codigo);
		printf("\tSucursal:%s Fecha:%i/%i/%i Cliente:%s Total:%i\n\n", t->sucursal, t->dia, t->mes, t->year, t->cliente, t->total);
		if (t->abajo) {
			printf("\tLote\tUnidades\tPrecio\tVenta\n");
			s = t->abajo;
			while (s) {
				printf("\t%s\t%i\t%.2f\t%.2f\n",s->codigo_lote,s->unidades,s->precio,s->venta);
				s = s->abajo;
			}
		}
		else {
			printf("\tFactura Vacia.\n");
		}
		t = t->prox;
	}
	if (!(*f)) printf("\tNo hay Facturas.");
	printf("\n");
}

void mostrar_clientes(cliente **c) {
	printf("\n\tCLIENTES\n\n");
	cliente *t = *c;
	while (t) {
		printf("\t%s\n\n", t->nombre);
		t = t->prox;
	}
	if (!(*c)) printf("\tNo hay Clientes.");
	printf("\n");
}

void mostrar_lotes(lote **l) {
	printf("\n\tLOTES\n\n");
	lote *t = *l;
	while (t) {
		printf("\tCodigo:%s\n", t->codigo);
		printf("\tSucursal:%s\tRubro:%s\tSubcategoria:%s\n", t->sucursal,t->rubro,t->subcategoria);
		printf("\tUnidades:%i\tExistencia:%i\tPeso:%.2f\tCosto:%.2f\n\n", t->unidades,t->existencia,t->peso,t->costo);
		t = t->prox;
	}
	if (!(*l)) printf("\tNo hay Lotes.");
	printf("\n");
}

void mostrar_sucursales(sucursal **s) {
	printf("\n\tSUCURSALES\n\n");
	sucursal *t = *s;
	while (t) {
		printf("\t%s\n\n", t->nombre);
		t = t->prox;
	}
	if (!(*s)) printf("\tNo hay Sucursales.");
	printf("\n");
}

void mostrar(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU MOSTRAR\n\n");
		printf("1.\tRubro\n");
		printf("2.\tFactura\n");
		printf("3.\tCliente\n");
		printf("4.\tLote\n");
		printf("5.\tSucursal\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: mostrar_rubros(r);
			break;
		case 2: mostrar_facturas(f);
			break;
		case 3: mostrar_clientes(c);
			break;
		case 4: mostrar_lotes(l);
			break;
		case 5: mostrar_sucursales(s);
			break;
		}
		if(op)system("pause");
	}
}

void eliminar_rubro() {

}

void eliminar_rubro_principal(rubros **r) {
	char palabra[30];
	system("cls");
	printf("\n\tELIMINAR RUBRO\n\n");
	mostrar_rubros(r);
	int cont = 0;
	do {
		if (cont) printf("\n\tError! Ingrese un rubro que exista!");
		printf("\n\tIngrese el rubro que desea eliminar de los mostrados anteriormente: ");
		scanf("%s",&palabra);
		cont++;
	} while (!(buscar_rubro(r,palabra)));
	eliminar_rubro(r,palabra);
	printf("\n\tEl rubro y sus subcategorias han sido eliminadas satisfactoriamente!\n");
	system("pause");
}

void eliminar_rubro_menu(rubros **r, factura ** f, lote **l) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU ELIMINAR RUBRO\n\n");
		printf("1.\tRubro\n");
		printf("2.\tSubCategoria\n");
		scanf("%i", &op);

		switch (op) {
		case 1: eliminar_rubro_principal(r,f,l);
			break;
		case 2: eliminar_subrubro_principal(r);
			break;
		}
	}
}

void eliminar(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU ELIMINAR\n\n");
		printf("1.\tRubro\n");
		printf("2.\tCliente\n");
		printf("3.\tLote\n");
		printf("4.\tSucursal\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: eliminar_rubro_menu(r,f,l);
			break;
		case 2: eliminar_cliente_principal(c);
			break;
		case 3: eliminar_lote_principal(l);
			break;
		case 4: eliminar_sucursal_principal(s);
			break;
		}
	}
}

void buscar_cosas_lote(lote *l, char pal[30], int v) {
	lote *b = l;
	while (b) {
		if (strcmp(b->codigo, pal) == 0) {
			printf("\tRubro:  %s\n", b->rubro);
			if (v)
				printf("\tSubcategoria:  %s\n", b->subcategoria);
		}
		b = b->prox;
	}
}

void mostrar_una_factura(factura *f, int v, lote *l, char palabra[30], char code[30]) {
	factura *t = f;
	subfactura *s;
	char pal[30]; int monto = 0, cont = 0;

	if (!v) { //GENERAL
		while (t) {
			if (strcmp(palabra, t->cliente) == 0) {
				strcpy(pal, t->codigo);
				printf("\tFactura:  %s\n", pal);
				if (t->abajo) {
					printf("- - - - - - - - - - - - - - - - - -\n");
					s = t->abajo;
					while (s) {
						strcpy(pal, s->codigo_lote);
						printf("\tLote:  %s\n", pal);
						buscar_cosas_lote(l, pal, 1);
						printf("\tUnidades: %i\n", s->unidades);
						printf("\tPrecio por Unidad: %.2lf\n", s->precio);
						printf("\tSubmonto: %.2lf\n", s->venta);
						s = s->abajo;
					}
				}
				else printf("\tEl cliente no ha comprado nada\n");
			}
			t = t->prox;
		}
	}
	else { //DETALLADAMENTE 
		while (t) {
			if ((strcmp(t->cliente, palabra) == 0) && (strcmp(t->codigo, code)) == 0) {
				cont = 1;
				strcpy(pal, t->codigo);
				printf("\tFactura:  %s\n", pal);
				printf("\tSucursal:  %s\n", t->sucursal);
				printf("\tFecha:  %i/%i/%i\n", t->dia, t->mes, t->year);
				printf("\tTotal:  %i\n", t->total);
				printf("- - - - - - - - - - - - - - - - - -\n");
				if (t->abajo) s = t->abajo;
				else printf("\tEl cliente no ha comprado nada\n");
				while (s) {
					strcpy(pal, s->codigo_lote);
					printf("\tLote:  %s\n", pal);
					buscar_cosas_lote(l, pal, 1);
					printf("\tUnidades: %i\n", s->unidades);
					printf("\tPrecio por Unidad: %.2lf\n", s->precio);
					printf("\tSubmonto: %.2lf\n", s->venta);
					s = s->abajo;
					if (s && s->abajo) printf("- - - - - - - - - - - - - - - - - -\n");
				}
			}
			t = t->prox;
		}
		if (cont == 0)
			printf("\tError! El cliente no posee esa factura.\n ");
	}
	system("pause");
}

void  mostrar_factura2(factura *f, char palabra[30], lote *l) {
	factura *t = f; char code[30];
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) printf("%s\n", t->codigo);
		t = t->prox;
	}
	printf("Escriba el codigo de la factura que desea ver detalladamente: ");
	scanf("%s", &code);
	mostrar_una_factura(f, 1, l, palabra, code);
}

void  buscar_facturas_cliente(factura *f, char palabra[30], lote *l) {
	factura *t = f; bool flag = false; char code[30];
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) {
			mostrar_una_factura(f, 0, l, palabra, code); flag = true;
		}
		t = t->prox;
	}
	if (!flag) printf("\tEl cliente no tiene facturas\n");
	system("pause");
}

void mostrar_compra_rubro(factura *f, lote *l, rubros *r, char palabra[30]) {
	factura *t = f; char pal[30];
	subfactura *s=NULL;
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) {
			if (t->abajo)
				s = t->abajo;
			while (s) {
				strcpy(pal, s->codigo_lote);
				buscar_cosas_lote(l, pal, 0);
				printf("\tUnidades: %i\n", s->unidades);
				printf("\tMonto del Rubro: %.2lf\n", s->venta);
				s = s->abajo;
			}
		}
		t = t->prox;
	}
	system("pause");
}

void consulta_cliente(rubros *r, factura *f, cliente *c, lote *l, sucursal *s, char palabra[30]) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU CONSULTA CLIENTE\n\n");
		printf("1.\t-Mostrar los datos generales de sus facturas con el total de unidades y monto.\n");
		printf("2.\t-Imprimir una factura con todos sus detalles.\n");
		printf("3.\t-Mostrar los totales de compras por rubro.\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: buscar_facturas_cliente(f, palabra, l);
			break;
		case 2: mostrar_factura2(f, palabra, l);
			break;
		case 3: mostrar_compra_rubro(f, l, r, palabra);
			break;
		}
	}
}

int exist_unid(lote *l, char ru[30], char subru[30], char palabra[30], long double *cost, long int *unid, int v, long double *prom, long double *tot) {
	lote *t = l; long int exist = 0, cont = 0;
	if (!v) {
		while (t) {
			if ((strcmp(t->sucursal, palabra) == 0) && (strcmp(t->rubro, ru) == 0) && (strcmp(t->subcategoria, subru) == 0)) {
				exist += t->existencia;
				*cost = t->costo;
				*unid += t->unidades;
			}
			t = t->prox;
		}
		return exist;
	}
	else {
		while (t) {
			if ((strcmp(t->sucursal, palabra) == 0) && (strcmp(t->rubro, ru) == 0)) {
				exist += t->existencia;
				*cost += t->costo;
				*unid += t->unidades;
				*tot += exist * (*cost);
				cont++;
			}
			t = t->prox;
		}
		*prom = (*cost) / cont;
		return exist;
	}
}

void exis_rub_subrub(rubros *r, lote *l, char palabra[30], int v) {
	rubros *t = r; long int z = 0, unid; long double cost, prom, tot;
	subrubros *sr;
	char ru[30], subru[30];
	if (v) {
		while (t) {
			if (t->abajo) {
				strcpy(ru, t->nombre);
				cost = 0;
				unid = 0;
				strcpy(subru, "");
				z = exist_unid(l, ru, subru, palabra, &cost, &unid, 1, &prom, &tot);
				printf("\n\tRubro: %s", ru);
				printf("\n\tExistencia: %i", z);
				if (z) {
					printf("\n\tCosto promedio del rubro: %.2lf", prom);
					printf("\n\tCosto total de existentes: %.2lf", tot);
				}
				printf("\n- - - - - - - - - - - - - - - - - -\n");
			}
			else {
				printf("\n\tRubro: %s", ru);
				printf("\n\tExistencia: %i", z);
				printf("\n- - - - - - - - - - - - - - - - - -\n");
			}
			t = t->prox;
		}
	}
	else {
		while (t) {
			strcpy(ru, t->nombre);
			if (t->abajo) {
				sr = t->abajo;
				printf("\n\tRubro: %s", ru);
				printf("\n- - - - - - - - - - - - - - - - - -");
				while (sr) {
					strcpy(subru, sr->nombre);
					cost = 0;
					unid = 0;
					z = exist_unid(l, ru, subru, palabra, &cost, &unid, 0, &prom, &tot);
					printf("\n\tSubcategoria: %s", subru);
					printf("\n\tUnidades: %i", unid);
					printf("\n\tExistencia: %i", z);
					printf("\n\tCosto de unidades: %.2lf\n", cost);
					sr = sr->abajo;
				}
			}
			else {
				printf("\n\tRubro: %s", ru);
				printf("\n\tExistencia: %i", z);
				printf("\n- - - - - - - - - - - - - - - - - -\n");
			}
			t = t->prox;
		}
	}
	system("pause");
}

int existe(lote *l, char ru[30], char subru[30], char palabra[30]) {
	lote *t = l; long int exist = 0, unid = 0;
	while (t) {
		if ((strcmp(t->sucursal, palabra) == 0) && (strcmp(t->rubro, ru) == 0) && (strcmp(t->subcategoria, subru) == 0)) {
			exist += t->existencia;
		}
		t = t->prox;
	}
	return exist;
}

void exis_cero(rubros *r, lote *l, char palabra[30]) {
	rubros *t = r; char ru[30], subru[30]; int z;
	subrubros *sr;
	while (t) {
		strcpy(ru, t->nombre);
		if (t->abajo) {
			sr = t->abajo;
			while (sr) {
				strcpy(subru, sr->nombre);
				z = existe(l, ru, subru, palabra);
				if (!z)
					printf("\n\tEn  la sucursal %s, del rubro %s, la Subcategoria %s no tiene existentes, se necesita pedir de este producto\n", palabra, ru, subru);
				sr = sr->abajo;
			}
		}
		else printf("\n\tEn  la sucursal %s, del rubro %s, se necesita pedir productos de este rubro\n", palabra, ru);
		t = t->prox;
	}
	system("pause");
}

void consulta_sucursal(rubros *r, factura *f, cliente *c, lote *l, sucursal *s, char palabra[30]) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU CONSULTA SUCURSAL\n\n");
		printf("1.\t-Total en existencia por rubros, indicando totales de unidades y costo.\n");
		printf("2.\t-Total en existencia por subcategoria, indicando totales de unidades y costo.\n");
		printf("3.\t-Total de subcategorias con existencia 0. Para hacer pedidos de esos productos.\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: exis_rub_subrub(r, l, palabra, 1);
			break;
		case 2: exis_rub_subrub(r, l, palabra, 0);
			break;
		case 3: exis_cero(r, l, palabra);
			break;
		}
	}
}

void rubros_lote(lote *l, char palabra[30], int v) {
	lote *t = l; long int exist = 0, unid = 0, cont = 0;
	long double prom, total = 0, bruto = 0,x = 0;
	if (v) {
		printf("\n\tRubro: %s", palabra);
		printf("\n- - - - - - - - - - - - - - - - - -\n");
		while (t) {
			if ((strcmp(t->rubro, palabra) == 0)) {
				exist += t->existencia;
				unid += t->unidades;
				cont++;
				x += t->costo;
				total += t->existencia * t->costo;
				printf("Lote: %s", t->codigo);
				printf("\n\tUnidades en este lote: %i", t->unidades);
				printf("\n\tExistentes en este lote: %i", t->existencia);
			}
			t = t->prox;
		}
		prom = x / cont;
		printf("\n\tUnidades: %i", unid);
		printf("\n\tExistencia: %i", exist);
		printf("\n\tCosto promedio: %.2lf", prom);
		printf("\n\tCosto total: %.2lf\n", total);
	}
	else {
		printf("\n\tRubro: %s", palabra);
		printf("\n- - - - - - - - - - - - - - - - - -\n");
		while (t) {
			if ((strcmp(t->rubro, palabra) == 0)) {
				x = t->unidades - t->existencia;
				total += (x * t->costo) * 2;
				bruto += (t->unidades * t->costo) * 2;
			}
			t = t->prox;
		}
		printf("\n\tIngreso Neto: %.2lf", total);
		printf("\n\tIngreso Bruto: %.2lf", bruto);
	}
	system("pause");
}

void consulta_rubro(rubros *r, factura *f, cliente *c, lote *l, sucursal *s, char palabra[30]) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU CONSULTA RUBRO\n\n");
		printf("1.\t-Total en existencia indicando unidades y costo así como el detalle de lotes y cantidades en ellos.\n");
		printf("2.\t-Total de ingreso bruto e ingreso neto de las ventas de esos rubros.\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: rubros_lote(l, palabra, 1);
			break;
		case 2: rubros_lote(l, palabra, 0);
			break;
		}
	}
}

void imp_lote(lote *l, char palabra[30], factura *f) {
	factura *t = f; lote *a = l;
	subfactura *s;
	while (a) {
		if ((strcmp(a->codigo, palabra) == 0)) {
			printf("\n\tLote: %s", palabra);
			printf("\n\tSucursal: %s", a->sucursal);
			printf("\n\tRubro: %s", a->rubro);
			printf("\n\tSubcategoria: %s", a->subcategoria);
			printf("\n\tUnidades: %i", a->unidades);
			printf("\n\tExistencia: %i", a->existencia);
			printf("\n\tPeso: %.2f", a->peso);
			printf("\n\tCosto: %.2lf", a->costo);
		}
		a = a->prox;
	}
	while (t) {
		if (t->abajo) {
			s = t->abajo;
			while (s) {
				if ((strcmp(s->codigo_lote, palabra) == 0)) {
					printf("\n- - - - - - - - - - - - - - - - - -\n");
					printf("\n\tFactura: %s", t->codigo);
					printf("\n\tCantidad en factura: %i", s->unidades);
				}
				s = s->abajo;
			}
		}
		t = t->prox;
	}
	system("pause");
}

void consulta_lote(rubros *r, factura *f, cliente *c, lote *l, sucursal *s, char palabra[30]) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU CONSULTA LOTE\n\n");
		printf("1.\tImprimir datos del lote y los números de factura y cantidad en ellas de sus productos.\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: imp_lote(l, palabra, f);
			break;
		}
	}
}

void consultas(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	int op = -1, cont;
	char palabra[30];
	while (op) {
		system("cls");
		printf("\n\tMENU CONSULTAS\n\n");
		printf("1.\tDado un cliente\n");
		printf("2.\tDado una sucursal\n");
		printf("3.\tDado un rubro\n");
		printf("4.\tDado un lote\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: mostrar_clientes(c);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un cliente que exista!\n");
				printf("Escriba el nombre de uno de los clientes mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_cliente(c, palabra)));
			consulta_cliente(*r, *f, *c, *l, *s, palabra);
			break;

		case 2:mostrar_sucursales(s);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese una sucursal que exista!\n");
				printf("Escriba el nombre de una de las sucursales mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_sucursal(s, palabra)));
			consulta_sucursal(*r, *f, *c, *l, *s, palabra);
			break;

		case 3:mostrar_rubros(r);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que exista!\n");
				printf("Escriba el nombre de uno de los rubros mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_rubro(r, palabra)));
			consulta_rubro(*r, *f, *c, *l, *s, palabra);
			break;

		case 4:mostrar_lotes(l);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un lote que exista!\n");
				printf("Escriba el codigo de uno de los lotes mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_lote(l, palabra)));
			consulta_lote(*r, *f, *c, *l, *s, palabra);
			break;
		}
	}
}

    //ARCHIVOS ARCHIVOS ARCHIVOS

void leer_rubros(rubros **p) {
	// Lee datos de archivo de rubros
	FILE* M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\rubros.txt", "r");//ES NECESARIO AGREGAR DIRECCION COMPLETA
	if (M == NULL) {
		printf("Error al abrir el archivo rubros.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char nombre[20];
		rubros *t = new rubros;

		while (!(feof(M))) {
			fscanf(M, "%s", &nombre);
			fflush(stdin);
			agregar_rubro(p, nombre);
		}
		fclose(M);
	}
}

void leer_subrubros(rubros **p) {
	// Lee datos de archivo de subrubros
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\subrubros.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo subrubros.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char nombrerub[30], nombresubrub[30];

		while (!(feof(M))) {
			fscanf(M, "%s", &nombrerub);
		fflush(stdin);
		fscanf(M, "%s", &nombresubrub);
		fflush(stdin);
		agregar_subrubro(p, nombrerub, nombresubrub);
		}
		fclose(M);
	}
}

void leer_lotes(lote **p) {
	// Lee datos de archivo de lotes
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\lotes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo lotes.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else { 
		char codigo[30],sucursal[30],rubro[30],subcategoria[30];
		long int unidades, existencia;
		float peso;
		long double costo;

		while (!(feof(M))) {
			fscanf(M, "%s", &codigo);
			fflush(stdin);
			fscanf(M, "%s", &sucursal);
			fflush(stdin);
			fscanf(M, "%s", &rubro);
			fflush(stdin);
			fscanf(M, "%s", &subcategoria);
			fflush(stdin);
			fscanf(M, "%i", &unidades);
			fflush(stdin);
			fscanf(M, "%i", &existencia);
			fflush(stdin);
			fscanf(M, "%f", &peso);
			fflush(stdin);
			fscanf(M, "%lf", &costo);
			fflush(stdin);

			agregar_lote(p, codigo, sucursal, rubro, subcategoria, unidades, existencia, peso, costo);
		}
		fclose(M);
	}
}

void leer_clientes(cliente **p) {
	// Lee datos de archivo de cliente
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\clientes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo clientes.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char nombre[30];

		while (!(feof(M))) {
			fscanf(M, "%s", &nombre);
			fflush(stdin);
			agregar_cliente(p,nombre);
		}
		fclose(M);
	}
}

void leer_sucursales(sucursal **p) {
	// Lee datos de archivo de sucursales
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\sucursales.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo sucursales.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char nombre[30];

		while (!(feof(M))) {
			fscanf(M, "%s", &nombre);
			fflush(stdin);
			agregar_sucursal(p, nombre);
		}
		fclose(M);
	}
}

void leer_facturas(factura **p) {
	// Lee datos de archivo de facturas
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\facturas.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo facturas.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char codigo[30], sucursal[30], cliente[30];
		int dia, mes, year;
		long int total;

		while (!(feof(M))) {
			fscanf(M, "%s", &codigo);
			fflush(stdin);
			fscanf(M, "%s", &sucursal);
			fflush(stdin);
			fscanf(M, "%i", &dia);
			fflush(stdin);
			fscanf(M, "%i", &mes);
			fflush(stdin);
			fscanf(M, "%i", &year);
			fflush(stdin);
			fscanf(M, "%s", &cliente);
			fflush(stdin);
			fscanf(M, "%i", &total);
			fflush(stdin);

			agregar_factura(p,codigo,sucursal,dia,mes,year,cliente,total);
		}
		fclose(M);
	}
}

void leer_subfacturas(factura **p) {
	// Lee datos de archivo de subfacturas
	FILE* M;
	M = fopen("C:\\Users\\Armando\\source\\repos\\ArmandoGonzalez-MarcosBetancourt\\Debug\\subfacturas.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo subfacturas.txt\n");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char codigo[30], codigo_lote[30];
		long double precio,venta;
		long int unidades;

		while (!(feof(M))) {
			fscanf(M, "%s", &codigo);
			fflush(stdin);
			fscanf(M, "%s", &codigo_lote);
			fflush(stdin);
			fscanf(M, "%i", &unidades);
			fflush(stdin);
			fscanf(M, "%lf", &precio);
			fflush(stdin);
			fscanf(M, "%lf", &venta);
			fflush(stdin);

			agregar_subfactura(p,codigo,codigo_lote,unidades,precio,venta);
		}
		fclose(M);
	}
}

void cargar_datos(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	leer_rubros(r);
	leer_subrubros(r);
	leer_lotes(l);
	leer_clientes(c);
	leer_sucursales(s);
	leer_facturas(f);
	leer_subfacturas(f);
}

int  main() {
	rubros *r=NULL;
	factura *f=NULL;
	cliente *c=NULL;
	lote *l=NULL;
	sucursal *s=NULL;
	cargar_datos(&r,&f,&c,&l,&s);
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tMENU PRINCIPAL\n\n");
		printf("1.\tAgregar\n");
		printf("2.\tEliminar\n");
		printf("3.\tModificar\n");
		printf("4.\tMostrar\n");
		printf("5.\tConsultas\n");
		printf("0.\tSALIR\n\n");
		scanf("%i", &op);

		switch (op) {
		case 1: agregar(&r, &f, &c, &l, &s);
			break;
		case 2: //eliminar(&r, &f, &c, &l, &s);
			break;
		case 3: //modificar(&r, &f, &c, &l, &s);
			break;
		case 4: mostrar(&r, &f, &c, &l, &s);
			break;
		case 5: consultas(&r, &f, &c, &l, &s);
			break;
		}
		if (op) system("pause");
	}
	//guardardatos();
}