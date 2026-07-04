# Construíndo un exemplo de SLI/SLO/SLA con IA: as iteracións

Este documento mostra a secuencia real de interaccións cun axente de IA (Cursor + Claude) para construír o exemplo da asistencia a clase que ilustra SLI, SLO, SLA e alertas multi-window multi-burn-rate. O obxectivo non é explicar estes conceptos, senón mostrar **como se itera coa IA** para chegar a un resultado útil.

Cada fase inclúe os prompts exactos, un resumo do que cambiou, e unha lección sobre o proceso iterativo.

---

## Fase 1 -- Propoñer a analoxía inicial

> **Prompt 1:** En la presentación quiero poner este ejemplo para los estudiantes:
> - Veces que van a clase los viernes por la mañana por mes.
> - tienen el objetivo de ir siempre pero pasan cosas.
> - necesitan una asistencia del 75% para aprobar

> **Prompt 2:** imaginemos que se mide mes a mes. El alumno va la primera y la segunda semana, pero falta la tercera

> **Prompt 3:** imaginemos que sólo se hacen medidas los días 30 de mes, es decir al final

### Que cambiou

A IA xerou un primeiro exemplo con 1 alumno, 4 venres (1 mes), e medicións ao final do mes. O exemplo funcionaba para explicar SLI e SLA, pero era demasiado simple para mostrar alertas multi-window -- con só 4 puntos de datos non hai espazo para varias ventás.

### Lección

**A IA responde ao escenario que lle das.** Se o resultado non funciona, cambia o escenario (máis datos, máis tempo, máis casos), non a pregunta. A IA non vai dicirche que o teu plantexamento é insuficiente a menos que llo preguntes.

---

## Fase 2 -- Escalar ao cuatrimestre e corrixir alertas

> **Prompt 4:** me da la sensación que es difícil explicarlo sólo con un mes (4 viernes), sería más fácil con todo el cuatrimestre?

> **Prompt 5:** en el ejemplo no está bien marcado cuando saltan las alertas no? por ejemplo la corta debería saltar en varios meses no?

> **Prompt 6:** hazme lo del alumno C también y identifica de alguna forma cuando coinciden las 3 y cuando se rompe el SLA

### Que cambiou

O exemplo pasou de 4 a 16 venres (cuatrimestre completo), de 1 a 3 alumnos con patróns distintos, e engadéronse marcadores visuais: 🔔 para alertas individuais, 🚨 para cando coinciden as 3 ventás, e 💥 para cando se rompe o SLA. As alertas estaban mal marcadas na versión anterior e corrixíronse.

### Lección

**Cuestiona o que a IA produce.** O usuario viu que 1 mes era insuficiente antes que a IA. Tamén detectou que as alertas non estaban ben marcadas. A IA non valida o seu propio traballo a menos que llo pidas explicitamente. Os marcadores visuais (emojis) non os inventou a IA -- foron pedidos polo usuario.

---

## Fase 3 -- Gran pivot: tirar e refacer

> **Prompt 7:** Vamos a rehacer el análisis con:
> - Larga (2 meses).
> y vamos a generar 3 casos representativos de los 3 alumnos asumiendo que han ido siempre los viernes de los primeros 2 meses de clase

### Que cambiou

Descartouse todo o anterior. As novas premisas nun único prompt:
- V1-V8 con asistencia perfecta (simplifica a narrativa)
- 3 ventás definidas: curta (1 semana), media (4 venres), longa (8 venres rolling)
- 3 alumnos con patróns distintos (espazadas, seguidas, grave)

Isto xerou as táboas que serían a base do resultado final.

### Lección

**Non ter medo de tirar todo e volver a empezar.** Cando o enfoque non funciona, un prompt claro con todas as premisas novas nunha soa mensaxe é moito máis eficaz que intentar parchear o que hai. A IA traballa mellor con instruccións completas que con correccións incrementais sobre un modelo roto.

---

## Fase 4 -- Corrixir erros e mellorar formato

> **Prompt 8:** como se explican estos números? *(sinalando unha fila de SLI con valores incorrectos)*

> **Prompt 9:** Corrige y revisa los cálculos

> **Prompt 10:** explica esto del alumno A

> **Prompt 11:** Las tablas no están bien alineadas. Genera tablas de md

> **Prompt 12:** Pasa todo el texto a Gallego

### Que cambiou

A IA tiña erros nos cálculos acumulativos do SLI (porcentaxes globais mal calculadas). O usuario detectounos copiando os números e pedindo que os explicase -- ao intentar explicar, a IA decatouse do erro. As táboas en ASCII art pasaron a formato Markdown (máis lexibles). Todo o texto traduciuse ao galego.

### Lección

**A IA comete erros matemáticos. Hai que verificar cada número.** Un truco útil: en vez de dicir "isto está mal", pide que explique os números. Ao intentar xustificalos, a IA detecta as inconsistencias soa. O formato (táboas md vs ASCII, idioma) pídese explicitamente -- a IA non o cambia por iniciativa propia.

---

## Fase 5 -- Refinar a narrativa dos alumnos

> **Prompt 13:** os tres alumnos chegan correctamente cumplindo o SLA á semana 16. Move o exemplo C ao B, e fai que o alumno C non cumpla o SLA na semana 16

> **Prompt 14:** al lado de cada 🔔 en cada celda vamos a añadir el valor por el que hace que salte

> **Prompt 15:** Baja el SLO al 80% y recalcula todo

### Que cambiou

