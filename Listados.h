#ifndef LISTADOS_H_INCLUDED
#define LISTADOS_H_INCLUDED

typedef struct
{
    int idCliente;
    int cantPedidos;
    char Apellido[30];
    char Nombre[30];
}PedidosXCliente;

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

#endif // LISTADOS_H_INCLUDED
