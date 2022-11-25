#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "math.h"
#include <time.h>


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

typedef struct{
    int cantidadProducto;
    char producto [30];
    float valorUnitario;
}stDescripcion;

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct{
long int idPedido;
int idCliente;
float costoPedido;
Fecha fechaPedido;
int estadoPedido;
stDescripcion descripcion[30];
int cantidadProductosDistintosPedido;
}stPedido;

typedef struct
{
    int idCliente;
    int cantPedidos;
    char Apellido[30];
    char Nombre[30];
}PedidosXCliente;


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

stPedido cargarPedido (stPedido A, int dimension);
void guardarPedidoEnArchivo (char nombreArchivoPedidos[]);
void mostrarUnaDescripcionPedido (stDescripcion e);
void mostrarDescripcionPedido (stDescripcion descrip[], int validos);
void mostrarPedido (stPedido e);
void mostrarArchivoPedidos (char nombreArchivoPedidos[]);
void mostrarPedidosXIdClienteArchivo (char nombreArchivo[], int id);
stPedido modificarPedido(stPedido e, int validos);
long int buscarPosicionPedidoArchivoXidPedido (char nombreArch[], long int idPedido);
void modificarPedidoenArchivoXidPedido (char nombreArch[], int idPedido);

int pasarArchivoPedidosAarreglo (char nombreArch[], stPedido A[], int dimension);
int buscarMenorFechaPedido (stPedido A[], int validos, int pos);
void ordenarPedidosXFechaAntiguaAReciente (stPedido A[], int validos);
void mostrarArregloPedidos (stPedido A[], int validos);
void pasarArregloAarchivoPedidos (stPedido A[], int validos, char nombreArch[]);
void cargarPedidosXIdClienteEnArchivo (char nombreArchivo[], int id, char nombrearch[]);
int pasarPedidosArchivoAarregloDeCantPedidos (char archPedidos[], char archClientes[], PedidosXCliente P[], int dimension);
void mostrarCantPedidosXUnCliente (PedidosXCliente A);
void mostrarArregloTipoPedidosXCliente(PedidosXCliente A[], int validos);
int buscarClienteConMayorCantPedidos (PedidosXCliente A[], int validos, int pos);
void ordenacionArregloSeleccionClientesXcantPedidos (PedidosXCliente A[], int validos);
void mostrarTopTenMejoresClientesArreglo (PedidosXCliente A[], int validos);
void mostrarPeorClienteXCantPedidos (PedidosXCliente A[], int validos);
void pasarArregloAarchivoCantPedidosXCliente (PedidosXCliente A[], int validos, char nombreArch[]);
void mostrarArchivoPedidosXCliente (char nombreArchivoPedidos[]);

int main()
{

///--------------MAIN DE CLIENTES-------------------------------

char nombreArch[20]="ArchivoX";
char archOrdenApellido[20]="ListaOrdenClientesXApellidoYNombre";
char archOrdenIdCliente[30]="ListaOrdenXIdCliente";
char num[30];
int cant;
int validos;
Cliente f[20];


char nombreArchivoPedidos[30]="ArchivoPedidos";
char pedidos[30]="Pedidos";
int flag=0;

char archPedidosXFecha[30]="ListaPedidosOrdenFecha";
char archPedidosXCliente[30]="ListaPedidosXCliente";

stPedido Orden[30];
int validosOrden;
char archTopTenClientes[30]="ListaTopTenClientes";



printf("\nFUNCION PARA CARGA Y MUESTRA DE CLIENTES\n");
guardarClientesEnArchivo(nombreArch);
printf("\nArchivo de clientes:\n");
system("cls");

mostrarArchivoClientes(nombreArch);
system("pause");


printf("\nFUNCION PARA MODIFICAR CLIENTE\n");
printf("\nIngrese el DNI del cliente a buscar\n");
fflush(stdin);
gets(num);
cant=buscarIdClienteXDni(nombreArch,num);

system("pause");
system("cls");

modificarClienteenArchivoXidCliente(nombreArch,cant);
system("pause");
system("cls");
printf("\nArchivo de clientes:\n");
mostrarArchivoClientes(nombreArch);
system("pause");

printf("\nFUNCION PARA DAR DE BAJA CLIENTE\n");
printf("\nIngrese el DNI del cliente a buscar\n");
fflush(stdin);
gets(num);
cant=buscarIdClienteXDni(nombreArch,num);
bajaCliente(nombreArch,cant);
printf("\nArchivo de clientes:\n");
system("pause");
mostrarArchivoClientes(nombreArch);


system("pause");
validos=pasarArchivoClientesAarreglo(nombreArch,f,20);
printf("ARREGLO CLIENTES");
mostrarArregloClientes(f,validos);
system("pause");

OrdenarInsercionArregloClientesXApellidoYNombre(f,validos);
printf("ARREGLO ORDENADO POR INSERCION POR APELLIDO");
mostrarArregloClientes(f,validos);
pasarArregloAarchivoClientes(f,validos,archOrdenApellido);
system("pause");

ordenacionArregloSeleccionIdCliente(f,validos);
printf("ARREGLO ORDENADO SELECCION IDCLIENTE");
mostrarArregloClientes(f,validos);
pasarArregloAarchivoClientes(f,validos,archOrdenIdCliente);


///--------------MAIN DE PEDIDOS-------------------------------


guardarPedidoEnArchivo(nombreArchivoPedidos);
printf("\nARCHIVO DE PEDIDOS\n");
mostrarArchivoPedidos(nombreArchivoPedidos);
system("pause");

system("pause");
long int cantx;
printf("\nPEDIDO DEL ID CLIENTE Nº1\n");
mostrarPedidosXIdClienteArchivo(nombreArchivoPedidos,1);

do
    {
        printf("\n\Ingrese el id del pedido que desea modificar\n");
        fflush(stdin);
        flag=scanf("%li",&cantx);
        if(flag==0)
                printf("\nFormato de numero no valido\n");
    }while(flag==0);


modificarPedidoenArchivoXidPedido(nombreArchivoPedidos,cantx);
system("pause");
printf("\nARCHIVO DE PEDIDOS\n");
mostrarArchivoPedidos(nombreArchivoPedidos);



///----------------MAIN DE LISTADOS Y ESTADISTICAS--------------------------------


validosOrden=pasarArchivoPedidosAarreglo(nombreArchivoPedidos, Orden, 30);
ordenarPedidosXFechaAntiguaAReciente(Orden,validosOrden);
mostrarArregloPedidos(Orden, validosOrden);
pasarArregloAarchivoPedidos(Orden,validosOrden,archPedidosXFecha);
mostrarArchivoPedidos(archPedidosXFecha);

cargarPedidosXIdClienteEnArchivo(nombreArchivoPedidos,1,archPedidosXCliente);
mostrarArchivoPedidos(archPedidosXCliente);


int dimension6=cantidadRegistrosArchivoGenerica("ArchivoX",sizeof(Cliente));

system("pause");
PedidosXCliente P[dimension6];
int validos6;

validos6=pasarPedidosArchivoAarregloDeCantPedidos(nombreArchivoPedidos,nombreArch,P,dimension6);
mostrarArregloTipoPedidosXCliente(P,validos6);
system("pause");
ordenacionArregloSeleccionClientesXcantPedidos(P,validos6);
printf("\nLISTA DE CLIENTES POR CANTIDAD DE PEDIDOS\n");
mostrarArregloTipoPedidosXCliente(P,validos6);
system("pause");
printf("\nTOP TEN MEJORES CLIENTES POR CANTIDAD DE PEDIDOS\n");
mostrarTopTenMejoresClientesArreglo (P,validos6);
system("pause");

pasarArregloAarchivoCantPedidosXCliente(P,validos6,archTopTenClientes);
mostrarArchivoPedidosXCliente(archTopTenClientes);
system("pause");
printf("\nCLIENTE CON MENOR CANTIDAD DE PEDIDOS\n");
mostrarPeorClienteXCantPedidos (P,validos6);



    return 0;
}

