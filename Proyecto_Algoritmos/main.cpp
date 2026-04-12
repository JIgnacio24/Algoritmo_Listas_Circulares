#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

class Node{// Pelicula individual
	
	public:
		string code;	
		string title;	
		string gender;	
		string total;	
		string subtitled;	
		string premier;	
		
		Node* next;
		Node* prev;
		
		Node(string codeI, string titleI, string genderI, string totalI, string subtitledI, string premierI){
		 code = codeI;	
		 title = titleI;	
		 gender = genderI;	
		 total = totalI;	
		 subtitled = subtitledI;	
		 premier = premierI;
		}// constructor
}; // class Node

class DublyCircularLinkedList{// peliculas por genero
	
	private:
		Node* generalPtr; // puntero principal
		
	public:
		string genero;
		
		DublyCircularLinkedList(string generoI){
			genero = generoI;
			generalPtr = NULL;
		}// constructor
		
			void insert(string codeI, string titleI, string genderI, string totalI, string subtitledI, string premierI){
				Node* movie = new Node(codeI, titleI, genderI, totalI, subtitledI, premierI); // instancia del nodo
				
			if(generalPtr == NULL){ // comprobar si esta vacio
				generalPtr = movie;
				return;
			} 
				
			if(generalPtr->next == NULL){// preguntar es el segundo nodo
				generalPtr->next = movie;
				movie->prev = generalPtr;
				generalPtr->prev = movie;
				movie->next = generalPtr;
			}else{ // el resto de los nodo
				
				Node* temp = generalPtr->next;
				while(temp->next != generalPtr){
					temp = temp->next;
				}// while
				temp->next = movie;
				movie->prev = temp;
				movie->next = generalPtr;
				generalPtr->prev = movie;
			}
						
		}//insert
		
		void insert_alphabetically(Node* movieI){
			Node* movie = movieI;
			
			if(generalPtr == NULL){  // comprobar si esta vacio
				generalPtr = movie;
				return;
			}// if
			
				if(generalPtr->next == NULL){// preguntar es el segundo nodo
					
					if(generalPtr->title < movie->title){ // para comprobar la diferencia de nombres
						generalPtr->next = movie;
						movie->prev = generalPtr;
						generalPtr->prev = movie;
						movie->next = generalPtr;
						generalPtr = movie;
					}else{
						generalPtr->next = movie;
						movie->prev = generalPtr;
						generalPtr->prev = movie;
						movie->next = generalPtr;
					}
				}else{  // el resto de los nodos
					Node* previ = generalPtr;
					Node* curr = generalPtr->next;
					while(curr->title < movie->title && curr != generalPtr){
						previ = curr;
						curr = curr->next;;
					}// while
					previ->next = movie;
					movie->prev = previ;
					movie->next = curr;
					curr->prev = movie;
				}// if
			
		}// insert_alphabetically
		
		void busquedaPorNombre (string nombre){
			
			if(generalPtr->title == nombre){ //  compara el nombre para imprimirlo
				cout << "Code: " << generalPtr->code << endl;
        		cout << "Title: " << generalPtr->title << endl;
        		cout << "Gender: " << generalPtr->gender << endl;
        		cout << "Total: " << generalPtr->total << endl;
        		cout << "Subtitled: " << generalPtr->subtitled << endl;
        		cout << "Premier: " << generalPtr->premier << endl;
        		cout << endl;
        		return;
			}
			
			int vueltas = 0;
			Node* temp = generalPtr->next;
			while(temp->title != nombre && vueltas != 1){ // busca por todos los nodos de la lista
				if(temp == generalPtr){
					vueltas++;
				}
				temp = temp->next;
			}// while
			
			if(vueltas == 1){ // en caso se completar una vuelta a la lista se sale paraque no se encicle
				cout << "No se encontro la pelicula";
			}else{
				cout << "Code: " << temp->code << endl;
        		cout << "Title: " << temp->title << endl;
        		cout << "Gender: " << temp->gender << endl;
        		cout << "Total: " << temp->total << endl;
        		cout << "Subtitled: " << temp->subtitled << endl;
        		cout << "Premier: " << temp->premier << endl;
        		cout << endl;
        }
    }// busquedaPorNombre
    
