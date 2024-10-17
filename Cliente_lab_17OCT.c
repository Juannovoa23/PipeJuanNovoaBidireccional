/***********************************************************

FECHA: 17/10/2024
AUTOR: JUAN SEBASTIAN NOVOA GARCIA
MATERIA: SISTEMAS OPERATIVOS
LABORATORIO: Cliente - Servidor 
        - Funcionamiento del codigo
*************************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// Define el nombre del archivo FIFO (pipe con nombre) que se usará para la comunicación
#define FIFO_FILE "/tmp/fifo_twoway"

int main() {
    int fd;                 // Descriptor de archivo para el FIFO
    int end_process;        // Variable para determinar cuándo finalizar el proceso
    int stringlen;          // Longitud de la cadena de texto introducida
    int read_bytes;         // Número de bytes leídos desde el FIFO
    char readbuf[80];       // Buffer para leer y escribir mensajes
    char end_str[5];        // Cadena que indica el fin del proceso

    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

    // Abre el FIFO para lectura y escritura
    fd = open(FIFO_FILE, O_CREAT | O_RDWR);
    strcpy(end_str, "end");

    while (1) {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        
        // Elimina el carácter de nueva línea
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        
        // Verifica si la entrada es "end" para terminar el proceso
        end_process = strcmp(readbuf, end_str);

        if (end_process != 0) {
            // Escribe el mensaje en el FIFO
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

            // Lee la respuesta del servidor
            read_bytes = read(fd, readbuf, sizeof(readbuf));
            readbuf[read_bytes] = '\0'; // Asegura el final de la cadena
            printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        } else {
            // En caso de introducir "end", termina el proceso
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            close(fd);
            break;
        }
    }
    return 0;
}
