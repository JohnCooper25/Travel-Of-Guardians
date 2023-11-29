# Travel-Of-Guardians
El juego Travel of Guardians es un juego enfocado basado en ciudades capitales y guardianes.
Por su parte las capitales son lugares en los que habitan todos estos guardianes y estan separadas por todo el mundo. 
Por otro lado los guardines son personajes los cuales cuentan con diversa informacion. Sean su nombre, poder, maestro, lugar donde vive. Con todo lo anteriormente destacado podemos crear una especie de simulacion de juego la cual esta enfocada en poder manipular todas las informaciones de manera satisfactoria.
A continuacion se mostrara el objetivo a alcanzar y como se abordo la solucion a este proyecto.

## Objetivo a alcanzar.
El objetivo principal de el juego es demostrar el buen funcionamiento de los algoritmos utilizados para llevarlo a cabo, dicha demostracion se realiza a travez de las siguientes acciones.
El juego consta del siguiente menu en el cual el jugador debe seleccionar la accion a realizar:
"Carga de informacion".
"Ver Lista de Candidatos".
"Ver al Guardian".
"Conocer el Reino"
"Presenciar una Batalla"
"Salir".

### Carga de informacion.
Es la primera funcion a realizar. Esto debido a que es la encargada de realizar las cargas de datos tanto de los guardianes como de las ciudades. Tambien en ella se asigna toda la informacion proveniente de archivos **.txt**. Esta misma va dirigida a las distintas estructuras que se necesitan para poder ser utilizadas durante el juego.

### Ver Lista de Candidatos.
Esta opcion cumple la funcion de mostrar una lista de todos los guardianes ordenados por su nivel de poder. Para llevar a cabo esto mismo se utiliza un arbol binario el cual recibe los datos de todos los guardianes para luego recorrer dicha estructura y poder mostrar los datos de manera eficiente y clara.

Gracias a esta misma funcion tambien podemos utilizarla para ir actualizando los datos despues de cada batalla entre guardines. De esta manera se demuestra de manera correcta que la informacion esta siendo bien manipulada en dicha estructura.

### Ver al Guardian.
En esta opcion tiene como fin mostrar la lista de todos los guardianes al usuario y pedirle que escoja a uno de la lista para poder ver todos los datos correspondientes a dicho guardian.

Para llevar a cabo esta funcionalidad se necesitan de 3 pasos super importantes:

- Mostrar la lista de guardianes=> Para esto se debe recorrer el arbol general creado con los datos de los guardianes, posteriormente se muestra la informacion al jugador
- Seleccionar un guardian => El usuario debe seleccionar el guardian que desea por medio de la escritura del nombre de este mismo. Con esto podremos utilizar la funcion de busqueda para encontrar el personaje seleccionado.
- Entregar la informacion => Por ultimo se le muestra por pantalla al usuario toda la informacion correspondiente a el guardian escogido. Dicha informacion es nonbre, poder, maestro, ciudad donde vive.

### Conocer el Reino.
En esta opcion se le muestra el siguiente menu de acciones a realizar al usuario:

- Mostrar Ciduades y Conexiones => Por medio de esta accion se le muestra la matriz de adyacencia del grafo de ciudades al usuario. Esto con el fin de que este mismo pueda ver las ciudades que estan conectadas entre si, para realizarlo se debe imprimir dicha estructura la cual contiene todos los datos de las conexiones entre ciudades los cuales provienen desde su archivo correspondiente.
  
- Crear nuevos caminos => Para esta accion se necesita que el usuario seleccione las ciudades que desea conectar para poder realizar el cambio correspondiente en la matriz de adyacencia. Con este fin se debe recibir ambos datos y agregarlos como nuevas aristas entre los 2 vertices de las ciudades seleccionadas.

- Viajar por el reino => En esta accion se le permite al usuario seleccionar una ciudad para luego mostrarle los datos acerca de esta misma. Ya sean su nombre y las distintas conexiones que posee con otras ciudades. En el caso de no existir una conexion directa, se le entrega al usuario una ruta alternativa la cual involucra visitar otras ciudades con las que tiene conexion para poder llegar al destino deseado. Esto se hace por medio de una funcion que verifica las conexiones que hay entre todas las ciudades y va almacenando los datos de las conexiones recorridas hasta llegar al destino para luego imprimir dicho camino hasta la ciudad deseada.

### Presenciar una Batalla.
Es la opcion mas imporante del juego. Debido a que por medio de esta es donde se lleva a cabo la accion.Primero se le muestra al usuario una lista de todos los guardianes para que escoja el que desea utilizar para pelear o viajar dependiendo lo que desee realizar. Luego de seleccionar el guardian se le presenta una lista de los guardianes que existen en la ciudad en que se encuentra el guardian seleccionado (Es posible que el guardian escogido sea el unico en esa ciudad). Finalmente presentamos el siguiente menu al usuario:

