# Filósofos

Este proyecto es una implementación del clásico problema de los Filósofos Cenando, que ilustra problemas de sincronización y técnicas para resolverlos en programación concurrente.

## Descripción General

El programa simula un escenario donde los filósofos se sientan en una mesa redonda, alternando entre comer, pensar y dormir. Cada filósofo necesita dos tenedores para comer, y hay tantos tenedores como filósofos en la mesa.

## Características

- Múltiples filósofos ejecutándose como hilos concurrentes
- Sincronización basada en mutex para el manejo de tenedores
- Sistema de detección de muerte
- Temporización precisa para las acciones
- Salida de consola colorida para diferentes estados

## Uso

### Compilación
```bash
make
```

### Ejecutando el Programa
```bash
./philo numero_de_filosofos tiempo_para_morir tiempo_para_comer tiempo_para_dormir [numero_de_veces_que_cada_filosofo_debe_comer]
```

Parámetros:
- `numero_de_filosofos`: El número de filósofos (y tenedores)
- `tiempo_para_morir`: Tiempo en milisegundos hasta que un filósofo muere de hambre
- `tiempo_para_comer`: Tiempo en milisegundos que tarda un filósofo en comer
- `tiempo_para_dormir`: Tiempo en milisegundos que un filósofo pasa durmiendo
- `numero_de_veces_que_cada_filosofo_debe_comer` (opcional): El programa se detiene cuando todos los filósofos han comido esta cantidad de veces

### Ejemplo
```bash
./philo 4 410 200 200
```

## Estados y Visualización

El programa utiliza salida coloreada para mostrar diferentes estados:
- 🤦 Pensando
- 🍴 Tomando tenedores
- 🍜 Comiendo
- 💤 Durmiendo
- ☠️ Muerte

## Detalles Técnicos

### Estructuras de Datos
- `t_list`: Estructura de datos principal del programa que contiene parámetros de tiempo, mutex e información de hilos
- `t_phi`: Estructura de datos individual del filósofo

### Sincronización
- Utiliza mutex para prevenir conflictos con los tenedores
- Implementa mecanismo de detección de muerte
- Maneja acceso concurrente a recursos compartidos

### Manejo de Errores
- Validación de entrada
- Verificaciones de asignación de recursos
- Limpieza adecuada al salir

## Gestión de Memoria

El programa gestiona cuidadosamente la asignación y liberación de memoria, usando:
- Asignación dinámica de memoria para filósofos y tenedores
- Inicialización y destrucción adecuada de mutex
- Terminación limpia de hilos

## Requisitos

- Compilador GCC
- Biblioteca POSIX threads
- Sistema operativo basado en Unix



