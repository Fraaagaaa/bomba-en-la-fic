## Tema 1

### Tiempo de respuesta / latencia
$$R_x = \frac{1}{tiempo\ de\ ejecucion_x}$$

### Tiempo de ejecución de la CPU
$$T_{cpu} = T_{user} + T_{s.o.}$$

### Tiempo de ejecución de CPU
$$Tiempo\ de\ CPU = {ciclos\ de\ CPU} \times {tiempo\ de\ ciclo}$$

### Ciclo de reloj por instrucción (CPI)
$$CPI = \frac{\sum_{i=1}^{m} CPI_i \, N_i}{N}$$

### Tiempo de CPU
$$T_{cpu} = N \times {CPI} \times {T_{ciclo}} = \frac {N \times {CPI}} {f_{CPU}}$$

### MIPS: millones de instrucciones por segundo
$$MIPS = \frac N {T_{CPU} \times {10⁶}}$$

### GFLOPS: miles de millones de operaciones en punto flotante (flops) por segundo
$$ GFLOPS = \frac {flops} {T_{cpu} \times {10⁹}}$$

### Comparación de una máquina X con una máquina Y
$$R_x > R_y$$
$$ \frac 1 {Texec_x} > \frac 1 {Texec_y} $$
$$ Texec_x < Texec_y$$

### Relación cuantitativa entre dos máquinas diferentes
$$n = \frac {R_x} {R_y}$$
La máquina X es n veces más rápida que la máquina Y

### Aceleración
$$A = \frac {R_{después}} {R_{antes}} = \frac {T_{antes}} {T_{después}}$$
Es fundamental acotar la aceleración potencial a obtener con una posible mejora.

### Ley de Amdahl
La mejora obtenida en el rendimiento al utilizar una parte optimizada está limitada por la fabricación de tiempo que se puede utilizar esa parte.
$$ T_{después} = \frac {T_{afectado}} {A_m} + T_{no\ afectado}$$
$$A = \frac {T_{antes}} {T_{después}} = \frac 1 {(1- F_m) + \frac {F_m} {A_m}}$$
donde $F_m$ es la fracción de tiempo afectada por la mejora y $A_m$ es el factor de mejora