- Pelear => En esta opcion el usuario podra escoger uno de los guardianes que existen en su ciudad para disputar una batalla con el seleccionado, luego de esto se lleva a cabo una simulacion de batalla en la cual existe una probabilidad de 4 a 6 a favor del desafiante. Una vez concluido el duelo el ganador obtiene puntos de poder dependiendo las siguientes condiciones:
*Si el Guardian derrotado es aprendiz, es decir, no es maestro de ningun guardian el ganador obtiene 3 puntos de poder.
*Si el guardian derrotado es Maestro de algun otro guardian. Entonces el ganador obtiene 5 puntos de poder.

En ambos casos al guardian perdedor se le resta 1 punto de poder.

- Viajar => En esta Opcion se le entrega el siguiente menu de opciones al usuario y tambien se entrega una lista de las ciudades con las que tiene conexion la ciudad del guardian elegido al comienzo de la funcion:
  
_Selecccionar Ciudad para Viajar_ => Aqui el usuario debe escoger una ciudad de la lista de conexiones proporcionada y una vez seleccionada se realizara el cambio de ciudad del guardian.

_Revisar Conexiones entre ciudades_ => Se ejecuta la funcion que le permite ver conexiones de cualquier ciudad que el escoja.

_Agregar Nuevo Camino_ => Aca se ejecuta la ciudad para generar la conexion que el usuario estime conveniente creando la conexion la cual sera mostrada despues al salir de la funcion.

_Eliminar Caminos_ => En esta opcion se ejecuta la funcion para eliminar un camino entre 2 ciudades. Esto segun estime conveniente el usuario. En general el funcionamiento es el mismo que se utiliza en la funcion Conocer El Reino.

_Consultar Rutas Existentes_ => En esta opcion se ejecuta la funcion para buscar Rutas entre ciudades la cual le permitiria al usuario revisar como llegar desde su ciudad a otra o revisar multiples conexiones entre ciudades.

## Solucion.
Este proyecto se abordo en 3 grandes pasos:
1. Identificacion.
2. Implementacion.
3. Ejecucion.

### Identificacion.
En esta parte, como su nombre indica se tenia que analizar e identificar el proyecto. Pensar en los tipos de datos a utilizar, funciones a realizar, algoritmos, logica, orden, secuencia.
En esta etapa se determinaron los siguientes puntos:
(1) Se debe utilizar 3 tipos de estructuras las cuales son Arbol General y Arbol Binario. Tambien se llego a la conclusion de la utilizacion de un grafo no dirigido en conjunto con una matriz de adyacencia para reflejar las conexiones de este mismo.
(2) Por su parte de los arboles tienen la siguiente designacion. El Arbol General va a ser utilizado para el orden jerarquico en base a el rango que tiene cada guardian ya sea "Aprendiz" o "Maestro". Luego el arbol binario va a ser utilizado para obtener la informacion de los guardianes y asi ordenarlos acorde a su estadistica de "Poder".
(3) Ambos arboles van a ser utilizados tanto para funciones de recorrerlos, Busqueda y eliminacion acorde a lo que se necesite realizar en el proyecto.
(4) Por otro lado el grafo y la matriz seran utilizados para recorrer, buscar y eliminar conexiones entre ciudades lo cual sera utilizado principalmente en acciones que tengan que ver directamente con el mundo.

### Implementacion.
La parte mas importante de la **solucion* En terminos de tiempo esta misma fue la que mas se trabajo, debido a que se debio llevar a cabo todo lo descrito en la etapa anterior.
Para poder cumplir con todas las acciones que se solicitaban en este proyecto. Se tuvieron que crear funciones para las estructuras mencionadas anteriormente. Dichas funciones estaban enfocadas en recorrer, busqueda y eliminacion. Todas estas funciones las utilizamos para llevar a cabo acciones como las de "Conocer El Reino" en esta misma se utilizaron los grafos y matriz de adyacencia. En funciones como "Ver Lista de Candidatos" y "Ver al Guardian" se utilizaron las operaciones en arboles Y finalmente en "Presenciar batalla" se utilizaron todas y cada una de las funcionalidades descritas anteriormente.

### Ejecucion.
Por su parte la ejecucion fue la etapa en donde los errores se identificaban y provocaba cambios en todo el programa. Cambios de logica, implementaciones y hasta tipos de datos.
Todo esto se iba probando y ejecutando para verificar el correcto funcionamiento del juego al igual que las logicas implementadas. Se logro completar el juego con todas sus funciones y opciones disponibles.
Teniendo en cuenta todos los detalles de la implementacion y las acciones que podia realizar el usuario en cada seccion del programa.
Sin duda alguna esta fue la parte mas complicada de este largo proceso.

## Material extra
A continuacion adjuntamos un link de acceso a un video en youtube en el cual se detalla todo lo implementado. Tambien se adjunta un link de acceso a el repositorio de **Github* que contiene todo el material del proyecto:

https://github.com/JohnCooper25/Travel-Of-Guardians