///--------------------FUNCIONES DE CLIENTES-------------------------------------------------------

int validarLetras (char Nombre[]) /// Funcion para validar la carga de datos que sean letras con formato char
{
    int i=0;
    int flag=0;
    int esLetra;

    while (i<strlen(Nombre)&& flag==0)
    {
        esLetra=isalpha(Nombre[i]) || isspace(Nombre[i]);
        if (esLetra!=0)
        {
            i++;
        }
        else
        {
            printf("\nError de carga de datos\n");
            flag=1;
        }
    }
    return flag;
}

int validarNumString (char Nombre[]) /// Funcion para validar la carga de datos que sean numeros con formato char
{
    int i=0;
    int flag=0;
    int esNum;

    while (i<strlen(Nombre)&& flag==0)
    {
        esNum=isdigit(Nombre[i]);
        if (esNum!=0)
        {
            i++;
        }
        else
        {
            printf("\nError de carga de datos\n");
            flag=1;
        }
    }
    return flag;
}

int validarMail (char Mail[]) /// Funcion para validar la carga de datos que correspondan al mail conteniendo el caracter @
{
    int i=0;
    int flag=0;

    while (i<strlen(Mail)&&flag==0)
    {
        if (Mail[i]=='@')
        {
            flag=1;
        }
        else
        {
            i++;
        }
    }
    if(flag==0)
    {
        printf("\nError de carga de datos\n");
    }
    return flag;
}

Cliente cargarUnCliente (Cliente A) /// Funcion Carga Clientes
{
    int flag=0;

        do
        {
            printf("\nIngrese el apellido del cliente\n");
            fflush(stdin);
            gets(A.Apellido);
            flag= validarLetras(A.Apellido);
        }while(flag==1);

        do
        {
            printf("\nIngrese el nombre del cliente\n");
            fflush(stdin);
            gets(A.Nombre);
            flag= validarLetras(A.Nombre);
        }while(flag==1);

        do
        {
            printf("\nIngrese el numero de DNI del cliente\n");
            fflush(stdin);
            gets(A.DNI);
            flag=validarNumString(A.DNI);
        }while(flag==1);

        do
        {
            printf("\nIngrese el numero de movil del cliente\n");
            fflush(stdin);
            gets(A.Movil);
            flag=validarNumString(A.Movil);
        }while(flag==1);

        do
        {
            printf("\nIngrese la calle del domicilio del cliente\n");
            fflush(stdin);
            gets(A.Domicilio.Calle);
            flag=validarLetras(A.Domicilio.Calle);
        }while(flag==1);

        do
        {
            printf("\nIngrese la altura de la calle del domicilio del cliente\n");
            fflush(stdin);
            gets(A.Domicilio.Numero);
            flag=validarNumString(A.Domicilio.Numero);
        }while(flag==1);

        do
        {
            printf("\nIngrese el mail del cliente\n");
            fflush(stdin);
            gets(A.Mail);
            flag= validarMail(A.Mail);
        }while(flag==0);

        A.Estado_del_cliente=0;

   return A;
}

int verificarPresenciaClienteBase (char nombreArch[],char DNINumero[]) /// Verificar si el cliente esta ya cargado
{
    int flag=0;
    FILE *buf=fopen(nombreArch,"rb");
    Cliente e;

    if (buf!=NULL)
    {
        while(fread(&e,sizeof(Cliente),1,buf)>0&&flag==0)
        {
            if (strcmp(e.DNI,DNINumero)==0)
            {
                flag=1;
            }
        }
     fclose(buf);
    }
    else
    {
        printf("\nError en la lectura del archivo");
    }
    return flag;
}

int cantidadRegistrosArchivoGenerica (char nombreArchivo[], int sizeofDato) /// Contar la cantidad de clientes hay en la base de datos
{
    FILE *buf= fopen(nombreArchivo,"rb");
    int cant;

    if (buf!=NULL)
    {
        fseek(buf,0,SEEK_END);
        cant= ftell(buf)/sizeofDato;
        fclose(buf);
    }
    else
    {
        printf("El archivo no se pudo abrir");
    }

    return cant;
}

