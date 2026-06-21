# Arquitectura en repositorio
Baséase na **facilitación do intercambio de información** entre compoñentes, que se canaliza a través dun **repositorio central compartido** que é accedido por todos.

A maior **vantaxe** é a minimización do número de envíos de información, especialmente relevante se a cantidade de información a compartir é grande.

O maior **inconveniente** é que o repositorio é un punto único de fallo.

## Caracterización da arquitectura en repositorio
Descripción: Todos os datos do sistema se xestionan nun repositorio central accesible a todos os compoñentes. Os compoñentes do sistema non interactúan entre eles, só através do repositorio.<br>
Aplicabilidade: Sistemas nos que se precisa intercambiar gran cantidade de información, ou nos que a aparición ou modificación de información no repositorio funciona como disparador de accións nos diferentes compoñentes. Nos casos nos que os compoñentes do sistema se especializan en só producir ou só consumir información.
<br>
Vantaxes:
- Os compoñentes do sistema son completamente independentes uns doutros, polo que os cambios neles nunca se afectan entre si.
- As políticas sobre os datos (por exemplo, *backups*) só se teñen que realizar sobre o repositorio compartido.
- Os cambios na información son inmediatamente visibles por todos os compoñentes.<br>

Desvantaxes:
- O repositorio é un punto único de fallo, polo que a súa distribución ou sincronización cunha copia de seguridade pode ser problemática.
- O formato da información do repositorio debe ser válida para todos os compoñentes, para evitar perdas de rendemento en conversións.
