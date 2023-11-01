# Actividad Integradora 1
**Autores:**
- Mario Frías Piña - A01782559
- Juan Pablo Cruz - A01783208
- Ma. Fernanda Cortés Lozano - A01026613

### Reflexion Evidencia Final

Durante el desarrollo de la primera evidencia, trabajamos de la mano con cadenas de  
caracteres, que encontramos en diferentes formatos y objetos de comunicacion. Se  
establecio un escenario donde se envia una serie de datos. Sin embargo, existe gente  
mal intencionada que intercepta estos mismos datos y los modifica con el objetivo de  
tomar control del dispositivo de destino.

Nuestro trabajo es encontrar estos archivos maliciosos dentro de los archivos de transmision  
para ejercer parametros de seguridad y evitar cualquier ataque a nuestro dispositivo.  
Para lograarlo, hemos implementado ciertos algortimos de manejo de string para identificar, manipular  
y evitar codigo malicioso dentro de los archivos de transmision. Esta practica permite que el usuario  
se sienta seguro ante cualquier peligro desconocido, simplificando la funcion de las defensas o  
protocolos que tiene ante estas mismas amenazas.

En este proyecto tuvimos que modificar los algoritmos que teníamos hechos para tratar con cadenas de texto. Estas modificaciones crearon nuevos problemas a los que nos tuvimos que enfrentar para llegar a la solución a la que queríamos llegar, como el tratar nuevos formatos de entrada y nuevos problemas con los caracteres que podían llegar a nuestras funciones.

El primer metodo o algoritmo que utilizamos fue el de KMP (Knuth-Morris) para hallar si existia algun  
codigo de dudosa prosedencia. Sin embargo, tambien planteamos la misma solucion con el algortimo de la  
funcion z.

Para la segunda parte del reto modificamos el archivo con el algoritmo de manacher que ya teníamos, cambiamos la forma en que se llama a la función y la información que regresa.