		void display(){
			Node* temp = generalPtr;
				while(temp->next != generalPtr){ // para comprobar que no encicle
					cout << "Code: " << temp->code << endl;
        			cout << "Title: " << temp->title << endl;
        			cout << "Gender: " << temp->gender << endl;
        			cout << "Total: " << temp->total << endl;
        			cout << "Subtitled: " << temp->subtitled << endl;
        			cout << "Premier: " << temp->premier << endl;
        			cout << endl;
					temp = temp->next;
				}// while
				// el ultimo nodo de la lista
				cout << "Code: " << temp->code << endl;
        		cout << "Title: " << temp->title << endl;
        		cout << "Gender: " << temp->gender << endl;
        		cout << "Total: " << temp->total << endl;
        		cout << "Subtitled: " << temp->subtitled << endl;
        		cout << "Premier: " << temp->premier << endl;
        		cout << endl;
				cout << endl;
		}// display
		
		void circular(){
			
			Node* temp = generalPtr->next;
			int vueltas = 0;
			while(vueltas != 6){ // hacer varias comprobaciones para verificar que es circular
				if(temp == generalPtr)
					vueltas++;
				temp = temp->next;
				cout<<"Numero de vueltas: "<<vueltas<<endl;
			}
			cout<<"Salio del ciclo"<<endl;
		}
};// DublyCircularLinkedList

class NodeList{// almacena listas de peliculas
	
	public:
		DublyCircularLinkedList* list;
		NodeList* next;
		
	NodeList(string genero){
		list = new  DublyCircularLinkedList(genero);
		next = NULL;
	}// constructor
};

class GeneralLinkedList{// generos de peliculas

	private:
		NodeList* head;
		int cont;
	public:
		GeneralLinkedList(){
			head = NULL;
			cont = 2;
		}// constructor
		
	void agregarGenero(Node* movie){
		NodeList* newNode = new NodeList(movie->gender);
		
		if(head == NULL){
			head = newNode;
			return;
		}
		
		bool verificado = true;
		NodeList* prev = head;
		NodeList* curr = head->next;
		
		if(prev->next == NULL){
			if(prev->list->genero == movie->gender){
        		verificado = false;
			}//if
			
		}else{
			while (curr != NULL) {
        		if(curr->list->genero == movie->gender || prev->list->genero == movie->gender){// compara el genero de las listas con las peliculas
        			verificado = false;
				}
			prev = curr;
            curr = curr->next;
        	}// while
		}// if
		
        if(verificado)// si son diferentes crea el nodo si es false es que esta repetida
			prev->next = newNode;
	}// agregarGenero
	
	void verGeneros(){
		NodeList* temp = head;
        while (temp != NULL) {
            cout <<"El genero es:"<<temp->list->genero << endl; // display para verificar los generos de las listas
            temp = temp->next;
        }
        cout << endl;
	}
	
	void agregarPeliculas(Node* movie){
		NodeList* temp = head;
		while(temp != NULL){
			if(temp->list->genero == movie->gender){ // compara si el genero es igual a las peliculas
    			stringstream ss;
    			ss << cont;
    			string cadena = ss.str();
    			movie->code = cadena;
				temp->list->insert_alphabetically(movie); // hace llamado al metodo para que lo añada a esa lista con el mismo genero
				cont++;
			}
			temp = temp->next;
		}
	}// agregarPeliculas
	
	void display(){
		NodeList* temp = head;
		while(temp != NULL){
			cout<<"El genero de las peliculas es: "<<temp->list->genero<<endl;
			temp->list->display(); // hace llamado al display de cada lista de peliculas
			temp = temp->next;
			cout<<" "<<endl;
		}	
	}
	