void guardarClientesEnArchivo (char nombreArch[]) /// Guardar Carga de clientes en el archivo
{
    FILE *buf= fopen(nombreArch,"rb");
    Cliente e;
    char control='s';
    char control2='s';
    char num[30];
    int flag;
    int numCliente=1;


    if (buf==NULL)
    {
        buf=fopen(nombreArch,"wb");

        if (buf!=NULL)
            {
                while (control=='s')
                {
                    e=cargarUnCliente(e);
                    e.idCliente=numCliente++;
                    fwrite(&e,sizeof(Cliente),1, buf);
                    printf("\nDesea seguir ingresando clientes? s/n");
                    fflush(stdin);
                    scanf("%c",&control);
                }
             fclose(buf);
            }
        else
            {
            printf("\nError de datos - El archivo no pudo ser abierto\n");
            }
    }
    else
    {
            buf=fopen(nombreArch,"ab");

            if(buf!=NULL)
            {
                numCliente=cantidadRegistrosArchivoGenerica(nombreArch,sizeof(Cliente))+1;
                while (control2=='s')
                {
                    do
                    {
                        printf("\nIngrese el DNI del cliente a ingresar en la base de datos\n");
                        fflush(stdin);
                        gets(num);
                        flag=validarNumString(num);
                    }while(flag==1);

                    flag=verificarPresenciaClienteBase(nombreArch,num);

                    if (flag==0)
                    {
                        printf("\nEse numero de DNI no corresponde a ningun cliente de la base de datos\n");
                        e=cargarUnCliente(e);
                        e.idCliente=numCliente;
                        fwrite(&e,sizeof(Cliente),1, buf);
                        numCliente++;
                    }
                    else
                    {
                        printf("\nEl cliente ya se encuentra en la base de datos\n");
                    }
                    printf("\nDesea seguir cargando clientes? s/n\n");
                    fflush(stdin);
                    scanf("%c", &control2);
                }
                fclose(buf);
            }
     }
}

void mostrarUnCliente(Cliente al) /// Mostrar un cliente
{
    printf("\n---------------------------------------------------------\n");
    printf("\nApellido del cliente:\n");
    printf("%s", al.Apellido);
    printf("\nNombre del cliente:\n");
    printf("%s", al.Nombre);
    printf("\nNumero de DNI del cliente:\n");
    printf("%s", al.DNI);
    printf("\nNumero de cliente:\n");
    printf("%d", al.idCliente);
    printf("\nNumero de movil del cliente:\n");
    printf("%s", al.Movil);
    printf("\nCalle del domicilio del cliente:\n");
    printf("%s", al.Domicilio.Calle);
    printf("\nAltura de la calle del domicilio del cliente:\n");
    printf("%s", al.Domicilio.Numero);
    printf("\nMail del cliente:\n");
    printf("%s", al.Mail);
    printf("\nEstado del cliente (0=activo; 1=inactivo):\n");
    printf("%d", al.Estado_del_cliente);
    printf("\n---------------------------------------------------------\n");

}

void mostrarArchivoClientes (char nombreArch[]) /// Mostrar el archivo de clientes
{
    FILE *buf=fopen(nombreArch,"rb");
    Cliente e;

    if (buf!=NULL)
    {
        while (fread(&e,sizeof(Cliente),1,buf)>0)
        {
            mostrarUnCliente(e);
        }

       fclose(buf);
    }
    else
    {
        printf("\nError de lectura de datos\n");
    }
}

int buscarIdClienteXDni (char nombreArch[], char num[]) /// Funcion para buscar un idcliente segun DNI
{
    FILE *buf=fopen(nombreArch,"rb");
    Cliente e;
    int flag=0,cant=0;

    if(buf!=NULL)
    {
        while(flag==0 &&fread(&e,sizeof(Cliente),1,buf)>0)
            {
                if (strcmp(e.DNI,num)==0)
                {
                    cant=e.idCliente;
                    flag=1;
                }
            }
        if(flag==0)
                {
                    printf("\nEse numero de DNI no figura en la base de clientes\n");
                }

        fclose(buf);
    }
    else
    {
        printf("\nError en la apertura del archivo\n");
    }
    return cant;
}

void mostrarRegistroClienteXIdCliente (char nombreArch [],int id) /// Funcion para mostrar un registro de cliente por idCliente
{
    FILE *buf=fopen(nombreArch,"rb");
    Cliente e;
    int flag=0, cant=0;

    if (buf!=NULL)
    {
      while(flag==0 && fread(&e,sizeof(Cliente),1,buf)>0)
            {
                if(e.idCliente==id)
                {
                    mostrarUnCliente(e);
                    flag=1;
                }

            }
            if(flag==0)
                {
                    printf("\nIdCliente inexistente\n");
                }

        fclose(buf);
    }
    else
    {
        printf("\nError de lectura del archivo\n");
    }
}

