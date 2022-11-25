#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct
{
    char Calle[30];
    char Numero[10];
}Dom;

typedef struct
{
    int idCliente;
    char Nombre[30];
    char Apellido[30];
    char DNI[30];
    Dom Domicilio;
    char Mail[40];
    char Movil[30];
    int Estado_del_cliente;
}Cliente;



int validarLetras (char Nombre[]);
int validarNumString (char Nombre[]);
int validarMail (char Mail[]);
Cliente cargarUnCliente (Cliente A);
int verificarPresenciaClienteBase (char nombreArch[],char DNINumero[]);
int cantidadRegistrosArchivoGenerica (char nombreArchivo[], int sizeofDato);
void guardarClientesEnArchivo (char nombreArch[]);
void mostrarUnCliente(Cliente al);
void mostrarArchivoClientes (char nombreArch[]);
void mostrarRegistroClienteXIdCliente (char nombreArch [],int id);
int buscarIdClienteXDni (char nombreArch[], char num[]);
Cliente modificarDatosCliente (Cliente a);
void modificarClienteenArchivoXidCliente (char nombreArch[], int id);
void bajaCliente (char nombreArch[], int id);
int pasarArchivoClientesAarreglo (char nombreArch[], Cliente A[], int dimension);
void mostrarArregloClientes (Cliente A[], int validos);
void insertarClienteEnArregloOrdenadoXApellidoYNombre (Cliente A[],int u,Cliente f);
void OrdenarInsercionArregloClientesXApellidoYNombre (Cliente A[], int validos);
void pasarArregloAarchivoClientes (Cliente A[],int validos, char nombreArch[]);
int buscarArregloMenorIdCliente (Cliente A[], int validos, int pos);
void ordenacionArregloSeleccionIdCliente (Cliente A[], int validos);

void gotoxy (int x, int y);
void mostrarUnClienteGo(Cliente al[], int y);

#endif // CLIENTES_H_INCLUDED