	void buscarPelicula(string gender, string title){
		NodeList* temp = head;
		while(temp != NULL){
			if(temp->list->genero == gender){// compara si el genero es igual al genero de la pelicula
				temp->list->busquedaPorNombre(title); // hace llamado al metodo de cada lista para la busqueda
			}
			temp = temp->next;
		}
		return;
	}
	
};// GeneralLinkedList

class ArchivoP{
		
	public:
		GeneralLinkedList list;
	//	string texto;
		ArchivoP(){
		}
	void generos(){
		ifstream archivo("movies_2.csv");
    	string linea;
    	char split = ',';
    	getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        string codeI, titleI,tempI, genderI, totalI, subtitledI, premierI;
       // texto = texto+linea+"\n";
		//cout<<"La linea ahora es : "<<linea<<endl;
		
		if(linea.find('"') != std::string::npos){//esto retorna true si encuentra el caracter
			//tiene las  linea que tienen comillas
			string codeI, titleI,tempI, genderI, totalI, subtitledI, premierI; //caso de que tenga comillas
			bool dentroComillas = false;
    		std::string textoEntreComillas;
			
			for (size_t i = 0; i < linea.length(); ++i) {
        		char caracter = linea[i];
        	if (caracter == '"') {
            	dentroComillas = !dentroComillas;
        } else if (dentroComillas) {
            textoEntreComillas += caracter;
        }//else
    }//for
    
    	getline(stream, codeI, split);  // Leer el código de la película
        getline(stream, titleI, split);//lee el titulo
        getline(stream, tempI, split);//lee el titulo 
        getline(stream, genderI, split);  // Leer el genero normalmente
        getline(stream, totalI, split);  // Leer el total
        getline(stream, subtitledI, split);  // Leer si es subtitulada
        getline(stream, premierI, split);  // Leer si es premier
		titleI = textoEntreComillas;
        Node* movie = new Node(codeI, textoEntreComillas, genderI, totalI, subtitledI, premierI);
        list.agregarGenero(movie);
		}else{
			
		string codeI, titleI, genderI, totalI, subtitledI, premierI;
	//	texto = texto+linea+"\n";
        getline(stream, codeI, split);  // Leer el código de la película
        getline(stream, titleI, split);//lee el titulo
        getline(stream, genderI, split);  // Leer el genero normalmente
        getline(stream, totalI, split);  // Leer el total
        getline(stream, subtitledI, split);  // Leer si es subtitulada
        getline(stream, premierI, split);  // Leer si es premier

        Node* movie = new Node(codeI, titleI, genderI, totalI, subtitledI, premierI);
        list.agregarGenero(movie);
		}
		
    }
    	list.verGeneros();
    	archivo.close();
	}// generos
	
	void llenar() {
    ifstream archivo("movies_2.csv");
    string linea;
    char split = ',';
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream stream(linea);
     //   texto = texto+linea+"\n";
        string codeI, titleI,tempI, genderI, totalI, subtitledI, premierI;
		
		if(linea.find('"') != std::string::npos){//esto retorna true si encuentra el caracter
			//tiene las  linea que tienen comillas
			string codeI, titleI,tempI, genderI, totalI, subtitledI, premierI; //caso de que tenga comillas
			bool dentroComillas = false;
    		std::string textoEntreComillas;
			
			for (size_t i = 0; i < linea.length(); ++i) {
        		char caracter = linea[i];
        	if (caracter == '"') {
            	dentroComillas = !dentroComillas;
        } else if (dentroComillas) {
            textoEntreComillas += caracter;
        }//else
    }//for
    
    	getline(stream, codeI, split);  // Leer el código de la película
        getline(stream, titleI, split);//lee el titulo
        getline(stream, tempI, split);//lee el titulo 
        getline(stream, genderI, split);  // Leer el genero normalmente
        getline(stream, totalI, split);  // Leer el total
        getline(stream, subtitledI, split);  // Leer si es subtitulada
        getline(stream, premierI, split);  // Leer si es premier
		titleI = textoEntreComillas;
        Node* movie = new Node(codeI, textoEntreComillas, genderI, totalI, subtitledI, premierI);
        list.agregarPeliculas(movie);
		}else{
			
		string codeI, titleI, genderI, totalI, subtitledI, premierI;
        getline(stream, codeI, split);  // Leer el código de la película
        getline(stream, titleI, split);//lee el titulo
        getline(stream, genderI, split);  // Leer el genero normalmente
        getline(stream, totalI, split);  // Leer el total
        getline(stream, subtitledI, split);  // Leer si es subtitulada
        getline(stream, premierI, split);  // Leer si es premier

        Node* movie = new Node(codeI, titleI, genderI, totalI, subtitledI, premierI);
        list.agregarPeliculas(movie);
		}
		
    }
    

	// list.display();
    archivo.close();
}//llenar
	
    void guardarPeliculaEnArchivo(Node* movie) {
	    ofstream archivo("movies_2.csv", ios::app); // Modo append para agregar al final
	
	    if (!archivo.is_open()) { // Verificar si la apertura del archivo fue exitosa
	        cout << "Error al abrir el archivo." << endl;
	        return;
	    }
	
	    // Concatenar los campos de la película en una cadena separada por comas
	    string cadena = movie->code + "," +
	                    movie->title + "," +
	                    movie->gender + "," +
	                    movie->total + "," +
	                    movie->subtitled + "," +
	                    movie->premier + "\n";
	
	    // Escribir la cadena en el archivo
	    archivo << cadena;
	
	    // Cerrar el archivo
	    archivo.close();
	
	    cout << "Pelicula guardada en el archivo correctamente." << endl;
	}//escribir en archivo
	
}; // Archivo

