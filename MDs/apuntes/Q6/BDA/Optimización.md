# Optimización
# Introducción
Usando un SXBD relacional, as consultas escríbense habitualmente en SQL, unha linguaxe declarativa. Indicamos *que* datos queremos, pero non *como* obtelos.
Pode haber varias formas (estratexias ou plans de execución) de obter os mesmos datos para cada unha mesma consulta.
**Obxectivo**: Obter un plan de execución eficiente...

O *optimizador* de consultas é o compoñente do SXBD que se encarga de xenerar ese plan de execución eficiente.
> [!NOTE]
> O nome "optimizador" non debe levar a engano: a estratexia seleccionada non ten por que ser a mellor (a óptima), ten que ser unha estratexia eficiente.

Calcular a estratexia óptima pode ser posible ou máis costos que executar a propia consulta.
Normalmente redúcese o espazo de búsqueda dos posibles plans de execución, considerando só os que por heurísitca serán máis baratos.

# Fases de execución dunha consulta
1. Transformación a linguaxe interpretado (álxebra relacional extendida)
    - Análise da consulta en SQL (sintáctico, léxico, semántico) para verificar que é correcta.
    - Verificación de outros aspectos, por ex. de seguridade (privilexios de acceso).
    - Transformación a unha expresión de álxebra relacional (normalmente representada por unha árbore ou un grafo).
2. Optimización alxebraica
    - Optimización baseada en heurísticas xerais.
    - Non ten en conta os datos.
    - Produce a forma canónica da consulta: equivalente á orixinal, pero probablemente algo máis eficiente.
3. Optimización baseada en costes.
    - Utiliza estatísticas da base de datos e coñecementos sobre os aspectos físicos das táboas involucradas. Esta información estará dispoñible no catálogo da basa de datos.
    - Busca procedementos candidatos para executar as operacións básicas, considerando os seus costes.
    - Produce varios plans de execución, compara os costes e selecciona o de menor coste.
4. Xeneración do código executable e execución da consulta, obtendo os datos.

# Transformación a álxebra relacional