Cambio narrativo: que os 3 alumnos aprobasen era menos didáctico. Agora un alumno non aproba, o que ilustra mellor as consecuencias de non reaccionar ás alertas. Engadíronse os valores concretos de SLI ao lado de cada alerta (p.ex. `🔔 75%` en vez de só `🔔`), facendo explícito por que salta cada unha. Probouse baixar o SLO ao 80% para ver como cambiaban as alertas.

### Lección

**Itera sobre a narrativa, non só sobre os datos.** Que un alumno non aprobe é moito máis impactante que que todos aprueben. Engadir valores concretos ao lado de cada alerta axuda a entender o "por que", non só o "cando". E probar distintos SLOs permite comparar antes de decidir.

---

## Fase 6 -- Cuestionar a consistencia do modelo

> **Prompt 16:** Alumno B -> V9 y V14 en ventana Media, está correcto?

> **Prompt 17:** Las ventanas deberían activarse sólo en base al SLO (80%) no?

> **Prompt 18:** Cómo es más realista y queda más claro con SLO 80% o SLO 90%?

> **Prompt 19:** Cambia a 90% y recalcula

### Que cambiou

O usuario detectou que os umbrais das ventás non eran consistentes co SLO: cada ventá tiña a súa propia regra en vez de derivar dun único número. Isto provocou unha discusión sobre se SLO 80% ou 90% era mellor para o exemplo (80% deixaba pouca marxe ata o SLA de 75%; 90% daba 15 puntos de marxe e mellor diferenciación entre ventás). Elixiuse 90% e recalculáronse todas as táboas.

### Lección

**O usuario detecta inconsistencias que a IA non ve.** A IA aplicou regras ad-hoc a cada ventá en vez de derivar todo dun único SLO, o que é conceptualmente incorrecto. Pedir unha análise comparativa (80% vs 90%) antes de decidir é moi útil -- a IA pode presentar pros e contras, pero a decisión é do usuario.

---

## Fase 7 -- Conectar coa realidade profesional

> **Prompt 20:** El SLO debería ser único para todas las ventanas, así es como funciona en la realidad

> **Prompt 21:** Como encaja con esta forma de definir SLOs de Cabify? *(achegando screenshot de Asadito)*

> **Prompt 22:** De donde saen esos cálculos de burn rates? cómo se fan profesionalmente? Qué dice Google ao respecto?

> **Prompt 23:** Debemos aclarar o Contexto do exemplo con cómo se calculan estes burn-rates e porqué (exemplo de Google). Pero temos que manter este apartado o máis curto posible

### Que cambiou

O usuario corrixiu o modelo conceptual: as ventás non son regras independentes, senón que derivan dun único SLO a través de burn rates (modelo do Google SRE Workbook, cap. 5). Achegou un exemplo real da empresa (Asadito YAML) para validar que o modelo do exemplo se correspondía coa realidade. Engadiuse ao contexto do exemplo unha explicación compacta de burn rates e unha táboa de referencia co modelo de Google.

### Lección

**O coñecemento do dominio do usuario é imprescindible.** A IA pode xerar táboas, calcular números e adaptarse ao que lle pidas, pero non vai corrixir un erro conceptual se non sabe que o é. O usuario sabía como funcionan os SLOs na realidade (un único número, burn rates derivados) e dirixiu a corrección. A IA adaptou, pero non liderou.

---

## Leccións aprendidas

1. **Empeza cun escenario simple e escala.** O primeiro exemplo (4 venres, 1 alumno) era demasiado simple, pero serviu para validar a analoxía antes de complicala.

2. **Verifica sempre os cálculos.** A IA comete erros matemáticos con frecuencia. Un truco: en vez de dicir "está mal", pídelle que explique os números. Ao xustificalos, detecta as inconsistencias.

3. **Non teñas medo de tirar e refacer.** A Fase 3 descartou todo o traballo anterior cun único prompt. O resultado foi moito mellor que intentar parchear o que había.

4. **O teu coñecemento do dominio dirixe o proceso.** A IA non vai corrixir erros conceptuais que non sabe que o son (Fases 6-7). O usuario sabía que os burn rates derivan dun único SLO e dirixiu esa corrección.

5. **Pide formato explicitamente.** Táboas markdown, idioma, emojis, valores concretos ao lado das alertas -- nada disto aparece por iniciativa da IA. Se o queres, pídeo.

6. **Cuestiona o que a IA produce.** O mellor resultado sae da fricción entre o que a IA xera e o que o usuario sabe que debería ser. A combinación das 3 ventás (🚨) como sinal fiable saíu desta fricción.

7. **O resultado final é un coproduto.** Nin só da IA (que comete erros e non ten criterio de dominio) nin só do usuario (que tería tardado moito máis en xerar as táboas e cálculos á man). O valor está na iteración.

---

## Resultado final

O exemplo completo está en [`añadir_exemplos_de_alumnos_al_plan_de_slides.plan.md`](añadir_ejemplos_de_alumnos_al_plan_de_slides_0d114738.plan.md) e contén:

- **Contexto** con SLI, SLO (90%), SLA (75%), burn rates e referencia a Google
- **Juanito** -- 2 faltas espazadas: alertas individuais pero 🚨 nunca salta. Caso "falsa alarma"
- **Pepito** -- 3 faltas seguidas: 🚨 en V10 (1 semana antes de romper SLA). Reacciona e recupérase
- **Menganito** -- 4 faltas + recaída: 🚨 múltiples veces, SLA roto dende V11, non aproba

A mensaxe central: a diferenza entre Pepito e Menganito non é o número de alertas, senón **reaccionar á sinal 🚨 a tempo**.
