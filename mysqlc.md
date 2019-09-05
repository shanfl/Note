#### C API Function Overview

- my_init(): Initializes global variables and the thread handler in thread-safe programs.

- mysql_affected_rows(): Returns the number of rows changed/deleted/inserted by the last UPDATE, DELETE, or INSERT query.

- mysql_autocommit(): Toggles autocommit mode on/off.

- mysql_change_user(): Changes the user and database on an open connection.

- mysql_character_set_name(): Returns the default character set name for the current connection.

- mysql_client_find_plugin(): Returns a pointer to a plugin.

- mysql_client_register_plugin(): Registers a plugin.

- mysql_close(): Closes a server connection.

- mysql_commit(): Commits the transaction.

- mysql_connect(): Connects to a MySQL server. This function is deprecated; use mysql_real_connect() instead.

- mysql_create_db(): Creates a database. This function is deprecated; use the SQL statement CREATE DATABASE instead.

- mysql_data_seek(): Seeks to an arbitrary row number in a query result set.

- mysql_debug(): Does a DBUG_PUSH with the given string.

- mysql_drop_db(): Drops a database. This function is deprecated; use the SQL statement DROP DATABASE instead.

- mysql_dump_debug_info(): Causes the server to write debug information to the log.

- mysql_eof(): Determines whether the last row of a result set has been read. This function is deprecated; use mysql_errno() or mysql_error() instead.

- mysql_errno(): Returns the error number for the most recently invoked MySQL function.

- mysql_error(): Returns the error message for the most recently invoked MySQL function.

- mysql_escape_string(): Escapes special characters in a string for use in an SQL statement.

- mysql_fetch_field(): Returns the type of the next table field.

- mysql_fetch_field_direct(): Returns the type of a table field, given a field number.

- mysql_fetch_fields(): Returns an array of all field structures.

- mysql_fetch_lengths(): Returns the lengths of all columns in the current row.

- mysql_fetch_row(): Fetches the next row from the result set.

- mysql_field_count(): Returns the number of result columns for the most recent statement.

- mysql_field_seek(): Puts the column cursor on a specified column.

- mysql_field_tell(): Returns the position of the field cursor used for the last mysql_fetch_field().

- mysql_free_result(): Frees memory used by a result set.

- mysql_get_character_set_info(): Returns information about default character set.

- mysql_get_client_info(): Returns client version information as a string.

- mysql_get_client_version(): Returns client version information as an integer.

- mysql_get_host_info(): Returns a string describing the connection.

- mysql_get_option(): Returns the value of a mysql_options() option.

- mysql_get_proto_info(): Returns the protocol version used by the connection.

- mysql_get_server_info(): Returns the server version number.

- mysql_get_server_version(): Returns the server version number as an integer.

- mysql_get_ssl_cipher(): Returns the current SSL cipher.

- mysql_hex_string(): Encodes a string in hexadecimal format.

- mysql_info(): Returns information about the most recently executed query.

- mysql_init(): Gets or initializes a MYSQL structure.

- mysql_insert_id(): Returns the ID generated for an AUTO_INCREMENT column by the previous query.

- mysql_kill(): Kills a given thread.

- mysql_library_end(): Finalizes the MySQL C API library.

- mysql_library_init(): Initializes the MySQL C API library.

- mysql_list_dbs(): Returns database names matching a simple regular expression.

- mysql_list_fields(): Returns field names matching a simple regular expression.

- mysql_list_processes(): Returns a list of the current server threads.

- mysql_list_tables(): Returns table names matching a simple regular expression.

- mysql_load_plugin(): Loads a plugin.

- mysql_load_plugin_v(): Loads a plugin.

- mysql_more_results(): Checks whether any more results exist.

- mysql_next_result(): Returns/initiates the next result in multiple-result executions.

- mysql_num_fields(): Returns the number of columns in a result set.

- mysql_num_rows(): Returns the number of rows in a result set.

- mysql_options(): Sets connect options for mysql_real_connect().

- mysql_options4(): Sets connect options for mysql_real_connect().

- mysql_ping(): Checks whether the connection to the server is working, reconnecting as necessary.

