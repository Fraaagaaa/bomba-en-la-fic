# Arquitectura cliente-servidor
Baséase na organización de **funcionalidades como servizos independentes**, proporcionados por compoñentes específicos.
A maior **vantaxe** é a robustez, xa que fallos nun servizo non afectan ao funcionamento do resto de servizos ofrecidos polo sistema.
O maior **inconveniente** é que para que os clientes non se acoplen cos servizos, precisamos un directorio intermedio que pode converterse en limitante do rendemento.
## Arquitectura cliente-servidor distribuído
Baséase, ao igual que a arquitectura cliente/servidor clásica, na organización de **funcionalidades como servizos independentes**, proporcionados por compoñentes específicos, e **despregados en máquinas diferentes**.
A maior **vantaxe** fronte á cliente/servidor clásica é que incrementa a súa robustez, escalabilidade e rendemento. O maior **inconveniente** segue a ser a necesidade dun directorio intermedio.

Preséntase en dúas variantes:
- **Cliente lixeiro**, encargado únicamente da representación da interface, e onde os servidores implementan toda a lóxica dos servizos.
	- A maior **vantaxe** é que son clientes fáciles de manter (importante se o número é elevado).
	- O maior **incoveniente** é que se intercambia gran cantidade de información pola rede.
- **Cliente pesado**, encargado de parte da lóxica dalgúns servizos, ademais da representación da interface.
	- A maior **vantaxe** é que aproveita a capacidade de proceso dos clientes.
	- O maior **incoveniente** é que o despregue e o mantemento requiren maior esforzo.

## Caracterización da arquitectura cliente-servidor
Descripción: As funcionalidades do sistema se organizan en servizos, cada un deles implementado por un compoñente dedicado. Os clientes do sistema usan estes servizos de xeito transparente.<br>
Aplicabilidade: Úsase cando se constrúen sistemas de xeito incremental, xa que non todos os servizos teñen que estar rematados para poder ofertar os que si o están aos clientes. Tamén cando a heteroxeneidade dos servizos a ofertar non encaixa con outras arquitecturas.<br>
## Caracterización arquitectura cliente-servidor distribuído
Descripción: As funcionalidades do sistema se organizan en servizos, cada un deles implementado por un compoñente dedicado, **nun servidor específico**. Os clientes do sistema usan estes servizos de xeito transparente.<br>
Aplicabilidade: Úsanse cando se quere aumentar a robustez, escalabilidade ou rendemento do cliente/servidor clásico.<br>

# Vantaxes e desvantaxes dos dous
Vantaxes: Os servizos son independientes entre sí, polo que poden duplicar para facer fronte a alta demanda, e o fallo dun (ou mesmo un fallo hardware) non debe afectar ao resto, de xeito que este estilo ofrece moi boa robustez. Tamén resulta doado ofrecer certos servizos a certos clientes, limitando a sua expansión.<br>
Desvantaxes: O desacoplamento de servizos e clientes lévase a cabo a través de servidores intermedios que balancean a carga e fan funcións de directorio, con risco de limitar o rendemento se non son suficientemente eficientes. O rendemento global é dificil de determinar, xa que pode depender moito de cada servizo, e en grande medida tamén da canle de comunicacións.