# Arquitectura líder-traballador
Baséase na presenza dun elemento (*lider*) **encargado da recepción e asignación de peticións** ao resto (*traballadores, centrados en tarefas específicas*), xunto coa súa xestión e coordinación.

A maior **vantaxe** é a separación clara entre as tarefas de xestión e as de execución de funcionalidades, que permite gran rendemento e escalabilidade.

O maior **inconveniente** é que o líder é un SPoF (*single point of failure*)

## Caracterización da arquitectura líder-traballador
Descripción: As peticións chegan ao sistema a través dun compoñente líder que concentra as responsabilidades de xestión, tanto das interaccións cos clientes como do resto de compoñentes específicos (os traballadores).<br>
Aplicabilidade: Este estilo resulta axeitado cando, ademáis da robustez que proporciona a diferenciación de tarefas administrativas vs. funcionalidades en máquinas diferentes, queremos ter a posibilidade de reacción elástica a cambios na carga/demanda do sistema.<br>
Vantaxes: O arranque/parada de traballadores permite optimizar o uso de recursos dando unha axeitada resposta aos niveles de demanda do sistema en cada momento.<br>
Desvantaxes: O líder é un punto único de fallo, polo que debe ser sometido a proba exhaustiva, técnicas de detección e recuperación ante erros, técnicas de reforzo da seguridade... para non comprometer a dispoñibilidade do sistema.