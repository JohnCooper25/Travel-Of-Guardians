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

- Ver matriz de adyacencia => Por medio de esta accion se le muestra la matriz de adyacencia del grafo de ciudades al usuario. Esto con el fin de que este mismo pueda ver las ciudades que estan conectadas entre si, para realizarlo se debe imprimir dicha estructura la cual contiene todos los datos de las conexiones entre ciudades los cuales provienen desde su archivo correspondiente.
  
- Crear nuevos caminos => Para esta accion se necesita que el usuario seleccione las ciudades que desea conectar para poder realizar el cambio correspondiente en la matriz de adyacencia. Con este fin se debe recibir ambos datos y agregarlos como nuevas aristas entre los 2 vertices de las ciudades seleccionadas.

- Viajar por el reino => En esta accion se le permite al usuario seleccionar una ciudad para luego mostrarle los datos acerca de esta misma. Ya sean su nombre y las distintas conexiones que posee con otras ciudades.

### Presenciar una Batalla.
Es la opcion mas imporante del juego. Debido a que por medio de esta es donde se lleva a cabo la accion. Para esto le presentamos el siguiente menu al usuario:


  

## Solucion.
Este proyecto se abordo en 3 grandes pasos:
1. Identificacion.
2. Implementacion.
3. Ejecucion.

### Identificacion.
En esta parte, como su nombre indica se tenia que analizar e identificar el proyecto. Pensar en los tipos de datos a utilizar, funciones a realizar, algoritmos, logica, orden, secuencia.
En esta etapa se llego a la idea de utilizar una lista como estructura de datos general para recibir la base de datos de las cartas. Posterior a esto se llego a la determinacion de utilizar **PILAS**.
Las pilas serian de lo mas importante pues estas mismas nos permitirian mover datos entre una y otra para poder llevar a cabo el juego y poder implementar la logica,la secuencia y el orden.
Por otra parte las funciones a realizar eran muchas desde agregar y quitar cartas hasta realizar operaciones entre ellas para llevar a cabo los ataques.

### Implementacion.
La parte mas importante de la **solucion* En terminos de tiempo esta misma fue la que mas se trabajo, debido a que se debio llevar a cabo todo lo descrito en la etapa anterior.
Se crearon las estructuras de datos en conjunto con las funciones que permitirian un correcto desarrollo del juego. Pero con esto tambien se debio abordar el orden logico del programa.
Se utilizaron funciones como **Push* y **Pop* para la manipulacion de datos al igual que iteradores que recorrian los mazos, manos y tableros dependiendo el caso.

### Ejecucion.
Por su parte la ejecucion fue la etapa en donde los errores se identificaban y provocaba cambios en todo el programa. Cambios de logica, implementaciones y hasta tipos de datos.
Todo esto se iba probando y ejecutando para verificar el correcto funcionamiento del juego al igual que las logicas implementadas. Se logro completar el juego con todas sus funciones y opciones disponibles.
Sin duda alguna esta fue la parte mas complicada de este largo proceso.

## Material extra
A continuacion adjuntamos un link de acceso a un video en youtube en el cual se detalla todo lo implementado. Tambien se adjunta un link de acceso a el repositorio de **Github* que contiene todo el material del proyecto:

https://github.com/JohnCooper25/The-Clash-Guardians/tree/main

https://youtu.be/Mo-KK3t0b7Y
 
 


