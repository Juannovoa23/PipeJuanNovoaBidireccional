#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// Define el nombre del archivo FIFO (pipe con nombre) que se usará para la comunicación
#define FIFO_FILE "/tmp/fifo_twoway"

// Prototipo de la función que invierte una cadena
void reverse_string(char *);

int main() {
    int fd;                 // Descriptor de archivo para el FIFO
    char readbuf[80];       // Buffer para leer mensajes
    char end[10];           // Cadena que indica el fin del proceso
    int to_end;             // Variable para determinar si se debe finalizar
    int read_bytes;         // Número de bytes leídos desde el FIFO

    // Crea el FIFO si no existe
    mkfifo(FIFO_FILE, S_IFIFO | 0640);
    strcpy(end, "end");
    
    // Abre el FIFO para lectura y escritura
    fd = open(FIFO_FILE, O_RDWR);
    
    while (1) {
        // Lee el mensaje del FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0'; // Asegura el final de la cadena
        
        printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

        // Verifica si la entrada es "end" para terminar el proceso
        to_end = strcmp(readbuf, end);

        if (to_end == 0) {
            close(fd);
            break;
        }
        
        // Invierte la cadena recibida
        reverse_string(readbuf);
        printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        
        // Envía la cadena invertida de vuelta al cliente
        write(fd, readbuf, strlen(readbuf));

        // Espera para asegurar que el cliente pueda leer la respuesta antes de continuar
        sleep(2);
    }
    return 0;
}

// Función para invertir una cadena de caracteres
void reverse_string(char *str) {
    int last, limit, first;
    char temp;
    last = strlen(str) - 1;
    limit = last / 2;
    first = 0;

    // Intercambia los caracteres desde los extremos hacia el centro
    while (first < last) {
        temp = str[first];
        str[first] = str[last];
        str[last] = temp;
        first++;
        last--;
    }
}
