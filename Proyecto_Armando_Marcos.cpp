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
	int exitencia;
	float peso;
	double costo;
	lote *prox;
};

struct cliente {
	char nombre[30];
	cliente *prox;
};

struct subfactura {
	char codigo[30];
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
			} while (!(buscar_rubro(r, palabra)));
			agregar_rubro(r, palabra);
			break;
		case 2: cont = 0;
			do {
				if (cont) printf("\nError! Ingrese un rubro que no exista!\n");
				printf("Ingrese el nombre del rubro: ");
				scanf("%s", &palabra);
				cont++;
			} while (!(buscar_rubro(r, palabra)));
			printf("Ingrese el nombre de la subcategoria: ");
			scanf("%s", &palabra2);
			agregar_subrubro(r, palabra, palabra2);
			break;
		}
	}
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
		case 2: agregar_factura(f);
			break;
		case 3: agregar_cliente(c);
			break;
		case 4: agregar_lote(l);
			break;
		case 5: agregar_sucursal(s);
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