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
	rubros *t = *r;
	if (strcmp(t->nombre,palabra)==0) return 1;
	while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_subrubro(rubros **r, char rub[30], char subrub[30]) {
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
	return 0;
}

int buscar_cliente(cliente **c, char palabra[30]) {
	cliente *t = *c;
	if (strcmp(t->nombre,palabra)==0) return 1;
	while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_lote(lote **l, char palabra[30]) {
	lote *t = *l;
	if (strcmp(t->codigo,palabra)==0) return 1;
	while (t && t->prox && strcmp(t->prox->codigo,palabra)!=0) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_sucursal(sucursal **s, char palabra[30]) {
	sucursal *t = *s;
	if (strcmp(t->nombre,palabra)==0) return 1;
	while (t && t->prox && strcmp(t->prox->nombre,palabra)!=0) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_factura(factura **f, char palabra[30]) {
	factura *t = *f;
	if (strcmp(t->codigo,palabra)==0) return 1;
	while (t && t->prox && strcmp(t->prox->codigo,palabra)!=0) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

long int obtener_existentes_lote(lote **l, char palabra[30]) {
	lote *t = *l;
	while (t) {
		if (strcmp(t->codigo,palabra)==0) return (t->existencia);
		t = t->prox;
	}
	return 0;
}

long double obtener_precio_lote(lote **l, char palabra[30]) {
	lote *t = *l;
	while (t) {
		if (strcmp(t->codigo, palabra) == 0) return (t->costo);
		t = t->prox;
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
	aux->existencia = unidades;
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
			printf("Rubro agregado satisfactoriamente!");
			system("pause");
			break;
		case 2: cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que no exista!\n");
				printf("Ingrese el nombre del rubro: ");
				scanf("%s", &palabra);
				cont++;
			} while (buscar_rubro(r, palabra));
			printf("Ingrese el nombre de la subcategoria: ");
			scanf("%s", &palabra2);
			agregar_subrubro(r, palabra, palabra2);
			printf("Subcategoria de rubro agregada satisfactoriamente!");
			system("pause");
			break;
		}
	}
}

void agregar_factura_principal(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {
	system("cls");
	printf("\n\tAGREGAR FACTURA\n\n");
	int cont = 1;
	char cliente[30];
	do {
		printf("Ingrese el nombre del cliente: ");
		scanf("%f", &cliente);
		if (!(buscar_cliente(c, cliente))) {
			printf("\nEl cliente que ingreso no existe desea agregarlo?\nPresione 1 para si y 0 para no: ");
			scanf("%i", &cont);
			if (cont) {
				agregar_cliente(c, cliente);
				printf("\nCliente agregado satisfactoriamente!");
			}
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
	int cont2 = 1;
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
			scanf("%s", &unidades);
			cont++;
		} while (unidades>0 && (unidades<obtener_existentes_lote(l, codigo_lote)));
		precio = (obtener_precio_lote(l,codigo_lote))*2;
		venta = precio * unidades;
		agregar_subfactura(f,codigo,codigo_lote,unidades,precio,venta);
		printf("\nCompra realizada, desea agregar elementos de otro lote a la factura?\nPresione 1 para si y 0 para no: ");
		scanf("%i",cont2);
	} while (!cont2);
	printf("Factura agregada satisfactoriamente!");
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
		scanf("%s", &unidades);
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
		scanf("%f", &costo);
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
		case 1: eliminar_rubro(r);
			break;
		case 2: eliminar_cliente(c);
			break;
		case 3: eliminar_lote(l);
			break;
		case 4: eliminar_sucursal(s);
			break;
		}
	}
}

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
		case 1: mostrar_rubro(r);
			break;
		case 2: mostrar_factura(f);
			break;
		case 3: mostrar_cliente(c);
			break;
		case 4: mostrar_lote(l);
			break;
		case 5: mostrar_sucursal(s);
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

void mostrar_una_factura(factura *f, int v, lote *l, char palabra[30], char *code[30]) {
	factura *t = f;
	subfactura *s;
	char pal[30]; int monto = 0, cont = 0;

	if (!v) { //GENERAL
		strcpy(pal, f->codigo);
		printf("\tFactura:  %s\n", pal);
		if (f->abajo) {
			printf("- - - - - - - - - - - - - - - - - -\n");
			s = f->abajo;
			while (s) {
				strcpy(pal, s->codigo_lote);
				printf("\tLote:  %s\n", pal);
				buscar_cosas_lote(l, pal, 1);
				printf("\tUnidades: &i\n", s->unidades);
				printf("\tPrecio por Unidad: &i\n", s->precio);
				printf("\tSubmonto: &i\n", s->venta);
				s = s->abajo;
			}
		}
		else
			printf("\tEl cliente no ha comprado nada\n");
	}
	else { //DETALLADAMENTE 

		while (t) {
			if ((strcmp(t->cliente, palabra) == 0) && (strcmp(t->codigo, *code)) == 0) {
				cont = 1;
				strcpy(pal, f->codigo);
				printf("\tFactura:  %s\n", pal);
				printf("\tSucursal:  %s\n", t->sucursal);
				printf("\tFecha:  %i/%i/%i\n", t->dia, t->mes, t->year);
				printf("\tTotal:  %i\n", t->total);
				printf("- - - - - - - - - - - - - - - - - -\n");
				if (t->abajo) s = t->abajo;
				else printf("\tEl cliente no ha comprado nada\n");
				while (s) {
					strcpy(pal, s->codigo_lote);
					printf("\tSubFactura:  %s\n", pal);
					strcpy(pal, s->codigo_lote);
					printf("\tLote:  %s\n", pal);
					buscar_cosas_lote(l, pal, 1);
					printf("\tUnidades: &i\n", s->unidades);
					printf("\tPrecio por Unidad: &i\n", s->precio);
					printf("\tSubmonto: &i\n", s->venta);
					s = s->abajo;
					if (s->abajo) printf("- - - - - - - - - - - - - - - - - -\n");
				}
			}
			t = t->prox;
		}
		if (cont == 0)
			printf("\tError! El cliente no posee esa factura.\n ");
	}
}

void  mostrar_factura2(factura *f, char palabra[30], lote *l) {
	factura *t = f; char *code[30];
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) printf("%s\n", t->codigo);
		t = t->prox;
	}
	printf("Escriba el codigo de la factura que desea ver detalladamente");
	scanf("%s", &code);
	mostrar_una_factura(f, 1, l, palabra, code);
}

