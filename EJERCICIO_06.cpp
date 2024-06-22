#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Producto{
protected:
    string nombre;
    int codigo;
    float precio;
    int cantidad;
    int puntaje;

public:
    Producto(string nombre, int codigo, float precio = 0, int cantidad = 0, int puntaje = 0){
        this -> nombre = nombre;
        this -> codigo = codigo;
        this -> precio = precio;
        this -> cantidad = cantidad;
        this -> puntaje = puntaje;
    }

    string get_Nombre(){
        return nombre;
    }

    int get_Stock(){
        return cantidad;
    }

    int get_Codigo(){
        return codigo;
    }

    float get_Precio(){
        return precio;
    }

    virtual void imprimir(){
        cout << "Nombre: " << nombre << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Precio: " << precio << endl;
        cout << "Cantidad: " << cantidad << endl;
        cout << "Puntaje: " << puntaje << " estrellas." << endl;
    };

    int get_Puntaje(){
        return puntaje;
    }


    virtual void venta(int cant) = 0;
    virtual int get_Tipo() = 0;
    virtual string get_Fecha() = 0;
};


template <typename T>
class Electronico : public Producto {
protected:
    const int tipo = 0;
    int anio_garantia;
    string fecha_compra;
    T marca;
    T modelo;

public:
    Electronico(string nombre, int codigo, float precio, int cantidad, int anio_garantia,int puntaje, T marca, T modelo, string fecha = "") : Producto(nombre, codigo, precio, cantidad, puntaje) {
        this->anio_garantia = anio_garantia;
        this->marca = marca;
        this->modelo = modelo;
        this->fecha_compra = fecha;
    }

    void imprimir() override {
        Producto :: imprimir();
        cout << "Anio de garantia: " << anio_garantia << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Fecha de compra: " << fecha_compra << endl;
    }

    int get_Tipo() override {
        return tipo;
    }

    string get_Fecha() override {
        return fecha_compra;
    }

    void actualizar_datos(const string& nuevoNombre, float nuevoPrecio, int nuevaCantidad, int nuevoPuntaje, const int& nuevoAniodeGarantia, const string& nuevaFechaCompra, const T& nuevaMarca, const T& nuevoModelo)  {
        nombre = nuevoNombre;
        precio = nuevoPrecio;
        cantidad = nuevaCantidad;
        puntaje = nuevoPuntaje;
        anio_garantia = nuevoAniodeGarantia;
        fecha_compra = nuevaFechaCompra;
        marca = nuevaMarca;
        modelo = nuevoModelo;
    }

    void venta(int cant) override {
        cantidad -= cant;
    }
};


template <typename T>
class Ropa : public Producto{
protected:
    const int tipo = 1;
    string talla;
    T marca;
    string fecha_compra;

public:
    Ropa(string nombre, int codigo, float precio, int cantidad,int puntaje, string talla, T marca, string fecha = "") : Producto(nombre, codigo, precio, cantidad,puntaje){
        this -> talla = talla;
        this -> marca = marca;
        this -> fecha_compra = fecha_compra;
    }

    void imprimir() override{
        Producto :: imprimir();
        cout << "Talla: " << talla << endl;
        cout << "Marca: " << marca << endl;
        cout << "Fecha de compra: " << fecha_compra << endl;
    }

    int get_Tipo() override {
        return tipo;
    }

    string get_Fecha() override {
        return fecha_compra;
    }

    void actualizar_datos(const string& nuevoNombre, float nuevoPrecio, int nuevaCantidad, int nuevoPuntaje, const string& nuevaTalla, const T& nuevaMarca, const string& nuevaFechaCompra) {
        nombre = nuevoNombre;
        precio = nuevoPrecio;
        cantidad = nuevaCantidad;
        puntaje = nuevoPuntaje;
        talla = nuevaTalla;
        marca = nuevaMarca;
        fecha_compra = nuevaFechaCompra;
    }

    void venta(int cant) override {
        cantidad -= cant;
    }

};


template <typename T>
class Alimento : public Producto{
protected:
    const int tipo = 2;
    string fecha_caducidad;
    T peso;
public:
    Alimento(string nombre, int codigo, float precio, int cantidad, int puntaje, string fecha_caducidad, T peso) : Producto(nombre, codigo, precio, cantidad, puntaje){
        this -> fecha_caducidad = fecha_caducidad;
        this -> peso = peso;
    }

    void imprimir() override{
        Producto :: imprimir();
        cout << "Fecha de caducidad: " << fecha_caducidad << endl;
        cout << "Peso: " << peso << endl;;
    }

    int get_Tipo() override {
        return tipo;
    }

    string get_Fecha() override {
        return fecha_caducidad;
    }

    void actualizar_datos(const string& nuevoNombre, float nuevoPrecio, int nuevaCantidad, int nuevoPuntaje, const string& nuevaFechaCaducidad, const T& nuevoPeso) {
        nombre = nuevoNombre;
        precio = nuevoPrecio;
        cantidad = nuevaCantidad;
        puntaje = nuevoPuntaje;
        fecha_caducidad = nuevaFechaCaducidad;
        peso = nuevoPeso;
    }

