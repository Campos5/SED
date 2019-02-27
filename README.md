# SED

Descargar e instalar el entorno de eclipseARM, así como OpenOCD (link en el campus [drive])

## Configuración del proyecto

### Creación/importación de proyecto

* Creación de uno nuevo
  * como C Project
  * **ARM Cross Target Application** Sourcery G++ Lite

* Importar
  * File/import -> General -> Existing Projects into Workspace
  * Seleccionar carpeta

### Definir directorios y linkers
* Propiedades del proyecto
  * Seleccionar el archivo rum_ice.ld (dentro de CommonEclipse) en:
    * C/C++ Build -> Settings -> Linker -> General
  * Seleccionar la carpeta CommonEclipse en:
     * C/C++ -> Build -> Settings -> Assembler -> Directories
     * C/C++ -> Build -> Settings -> Compiler -> Directories

### Definir OpenOCD
* Run -> External tools Configurations -> Nueva configuración (main)
  * Establecer nombre
  * Establecer el directorio de trabajo
  * Argumentos: -f test\arm-fdi-ucm.cfg

### Definir Debug (GDB Hardware Debugger)
* Main
  * Definir nombre
  * Seleccionar proyecto
  * C/C++ Application, seleccionar .elf después de compilar
  * Select other... 
    * Marcar ventana y seleccionar standar GDB
* Debugger
  * Command: arm-none-eabi-gdb
  * Port number: 3333
* Startup
  * Demarcar Reset and Delay y Halt
  * Escribir debajo: remote reset init


