#include "client.h"
#include <readline/readline.h>
#include <string.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");


	config = iniciar_config();

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PORT");
	valor = config_get_string_value(config, "VALUE");

	//Loggear valor de config
	log_info(logger, ip);
	log_info(logger, puerto);
	log_info(logger, valor);

	//leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	char* loggerFileName = string_from_format("client.log");
	char* programName = string_from_format("client");
	t_log_level logLevel = LOG_LEVEL_INFO;

	nuevo_logger = log_create(loggerFileName, programName, 0, logLevel);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	char* configFilePath = string_from_format("client.config");

	nuevo_config = config_create(configFilePath);
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	do {
		leido = readline("> ");

		// Acá la idea es que imprimas por el log lo que recibis de la consola.
		log_info(logger, leido);
	}
	while (strcmp(leido, "") != 0);
	log_info(logger, "Fin de lectura");
	free(leido);

}

void paquete(int conexion)
{
	char* leido;
	    t_paquete* paquete;
	    paquete = crear_paquete();

	    leido = readline("Ingrese (Vacio para salir)>");

	    while(strcmp(leido, "\0")!=0){
	        agregar_a_paquete(paquete,leido,strlen(leido)+1);
	        free(leido);
	        leido = readline("Ingrese (Vacio para salir)>");
	    }

	    enviar_paquete(paquete,conexion);
	    eliminar_paquete(paquete);
	    free(leido);

	//Ahora toca lo divertido!

	//char* lineasAEnviar;

	//t_paquete* paquete;

	//paquete = crear_paquete();

	//do {
	//	lineasAEnviar = readline("> ");
	//	agregar_a_paquete(paquete, lineasAEnviar, strlen(lineasAEnviar) + 1);
	//} while (strcmp(lineasAEnviar, "") != 0);

	//enviar_paquete(paquete, conexion);
	//free(lineasAEnviar);

	//eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado

	free(1);
	log_destroy(logger);
	config_destroy(config);
}
