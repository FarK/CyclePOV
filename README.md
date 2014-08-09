CyclePOV
========
CyclePOV es mi proyecto de fin de carrera. Se inició como un trabajo para la
asignatura "*[Arquitectura de Sistemas en Tiempo Real]
(http://www.us.es/estudios/titulaciones/plan_26_23/asignatura_260116 "ASTR")*"
de la *[Escuela Técnica Superior de Ingeniería Informática]
(https://www.informatica.us.es/)* de la *[Universidad de Sevilla]
(http://www.us.es/)* ([Repositorio del antiguo proyecto]
(https://github.com/FarK/CyclePOV-ASTR)).

El proyecto consiste en un sistema de **persistencia de visión**
([POV](https://en.wikipedia.org/wiki/Persistence_of_vision)) a base de LEDs
montados en la rueda de una bicicleta ([video de la primera versión]
(http://www.atc.us.es/news/120-final-astr)).

Hardware utilizado
------------------
* **[STM32F407-Discovery](http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/PF252419)**
* **[Tiras de LEDs direccionables RGB](https://encrypted.google.com/search?q=ws2812b+led+strip&tbm=isch)**. Con LEDs **[WS2812B](http://www.adafruit.com/datasheets/WS2812B.pdf)**
* **[Sensor de efecto Hall US1881](https://www.sparkfun.com/datasheets/Components/General/Hall-US1881EUA.pdf)**
* **[Módulo Bluetooth BC417](https://encrypted.google.com/search?q=BC417f&tbm=isch)**
* **[Módulo MircroSD](http://www.wvshare.com/product/Micro-SD-Storage-Board.htm)**

Características
---------------
Se pretenden implementar las siguientes características en el sistema:

* Carga de imágenes *.bmp de tamaño limitado desde una memoria MicroSD
* Posibilidad de mostrar texto
* Aplicación de control mediante Bluetooth para Android
	* Recepción de datos del sistema (velocidad de la rueda, imágen acutal, etc...)
	* Envío de nuevas imágenes al sistema
	* Control del sistema (imagen a mostrar, apagado/encendido, etc...)

Estructura del repositorio
--------------------------
* **CyclePOV**
	* **CyclePOV**:      Firmware de la placa
	* **Doc**:           Documentación
	* **EclipseConfig**: Archivos de configuración del WorkSpace de ecplise
