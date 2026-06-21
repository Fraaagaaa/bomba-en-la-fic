## 1. Etapas típicas del pipeline para operaciones de punto flotante

| Etapa  | Nombre                     | Descripción                                    |
| ------ | -------------------------- | ---------------------------------------------- |
| IF     | Instruction Fetch          | Se busca la instrucción                        |
| ID     | Instruction Decode / Issue | Se decodifica y leen los operandos             |
| A1, A2 | Add/Sub Execution          | Etapas de ejecución de suma/resta flotante     |
| M1–M4  | Multiply Execution         | Etapas de ejecución de multiplicación flotante |
| D1–D7  | Divide Execution           | Etapas de ejecución de división flotante       |
| MEM    | Memory access              | Carga / Guardado de datos en memoria           |
| WB     | Write Back                 | Se escribe el resultado al registro            |

---

## 2. Ejemplo de dependencias (RAW hazards)

```mips
mul.s $f0, $f1, $f2    # $f0 = $f1 * $f2
add.s $f3, $f0, $f4    # $f3 = $f0 + $f4
sub.s $f5, $f3, $f6    # $f5 = $f3 - $f6
div.s $f7, $f5, $f8    # $f7 = $f5 / $f8
```

**Dependencias:**
- `add.s` depende del resultado de `mul.s` → RAW (*read after write*)
- `sub.s` depende de `add.s`
- `div.s` depende de `sub.s`

---

- IF: Búsqueda de instrucción | Lee en la memoria de instrucciones la dirección escrita en. Calcula PC + 4
- ID: Decodificación / búsqueda de registros
- EX: Calcular operación / Evaluar condición / Calcular destino de salto
- MEM: Buscar dato / Guardar dato / Actualizar PC
- WB: Guardar Registro


| Instrucción      | ID                         | EX                                                              | MEM                                                  | WB                                        |
| ---------------- | -------------------------- | --------------------------------------------------------------- | ---------------------------------------------------- | ----------------------------------------- |
| `add $a, $b, $c` | Lee `$b` y `$c` del **BR** | Calcula `$b` + `$c` (**ALU**)                                   | -                                                    | Escribe el resultado en `$a` en el **BR** |
| `addi $a, $b, X` | Lee `$b` del **BR**        | Calcula `$b` + X (**ALU**)                                      | -                                                    | Escribe el resultado en `$a` en el BR     |
| `lw $a, X($b)`   | Lee `$b` del **BR**        | Calcula `$b` + X (**ALU**)                                      | Accede a la dirección de **memoria** `$b` + X        | Escribe el contenido de `$a` en el **BR** |
| `sw $a, X($b)`   | Lee `$a` y `$b` del **BR** | Calcula `$b` + X (**ALU**)                                      | Guarda `$a` en la dirección de **memoria**  `$b` + X | -                                         |
| `bne $a, $b, X`  | Lee `$a` y `$b` del **BR** | Comprueba `$a` == `$b` (**ALU**)<br>Calcula PC + 4X (**adder**) | Actualiza **PC** si `$a` != `$b`                     | -                                         |
| `j X`            | -                          | Construye destino de salto                                      | **Actualiza PC**                                     | -                                         |

---
# [[Unidad de control]]
# [[Riesgos en la ejecución]]

---
### Pipeline MIPS (16 ciclos)

| Instrucción           | Dependencias | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11  | 12  | 13  | 14  | 15  | 16  |
| --------------------- | ------------ | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `add.s $f0, $f2, $f4` |              | IF  | ID  | A1  | A2  | A3  | MEM | WB  |     |     |     |     |     |     |     |     |     |
| `lwc1 $f0 $0($a0)`    |              |     | IF  | ID  | X   | X   | EX  | MEM | WB  |     |     |     |     |     |     |     |     |
| `add.s $f1, $f0, $f4` |              |     |     | IF  | X   | X   | ID  | X   | A1  | A2  | A3  | MEM | WB  |     |     |     |     |
| `addi $a0, $a0, 4`    |              |     |     |     |     |     | IF  | X   | ID  | EX  | MEM | WB  |     |     |     |     |     |
| `addi $t0, $t0, -1`   |              |     |     |     |     |     |     |     | IF  | ID  | EX  | MEM | WB  |     |     |     |     |
| `swct $t0, 0($a0)`    |              |     |     |     |     |     |     |     |     | IF  | ID  | X   | EX  | MEM | WB  |     |     |
| `bne $t0, $0, tag`    |              |     |     |     |     |     |     |     |     |     | IF  |     |     |     |     |     |     |
| `swc1 $f1, 4($a0)`    |              |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

- IF se empieza siempre debajo de el último ID
- IF lee memoria, así que puede entrar en riesgo si otra instrucción está en MEM
- Si existe EX, tiene que ir siempre antes de MEM y sin ninguna burbuja en medio
- MEM y WB pueden procesar dos instrucciones cada una siempre y cuando a lo sumo una de ellas escriba o lea un registro no usado en la otra instrucción.
- Retardamos el acceso a memoria MEM para no escribir $f0 con lwc1 antes de que lo escriba add.s
- Mientras un add.s está en A1, A2 o A3 no se puede ejecutar un ID de otro add.s

