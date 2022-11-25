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


stPedido cargarPedido (stPedido A, int dimension) /// Funcion carga de pedido
{
    int flag=0,i=0,t=0;
    float costoTotal=0, num;
    char control='s';

    do
        {
            printf("\nIngrese el id del cliente o presione Enter para salir\n");
            fflush(stdin);
            flag=scanf("%d",&A.idCliente);
            if(A.idCliente==0)
            {
                flag=1;
                return;
            }
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

            printf("\nIngrese el nombre del producto\n");
            fflush(stdin);
            gets(A.descripcion[i].producto);


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
                    if(e.idCliente==0)
                        fclose(buf1);
                    else
                    {
                        e.idPedido=idPedido;
                        fwrite(&e,sizeof(stPedido),1, buf1);
                    }
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
                    if(e.idCliente==0)
                        fclose(buf1);
                    else
                    {
                        e.idPedido=idPedido;
                        fwrite(&e,sizeof(stPedido),1, buf1);
                    }

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

/*void mostrarDescripcionPedido (stDescripcion descrip[], int validos) /// Funcion que muestra la descripcion de los productos del pedido
{
    int i=0;

    while (i<validos)
    {
        mostrarUnaDescripcionPedidoGo(descrip[i]);
        system("pause");
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
*/
void mostrarArchivoPedidos (char nombreArchivoPedidos[]) /// Funcion que muestra el archivo de pedidos
{
    FILE *buf=fopen(nombreArchivoPedidos,"rb");
    stPedido e;
    int cant=0;

    if (buf!=NULL)
    {
        while (fread(&e,sizeof(stPedido),1,buf)>0)
        {
            mostrarPedidoGo(e);
            cant=ftell(buf)/sizeof(stPedido);
            if (cant%2==0)
            {
                printf("\n\n\n\n\n");
                system("pause");
            }

        }

       fclose(buf);
    }
    else
    {
        printf("\nError de lectura de datos\n");
    }
}

void bajaPedido (char nombreArch[], int id) /// Funcion para dar de baja un pedido por idPedido
{
    FILE *buf=fopen(nombreArch,"r+b");
    stPedido e;
    int opcion;

    if (buf!=NULL&& id!=0)
    {
         mostrarPedidoXidPedidoArchivo(nombreArch,id);
         fseek(buf,sizeof(stPedido)*(id-1),SEEK_SET);
         fread(&e,sizeof(stPedido),1,buf);
         if (e.estadoPedido==0)
         {
             printf("\nDesea dar de baja al pedido? Presione 1 para hacerlo o cualquier otra tecla para salir\n");
             scanf("%d", &opcion);
             if (opcion==1)
             {
                 e.estadoPedido=1;
                 fseek(buf,sizeof(stPedido)*(id-1),SEEK_SET);
                 fwrite(&e,sizeof(stPedido),1,buf);
             }
         }
         else if(e.estadoPedido==1)
         {
             printf("\nEl pedido ya se encuentra inactivo\n");
         }
    fclose(buf);
    }
    else if(buf==NULL)
    {
        printf("\nError en la lectura del archivo\n");
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
                    mostrarPedidoGo(e);
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

void mostrarPedidoXidPedidoArchivo (char nombreArchivo[], int id) /// Funcion que muestra el pedido por idPedido
{
    FILE *buf=fopen(nombreArchivo,"rb");
    stPedido e;
    int flag=0;

    if(buf!=NULL)
    {
        while(fread(&e,sizeof(stPedido),1,buf)>0)
            {
                if (e.idPedido==id)
                {
                    mostrarPedidoGo(e);
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
        printf("\n1:Fecha del pedido\n2:Producto\n3:Unidades del producto\n4:Valor Unitario del producto\n5:Activar pedido\n");
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
                                printf("\nIngrese el nombre del producto\n");
                                fflush(stdin);
                                gets(A.descripcion[i].producto);
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
            case 5:
                    if(A.estadoPedido==0)
                    {
                        printf("\nEl pedido ya se encontraba activo\n");
                        break;
                    }
                    else
                    {
                        A.estadoPedido=0;
                        break;
                    }

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
                        mostrarPedidoGo(e);
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



void mostrarUnaDescripcionPedidoGo (stDescripcion e, int y) /// MOSTRAR UNA DESCRIPCION DE PEDIDO CON GOTO (FORMATO TABLA)
{
   int i=0;

      /*  gotoxy(2,3);printf("|PRODUCTO");
        gotoxy(20,3);printf("|UNIDADES");
        gotoxy(30,3);printf("|VALOR UNITARIO");

        gotoxy(0,4);printf("\n----------------------------------------------------------------------------------------------------------------------\n");
*/

            gotoxy(40,y);printf("| %s", e.producto);
            gotoxy(60,y);printf("| %d",e.cantidadProducto);
            gotoxy(80,y);printf("| $%.2f\n",e.valorUnitario);

}

void mostrarPedidoGo (stPedido e) /// MOSTRAR UN PEDIDO CON GOTO (TABLA)
{
    int i=0,t=6,w=0;

    gotoxy(2,3);printf("|IDPEDIDO");
    gotoxy(12,3);printf("|IDCLIENTE");
    gotoxy(24,3);printf("|FECHA");
    gotoxy(40,3);printf("|PRODUCTOS");
    gotoxy(60,3);printf("|UNIDADES");
    gotoxy(80,3);printf("|VALOR UNITARIO");
    gotoxy(95,3);printf("|COSTO PEDIDO");
    gotoxy(110,3);printf("|ESTADO PEDIDO");

    gotoxy(0,4);printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");


    gotoxy(2,6);printf("| %li", e.idPedido);
    gotoxy(12,6); printf("| %i", e.idCliente);
    gotoxy(24,6); printf("| %d/%d/%d", e.fechaPedido.dia,e.fechaPedido.mes,e.fechaPedido.anio);


    mostrarDescripcionPedidoGo(e.descripcion,e.cantidadProductosDistintosPedido);

    gotoxy(95,6);printf("| $%.2f", e.costoPedido);
    gotoxy(110,6);printf("| %d", e.estadoPedido);
    ///printf("\n---------------------------------------------------\n");

}

void mostrarDescripcionPedidoGo (stDescripcion descrip[], int validos) /// MUESTRA DESCRIPCION PEDIDOS CON GOTO
{
    int i=0,t=6;

    while (i<validos)
    {
        mostrarUnaDescripcionPedidoGo(descrip[i],t);
        t++;
        i++;
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n");
}




