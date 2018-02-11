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
	int unidades;
	int existencia;
	float peso;
	double costo;
	lote *prox;
};

struct cliente {
	char nombre[30];
	cliente *prox;
};

struct subfactura {
	char codigo_lote[30];
	int unidades;
	double precio;
	double venta;
	subfactura *abajo;
};

struct factura {
	char codigo[30];
	char sucursal[30];
	int dia;
	int mes;
	int year;
	char cliente[30];
	int total;
	factura *prox;
	subfactura *abajo;
};

int buscar_rubro(rubros **r, char palabra[30]) {
	rubros *t = *r;
	if (t->nombre == palabra) return 1;
	while (t && t->prox && t->prox->nombre != palabra) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_subrubro(rubros **r, char rub[30], char subrub[30]) {
	rubros *t = *r;
	subrubros *s;
	while (t){
		if (t->abajo && t->nombre==rub) {
			s = t->abajo;
			while (s && s->nombre != subrub) s = s->abajo;
			if (s) { return 1; } else return 0;
		}
		t = t->prox;
	}
	return 0;
}

int buscar_cliente(cliente **c, char palabra[30]) {
	cliente *t = *c;
	if (t->nombre == palabra) return 1;
	while (t && t->prox && t->prox->nombre != palabra) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_lote(lote **l, char palabra[30]) {
	lote *t = *l;
	if (t->codigo == palabra) return 1;
	while (t && t->prox && t->prox->codigo != palabra) t = t->prox;
	if (t->prox) return 1;
	return 0;
}

int buscar_sucursal(sucursal **s, char palabra[30]) {
	sucursal *t = *s;
	if (t->nombre == palabra) return 1;
	while (t && t->prox && t->prox->nombre != palabra) t = t->prox;
	if (t->prox) return 1;
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
		if (t->nombre == palabra) {
			s = t->abajo;
			while (s && s->abajo) s = s->abajo;
			subrubros *nuevo = new subrubros;
			strcpy(nuevo->nombre, palabra2);
			nuevo->abajo = NULL;
			s->abajo = nuevo;
		}
	}
}

void agregar_cliente(cliente **c,char palabra[30]) {
	cliente *t = *c,*p = new cliente;
	strcpy(p->nombre, palabra);
	p->prox = NULL;
	if (*c) {
		while ((t) && (t->prox)) {
			t = t->prox;
		}
		t->prox = p;
	}
	else
		*c = p;
}

void agregar_lote(lote **l, char codigo[30], char sucur[30], char rub[30], char subrub[30], int unidades, float peso, double costo) {
	lote *t = *l, *aux;
	if (t) {

	}
	else {
		aux = new lote;
		strcpy(aux->codigo, codigo);
		strcpy(aux->sucursal, sucur);
		strcpy(aux->rubro, rub);
		strcpy(aux->subcategoria, subrub);
		aux->unidades = unidades;
		aux->existencia = unidades;
		t->peso = peso;
		t->costo = costo;
	}
}

void agregar_sucursal(sucursal **s, char palabra[30]) {

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

void agregar_factura_principal(factura **f) {
	int op = -1;
	while (op) {
		system("cls");
		printf("\n\tAGREGAR FACTURA\n\n");
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
		case 2: agregar_factura_principal(f);
			break;
		case 3: agregar_cliente_principal(c);
			break;
		case 4: agregar_lote_principal(l);
			break;
		case 5: agregar_sucursal_principal(s);
			break;
		}
	}
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
	int unidades;
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
	double costo;
	do {
		if (cont) printf("\nError! Ingrese un costo positivo!\n");
		printf("Ingrese el costo en BsF por unidad: ");
		scanf("%f", &costo);
		cont++;
	} while (costo <= 0);
	agregar_lote(l, codigo,sucur,rub,subrub,unidades,peso,costo);
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
		case 2: agregar_factura_principal(f);
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

void consultas(rubros **r, factura **f, cliente **c, lote **l, sucursal **s) {

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