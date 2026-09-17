#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# exerbda.py: 
# Programa python para completar seguindo o boletín de exercicios de BDA.
#
# Autor: Miguel Rodríguez Penabad (miguel.penabad@udc.es)
# Data: 2025-06-20

import psycopg2
import psycopg2.extras
import psycopg2.extensions
import psycopg2.errorcodes
import sys


## ------------------------------------------------------------
def pg_general_error(e):
    """
    Imprime un erro xenérico de PosgtreSQL, incluíndo pg_code e pg_error
    NOTA: Non sirve para capturar o erro de connect() xa que 
          este non ten pgcode nin pgerror
    Args:
        e: excepción (psycopg2.Exception ou subclase)
    """
    print(f"Erro xeral de PostgreSQL [{e.pgcode}]: {e.pgerror}")

## ------------------------------------------------------------
def connect_db():
    """
    Conéctase á BD. En caso de fallo mostra un erro e sae do programa.
    Returns:
        Unha conexión á BD (psycopg2.extensions.connection)
    """
    try:
        conn = psycopg2.connect()
        conn.autocommit = False
        return conn
    except psycopg2.Error as e:
        print("Non foi posible conectarse a PostgresSQL.")
        sys.exit(2)
    # pass

## ------------------------------------------------------------
def disconnect_db(conn):
    """
    Pecha a conexión coa BD
    Args:
        conn: Conexión a BD activa
    """

    conn.commit()
    conn.close()
    # pass

## ------------------------------------------------------------
def create_table(conn):
    """
    Crea a táboa artigo (codart, nomart, prezoart)
    Args:
        conn: Conexión a BD activa
    """
    sql = """
    CREATE TABLE artigo(
    codart int constraint pk_artigo primary key,
    nomart varchar(30) not null,
    prezoart numeric(5,2) constraint ch_art_prezo_pos check (prezoart >0)
    );
    """

    with conn.cursor() as cur:
        try:
            cur.execute(sql)
            conn.commit()
            print("Táboa artigo creada.")
        except psycopg2.Error as e:
            if e.pgcode == psycopg2.errorcodes.DUPLICATE_TABLE:
                print("A táboa artigo xa existe. Non se crea.")
            else:
                pg_general_error(e)
            conn.rollback()

## ------------------------------------------------------------
def add_row(conn):
    """
    Pide por teclado o código, nome e prezo, e inserta unha fila na táboa artigo
    Args:
        conn: Conexión a BD activa
    """
    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_READ_COMMITTED

    scod = input("Código: ")
    cod = None if scod == "" else int(scod)
    nome = input("Nome: ") or None
    sprezo = input("Prezo: ")
    prezo = None if sprezo == "" else float(sprezo)
    
    sql = """
    INSERT INTO artigo (codart, nomart, prezoart)
    VALUES (%(c)s, %(n)s, %(p)s)
    """
    
    params = {'c': cod, 'n': nome, 'p': prezo}

    with conn.cursor() as cur:
        try:
            cur.execute(sql, params)
            conn.commit()
            print(f"Artigo engadido, filas insertadas: {cur.rowcount}")
        except psycopg2.Error as e:
            if e.pgcode == psycopg2.errorcodes.NOT_NULL_VIOLATION:
                if e.diag.column_name == "codart":
                    print("O código do artigo é requerido.")
                else:
                    print("O nome do artigo é requerido.")
            elif e.pgcode == psycopg2.errorcodes.UNIQUE_VIOLATION:
                print(f"O código de artido {cod} xa esite para outro artigo. Non se engade")
            elif e.pgcode == psycopg2.errorcodes.CHECK_VIOLATION:
                print(f"O prezo introducido ({prezo}) non é válido. Debe ser positivo")
            else:
                pg_general_error(e)
            conn.rollback() # Rollback sempre
## ------------------------------------------------------------
def delete_row(conn):
    """
    Pide por teclado un código e borra unha fila na táboa artigo
    Args:
        conn: Conexión a BD activa
    """

    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_READ_COMMITTED

    scod = input("Código do artigo a eliminar: ")
    cod = None if scod == "" else int(scod)

    sql = """
    DELETE FROM artigo
    WHERE codart = %(c)s
    """

    params = {'c': cod}


    with conn.cursor() as cur:
        try:
            cur.execute(sql, params)
            conn.commit()
            if(cur.rowcount == 0):
                print(f"O artigo con código {cod} non existe")
            else:
                print(f"Artigo borrado, filas borradas: {cur.rowcount}")
        except psycopg2.Error as e:
            pg_general_error(e)
            conn.rollback() # Rollback sempre
## ------------------------------------------------------------
def find_by_id(conn, control_tx = True):
    """
    Pide por teclado un nome e mostra a información do artigo
    Args:
        conn: Conexión a BD activa
        control_tx: Para usarse con otras funciones
    """

    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_READ_COMMITTED

    scod = input("Código do artigo a buscar: ")
    cod = None if scod == "" else int(scod)

    sql = """
    SELECT nomart, prezoart 
    FROM artigo
    WHERE codart = %(c)s
    """
    params = {'c': cod}

    retval = None

    with conn.cursor(cursor_factory=psycopg2.extras.DictCursor) as cur:
        try:
            cur.execute(sql, params)
            row = cur.fetchone()
            if row:
                retval = cod
                print(f"Código: {cod}   Nome: {row['nomart']}   Prezo: {row['prezoart'] or 'Descoñecido'}")
            else:
                print(f"O artigo {cod} non existe.")
            if control_tx:
                conn.commit()
        except psycopg2.Error as e:
            pg_general_error(e)
            if control_tx:
                conn.rollback() # Rollback sempre
    return retval