void  buscar_facturas_cliente(factura *f, char palabra[30], lote *l) {
	factura *t = f; bool flag = false; char *code[30];
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) {
			mostrar_una_factura(f, 0, l, palabra, code); flag = true;
		}
		t = t->prox;
	}
	if (!flag)
		printf("\tEl cliente no tiene facturas\n");
	else
		system("pause");
}

void mostrar_compra_rubro(factura *f, lote *l, rubros *r, char palabra[30]) {
	factura *t = f; char pal[30];
	subfactura *s;
	while (t) {
		if (strcmp(t->cliente, palabra) == 0) {
			if (t->abajo)
				s = t->abajo;
			while (s) {
				strcpy(pal, s->codigo_lote);
				buscar_cosas_lote(l, pal, 0);
				printf("\tUnidades: &i\n", s->unidades);
				printf("\tMonto del Rubro: &i\n", s->venta);
				s = s->abajo;
			}
		}
	}
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

/*void consulta_sucursal(rubros *r, factura *f, cliente *c, lote *l, sucursal *s, char palabra[30]) {
buscar_un_lote(l, palabra);
}*/


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
		case 1: mostrar_cliente(*c);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un cliente que exista!\n");
				printf("Escriba el nombre de uno de los clientes mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_cliente(c, palabra)));
			consulta_cliente(*r, *f, *c, *l, *s, palabra);
			break;

		case 2:mostrar_sucursal(*s);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese una sucursal que exista!\n");
				printf("Escriba el nombre de una de las sucursales mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_sucursal(s, palabra)));
			consulta_sucursal(*r, *f, *c, *l, *s, palabra);
			break;

		case 3:mostrar_rubro(*r);
			cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que exista!\n");
				printf("Escriba el nombre de uno de los rubros mencionados anteriormente: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_rubro(r, palabra)));
			consulta_rubro(*r, *f, *c, *l, *s, palabra);
			break;

		case 4:mostrar_lote(*l);
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
	FILE* M;
	M = fopen("rubros.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo rubros.txt");
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
	M = fopen("subrubros.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo subrubros.txt");
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
	M = fopen("lotes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo lotes.txt");
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
			fscanf(M, "%f", &costo);
			fflush(stdin);

			agregar_lote(p, codigo, sucursal, rubro, subcategoria, unidades, existencia, peso, costo);
		}
		fclose(M);
	}
}

void leer_cliente(cliente **p) {
	// Lee datos de archivo de cliente
	FILE* M;
	M = fopen("clientes.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo clientes.txt");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char nombre[30];
		int dia, mes, year, total;

		while (!(feof(M))) {
			fscanf(M, "%s", &nombre);
			fflush(stdin);
			agregar_cliente(p,nombre);
		}
		fclose(M);
	}
}

void leer_factura(factura **p) {//TERMINAR
	// Lee datos de archivo de factura
	FILE* M;
	M = fopen("facturas.txt", "r");
	if (M == NULL) {
		printf("Error al abrir el archivo facturas.txt.txt");
		system("pause");
		fclose(M);
		exit(1);
	}
	else {
		char codigo[30], sucursal[30], cliente[30];
		int dia, mes, year, total;

		while (!(feof(M))) {
			fscanf(M, "%s", &nombre);
			fflush(stdin);
			agregar_cliente(p, nombre);
		}
		fclose(M);
	}
}

int  main() {
	rubros *r;
	factura *f;
	cliente *c;
	lote *l;
	sucursal *s;
	//cargardatos(&r,&f,&c,&l,&s);
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
		case 2: eliminar(&r, &f, &c, &l, &s);
			break;
		case 3: modificar(&r, &f, &c, &l, &s);
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