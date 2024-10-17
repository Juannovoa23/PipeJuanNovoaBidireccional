# PipeJuanNovoaBidireccional
Se entrega Taller 17/0CT/2023 Sistemas Operativos
# Muestra de entrada y salida
![image](https://github.com/user-attachments/assets/6e0465fa-62df-4400-9648-1d685e7ba0a1)
Este proyecto es una implementación de comunicación bidireccional entre procesos en Linux utilizando **tuberías nombradas** (FIFOs). Incluye un cliente y un servidor, donde el cliente envía mensajes al servidor y el servidor responde con una versión invertida del mensaje recibido. Esta comunicación se realiza en tiempo real y permite comprender el uso de la IPC (Inter-Process Communication).

## Componentes Principales

### 1. **Cliente_Lab_17OCT.c**
Este archivo representa el programa **cliente**, que tiene las siguientes responsabilidades:

- **Enviar mensajes al servidor** a través de la tubería nombrada (`/tmp/fifo_twoway`).
- **Recibir respuestas** del servidor después de que el mensaje haya sido procesado.
- **Permitir al usuario interactuar** a través de la terminal para escribir mensajes que se envían al servidor.
- **Cierre controlado**: Si el usuario escribe `end`, el cliente envía este mensaje al servidor y cierra la conexión.

#### Flujo de Trabajo del Cliente:
1. Solicita al usuario que ingrese un mensaje.
2. Envía el mensaje a través del FIFO al servidor.
3. Espera una respuesta del servidor y la muestra.
4. Repite el proceso hasta que el usuario ingrese `end`, que indica el final de la comunicación.

### 2. **Servidor_Lab_17OCT.c**
Este archivo representa el programa **servidor**, que tiene las siguientes responsabilidades:

- **Crear la tubería nombrada** si no existe (`/tmp/fifo_twoway`).
- **Esperar mensajes del cliente**, recibirlos y procesarlos.
- **Invertir la cadena recibida** y enviarla de vuelta al cliente.
- **Cerrar la conexión** cuando recibe la cadena `end` del cliente.

#### Flujo de Trabajo del Servidor:
1. Espera recibir un mensaje del cliente.
2. Lee el mensaje y lo invierte.
3. Envía la cadena invertida de vuelta al cliente.
4. Repite el proceso hasta recibir el mensaje `end`, que indica que debe cerrar la conexión.

### 3. **Comunicación Bidireccional con FIFO**
- Este proyecto utiliza **tuberías nombradas** (FIFOs) para permitir que el cliente y el servidor se comuniquen. 
- Las tuberías nombradas son archivos especiales en el sistema de archivos que permiten la transferencia de datos entre procesos. 
- **`/tmp/fifo_twoway`** es el archivo FIFO que actúa como un canal de comunicación entre el cliente y el servidor. 

## Ejecución del Proyecto

### Requisitos
- Sistema operativo Linux.
- Compilador `gcc` para compilar los archivos `.c`.

### Pasos para Compilar y Ejecutar

1. **Compilar el servidor:**
   ```bash
   gcc Servidor_Lab_17OCT.c -o servidor
   ```

2. **Compilar el cliente:**
   ```bash
   gcc Cliente_Lab_17OCT.c -o cliente
   ```

3. **Ejecutar el servidor:**
   ```bash
   ./servidor
   ```

4. **Ejecutar el cliente en otra terminal:**
   ```bash
   ./cliente
   ```

5. Para finalizar la comunicación, ingresa `end` en el cliente.

### Ejemplo de Uso
1. El cliente inicia y pide al usuario que ingrese una cadena.
2. El usuario escribe: `hello`.
3. El cliente envía `hello` al servidor.
4. El servidor recibe `hello`, lo invierte a `olleh`, y lo envía de vuelta.
5. El cliente muestra el mensaje recibido: `olleh`.