int main() {

    ArchivoP* a = new ArchivoP();
    a->generos();
    a->llenar();
    
    int opcion;
    string archivo;
    string code;
    string title;
    string gender;
    string total;
    string subtitled;
    string premier;

    bool salir = false;

    while (!salir) {
        system("cls");  // Limpiar la consola en Windows

        cout << "\nMenu de opciones:" << endl;
        cout << "1. Ingresar una pelicula" << endl;
        cout << "2. Buscar una pelicula" << endl;
        cout << "3. Listar todas las peliculas" << endl;
        cout << "4. Salir del programa" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: { // Registrar película
                system("cls"); 
                cout << "Ingrese el titulo de la pelicula" << endl;
                cin >> title;
                cout << "Ingrese el genero de la pelicula" << endl;
                cin >> gender;
                cout << "Ingrese el total de la pelicula" << endl;
                cin >> total;
                cout << "Indique si es subtitulada" << endl;
                cout << "1. Si" << endl;
                cout << "0. No" << endl;
                cin >> subtitled;
                cout << "Indique si es premier" << endl;
                cout << "1. Si" << endl;
                cout << "0. No" << endl;
                cin >> premier;
                Node* peli = new Node("", title, gender, total, subtitled, premier);
                 a->list->agregarPeliculas(peli);
                a->guardarPeliculaEnArchivo(peli);
                break;
            }
            case 2: { // Buscar película
                system("cls");
                cout << "Ingrese el titulo de la pelicula" << endl;
                cin >> title;
                cout << "Ingrese el genero de la pelicula" << endl;
                cin >> gender;
                a->list.buscarPelicula(gender, title);
                break;
            }
            case 3: {
                system("cls"); 
                a->list.display();
                break;
            }
            case 4: {
                cout << "Saliendo del programa." << endl;
                salir = true;
                break;
            }
        }

        if (!salir) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
    
}//main
