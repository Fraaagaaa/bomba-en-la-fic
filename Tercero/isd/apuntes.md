# APIs
HTTPClient en la capa cliente
Apache Thrift en Acceso a servicio y el modelo RPC
JDBC en la capa modelo
Servlets en la capa Servico
# Capas
Si se cambia algo de una capa, todas las partes de esa capa las hay que reintalar
## Capa de acceso a datos
Es donde están los DAO
Aquí es donde pueden salir SQL exeption
## Capa de Lógica de negocio
Esto mira las excepciones y si son viables las operaciones
p.e. mirar si está cancelada una encuesta
## Capa de servicios REST
Traduce URLs y devuelve los códigos

# Cambiar de gestor de bases de datos
Reemplazar el driver JDBC por el nuevo
Actualizar la configuración de los DataSources
# XML
El orden en los atributos importa y tienen que seguir el de referencia.
Los parsers XML de tipo "streaming" no construyen un árbol en memoria, sino que procesan secuencialmente el documento en bloques
# RPC
Para el programador, invocar una operación remota es similar a la invocación de un método de una librería local.
# Thrift
Cuando se utiliza Java como lenguaje para desarrollar un servicio, permite que el servicio se ejecute dentro de un servidor de aplicaciones
# Cacheos
Por defecto se cachean:
- SOLO LAS GET
- 200 OK
- 204 NO CONTENT
- 301 Moved Permanently
- 400 Bad request
- 404 Not found
- 405 Method not allowed

# Generar claves
Si la base de datos proporciona secuencias, puede lanzarse una consulta para que la base de datos genere una clave numérica y posteriormente realiza la inserción
Si la base de datos dispone de "columnas contador", primero hay que insertar la fila, sin especificar un valor para la clave, y posteriormente se puede usar un método de la API de JDBC, para recuperar el identificador generado

