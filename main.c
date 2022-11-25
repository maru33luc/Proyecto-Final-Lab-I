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

int main()
{

char nombreArch[20]="ArchivoX";
char archOrdenApellido[20]="ListaOrdenClientesXApellidoYNombre";
char archOrdenIdCliente[30]="ListaOrdenXIdCliente";
char num[30];
int cant;
int validos;
Cliente f[100];

char nombreArchivoPedidos[30]="ArchivoPedidos";
char pedidos[30]="Pedidos";
int flag=0,id;
long int cantx,cantdni,dnip;
char dninum[30];

char archPedidosXFecha[30]="ListaPedidosOrdenFecha";
char archPedidosXCliente[30]="ListaPedidosXCliente";
stPedido Orden[30];
int validosOrden;
int dimension6;

PedidosXCliente P[100];
int validos6,idx;
char archTopTenClientes[30]="ListaTopTenClientes";

int opcionPantallaPrincipal;
char controlopciones='s';
int idxx,idp, opcion2;

const char *const verde = "\033[0;40;32m";
const char *const subrayado_fazul_verde = "\033[4;44;32m";
const char *const normal = "\033[0m";
const char *const rojo = "\033[0;40;31m";
const char *const azul = "\033[0;40;34m";


do
{
    system("cls");
    printf("\n%sIngrese la opcion a la cual desea ingresar:\n\n[1]-Clientes \n \n[2]-Pedidos\n \n[3]-Salir\n\n%s",azul, normal);
    scanf("%d", &opcionPantallaPrincipal);
    if(opcionPantallaPrincipal==3)
        return;
    switch (opcionPantallaPrincipal)
{
int opcion1;
    case 1:
            system("cls");
            printf("\n%sIngrese la opcion deseada\n \n[1]-Alta Clientes \n\n[2]-Baja Clientes\n \n[3]-Modificacion de clientes\n \n[4]-Listar Clientes\n \n[0]-salir\n\n%s", azul, normal);
            fflush(stdin);
            scanf("%d",&opcion1);
            switch(opcion1)
                {
                case 1:
                        guardarClientesEnArchivo(nombreArch);
                        break;
                case 2:
                        system("cls");
                        printf("\n%sIngrese el DNI del cliente a buscar o Enter para salir\n\n%s", azul, normal);
                        fflush(stdin);
                        gets(num);
                        if(strlen(num)==0)
                            break;
                        else
                        {
                            cant=buscarIdClienteXDni(nombreArch,num);
                            bajaCliente(nombreArch,cant);
                            break;
                        }


                case 3:
                        system("cls");
                        printf("\n%sIngrese el DNI del cliente a buscar o presione Enter para salir\n\n%s", azul, normal);
                        fflush(stdin);
                        gets(num);
                        if(strlen(num)==0)
                            break;
                        else
                        {
                        cant=buscarIdClienteXDni(nombreArch,num);
                        modificarClienteenArchivoXidCliente(nombreArch,cant);
                        mostrarRegistroClienteXIdCliente(nombreArch,cant);
                        break;
                        }

                case 4:
                        system("cls");
                        printf("\n%sIngrese la opcion deseada\n \n[1]-Lista clientes ordenados por apellido y nombre \n\n[2]-Lista clientes ordenados por idCliente\n \n[3]-Listar cliente por idCliente \n\n[4]-Listar cliente por DNI \n\n[0]-Salir\n\n%s", azul, normal);
                        scanf("%d", &opcion1);
                        validos=pasarArchivoClientesAarreglo(nombreArch,f,100);

                        switch(opcion1)
                        {
                        case 1:
                                system("cls");
                                OrdenarInsercionArregloClientesXApellidoYNombre(f,validos);
                                system("cls");
                                printf("\nClientes por orden de Apellido y Nombre\n");
                                mostrarUnClienteGo(f,validos);
                                system("pause");
                                pasarArregloAarchivoClientes(f,validos,archOrdenApellido);
                                break;
                        case 2:
                                system("cls");
                                ordenacionArregloSeleccionIdCliente(f,validos);
                                system("cls");
                                printf("\nClientes por orden de idCliente\n");
                                printf("\n");
                                mostrarUnClienteGo(f,validos);
                                system("pause");
                                pasarArregloAarchivoClientes(f,validos,archOrdenIdCliente);
                                break;
                        case 3:
                                system("cls");
                                printf("%s\nIngrese el idCliente\n\n%s", azul, normal);
                                scanf("%d", &idx);
                                mostrarRegistroClienteXIdCliente(nombreArch,idx);
                                break;
                        case 4:
                                system("cls");
                                printf("\n%sIngrese el DNI del cliente\n\n%s", azul, normal);
                                fflush(stdin);
                                gets(dninum);
                                idxx=buscarIdClienteXDni(nombreArch,dninum);
                                mostrarRegistroClienteXIdCliente(nombreArch,idxx);
                                break;

                        }
                        break;
                }
                break;
    case 2:
            system("cls");
            printf("\n%sIngrese la opcion deseada\n \n[1]-Alta Pedido\n \n[2]-Baja Pedidos \n\n[3]-Modificacion de pedidos\n \n[4]-Listados \n\n[0]-salir\n\n%s", azul, normal);
            fflush(stdin);
            scanf("%d",&opcion1);
            switch(opcion1)
                {
                case 1:
                        guardarPedidoEnArchivo(nombreArchivoPedidos);
                        break;
                case 2:
                        system("cls");
                        printf("\n%sIngrese el id del pedido que desea dar de baja o 0 para salir\n\n%s", azul, normal);
                        scanf("%d", &id);
                        if(id==0)
                            break;
                        else
                        {
                             bajaPedido(nombreArchivoPedidos,id);
                             mostrarPedidoXidPedidoArchivo (nombreArchivoPedidos,id);
                             break;
                        }

                case 3:
                        system("cls");
                        do
                            {
                                printf("\n\%sIngrese el id del pedido que desea modificar o 0 para salir\n\n%s", azul, normal);
                                fflush(stdin);
                                flag=scanf("%li",&cantx);
                                if(flag==0)
                                        printf("\nFormato de numero no valido\n");
                            }while(flag==0);

                        if(cantx==0)
                                break;
                        else
                        {
                            system("cls");
                            modificarPedidoenArchivoXidPedido(nombreArchivoPedidos,cantx);
                            printf("\nPedido numero %d\n", cantx);
                            mostrarPedidoXidPedidoArchivo (nombreArchivoPedidos,cantx);
                            break;
                        }


                case 4:
                        system("cls");
                        printf("\n%sIngrese la opcion deseada \n\n[1]-Mostrar un pedido por idPedido o DNI\n \n[2]-Pedidos por Orden Fecha\n \n[3]-Pedidos por Cliente\n \n[4]-Top Ten Mejores Clientes\n \n[5]-Peor Cliente\n\n%s", azul, normal);
                        fflush(stdin);
                        scanf("%d", &opcion1);
                        switch (opcion1)
                        {
                        case 1:
                                system("cls");
                                printf("\n%s\n[1]-Mostrar el pedido por idPedido\n \n[2]-Mostrar pedido por DNI del cliente\n\n%s", azul, normal);
                                scanf("%d", &opcion2);
                                switch(opcion2)
                                {
                                case 1:
                                        system("cls");
                                        printf("\n%sIngrese el id\n\n%s", azul, normal);
                                        scanf("%d", &idp);
                                        mostrarPedidoXidPedidoArchivo(nombreArchivoPedidos,idp);
                                        printf("\n\n\n\n");
                                        system("pause");
                                        break;
                                case 2:
                                        system("cls");
                                        printf("\n%sIngrese el DNI del cliente\n\n%s", azul, normal);
                                        fflush(stdin);
                                        gets(num);
                                        idp=buscarIdClienteXDni(nombreArch,num);
                                        mostrarPedidosXIdClienteArchivo(nombreArchivoPedidos,idp);
                                        break;
                                }break;

                        case 2:
                                system("cls");
                                validosOrden=pasarArchivoPedidosAarreglo(nombreArchivoPedidos,Orden,30);
                                ordenarPedidosXFechaAntiguaAReciente(Orden,validosOrden);
                                pasarArregloAarchivoPedidos(Orden,validosOrden,archPedidosXFecha);
                                printf("\nPedidos por orden de fecha de antiguos a recientes\n");
                                mostrarArchivoPedidos(archPedidosXFecha);
                                break;
                        case 3:
                                system("cls");
                                cargarPedidosXIdClienteEnArchivo(nombreArchivoPedidos,3,archPedidosXCliente);
                                printf("\nPedidos por Cliente\n");
                                mostrarArchivoPedidos(archPedidosXCliente);
                                break;
                        case 4:
                                system("cls");
                                dimension6=cantidadRegistrosArchivoGenerica(nombreArch,sizeof(Cliente));
                                validos6=pasarPedidosArchivoAarregloDeCantPedidos(nombreArchivoPedidos,nombreArch,P,dimension6);
                                ordenacionArregloSeleccionClientesXcantPedidos(P,validos6);
                                printf("\nTop Ten Mejores Clientes por cantidad de pedidos\n");
                                mostrarTopTenMejoresClientesArreglo (P,validos6);
                                break;
                        case 5:
                                system("cls");
                                pasarArregloAarchivoCantPedidosXCliente(P,validos6,archTopTenClientes);
                                printf("\nCliente con menor cantidad de pedidos\n");
                                mostrarPeorClienteXCantPedidos (P,validos6);
                                break;
                        }
                }
                break;
}
system("cls");
printf("\n%sDesea seguir en el sistema? s/n\n\n%s", azul, normal);
fflush(stdin);
scanf("%c", &controlopciones);
}while(controlopciones=='s');


    return 0;
}

