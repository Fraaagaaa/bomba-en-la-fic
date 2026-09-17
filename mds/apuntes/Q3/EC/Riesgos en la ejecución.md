El CPI ideal de un procesador segmentado es uno. Sin embargo, hay situaciones, denominadas **riesgos (hazards)**, que impiden que se ejecute la siguiente instrucción del flujo de instrucciones durante su ciclo de reloj:
- Riesgos estructurales: el hardware no puede soportar la combinación de instrucciones que se quieren ejecutar en el mismo ciclo.
- Riesgos de control: surgen del problema de determinar la instrucción correcta que se tiene que ejecutar después de un salto.
- Riesgo de datos: surgen de la existencia de dependencias entre las instrucciones.

### Riesgos estructurales:
Los recursos deben ser capaces de satisfacer la demanda de uso.
Ejemplo 1: sólo existe una unidad de división, si dos instrucciones div.s se programan, una no se procesará hasta que haya terminado la otra.
Ejemplo 2: Si varias instrucciones terminan en el mismo ciclo y necesitan escribir en un registro, deberán esperar hasta que esté libre, ya que sólo hay un puerto de escritura.

### Riesgos de control
Aparecen cuando surge la necesidad de tomar una decisión basada en los resultados de una instrucción mientras las otras se están ejecutando.


|                      | 1   | 2      | 3      | 4       | 5       | 6   |
| -------------------- | --- | ------ | ------ | ------- | ------- | --- |
| `bne $t0, $t1, loop` | IF  | **ID** | **EX** | **MEM** | WB      |     |
| `sw $t4, 0($a0)`     |     | IF     | ID     | EX      | **MEM** | WB  |
En este ejemplo no sabemos aún si vamos a ir a loop o continuar con el código de forma secuencial.

- Primera opción: detener el cauce hasta que se toma la decisión.
- Segunda opción: aplicar una técnica de predicción.
- Tercera opción: aplicar una técnica de salto retardado.

### Riesgos de datos
Se deben a la alteración temporal de la ejecución de las instrucciones que produce la segmentación:
- RAW (read after write): *j* intenta leer un dato antes de que *i* lo escriba. Se corresponde con una dependencia verdadera.
- WAW (write after write): j intenta escribir un operando antes de que éste sea escrito por i. Se corresponde con una dependencia de salida.
- WAR (Write after read): j trata de escribir en su destino antes de que sea leído por i. Se corresponde con una antidependencia. Es imposible en nuestro MIPS
#### Riesgo RAW (de flujo)

|                     | 1   | 2   | 3      | 4   | 5      | 6   |
| ------------------- | --- | --- | ------ | --- | ------ | --- |
| `lw $t0, 0($a0)`    | IF  | ID  | EX     | MEM | **WB** |     |
| `add $t2, $t0, $t1` |     | IF  | **ID** | EX  | MEM    | WB  |

La instrucción `lw` no conoce el valor de `$t0` hasta el final del ciclo 4. Lo escribe en el banco de registros en el ciclo 4. La instrucción add lee el valor (incorrecto) de `$t0` en el ciclo 3.


|                   | 1   | 2   | 3   | 4       | 5   | 6   |
| ----------------- | --- | --- | --- | ------- | --- | --- |
| `addi $t4, $0, 7` | IF  | ID  | EX  | **MEM** | WB  |     |
| `sw $t4, 0($a0)`  |     | IF  | ID  | EX      | MEM | WB  |
La instrucción `addi` no conoce el valor de `$t4` hasta el final del ciclo 3, lo escribe en el banco de registros en el ciclo 5. La instrucción `sw` lee el valor de `$t4` en el ciclo 3.

#### Riesgo WAW (de salida)

|                       | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| `mul.s $f0, $f0, $f1` | IF  | ID  | M1  | M2  | M3  | M4  | MEM | WB  |
| `add.s $f0, $f1, $f2` |     | IF  | ID  | A1  | A2  | MEM | WB  |     |
La instrucción add.s escribe el valor de `$f0` en el ciclo 7
En el ciclo 8 la instrucción `mul.s` sobrescribe ese valor, a partir del ciclo 8, el contenido de `$f0` es incorrecto.


|                       | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --------------------- | --- | --- | --- | --- | --- | --- | --- | --- |
| `mul.s $f0, $f0, $f1` | IF  | ID  | M1  | M2  | M3  | M4  | MEM | WB  |
| `swc1 $f0, 0($a0)`    |     | IF  | ID  | EX  | MEM | WB  |     |     |
| `lwc1 $f0, 4($a0)`    |     |     | IF  | ID  | EX  | MEM | WB  |     |
Existe un riesgo RAW entre `mul.s` y `swc1`
Entre `mul.s` y `lwc1` hay un riesgo WAW




#### Riesgo WAR (antidependencia)

|                     | 1   | 2   | 3   | 4   | 5   | 6   |
| ------------------- | --- | --- | --- | --- | --- | --- |
| `add $t0, $t1, $t2` | IF  | ID  | EX  | MEM | WB  |     |
| `add $t2, $t3, $t4` |     | IF  | ID  | EX  | MEM | WB  |
|                     |     |     |     |     |     |     |
En el procesador MIPS que estudiamos, este tipo de riesgos es **IMPOSIBLE** que suceda.
En una antidependencia, tendría que ejecutarse la etapa WB de la segunda instrucción antes que la etapa ID de la primera.