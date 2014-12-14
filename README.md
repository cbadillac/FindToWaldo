Where's Waldo?? (FindToWaldo)
==============
##PDI

####Autores:
				Marcelo Ehrenfeld
				Roberto Farias
				Cristóbal Badilla
				René Pozo
				Cristóbal Ramírez
	
Introducción
------------
MOTIVACIÓN:
Donde está Wally es una serie de libros los cuales poseen la peculiaridad de solo tener imágenes. La idea de estos libros consiste en encontrar a Wally, un personaje que viste un sueter de rayas horizontales rojo y blanco, lentes, pantalón de vaquero y un gorro de lana, también de rayas. La dificultad de encontrarlo radica en que en la misma imagen hay un serie de objetos y personajes con un gran parecido, para así despistar al lector. A veces la búsqueda se torna muy difícil y la búsqueda puede durar varios minutos, si no más. En este contexto es que surgió nuestra motivación de crear un software que mediante el Procesamiento Digital de Imágenes (PDI) ayude al lector a encontrar a nuestro personaje en cosa de segundos.

IDEA O PROBLEMA A RESOLVER:
Dada la dificultad del juego es necesario poder idear una aplicación la cual automáticamente con herramientas de procesamiento de imágenes pueda encontrar a Wally en algún cuadro de este libro.

DESCRIPCIÓN DE LA SOLUCIÓN
La solución consiste en que el software a desarrollar sea capaz de reconocer a Wally (una pose en específica) e indicar la posición donde éste lo ha encontrado. Para aquello, la interfaz con el usuario solicitará que se ingrese una imagen de donde se encuentra Wally. Una vez que el programa carga la correspondiente imagen, se realiza una leve ecualización de la imagen en caso de que esta viniera muy deteriorada. En el caso que cumpla con ciertos requisitos mínimos de calidad, como por ejemplo una resolución mínima, se procede con el análisis de la imagen, en caso contrario se pedirá cargar una nueva imagen.
El análisis de la imagen consiste en un análisis morfológico y un algoritmo que discrimine entre los resultados obtenidos. Cabe destacar que el patrón de Wally está previamente incorporado en el programa, por lo tanto no es algo que el usuario pueda cambiar. A partir de este patrón se realiza una búsqueda. Dado que existen muchos patrones similares al buscado en cada imagen, se detectan varios posibles aciertos. El algoritmo sera el responsable de discriminar entre los aciertos encontrados.
Finalmente, una vez que el programa ha detectado a Wally, muestra la imagen al usuario con Wally encerrado en un rectángulo o en su defecto indica que Wally no ha sido encontrado.
