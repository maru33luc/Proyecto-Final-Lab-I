#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED



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



stPedido cargarPedido (stPedido A, int dimension);
void guardarPedidoEnArchivo (char nombreArchivoPedidos[]);
void mostrarUnaDescripcionPedido (stDescripcion e);
void mostrarDescripcionPedido (stDescripcion descrip[], int validos);
void mostrarPedido (stPedido e);
void mostrarArchivoPedidos (char nombreArchivoPedidos[]);
void bajaPedido (char nombreArch[], int id);
void mostrarPedidosXIdClienteArchivo (char nombreArchivo[], int id);
void mostrarPedidoXidPedidoArchivo (char nombreArchivo[], int id);
stPedido modificarPedido(stPedido e, int validos);
long int buscarPosicionPedidoArchivoXidPedido (char nombreArch[], long int idPedido);
void modificarPedidoenArchivoXidPedido (char nombreArch[], int idPedido);

void mostrarDescripcionPedidoGo (stDescripcion descrip[], int validos);
void mostrarPedidoGo (stPedido e);
void mostrarUnaDescripcionPedidoGo (stDescripcion e, int y);



#endif // PEDIDOS_H_INCLUDED
