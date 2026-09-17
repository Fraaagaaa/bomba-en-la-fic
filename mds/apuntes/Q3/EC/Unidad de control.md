La unidad de control tiene divididas las líneas de control en grupos:
- IF: las señales de control necesarias siempre están activas.
- ID: las señales de control necesarias siempre están activas.
- EX: **RegDest**, **ALUOp** y **ALUSrc**
- MEM: **Brancht**, **MemRead** y **MemWrite**
- WB: **MemtoReg** y **RegWrite**

## Etapa IF (Instruction Fetch)![[Etapa IF.png]]
- PC Próxima instrucción
- **Memoria de instrucciones** Envía los 32 bits de la instrucción al registro de segmentación
- **Sumador**: Calcula **PC+ 4**
- **MUX** Decide si se carga la siguiente instrucción o el destino de un salto condicional
## Etapa ID (Instruction Decode)
![[Etapa ID.png]]
- **Banco de registros**: Lee los registros Rs y Rt de la instrucción y los envía al registro de segmentación.
	- Las líneas WRreg, WRdata y la señal de control RegWrite vienen de la etapa WB.
- **Extensión de signo** Convierte los 16 bits del campo inmediato de la instrucción a 32 bits.
- PC + 4 y otras partes de la instrucción se redirigen a la siguiente etapa pasando del registro IF/ID al registro ID/EX
## Etapa EX (Ejecución o ALU)
![[Etapa EX.png]]
- **MUX ALUsrc** Determina si la ALU operará con el registro de lectura 2 (add, beq, ...) o con el campo inmediato (lw, sw, addi, ...).
- **ALU** Opera con el registro de lectura 1 (Rs) y la salida del MUX ALUsrc
- **MUX RegDst** Determina si el resultado de la instrucción se escribirá en el registro Rt (lw, addi, ...) o en el registro Rd (add, ...)
- **Sumador**: Calcula la dirección destino de salto condicional: PC + 4 + (INM X 4).
## Etapa MEM (Memoria)
![[Etapa MEM.png]]
- **Resultado de la ALU**: Se redirige tanto a la entrada de dirección de la memoria de datos como a la siguiente etapa.
- **Memoria de datos**: Acceden a ella las instrucciones `lw` y `sw`
	- `lw`: La señal MemRead está activa. El contenido de la dirección *Addr* se envía a la siguiente etapa.
	- `sw`: La señal **MemWrite** está activa. Se guarda en la memoria el contenido del registro Rt.
- El **registro destino** se envía a la siguiente etapa.
## Etapa WB (Writeback)
![[Etapa WB.png]]
- Si la instrucción en esta etapa escribe datos en registros, se activa la señal **RegWrite**.
- **MUX MemToReg** Determina si se escribe el resultado de la ALU o el contenido leído de la memoria.
- Se envían al banco de registro de la señal **RegWrite**, el registro de escritura **WRreg** y los datos a escribir **WRdata**.
## Procesamiento de saltos
En el procesador visto, las instrucciones de salto condicional (bne, beq) se procesan en 3 ciclos:
- ID: Obtiene valores de registros a comparar
- EX: Evaluación de la condición de salto mediante la ALU, y cálculo de dirección de salto con el sumador (distinto a la ALU).
- MEM: Si el salto es efectivo, se actualiza el PC

## Operaciones Multiciclo
Algunas operaciones tardan más de un ciclo de reloj en la etapa de ejecución. Las instrucciones en punto flotante tienen la misma segmentación que las enteras, pero con las siguientes modificaciones:
- La etapa EX tiene diferente latencia dependiendo de la instrucción.
- Existen diversas unidades funcionales para cada tipo de operación