Cliente modificarDatosCliente (Cliente a) /// Modifica los datos de un cliente
{

    char control='s';
    int opcion;

    while (control=='s')
    {
        printf("\nQue datos desea modificar?\n");
        printf("\n1:Apellido\n2:Nombre\n3:DNI\n4:Movil\n5:Calle del domicilio\n6:Altura de la calle del domicilio\n7:Mail\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
            int flag=0;

            case 1:
                    do
                    {
                        printf("\nIngrese el apellido del cliente\n");
                        fflush(stdin);
                        gets(a.Apellido);
                        flag= validarLetras(a.Apellido);
                    }while(flag==1);
                    break;
            case 2:
                    do
                    {
                        printf("\nIngrese el nombre del cliente\n");
                        fflush(stdin);
                        gets(a.Nombre);
                        flag= validarLetras(a.Nombre);
                    }while(flag==1);
                    break;
            case 3:
                    do
                    {
                        printf("\nIngrese el numero de DNI del cliente\n");
                        fflush(stdin);
                        gets(a.DNI);
                        flag=validarNumString(a.DNI);
                    }while(flag==1);
                    break;
            case 4:
                   do
                    {
                        printf("\nIngrese el numero de movil del cliente\n");
                        fflush(stdin);
                        gets(a.Movil);
                        flag=validarNumString(a.Movil);
                    }while(flag==1);
                    break;
            case 5:
                    do
                    {
                        printf("\nIngrese la calle del domicilio del cliente\n");
                        fflush(stdin);
                        gets(a.Domicilio.Calle);
                        flag=validarLetras(a.Domicilio.Calle);
                    }while(flag==1);
                    break;
            case 6:
                     do
                    {
                        printf("\nIngrese la altura de la calle del domicilio del cliente\n");
                        fflush(stdin);
                        gets(a.Domicilio.Numero);
                        flag=validarNumString(a.Domicilio.Numero);
                    }while(flag==1);
                    break;

            case 7:
                     do
                    {
                        printf("\nIngrese el mail del cliente\n");
                        fflush(stdin);
                        gets(a.Mail);
                        flag= validarMail(a.Mail);
                    }while(flag==0);
                    break;
        }

        printf("\nDesea modificar algun otro dato de este cliente? s/n\n");
        fflush(stdin);
        scanf("%c", &control);

    }
return a;
}

void modificarClienteenArchivoXidCliente (char nombreArch[], int id) /// Funcion para modificar un cliente en el archivo
{
    FILE *buf=fopen(nombreArch,"r+b");
    Cliente e;


    if (buf!=NULL)
    {
            if (id==0)
            {
                printf("\nIdCliente inexistente\n");
            }
            else
            {
                mostrarRegistroClienteXIdCliente(nombreArch,id);
                fseek(buf,sizeof(Cliente)*(id-1),SEEK_SET);
                fread(&e,sizeof(Cliente),1,buf);
                e=modificarDatosCliente(e);
                fseek(buf,sizeof(Cliente)*(id-1),SEEK_SET);
                fwrite(&e,sizeof(Cliente),1,buf);
            }

    fclose(buf);
    }
    else
    {
        printf("\nError en la lectura del archivo\n");
    }
}

int pasarArchivoClientesAarreglo (char nombreArch[], Cliente A[], int dimension) /// Funcion para pasar datos de un archivo de tipo cliente a un arreglo
{
    FILE *buf=fopen(nombreArch,"rb");

    Cliente e;
    int i=0;

    if(buf!=NULL)
    {
        while (fread(&e,sizeof(Cliente),1,buf)>0&& i<dimension)
        {
            A[i]=e;
            i++;
        }

    fclose(buf);
    }
    else
    {
        printf("\nError de apertura del archivo\n");
    }
    return i;

}

void bajaCliente (char nombreArch[], int id) /// Funcion para dar de baja al cliente
{
    FILE *buf=fopen(nombreArch,"r+b");
    Cliente e;
    int opcion;

    if (buf!=NULL&& id!=0)
    {
         mostrarRegistroClienteXIdCliente(nombreArch,id);
         fseek(buf,sizeof(Cliente)*(id-1),SEEK_SET);
         fread(&e,sizeof(Cliente),1,buf);
         if (e.Estado_del_cliente==0)
         {
             printf("\nDesea dar de baja al cliente? Presione 1 para hacerlo o cualquier otra tecla para salir\n");
             scanf("%d", &opcion);
             if (opcion==1)
             {
                 e.Estado_del_cliente=1;
                 fseek(buf,sizeof(Cliente)*(id-1),SEEK_SET);
                 fwrite(&e,sizeof(Cliente),1,buf);
             }
         }
         else if(e.Estado_del_cliente==1)
         {
             printf("\nEl cliente ya se encuentra inactivo\n");
         }
    fclose(buf);
    }
    else if(buf==NULL)
    {
        printf("\nError en la lectura del archivo\n");
    }

}

void mostrarArregloClientes (Cliente A[], int validos) /// Funcion que muestra un arreglo de tipo Cliente
{
    int i=0;

    for (i=0;i<validos;i++)
    {
        printf("\nCliente numero %d\n",i);
        printf("----------------------");
        mostrarUnCliente(A[i]);
        printf("----------------------");
    }
}

void insertarClienteEnArregloOrdenadoXApellidoYNombre (Cliente A[],int u,Cliente f) /// Funcion auxiliar de ordenamiento para insertar un Apellido y Nombre en un arreglo ordenado
{
    while(u>=0&& strcmpi(A[u].Apellido,f.Apellido)>0)
    {
        A[u+1]=A[u];
        u--;
    }
    if(strcmpi(A[u].Apellido,f.Apellido)==0)
    {
        if(strcmpi(A[u].Nombre,f.Nombre)>0)
        {
            A[u+1]=A[u];
            A[u]=f;
        }

    }
    else
    {
        A[u+1]=f;
    }
}

void OrdenarInsercionArregloClientesXApellidoYNombre (Cliente A[], int validos) /// Funcion que ordena por insercion un arreglo de tipo Cliente por Apellido y Nombre
{
    int i=0;

    while (i<validos-1)
    {

        insertarClienteEnArregloOrdenadoXApellidoYNombre(A,i,A[i+1]);
        i++;
    }
}

void pasarArregloAarchivoClientes (Cliente A[], int validos, char nombreArch[]) /// Funcion que guarda en un archivo un arreglo de tipo cliente
{
    FILE *buf=fopen(nombreArch,"wb");
    int i=0;

    if (buf!=NULL)
    {
        while(i<validos)
        {
            fwrite(&A[i],sizeof(Cliente),1,buf);
            i++;
        }

        fclose(buf);
    }
    else
    {
        printf("\nError de apertura del archivo\n");
    }
}


