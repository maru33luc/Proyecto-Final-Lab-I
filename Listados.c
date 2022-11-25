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
        mostrarPedidoGo(A[i]);
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
///su correspondientes cantidades de pedido a un arreglo de tipo PedidosXCliente
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
        if(i%2==0)
            system("pause");
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
