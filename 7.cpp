#include <bits/stdc++.h> 

using namespace std;

class Producto {
protected:
    string nombreProducto;
    double precioProducto;

public:
    Producto(const string& nombre, double precio) : nombreProducto(nombre), precioProducto(precio) {}

    string getNombre() const { return nombreProducto; }

    double getPrecio() const { return precioProducto; }

    void setNombre(const string& nombre) { nombreProducto = nombre; }

    void setPrecio(double precio) { precioProducto = precio; }

    virtual double calcularTotal(int cantidad) const = 0;

    virtual string toString() const {
        ostringstream oss;
        oss << "Producto: " << nombreProducto << ", Precio: $" << precioProducto;
        return oss.str();
    }

    virtual ~Producto() = default;  // Destructor virtual
};

class Perecedero : public Producto {
private:
    int diasParaCaducar;

public:
    Perecedero(const string& nombre, double precio, int diasCaducidad)
        : Producto(nombre, precio), diasParaCaducar(diasCaducidad) {}

    int getDiasParaCaducar() const { return diasParaCaducar; }

    void setDiasParaCaducar(int dias) { diasParaCaducar = dias; }

    double calcularTotal(int cantidad) const override {
        double precioFinal = precioProducto;
        switch (diasParaCaducar) {
            case 1: precioFinal /= 4; break;
            case 2: precioFinal /= 3; break;
            case 3: precioFinal /= 2; break;
        }
        return precioFinal * cantidad;
    }

    string toString() const override {
        ostringstream oss;
        oss << Producto::toString() << ", Días para caducar: " << diasParaCaducar;
        return oss.str();
    }
};

class NoPerecedero : public Producto {
private:
    string tipoProducto;

public:
    NoPerecedero(const string& nombre, double precio, const string& tipo)
        : Producto(nombre, precio), tipoProducto(tipo) {}

    string getTipoProducto() const { return tipoProducto; }

    void setTipoProducto(const string& tipo) { tipoProducto = tipo; }

    double calcularTotal(int cantidad) const override {
        return precioProducto * cantidad;
    }

    string toString() const override {
        ostringstream oss;
        oss << Producto::toString() << ", Tipo: " << tipoProducto;
        return oss.str();
    }
};

int main() {
    vector<Producto*> listaProductos = {
        new Perecedero("Leche", 1.50, 1),
        new Perecedero("Queso", 2.50, 2),
        new Perecedero("Carne", 5.00, 3),
        new NoPerecedero("Arroz", 1.00, "Alimento"),
        new NoPerecedero("Jabón", 0.75, "Limpieza")
    };

    for (const auto& producto : listaProductos) {
        cout << producto->toString() << endl;
        cout << "Precio total: $" << producto->calcularTotal(5) << endl;
        cout << "-----------------------------------------------------------" << endl;
        delete producto;  // Liberar memoria
    }

    return 0;
}