int buscarArregloMenorIdCliente (Cliente A[], int validos, int pos) /// Funcion que busca en un arreglo de clientes el menor id
{
    int posmenor=pos;
    Cliente menor=A[pos];
    int i=pos+1;


    while (i<validos)
    {
        if (A[i].idCliente<menor.idCliente)
        {
            menor=A[i];
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}

void ordenacionArregloSeleccionIdCliente (Cliente A[], int validos) /// Funcion principal que ordena el arreglo de clientes por seleccion segun idcliente
{
    int posmenor;
    Cliente aux;
    int i=0;

    while (i<validos-1)
    {
        posmenor=buscarArregloMenorIdCliente(A,validos,i);
        aux=A[posmenor];
        A[posmenor]=A[i];
        A[i]=aux;
        i++;
    }

}

///--------------------FUNCIONES DE PEDIDOS-------------------------------------------------------

stPedido cargarPedido (stPedido A, int dimension) /// Funcion carga de pedido
{
    int flag=0,i=0,t=0;
    float costoTotal=0, num;
    char control='s';

    do
        {
            printf("\nIngrese el id del cliente\n");
            fflush(stdin);
            flag=scanf("%d",&A.idCliente);
            if(flag==0)
                printf("\nFormato de numero no valido\n");
        }while(flag==0);

    do
        {
            printf("\nIngrese el anio del pedido: (2022-2040)\n");
            fflush(stdin);
            flag=scanf("%d",&A.fechaPedido.anio);
            if(flag==0||A.fechaPedido.anio<2022 || A.fechaPedido.anio>2040)
               {
                   printf("\nFormato de anio no valido\n");
                   flag=0;
               }

        }while(flag==0);

     do
        {
            printf("\nIngrese el mes del pedido (1-12)\n");
            fflush(stdin);
            flag=scanf("%d",&A.fechaPedido.mes);
            if(flag==0|| A.fechaPedido.mes<1 || A.fechaPedido.mes>12)
            {
                printf("\nFormato de mes no valido\n");
                flag=0;
            }

        }while(flag==0);

      do
        {
            printf("\nIngrese el dia del pedido (1-30/31)\n");
            fflush(stdin);
            flag=scanf("%d",&A.fechaPedido.dia);
            if(flag==0||A.fechaPedido.dia<1 ||A.fechaPedido.dia>31)
            {   printf("\nFormato de numero no valido\n");
                flag=0;
            }
            else if (A.fechaPedido.mes==4 ||A.fechaPedido.mes==6||A.fechaPedido.mes==9||A.fechaPedido.mes==11)
            {
                if(A.fechaPedido.dia>30)
                {
                    printf("\nFormato de numero no valido\n");
                    flag=0;
                }
            }
            else if (A.fechaPedido.anio%4==0 && A.fechaPedido.mes==2 && A.fechaPedido.dia>29)
            {
                    printf("\nFormato de numero no valido\n");
                    flag=0;
            }
            else if (A.fechaPedido.anio%4!=0 && A.fechaPedido.mes==2 && A.fechaPedido.dia>28)
            {
                    printf("\nFormato de numero no valido\n");
                    flag=0;
            }
        }while(flag==0);


    while (control=='s'&& i<dimension)
    {
       do
        {
            printf("\nIngrese el nombre del producto\n");
            fflush(stdin);
            gets(A.descripcion[i].producto);
            flag= validarLetras(A.descripcion[i].producto);
            if(flag==1)
                printf("\nFormato de letra no valido\n");
        }while(flag==1);

        do
        {   printf("\nCuantas unidades del producto %s desea agregar al pedido?\n", A.descripcion[i].producto);
            fflush(stdin);
            flag=scanf("%d",&A.descripcion[i].cantidadProducto);
            if(flag==0)
                printf("\nFormato de numero no valido\n");
        }while(flag==0);

         do
        {   printf("\nIngrese el valor unitario del producto %s\n", A.descripcion[i].producto);
            fflush(stdin);
            flag=scanf("%f", &A.descripcion[i].valorUnitario);
            if(flag==0)
                printf("\nFormato de numero no valido\n");
        }while(flag==0);

        printf("\nDesea ingresar mas productos al pedido? s/n\n");
        fflush(stdin);
        scanf("%c", &control);
        i++;
    }
    A.cantidadProductosDistintosPedido=i;

    while (t<i)
    {
        num=A.descripcion[t].cantidadProducto * A.descripcion[t].valorUnitario;
        costoTotal= (float)num + (float)costoTotal;
        t++;
    }
    A.costoPedido=(float)costoTotal;

    A.estadoPedido=0;

return A;
}

void guardarPedidoEnArchivo(char nombreArchivoPedidos[]) /// Funcion para guardar los pedidos en el archivo de Pedidos
{
    FILE*buf1=fopen(nombreArchivoPedidos,"rb");
    stPedido e;
    long int idPedido=1;
    char control='s';

    if(buf1==NULL)
    {
        buf1=fopen(nombreArchivoPedidos,"wb");

        if(buf1!=NULL)
        {
             while (control=='s')
                {
                    e=cargarPedido(e,30);
                    e.idPedido=idPedido++;
                    fwrite(&e,sizeof(stPedido),1, buf1);
                    printf("\nDesea seguir ingresando pedidos? s/n");
                    fflush(stdin);
                    scanf("%c",&control);
                }

        fclose(buf1);
        }
        else
            printf("\nError de datos - El archivo no pudo ser abierto\n");
    }
    else
    {
            buf1=fopen(nombreArchivoPedidos,"ab");

            if(buf1!=NULL)
            {
                idPedido=cantidadRegistrosArchivoGenerica(nombreArchivoPedidos,sizeof(stPedido))+1;
                while(control=='s')
                {
                    e=cargarPedido(e,30);
                    e.idPedido=idPedido;
                    fwrite(&e,sizeof(stPedido),1, buf1);
                    printf("\nDesea seguir ingresando pedidos? s/n");
                    fflush(stdin);
                    scanf("%c",&control);
                    idPedido++;
                }
            fclose(buf1);
            }
            else
                printf("\nError de datos - El archivo no pudo ser abierto\n");
    }

}

void mostrarUnaDescripcionPedido (stDescripcion e) /// Funcion que muestra una descripcion de un pedido
{
        printf("\nProducto: %s\n", e.producto);
        printf("\nUnidades de %s: %d\n", e.producto,e.cantidadProducto);
        printf("\nValor unitario de %s : $%.2f\n", e.producto,e.valorUnitario);
}

void mostrarDescripcionPedido (stDescripcion descrip[], int validos) /// Funcion que muestra la descripcion de los productos del pedido
{
    int i=0;

    while (i<validos)
    {
        mostrarUnaDescripcionPedido(descrip[i]);
        i++;
    }

}

void mostrarPedido (stPedido e) /// Funcion que muestra un pedido
{
    int i=0;

    printf("\n------------------------------------------\n");
    printf("\nId del pedido: %li\n", e.idPedido);
    printf("\nId del cliente: %i\n", e.idCliente);
    printf("\nFecha del pedido: %d/%d/%d\n", e.fechaPedido.dia,e.fechaPedido.mes,e.fechaPedido.anio);

    mostrarDescripcionPedido(e.descripcion,e.cantidadProductosDistintosPedido);

    printf("\nCosto Total del pedido: $%.2f\n", e.costoPedido);
    if (e.estadoPedido==0)
    {
        printf("\nEstado del pedido: activo\n");
    }
    else
    {
        printf("\nEstado del pedido: anulado\n");
    }
    printf("\n------------------------------------------\n");

}

void mostrarArchivoPedidos (char nombreArchivoPedidos[]) /// Funcion que muestra el archivo de pedidos
{
    FILE *buf=fopen(nombreArchivoPedidos,"rb");
    stPedido e;

    if (buf!=NULL)
    {
        while (fread(&e,sizeof(stPedido),1,buf)>0)
        {
            mostrarPedido(e);
        }

       fclose(buf);
    }
    else
    {
        printf("\nError de lectura de datos\n");
    }
}

void mostrarPedidosXIdClienteArchivo (char nombreArchivo[], int id) /// Funcion que muestra los pedidos por idCliente
{
    FILE *buf=fopen(nombreArchivo,"rb");
    stPedido e;
    int flag=0;
    long int cant=0;

    if(buf!=NULL)
    {
        while(fread(&e,sizeof(stPedido),1,buf)>0)
            {
                if (e.idCliente==id)
                {
                    cant=e.idPedido;
                    mostrarPedido(e);
                    flag=1;
                }
            }
        if(flag==0)
                {
                    printf("\nNo se encontraron pedidos\n");
                }

        fclose(buf);
    }
    else
    {
        printf("\nError en la apertura del archivo\n");
    }

}

stPedido modificarPedido(stPedido A, int validos) /// Funcion que modifica un pedido
{
    char control='s';
    int opcion;

    while (control=='s')
    {
        int i=0;
        printf("\nQue datos del pedido desea modificar?\n");
        printf("\n1:Fecha del pedido\n2:Producto\n3:Unidades del producto\n4:Valor Unitario del producto\n");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion)
        {
            int flag=0;

            case 1:
                    do
                    {
                        printf("\nIngrese el anio del pedido: (2022-2040)\n");
                        fflush(stdin);
                        flag=scanf("%d",&A.fechaPedido.anio);
                        if(flag==0||A.fechaPedido.anio<2022 || A.fechaPedido.anio>2040)
                           {
                               printf("\nFormato de anio no valido\n");
                               flag=0;
                           }

                    }while(flag==0);

                     do
                    {
                        printf("\nIngrese el mes del pedido (1-12)\n");
                        fflush(stdin);
                        flag=scanf("%d",&A.fechaPedido.mes);
                        if(flag==0|| A.fechaPedido.mes<1 || A.fechaPedido.mes>12)
                        {
                            printf("\nFormato de mes no valido\n");
                            flag=0;
                        }

                    }while(flag==0);

                     do
                    {
                        printf("\nIngrese el dia del pedido (1-30/31)\n");
                        fflush(stdin);
                        flag=scanf("%d",&A.fechaPedido.dia);
                        if(flag==0||A.fechaPedido.dia<1 ||A.fechaPedido.dia>31)
                        {   printf("\nFormato de numero no valido\n");
                            flag=0;
                        }
                        else if (A.fechaPedido.mes==4 ||A.fechaPedido.mes==6||A.fechaPedido.mes==9||A.fechaPedido.mes==11)
                        {
                            if(A.fechaPedido.dia>30)
                            {
                                printf("\nFormato de numero no valido\n");
                                flag=0;
                            }
                        }
                        else if (A.fechaPedido.anio%4==0 && A.fechaPedido.mes==2 && A.fechaPedido.dia>29)
                        {
                                printf("\nFormato de numero no valido\n");
                                flag=0;
                        }
                        else if (A.fechaPedido.anio%4!=0 && A.fechaPedido.mes==2 && A.fechaPedido.dia>28)
                        {
                                printf("\nFormato de numero no valido\n");
                                flag=0;
                        }
                    }while(flag==0);
                    break;
            case 2:
                    while (i<validos)
                    {
                       mostrarUnaDescripcionPedido(A.descripcion[i]);
                       printf("\nDesea modificar este producto s/n?\n");
                       fflush(stdin);
                       scanf("%c", &control);
                       if(control=='s')
                       {
                               do
                            {
                                printf("\nIngrese el nombre del producto\n");
                                fflush(stdin);
                                gets(A.descripcion[i].producto);
                                flag= validarLetras(A.descripcion[i].producto);
                                if(flag==1)
                                    printf("\nFormato de letra no valido\n");
                            }while(flag==1);
                       }
                       i++;
                    }
                    break;
            case 3:
                   while (i<validos)
                    {
                       mostrarUnaDescripcionPedido(A.descripcion[i]);
                       printf("\nDesea modificar la cantidad de unidades de este producto? s/n\n");
                       fflush(stdin);
                       scanf("%c", &control);
                       if(control=='s')
                       {
                           do
                            {   printf("\nCuantas unidades del producto %s desea agregar al pedido?\n", A.descripcion[i].producto);
                                fflush(stdin);
                                flag=scanf("%d",&A.descripcion[i].cantidadProducto);
                                if(flag==0)
                                printf("\nFormato de numero no valido\n");
                            }while(flag==0);
                       }
                       i++;
                    }
                    break;
            case 4:
                   while (i<validos)
                    {
                       mostrarUnaDescripcionPedido(A.descripcion[i]);
                       printf("\nDesea modificar este producto? s/n\n");
                       fflush(stdin);
                       scanf("%c", &control);
                       if(control=='s')
                       {
                           do
                            {   printf("\nIngrese el valor unitario del producto %s\n", A.descripcion[i].producto);
                                fflush(stdin);
                                flag=scanf("%f", &A.descripcion[i].valorUnitario);
                                if(flag==0)
                                    printf("\nFormato de numero no valido\n");
                            }while(flag==0);
                       }
                       i++;
                    }
                    break;
        }
        printf("\nDesea modificar algun otro dato de este pedido? s/n\n");
        fflush(stdin);
        scanf("%c", &control);

    }
return A;
}

long int buscarPosicionPedidoArchivoXidPedido (char nombreArch[], long int idPedido) /// Funcion que retorna la posicion de un idPedido en el archivo
{
    FILE *buf=fopen(nombreArch,"rb");
    stPedido e;
    long int cant=0;
    int flag=0;

    if(buf!=NULL)
    {
        while(flag==0 && fread(&e, sizeof(stPedido),1,buf)>0)
        {
            if (e.idPedido==idPedido)
            {
                cant= ftell(buf)/sizeof(stPedido);
            }
        }
        fclose(buf);
    }
    else
        printf("\nError de apertura del archivo\n");

    return cant;
}

void modificarPedidoenArchivoXidPedido (char nombreArch[], int idPedido) /// Funcion que modifica en el archivo los datos de un pedido
{
    FILE *buf=fopen(nombreArch,"r+b");
    stPedido e;
    int flag=0;

    long int cant=buscarPosicionPedidoArchivoXidPedido(nombreArch,idPedido);

    if (buf!=NULL&&cant!=0)
    {
            if (idPedido==0)
            {
                printf("\nPedido inexistente\n");
            }
            else
            {
                while(flag==0 && fread(&e,sizeof(stPedido),1,buf)>0)
                {
                    if (e.idPedido==idPedido)
                    {
                        mostrarPedido(e);
                        fseek(buf,sizeof(stPedido)*(idPedido-1),SEEK_SET);
                        fread(&e,sizeof(stPedido),1,buf);
                        e=modificarPedido(e,e.cantidadProductosDistintosPedido);
                        fseek(buf,sizeof(stPedido)*(idPedido-1),SEEK_SET);
                        fwrite(&e,sizeof(stPedido),1,buf);
                        flag=1;
                    }
                }
            }
    fclose(buf);
    }
    else
    {
        printf("\nError en la lectura del archivo\n");
    }
}

/// -------------FUNCIONES DE LISTADOS Y ESTADISTICAS---------------------------

int pasarArchivoPedidosAarreglo (char nombreArch[], stPedido A[], int dimension) /// Funcion que pasa los datos de un archivo de tipo pedido a un arreglo
{
    FILE *buf=fopen(nombreArch,"rb");

    stPedido e;
    int i=0;

    if(buf!=NULL)
    {
        while (fread(&e,sizeof(stPedido),1,buf)>0&& i<dimension)
        {
            A[i]=e;
            i++;
        }

    fclose(buf);
    }
    else
    {
        printf("\nError de apertura del archivo\n");
    }
    return i;

}


int buscarMenorFechaPedido (stPedido A[], int validos, int pos) /// Funcion que busca la menor fecha de pedido en el arreglo de pedidos
{
    int posmenor=pos;
    stPedido FechaMenor=A[pos];
    int i=pos +1;

    while(i<validos)
    {
        if(A[i].fechaPedido.anio<FechaMenor.fechaPedido.anio)
        {
            FechaMenor=A[i];
            posmenor=i;
        }
        else if(A[i].fechaPedido.anio==FechaMenor.fechaPedido.anio)
        {
            if(A[i].fechaPedido.mes<FechaMenor.fechaPedido.mes)
            {
                FechaMenor=A[i];
                posmenor=i;
            }
            else if(A[i].fechaPedido.mes==FechaMenor.fechaPedido.mes)
            {
                if(A[i].fechaPedido.dia<FechaMenor.fechaPedido.dia)
                {
                    FechaMenor=A[i];
                    posmenor=i;
                }
            }
        }
        i++;
    }
    return posmenor;
}

void ordenarPedidosXFechaAntiguaAReciente (stPedido A[], int validos) /// Funcion que ordena los pedidos del arreglo por seleccion de menor a mayor
{
    int posmenor;
    stPedido aux;
    int i=0;

    while (i<validos)
    {
        posmenor=buscarMenorFechaPedido(A, validos, i);
        aux=A[posmenor];
        A[posmenor]=A[i];
        A[i]=aux;
        i++;
    }
}

void mostrarArregloPedidos (stPedido A[], int validos) /// Funcion que muestra un arreglo de tipo Pedidos
{
    int i=0;

    for (i=0;i<validos;i++)
    {
        printf("\nPedido numero %d\n",i);
        printf("----------------------");
        mostrarPedido(A[i]);
        printf("----------------------");
    }
}

void pasarArregloAarchivoPedidos (stPedido A[], int validos, char nombreArch[]) /// Funcion que guarda en un archivo un arreglo de tipo pedidos
{
    FILE *buf=fopen(nombreArch,"wb");
    int i=0;

    if (buf!=NULL)
    {
        while(i<validos)
        {
            fwrite(&A[i],sizeof(stPedido),1,buf);
            i++;
        }

        fclose(buf);
    }
    else
    {
        printf("\nError de apertura del archivo\n");
    }
}

void cargarPedidosXIdClienteEnArchivo (char nombreArchivo[], int id, char nombrearch[]) /// Funcion que los carga los pedidos de un cliente en un archivo
{
    FILE *buf=fopen(nombreArchivo,"rb");
    FILE *buf1=fopen(nombrearch,"wb");
    stPedido e;
    int flag=0;

    if(buf!=NULL&&buf1!=NULL)
    {
        while(fread(&e,sizeof(stPedido),1,buf)>0)
            {
                if (e.idCliente==id)
                {
                    fwrite(&e, sizeof(stPedido),1,buf1);
                    flag=1;
                }
            }
        if(flag==0)
                {
                    printf("\nNo se encontraron pedidos\n");
                }

        fclose(buf);
        fclose(buf1);
    }
    else
    {
        printf("\nError en la apertura del archivo\n");
    }

}

int pasarPedidosArchivoAarregloDeCantPedidos (char archPedidos[], char archClientes[], PedidosXCliente P[], int dimension) /// Funcion que pasa los idClientes y
///su correspondientes cantidades de pedido a una struc de tipo PedidosXCliente
{
    FILE *buf=fopen(archPedidos,"rb");
    FILE *buf1=fopen(archClientes,"rb");
    stPedido e;
    Cliente a;
    int i=0,t, flag=0;

    if(buf!=NULL&&buf1!=NULL)
    {
        while(i<dimension)
        {
            t=0;
            rewind(buf);
            while(fread(&e, sizeof(stPedido),1,buf)>0)
            {
                if (e.idCliente==i+1)
                {
                    t++;
                }
            }
            P[i].idCliente=i+1;
            P[i].cantPedidos=t;
            i++;

        }
         i=0;
         while(fread(&a, sizeof(Cliente),1,buf1)>0&&i<dimension)
            {

                if(a.idCliente==i+1)
                {
                    strcpy(P[i].Apellido,a.Apellido);
                    strcpy(P[i].Nombre,a.Nombre);
                }
                i++;
            }
    fclose(buf);
    fclose(buf1);
    }
    else
        printf("\nError de apertura del archivo\n");

    return i;
}

void mostrarCantPedidosXUnCliente (PedidosXCliente A) /// Funcion que muestra la cantidad de pedidos de un cliente
{
        printf("\n--------------------------------------------------\n");
        printf("\nIdCliente: %d\n", A.idCliente);
        printf("\nApellido del cliente: %s\n", A.Apellido);
        printf("\nNombre del cliente: %s\n", A.Nombre);
        printf("\nNumero de pedidos del cliente %d:  %d\n", A.idCliente,A.cantPedidos);
        printf("\n--------------------------------------------------\n");
}

void mostrarArregloTipoPedidosXCliente(PedidosXCliente A[], int validos) /// Funcion que muestra un arreglo de tipo PedidosXCliente
{
    int i=0;

    while(i<validos)
    {
        mostrarCantPedidosXUnCliente (A[i]);
        i++;
    }
}

int buscarClienteConMayorCantPedidos (PedidosXCliente A[], int validos, int pos) /// Funcion auxiliar que busca en un arreglo el cliente con mas pedidos
{
    int posmayor=pos;
    PedidosXCliente mayor=A[pos];
    int i=pos+1;


    while (i<validos)
    {
        if (A[i].cantPedidos>mayor.cantPedidos)
        {
            mayor=A[i];
            posmayor=i;
        }
        i++;
    }
    return posmayor;
}

void ordenacionArregloSeleccionClientesXcantPedidos (PedidosXCliente A[], int validos) /// Funcion principal que ordena el arreglo segun la cantidad de pedidos de los clientes
{
    int posmayor;
    PedidosXCliente aux;
    int i=0;

    while (i<validos-1)
    {
        posmayor=buscarClienteConMayorCantPedidos(A,validos,i);
        aux=A[posmayor];
        A[posmayor]=A[i];
        A[i]=aux;
        i++;
    }

}

void mostrarTopTenMejoresClientesArreglo (PedidosXCliente A[], int validos) /// Funcion que muestra los primeros diez mejores clientes del arreglo
{
    int i=0;

    ordenacionArregloSeleccionClientesXcantPedidos(A,validos);
    while(i<10 && i<validos)
    {
        printf("\nCliente en el puesto numero %d\n",i+1);
        mostrarCantPedidosXUnCliente (A[i]);
        i++;
    }

}

void mostrarPeorClienteXCantPedidos (PedidosXCliente A[], int validos) /// Funcion que busca el peor cliente en el arreglo segun cantidad de pedidos
{
    int i=validos;
    ordenacionArregloSeleccionClientesXcantPedidos(A,validos);
    mostrarCantPedidosXUnCliente(A[i-1]);
}

void pasarArregloAarchivoCantPedidosXCliente (PedidosXCliente A[], int validos, char nombreArch[]) /// Funcion que guarda en un archivo un arreglo de tipo pedidos por cliente
{
    FILE *buf=fopen(nombreArch,"wb");
    int i=0;

    if (buf!=NULL)
    {
        while(i<validos)
        {
            fwrite(&A[i],sizeof(PedidosXCliente),1,buf);
            i++;
        }

        fclose(buf);
    }
    else
    {
        printf("\nError de apertura del archivo\n");
    }
}

void mostrarArchivoPedidosXCliente (char nombreArchivoPedidos[]) /// Funcion que muestra el archivo de pedidos x cliente
{
    FILE *buf=fopen(nombreArchivoPedidos,"rb");
    PedidosXCliente e;

    if (buf!=NULL)
    {
        while (fread(&e,sizeof(stPedido),1,buf)>0)
        {
            mostrarCantPedidosXUnCliente(e);
        }

       fclose(buf);
    }
    else
    {
        printf("\nError de lectura de datos\n");
    }
}