    void venta(int cant) override {
        cantidad -= cant;
    }
};


template <typename T>
class Gestor_Producto{
protected:
    vector<T*> productos;
    string nombre_admin;

public:
    Gestor_Producto(string nombre_admin){
        this -> nombre_admin = nombre_admin;
    }

    void agregar_producto(T* producto){
        cout << "Producto de nombre " << producto -> get_Nombre() << " agregado." << endl;
        productos.push_back(producto);
    }

    void venta_producto(int code, int cantidad){
        for(Producto* p : productos){
            if (p->get_Codigo() == code){
                p->venta(cantidad);
            }
        }
    }

    void imprimir_listado(){
        for(Producto* p: productos){
            p->imprimir();
            cout << endl;
        }
    }


    void eliminar_producto(){
        int i = 0;
        for(Producto* p : productos){
            if (p->get_Stock() <= 0){
                productos.erase(productos.begin() + i);
                i--;
            }
            i++;
        }
    }


    static bool comparar_precio(Producto* a, Producto* b) {
        return a->get_Precio() > b->get_Precio();
    }

    static bool comparar_puntaje(Producto* a, Producto* b) {
        return a->get_Puntaje() > b->get_Puntaje();
    }

    void ordenar_productos(int tipo){
        switch(tipo){
            case 1:
                sort(productos.begin(), productos.end(), comparar_precio);
                cout << "Listado Ordenado: " << endl;
                imprimir_listado();
                break;

            case 2:
                sort(productos.begin(), productos.end(), comparar_puntaje);
                cout << "Listado Ordenado: " << endl;
                imprimir_listado();
                break;

        }

    }




    void imprimir_popularidad(){
        sort(productos.begin(), productos.end(), comparar_puntaje);
        cout << "Productos mas populares:" << endl;
        productos[0]->imprimir();
        productos[1]->imprimir();
        productos[2]->imprimir();
    }


    void buscar_producto(string name){
        for(Producto* p : productos){
            if (p->get_Nombre() == name){
                p->imprimir();
            }
        }
    }

    void imprimir_electronico(){
        cout << "Electronicos: " << endl;
        for(Producto* p : productos){
            if (p->get_Tipo() == 0){
                p->imprimir();
            }
        }
    }

    void imprimir_ropa(){
        cout << "Ropas: " << endl;
        for(Producto* p : productos){
            if (p->get_Tipo() == 1){
                p->imprimir();
            }
        }
    }

    void imprimir_alimentos(){
        cout << "Alimentos: " << endl;
        for(Producto* p : productos){
            if (p->get_Tipo() == 2){
                p->imprimir();
            }
        }
    }


    void imprimir_alimentos_no_caducables(){
        cout << "Alimentos sin fecha de caducidad: " << endl;
        for(Producto* p : productos){
            if (p->get_Tipo() == 2 and p->get_Fecha() == ""){
                p->imprimir();
            }
        }
    }



    void informes(int dato){
        switch(dato){
            case 1:
                imprimir_electronico();
                imprimir_ropa();
                imprimir_alimentos();
                break;
            case 2:
                imprimir_popularidad();
                break;
            case 3:
                imprimir_alimentos_no_caducables();
                break;
        }
    }


};



int main() {


    Producto* electronico1 = new Electronico<string>("Telefono Samsung A71", 1, 100.5, 5, 2, 5, "Samsung", "A71", "2024/06/20");

    Producto* electronico2 = new Electronico<string>("Laptop HP", 2, 800.75, 3, 3, 4, "HP", "Pavilion", "2024/06/15");

    Producto* ropa1 = new Ropa<string>("Camiseta Adidas", 3, 29.99, 10, 4, "M", "Adidas", "2024/06/10");

    Producto* alimento1 = new Alimento<string>("Brocoli", 4, 22.99, 11, 4, "29/12/2005", "2 kilos");

    alimento1->imprimir();


    Gestor_Producto<Producto> gestor("Administrador");



    gestor.agregar_producto(electronico1);
    gestor.agregar_producto(electronico2);
    gestor.agregar_producto(alimento1);
    gestor.agregar_producto(ropa1);



    cout << "Listado de Productos:" << endl;
    gestor.imprimir_listado();
    cout << endl;


    cout << "Realizando una venta..." << endl;
    gestor.venta_producto(1, 2);
    cout << "Listado de productos actualizado:" << endl;
    gestor.imprimir_listado();
    cout << endl;


    cout << "Eliminando productos sin stock..." << endl;
    gestor.eliminar_producto();

    cout << "Listado de productos actualizado despues de eliminar:" << endl;
    gestor.imprimir_listado();

    cout << endl;



    gestor.informes(1);
    cout << endl;

    return 0;
}