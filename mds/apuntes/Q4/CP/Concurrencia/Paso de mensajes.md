Paradigma de programación concurrente basado en el envío de mensajes entre procesos, sin compartir memoria.

## Introducción
No hay memoria compartida, no es necesario usar semáforos o mutexes, cada proceso tiene una copia de la información que necesita.
Principal problema:
- Memoria compartida -> gestionar el acceso a la zona compartida
- Compartición nula -> mantener la coherencia de información de los distintos procesos.

## Almacenamiento de mensajes

Dependiendo de la librería de paso de mensajes, la recepción de mensajes puede ser:
- Directa, no se almacenan mensajes. Se procesa el mensaje inmediatamente al enviar, o se bloquea al proceso que la envió.
- En cola, los mensajes se extraen en el mismo orden que llegan.
- Con un mailbox, se puede extraer los mensajes ya recibidos en cualquier orden.

``` erl
send(dst, type, msg)
recv(src, type, msg)
```
### Síncrono / Asíncrono

Send puede ser
- Síncrono: se bloquea al proceso que envió el send hasta que se completa la operación.
- Asíncrono: el proceso puede continuar y sincronizar manualmente más adelante.

Con send asíncrono, se puede implementar send síncrono

![[Pasted image 20260402153746.png]]