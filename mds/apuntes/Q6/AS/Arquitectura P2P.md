# Arquitectura P2P
Baséase na **facilitación do reparto de traballo** entre **compoñentes**, que son todos **equivaletnes**, capaces de realizar as mesmas tarefas.

A maior **vantaxe** reside na súa gran capacidade para a dispoñibilidade, ao non ter puntos únicos de fallo, e a escalabilidade, ao poder incorporar compoñentes de xeito transparente.

O maior **inconveniente** reside na ausencia de control coordinado ou sincronización (non eventual) entre os compoñentes, e os posibles riscos de seguridade.

## Caracterización da arquitectura peer-to-peer

Descripción: Sistemas descentralizados nos que calquera compoñente (par) pode atender una determinada petición recibida.<br>
Aplicabilidade: Sistemas nos que os pares poden variar dinamicamente mais son quen de realizar as mesmas tarefas empregando a súa información local. Pode aparecer un compoñente específico (*super-peer*) para facilitar que os pares coñezan aos seus veciños e os clientes coñezan algún par.<br>
Vantaxes: Aproveitamento óptimo dos recursos dispoñibles en cada momento no sistema (pares), configuración dinámica e auto-organizada do sistema.<br>
Desvantaxes: Pode ser precisa unha aproximación semi-centralizada para simplificar os mecanismos ou protocolos de auto-descubrimentos entre pares, ou para introducir algunha medida de seguridade na entrada ao sistema de novos compoñentes/clientes. Os pares integran tanto lóxica de xestión (veciñanza) como lóxica de negocio (tarefas).