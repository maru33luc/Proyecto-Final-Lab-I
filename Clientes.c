#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "math.h"
#include <time.h>
#include "Clientes.h"
#include "Pedidos.h"
#include "Listados.h"
#include <windows.h>

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

    if(strlen(Mail)==0)
        flag=1;
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
            printf("\nIngrese el apellido del cliente o presione Enter para salir\n");
            fflush(stdin);
            gets(A.Apellido);
            if(strlen(A.Apellido)==0)
                return;
            else
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
    Cliente e,a,b;
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
                    a=cargarUnCliente(a);
                    if(strlen(a.Apellido)==0)
                        fclose(buf);
                    else
                    {
                        e=a;
                        e.idCliente=numCliente++;
                        fwrite(&e,sizeof(Cliente),1, buf);
                    }
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
                        printf("\nIngrese el DNI del cliente a ingresar en la base de datos o presione Enter para salir\n");
                        fflush(stdin);
                        gets(num);
                        if(strlen(num)==0)
                        {
                            flag==0;
                            fclose(buf);
                            return;
                        }
                        flag=validarNumString(num);
                    }while(flag==1);

                    flag=verificarPresenciaClienteBase(nombreArch,num);

                    if (flag==0)
                    {
                        printf("\nEse numero de DNI no corresponde a ningun cliente de la base de datos\n");

                        a=cargarUnCliente(a);
                        if(strlen(a.Apellido)==0)
                            fclose(buf);
                        else
                        {
                            e=a;
                            e.idCliente=numCliente;
                            fwrite(&e,sizeof(Cliente),1, buf);
                            numCliente++;
                        }
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
    printf("\nApellido del cliente: %s\n", al.Apellido);
    printf("\nNombre del cliente: %s\n", al.Nombre);
    printf("\nNumero de DNI del cliente: %s\n", al.DNI);
    printf("\nNumero de cliente: %d\n", al.idCliente);
    printf("\nNumero de movil del cliente: %s\n", al.Movil);
    printf("\nCalle del domicilio del cliente: %s\n", al.Domicilio.Calle);
    printf("\nAltura de la calle del domicilio del cliente: %s\n", al.Domicilio.Numero);
    printf("\nMail del cliente: %s\n", al.Mail);
    printf("\nEstado del cliente (0=activo; 1=inactivo): %d\n", al.Estado_del_cliente);
    printf("\n---------------------------------------------------------\n");

}

void mostrarArchivoClientes (char nombreArch[]) /// Mostrar el archivo de clientes
{
    FILE *buf=fopen(nombreArch,"rb");
    Cliente e;
    int cant=0;

    if (buf!=NULL)
    {
        while (fread(&e,sizeof(Cliente),1,buf)>0)
        {
            mostrarUnCliente(e);
            cant=ftell(buf)/sizeof(Cliente);
            if (cant%2==0)
                system("pause");
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
        printf("\n1:Apellido\n2:Nombre\n3:DNI\n4:Movil\n5:Calle del domicilio\n6:Altura de la calle del domicilio\n7:Mail\n8:Activar cliente\n9:Salir\n");
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
            case 8:
                    if(a.Estado_del_cliente==0)
                    {
                        printf("\nEl cliente ya se encuentra activo\n");
                        break;
                    }
                    else
                    {
                        a.Estado_del_cliente=0;
                        break;
                    }

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
                fclose(buf);
                return;
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
        mostrarUnCliente(A[i]);
        if(i%2==0)
            system("pause");
    }
}

void insertarClienteEnArregloOrdenadoXApellidoYNombre (Cliente A[],int u,Cliente f) /// Funcion auxiliar de ordenamiento para insertar un Apellido y Nombre en un arreglo ordenado
{
    while(u>=0&& strcmpi(A[u].Apellido,f.Apellido)>0)
    {
        A[u+1]=A[u];
        u--;
    }
    while(u>=0 &&strcmpi(A[u].Apellido,f.Apellido)==0)
    {
        if(strcmpi(A[u].Nombre,f.Nombre)>0)
        {
            A[u+1]=A[u];
            u--;
        }
        else
        {
            A[u+1]=f;
            return;
        }

    }
    A[u+1]=f;
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

void mostrarUnClienteGo(Cliente al[], int y) /// MOSTRAR UN CLIENTE CON GOTO (FORMATO TABLA)
{
    int i=0;
    int t=6;

    gotoxy(2,3); printf("|APELLIDO");
    gotoxy(20,3); printf("|NOMBRE");
    gotoxy(40,3); printf("|DNI");
    gotoxy(45,3); printf("|ID");
    gotoxy(53,3); printf("|MOVIL");
    gotoxy(64,3); printf("|DOMICILIO CALLE");
    gotoxy(80,3); printf("|NUMERO");
    gotoxy(88,3); printf("|MAIL");
    gotoxy(114,3); printf("|ESTADO CLIENTE");

    gotoxy(0,4);printf("\n----------------------------------------------------------------------------------------------------------------------\n");

    while(i<y)
    {

    gotoxy(2,t); printf("| %s", al[i].Apellido);
    gotoxy(20,t); printf("| %s", al[i].Nombre);
    gotoxy(35,t);printf("| %s", al[i].DNI);
    gotoxy(45,t);printf("| %d", al[i].idCliente);
    gotoxy(53,t);printf("| %s", al[i].Movil);
    gotoxy(64,t);printf("| %s", al[i].Domicilio.Calle);
    gotoxy(80,t);printf("| %s", al[i].Domicilio.Numero);
    gotoxy(88,t);printf("| %s", al[i].Mail);
    gotoxy(114,t);printf("| %d", al[i].Estado_del_cliente);
    t++;
    i++;
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
}

void gotoxy (int x, int y){

    HANDLE manipulador;
    COORD coordenadas;
    manipulador = GetStdHandle (STD_OUTPUT_HANDLE);
    coordenadas.X = x;
    coordenadas.Y = y;
    SetConsoleCursorPosition (manipulador, coordenadas);
}