## ------------------------------------------------------------
def find_by_name(conn):
    """
    Pide por teclado un nome e mostra a información do artigo
    Args:
        conn: Conexión a BD activa
    """

    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_READ_COMMITTED

    patron = input("Introduce (parte do) nome dos artigos ")
    patron = f"%{patron}%"

    sql = """
    SELECT codart, nomart, prezoart 
    FROM artigo
    WHERE nomart ILIKE %(pat)s
    """
    params = {'pat': patron}


    with conn.cursor(cursor_factory=psycopg2.extras.DictCursor) as cur:
        try:
            cur.execute(sql, params)
            rows = cur.fetchall()
            print(f"Atopáronse {cur.rowcount} artigos.")
            for row in rows:
                print(f"Código: {row['codart']} Nome: {row['nomart']}   Prezo: {row['prezoart'] or 'Descoñecido'}")

            conn.commit()
        except psycopg2.Error as e:
            pg_general_error(e)
            conn.rollback() # Rollback sempre
## ------------------------------------------------------------
def update_row(conn):
    """
    Pide por teclado un código de artigo e permite modificar os seus datos
    Args:
        conn: Conexión a BD activa
    """
    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_READ_COMMITTED

    cod = find_by_id(conn, control_tx = False)

    if cod is None:
        conn.rollback()
        return

    nome = input("Novo nome: ") or None
    sprezo = input("Novo prezo: ")
    prezo = None if sprezo == "" else float(sprezo)

    sql = """
        UPDATE artigo
        SET nomart = %(n)s, prezoart = %(p)s
        WHERE codart = %(c)s
    """

    params = {'n': nome, 'p': prezo, 'c': cod}


    with conn.cursor(cursor_factory=psycopg2.extras.DictCursor) as cur:
        try:
            cur.execute(sql, params)
            conn.commit()
            print("Artigo actualizado correctamente")
        except psycopg2.Error as e:
            if e.pgcode == psycopg2.errorcodes.NOT_NULL_VIOLATION:
                print("O nome do artigo é requerido.")
            elif e.pgcode == psycopg2.errorcodes.CHECK_VIOLATION:
                print(f"O prezo introducido ({prezo}) non é válido. Debe ser positivo")
            else:
                pg_general_error(e)
            conn.rollback() # Rollback sempre
## ------------------------------------------------------------
def increase_price(conn):
    """
    Pide por teclado un código de artigo e permite modificar os seus datos
    Args:
        conn: Conexión a BD activa
    """

    conn.isolation_level = psycopg2.extensions.ISOLATION_LEVEL_SERIALIZABLE
    
    cod = find_by_id(conn, control_tx = False)

    if cod is None:
        conn.rollback()
        return

    sinc = input("Incremento: ")
    inc = None if sinc == "" else float(sinc)

    sql = """
        UPDATE artigo
        SET prezoart = prezoart * (1 + %(i)s /100.0)
        WHERE codart = %(c)s
    """

    params = {'i': inc, 'c': cod}


    with conn.cursor(cursor_factory=psycopg2.extras.DictCursor) as cur:
        try:
            cur.execute(sql, params)
            input("Pulse ENTER")
            conn.commit()
            print("Artigo actualizado correctamente")
        except psycopg2.Error as e:
            if e.pgcode == psycopg2.errorcodes.CHECK_VIOLATION:
                print(f"o incremento introducido ({inc}) porque produce un prezo non positivo.")
            elif e.pgcode == psycopg2.errorcodes.SERIALIZATION_FAILURE:
                print(f"Non se pode actualizar o prezo. Outra persoa xa o modificou.")
            else:
                pg_general_error(e)
            conn.rollback() # Rollback sempre
## ------------------------------------------------------------
def menu(conn):
    """
    Imprime un menú de opcións, solicita a opción e executa a función asociada.
    'q' para saír.
    Args:
        conn: Conexión a BD activa
    """
    MENU_TEXT = """
      -- MENÚ --
1 - Crear táboa artigo      2 - Engadir artigo      3 - Borrar artigo
4 - Buscar por id           5 - Buscar por nome     6 - Modificar artigo
7 - Actualizar prezo
q - Saír   
"""
    opcions= {
            '1': create_table,
            '2': add_row,
            '3': delete_row,
            '4': find_by_id,
            '5': find_by_name,
            '6': update_row,
            '7': increase_price
            }
    while True:
        print(MENU_TEXT)
        tecla = input('Opción> ').strip()
        if tecla == 'q':
            break
        fun = opcions.get(tecla)    
        fun(conn) if fun else print("Opción inválida.")


## ------------------------------------------------------------
def main():
    """
    Función principal. Conecta á bd e executa o menú.
    Cando sae do menú, desconecta da bd e remata o programa
    """
    print('Conectando a PosgreSQL...')
    conn = connect_db()
    print('Conectado.')
    menu(conn)
    disconnect_db(conn)

## ------------------------------------------------------------

if __name__ == '__main__':
    main()
