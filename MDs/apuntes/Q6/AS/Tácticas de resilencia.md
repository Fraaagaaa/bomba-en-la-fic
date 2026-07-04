# Tácticas de resilencia
# Resilencia

O sistema debe **proporcionar**, de xeito observable, un **servizo** consistente coa súa especificación. Cando un sistema **non proporciona un servizo consistente coa súa especificación**, percíbese como un **fallo**. O fallo é **observable** polos usuarios do sistema, sexan humanos ou outros sistemas.

A descrición deste parámetro determina cales son as **consecuencias aceptables** de que se presente un **fallo no sistema**.

Pódese medir como a fracción de **tempo que o sistema presta servizo** consistente coa súa especificación, debe ter en conta o tempo necesario para reparar e reiniciar o sistema en caso de fallo. (e.x. Unha *dispoñibilidade* de 0.998 significa que o sistema está listo 998 de cada 1000 unidades de tempo)

Preguntas chave:
- ¿Como se **identifica** un fallo?
	- Omisión / *crash* / tempo resposta / ...
- Con canta **frecuencia** se permite? Canto **tempo** pode levar **recuperar** o sistema?
	- $T{recuperación},  T{dispoñibilidade},  T{degradado},  T{reparación}$
- **Que pasa** cando ocorre?
	- Notificar / continuar en operación / desactivar compoñente / deter o sistema / ...

Podemos diferenciar unha caída no **rendemento** dunha caída do sistema?
- **Resposta** do sistema a **eventos** temporais
- Debe realizarse nun **intervalo aceptable** (especificación)
- Preguntas chave
	- Como se **identifica** a caída do rendemento?
		- Lantecia (*t* en procesar un evento), *deadline*, *throughtput* (eventos procesados en *t*), *jitter* (variabilidade do throughtput), taxa de fallo (eventos, datos).
	- Que **tipo** de peticións se agardan?
		- Eventos periódicos / estáticos / esporádicos
	- **Que ocorre** cando se produce?
		- Notificar / continuar en operación / activar compoñente / rexeitar peticións / ...


## Tácticas de resilencia
Estratexias complementarias á arquitectura, orientadas a *enviar a percepción de fallos do sistema*, incluido respostas demasiado tarde (rendemento).
Adoitan involucrar mecanismos de monitorización, redundancia e prevención (sexa manual ou atomatizada).
Son 3: Tácticas de monitorización, de redundancia y de prevención.
### Tácticas de monitorización
**Ping/echo**: incluír un compoñente que comproba a dispoñibilidade de outros facendo ping e agardando unha resposta nun tempo determinado.
**Heartbeat** (dead man timer): os compoñentes emiten sinais periodicamente, que son escoitadas por outros; se un sinal non chega, o compoñente correspondente dáse por morto (e poden tomarse medidas).
**Monitor de procesos**: proceso supervisor que detecta o mal funcionamento doutros. detén, reinicia, substitúe... compoñentes segundo o seu comportamento, ou cada certo tempo (prevén quedarse sen memoria por *memory leaks* presentes pero non detectalos, buzóns cheos...).
- Comparación de patróns de "tráfico" (historicos).
- Filtrado de peticións (procedencia, tipoloxía...)
- Monitorización, almacenamiento, notificación

### Tácticas de redundancia
**Votación**: incluír compoñentes equivalentes que realizan a mesma operación en paralelo e un de control que comproba as súas respostas; se algún difire moito anúlase ou reiníciase; co resto tómase unha decisión.
**Redundancia activa**: incluír compoñentes redundantes que procesan en paralelo; só se usa un (p.ex. o máis rápido); se ese falla, recórrese á resposta de outro.
**Resposta pasiva**: incluír un conxunto de compoñentes dos que un responde aos eventos e infroma ao resto do resultado; se falla, un compoñente de control substitúeo por outro.
**Reposto/replicación**: incluír compoñente equivalente que configurar e inicializar en caso de fallo do orixinal; *checkpoints* ou *backups* periódicos do orixinal con *log* de operación.
- Réplicas para reducior o tempo de agarda por un recurso.
- Se o recurso replicado son datos, o sistema é responsable de manter consistencia e sincronización.

### Tácticas de prevención
**Xestión da ratio de eventos**: Reducir a frecuencia coa que se tratan os eventos, descartándoos se non temos control sobre a súa ratio de chegada.
**Control da frecuencia de mostraxe**: Reducir a frecuencia coa que se monitoriza o contorno para reducir o número de eventos.
**Limitación do tempo de execución**: Limitar o tempo que se agarda pola resposta a un evento para controlar o uso de recursos
**Limitación do tamaño dos buffers**: Limitar a cantidade de eventos pendentes de ser procesados para controlar o uso de recursos.