- mysql_plugin_options(): Sets a plugin option.

- mysql_query(): Executes an SQL query specified as a null-terminated string.

- mysql_real_connect(): Connects to a MySQL server.

- mysql_real_escape_string(): Escapes special characters in a string for use in an SQL statement, taking into account the current character set of the connection.

- mysql_real_escape_string_quote(): Escapes special characters in a string for use in an SQL statement, taking into account the current character set of the connection and the quoting context.

- mysql_real_query(): Executes an SQL query specified as a counted string.

- mysql_refresh(): Flushes or resets tables and caches.

- mysql_reload(): Tells the server to reload the grant tables.

- mysql_reset_connection(): Resets the connection to clear session state.

- mysql_reset_server_public_key(): Clears a cached RSA public key from the client library.

- mysql_result_metadata(): Whether a result set has metadata.

- mysql_rollback(): Rolls back the transaction.

- mysql_row_seek(): Seeks to a row offset in a result set, using value returned from mysql_row_tell().

- mysql_row_tell(): Returns the row cursor position.

- mysql_select_db(): Selects a database.

- mysql_server_end(): Finalizes the MySQL C API library.

- mysql_server_init(): Initializes the MySQL C API library.

- mysql_session_track_get_first(): Gets the first part of session state-change information.

- mysql_session_track_get_next(): Gets the next part of session state-change information.

- mysql_set_character_set(): Sets the default character set for the current connection.

- mysql_set_local_infile_default(): Sets the LOAD DATA LOCAL handler callbacks to their default values.

- mysql_set_local_infile_handler(): Installs application-specific LOAD DATA LOCAL handler callbacks.

- mysql_set_server_option(): Sets an option for the connection (like multi-statements).

- mysql_sqlstate(): Returns the SQLSTATE error code for the last error.

- mysql_shutdown(): Shuts down the database server.

- mysql_ssl_set(): Prepares to establish an SSL connection to the server.

- mysql_stat(): Returns the server status as a string.

- mysql_store_result(): Retrieves a complete result set to the client.

- mysql_thread_end(): Finalizes a thread handler.

- mysql_thread_id(): Returns the current thread ID.

- mysql_thread_init(): Initializes a thread handler.

- mysql_thread_safe(): Returns 1 if the clients are compiled as thread-safe.

- mysql_use_result(): Initiates a row-by-row result set retrieval.

- mysql_warning_count(): Returns the warning count for the previous SQL statement.

Application programs should use this general outline for interacting with MySQL:
1. Initialize the MySQL client library by calling mysql_library_init().

2. Initialize a connection handler by calling mysql_init() and connect to the server by calling mysql_real_connect().

3. Issue SQL statements and process their results. (The following discussion provides more information about how to do this.)

4. Close the connection to the MySQL server by calling mysql_close().

5. End use of the MySQL client library by calling mysql_library_end().

##### c api
1. mysql_fetch_fields || mysql_fetch_field
```
    unsigned int num_fields;
    unsigned int i;
    MYSQL_FIELD *fields;
    num_fields = mysql_num_fields(result);
    fields = mysql_fetch_fields(result);
    for(i = 0; i < num_fields; i++)
    {
        printf("Field %u is %s\n", i, fields[i].name);
    }
```
```
	//指向  mysql 的查询字段集
	MYSQL_FIELD *fieldptr = NULL;

	//取得各字段名和类型
	while ((fieldptr = mysql_fetch_field(m_resultptr)))
	{
		typeset_t typeset;
		typeset.index = m_fieldtype.size();
		typeset.length = fieldptr->length;
		typeset.name = fieldptr->name;
		typeset.type = SetFieldType(fieldptr->type);
		m_fieldtype.push_back(typeset);
	}
```
2. 

##### 存储过程

1. 查看存储过程:
```
    1.select  `name` from mysql.proc where `db` =  your_db_name  and  `type`  = 'PROCEDURE'
    2.show procedure status;
```
2. 查看存储过程代码:
```
    show create procedure proc_name;
    show create function func_name;
```


##### 增删改查CRUD