//Programa que realice el recorrido en un laberinto es decir buscacaminos.
//Annely Hernandez Cruz

#include <iostream> //entrada y salida
#include <fstream>//lee el archivo
#include <vector>//usa vectror
#include <string>
#include <windows.h> // limpia pantalla y pausa
using namespace std;

vector<string> laberinto;//guarda las lineas del laberinto
vector<vector<bool> > visitado;//marca donde ya avanzo
int filas = 0, columnas = 0;// tama�o del laberinto
bool encontrado = false;//Se pone en true si se llega a la 'S'

// direcciones: arriba, abajo, izquierda, derecha
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// laberinto con animaci�n
void mostrarLaberinto() {
    system("cls"); // Limpia pantalla  Windows
    for (size_t i = 0; i < laberinto.size(); i++) {
        cout << laberinto[i] << endl;
    }
    Sleep(150);// animaci�n pausa 150 
}

//  animaci�n y control para no regresar 
bool buscar(int x, int y, int px, int py) {
    if (laberinto[x][y] == 'S') { // Si se encuentra la salida
        encontrado = true;
        return true;
    }

    visitado[x][y] = true;
    laberinto[x][y] = '0';  // paso actual
    mostrarLaberinto();//el laberinto

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];// posici�n x
        int ny = y + dy[i];//posici�n y

        // Evita regresar a la posici�n anterior (px, py)
        if (nx == px && ny == py) continue;
// Si est� dentro del laberinto y es un camino o la salida
        if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas &&
            (laberinto[nx][ny] == ' ' || laberinto[nx][ny] == 'S') &&
            !visitado[nx][ny]) {

            if (buscar(nx, ny, x, y)) return true;
        }
    }

    // limpia la posici�n actual
    laberinto[x][y] = ' ';//Si no encuntra camino borra la marca y retrocede
    mostrarLaberinto();
    return false;
}

int main() {
    ifstream archivo("laberinto.txt");//abfe archivo

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo laberinto.txt" << endl;
        return 1;
    }

    string linea; // Leer el laberinto l�nea por l�nea
    while (getline(archivo, linea)) {
        laberinto.push_back(linea);
    }
    archivo.close();//Cierra el archivo

    filas = laberinto.size();
    columnas = laberinto[0].size();
    visitado = vector<vector<bool> >(filas, vector<bool>(columnas, false));//  visitados en falso

    int inicioX = -1, inicioY = -1;

    // Buscar la posici�n de 'E'
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (laberinto[i][j] == 'E') {
                inicioX = i;
                inicioY = j;
                break;
            }
        }
        if (inicioX != -1) break;
    }

    if (inicioX == -1 || inicioY == -1) {
        cout << "No se encontr� la entrada (E)." << endl;
        return 1;
    }

    laberinto[inicioX][inicioY] = '0';  // posici�n inicial
    mostrarLaberinto();

    buscar(inicioX, inicioY, -1, -1);  // -1,-1 indica que no hay paso anterior al inicio

    if (encontrado) {
        cout << "\n�Se encontro la salida!" << endl;
    } else {
        cout << "\nNo se encontr� una salida (S)." << endl;
    }

    return 0;
}

