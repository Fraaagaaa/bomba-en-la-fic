Raid 0
- No incluye redundancia de datos
- Mayor prestaciones y capacidad a bajo coste, menor fiabilidad
- **Stripping**: información troceada en **tiras de datos** repartidas cíclicamente entre discos.
- **Franja**: Conjunto de tiras lógicamente consecutivas proyectadas sobre misma tira en cada disco.
- Op. E/S que implica a tiras lógicas contiguas. Acceso paralelo a discos, reducción del tiempo de transferencia.
- Array de discos presentado como 1 único disco grande.

Raid 1
- Todos los esquemas RAID salvo 0 incluyen información redundante para permitir cierta recuperación de datos.
- En RAID 1 la redundancia se logran con duplicación de todos los datos en **discos espejo**
- La información se almacena de forma contigua (sin stripping).
- Gran fiabilidad
- Ventajas
	- Una petición de lectura puede ser servida por cualquiera de los discos que contiene datos pedidos.
	- Respecto a RAID 0: posibilidad de recuperar errores
	- Respecto a RAID 2-5: apenas hay penalización de escritura
	- La recuperación tras un fallo es sencilla
- Desventajas:
	- Coste de almacenamiento: requiere el doble de espacio del disco lógico que se quiere soportar

RAID 2
- ECC: Códigos de Hamming, que se almacenan en discos de redundancia a parte de los datos.
- Stripping de datos a nivel de bit.
- Discos sincronizados, realizando misma operación E/S
- Altas velocidades de transferencia, aunque excesivamente complejo y costoso.

RAID 3
- También stripping de datos pero a nivel de byte
- También discos sincronizados, realizando en paralelo la misma operación E/S.
- Diferencia con RAID 2: sólo un disco de redundancia, usando **información de paridad** como ECC
- Alta velocidad de transferencia en cada transacción.
- Implementación bastante costosa

RAID 4
- Acceso independiente a los discos
	- Peticiones de E/S separadas se atienden en paralelo
- Tiras de datos de mayor tamaño que en RAID 2 y 3
- Tiras con bits de paridad en **un** disco de paridad
	- Existe cuello de botella en acceso a ese disco

RAID 5
- Como RAID 4, pero distribuyendo tiras de paridad a lo largo de todos los discos.
- Eliminamos cuello de botella de RAID 4

RAID 6
- Como RAID 5, pero con dos ECCs en discos diferentes
	- $paridad + paridad o paridad + otroECC$
- Permite recuperarse de dos fallos de disco simultáneos

# Resumen de niveles
Respecto a fiabilidad / redundancia
- RAID 0 no tiene redundancia, **no** es realmente \<\<RAID\>\>
- RAID 1 duplica toda la información.
- Resto de niveles RAID incrementan fiabilidad mediante esquemas de detección de errores, sin necesidad de duplicar toda la información.
	- Menor cantidad de información redudante que RAID 1.
	- Menor fiabilidad que RAID 1, pero mejor relación seguridad/precio
- En RAID 2, 3 y 4 información redundante en un único disco.
- En RAID 5 y 6 información redudante distribuida entre todos los discos

Respecto a rendimiento
- RAID 2 y 3: una única op. E/S que accede en paralelo a todos los discos.
	- Tiras muy pequeñas.
	- Incrementamos velocidad de transferencia de cada operación.
- Raid 4, 5 y 6: varias ops. E/S concurrentes
	- Tiras de mayor tamaño
	- Aumentamos número de operaciones por segundo

# Comparativa: RAID 1+0 vs. RAID 0+1

Ambos niveles de RAID combinan el **Mirroring** (espejo/RAID 1) y el **Striping** (división/RAID 0) para obtener velocidad y seguridad, pero existe un claro ganador en términos de fiabilidad.

La conclusión técnica es clara: **RAID 1+0 (RAID 10) es superior.**
## 1. Definiciones Estructurales

La diferencia principal radica en el orden en que se agrupan los discos:

* **RAID 0+1 (Mirror de Stripes):** Se crean dos conjuntos de discos en RAID 0 (velocidad) y luego se hace un espejo (RAID 1) entre esos dos conjuntos.
* **RAID 1+0 (Stripe de Mirrors):** Se crean varios pares de discos en RAID 1 (espejo) y luego se unen todos esos pares en un RAID 0 (un gran volumen rápido).

## 2. ¿Por qué RAID 1+0 es mejor?

Aunque ambos ofrecen el mismo rendimiento de lectura/escritura y la misma capacidad, el RAID 1+0 es el estándar de la industria por dos razones críticas:

### A. Tolerancia a Fallos Superior
* **En RAID 0+1:** Si un solo disco falla, el conjunto RAID 0 al que pertenece queda inoperativo. En ese momento, todo el sistema depende de un único conjunto RAID 0 restante. Si falla cualquier disco del segundo conjunto, **se pierden todos los datos**.
* **En RAID 1+0:** Si un disco falla, solo se ve afectado su "pareja" en el espejo. El sistema puede seguir funcionando incluso si fallan más discos, siempre y cuando no falle el disco que hace de espejo del que ya se rompió.

### B. Reconstrucción más Rápida y Segura
* **En RAID 0+1:** Al sustituir un disco, el sistema debe copiar los datos de **todos los discos** del conjunto sano para reconstruir el conjunto fallido. Esto genera un alto estrés en el hardware.
* **En RAID 1+0:** Solo se necesita copiar la información desde el disco espejo hacia el nuevo disco. Es un proceso mucho más rápido que minimiza el tiempo de exposición a un segundo fallo.
## 3. Cuadro Comparativo

| Característica                  | RAID 1+0 (RAID 10)                                        | RAID 0+1                              |
| :------------------------------ | :-------------------------------------------------------- | :------------------------------------ |
| **Rendimiento**                 | Excelente                                                 | Excelente                             |
| **Resiliencia**                 | Alta (soporta múltiples fallos si son en distintos pares) | Baja (un fallo degrada medio sistema) |
| **Velocidad de Reconstrucción** | Muy Rápida                                                | Lenta                                 |
| **Uso Recomendado**             | Servidores, Bases de Datos, Entornos Críticos             | Casi no se utiliza hoy en día         |
