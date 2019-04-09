/** @file servidor_u_cc.c
 *  @brief Archivo principal del Servidor.
 *
 *  Contiene el programa principal que ejecutará el servidor, así como las
 *  funciones principales y aplicaciones que puede invocar el cliente.
 *
 *  @author Matias Navarro
 */

/**
 * @brief Funcion 
 * @author Navarro, Matias Alejandro
 * @param 
 * @date 05/04/2019
 * @return 
 */

#include "../../includes/comunes_unix.h"
#include "../../includes/funciones_servidor_unix.h"

/**
* @brief Función principal del Servidor.
*
* Crea un socket, espera hasta 5 conexiones
* y ejecuta las funciones que recibe del cliente.
*/
int main(int argc, char *argv[])
{
	int sockfd, newsockfd, servlen, n, pid;
	unsigned int clilen;
	struct sockaddr_un cli_addr, serv_addr;
	char buffer[TAM];
	char promp[TAM];

	//Cargo los usuarios al sistema
	setUsers();

	/* Se toma el nombre del socket de la línea de comandos */
	if (argc != 2)
	{
		printf("Uso: %s <nombre_de_socket>\n", argv[0]);
		exit(1);
	}

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("creación de  socket");
		exit(1);
	}

	/* Remover el nombre de archivo si existe */
	unlink(argv[1]);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1]);
	servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
	{
		perror("ligadura");
		exit(1);
	}

	printf("Proceso: %d - socket disponible: %s\n", getpid(), serv_addr.sun_path);

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	while (1)
	{
		int conect;
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (newsockfd < 0)
		{
			perror("accept");
			exit(1);
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0)
		{ // proceso hijo
			close(sockfd);

			//Comprobacion de usuarios
			conect = userLog(promp);
			if (conect == 1)
			{
				printf("Autenticacion CORRECTA\n");
				getpromp(promp);
				n = write(newsockfd, "Servidor Conectado", sizeof("Servidor Conectado"));
			}
			else
			{
				printf("Error de autenticacion \n");
				exit(1);
			}

			while (1)
			{
				//Ingresa uno de los comando posibles para mandar al satelite
				if(conect==1){
					n = setComando(newsockfd, promp);
					if(n==-1){
						conect=0;
						write(newsockfd,"Conexion Cerrada",sizeof("Conexion Cerrada"));
						close(newsockfd);
					}
				}
							

				memset(buffer, 0, TAM);
				// n = read(newsockfd, buffer, TAM - 1);
				// if (n < 0)
				// {
				// 	perror("lectura de socket");
				// 	exit(1);
				// }

				// printf("%s ", promp);
				// printf("PROCESO: %d. ", getpid());
				// printf("Recibí: %s \n", buffer);
				// fflush(stdout);

				// n = write(newsockfd, "Obtuve su mensaje", 18);
				// if (n < 0)
				// {
				// 	perror("escritura en socket");
				// 	exit(1);
				// }

				// Verificación de si hay que terminar
				//buffer[strlen(buffer) - 1] = '\0';
				if (strcmp("fin", buffer) == 0)
				{
					printf("PROCESO %d. Como recibí 'fin', termino la ejecución.\n\n", getpid());
					exit(0);
				}
			}
		}
		else
		{
			printf("\n \nSERVIDOR: Nuevo cliente, que atiende el proceso hijo: %d\n", pid);
			close(newsockfd);
		}
	}

	return 0;
}

/**
 * @brief Funcion encargada de cargar los distintos usuarios en el servidor.
 * @date 05/04/2019.
 * @author Navarro, Matias Alejandro.
 */
void setUsers()
{
	strcpy(users[0].uname, "Nicolas"), strcpy(users[0].pass, "nn26");
	strcpy(users[1].uname, "Federico"), strcpy(users[1].pass, "fn25");
	strcpy(users[2].uname, "Matias"), strcpy(users[2].pass, "mn24");
	strcpy(users[3].uname, "Ciro"), strcpy(users[3].pass, "cn5");
	strcpy(users[4].uname, "Bianca"), strcpy(users[4].pass, "bn4");
	strcpy(users[5].uname, "Geronimo"), strcpy(users[5].pass, "gn0");
}

/**
 * @brief Funcion que comprueba la autenticacion de usuarios en el servidor. 
 * Reingresa el usuario, hasta que la contraseña y el usuario sean correctas.
 * @param promp: arreglo donde se guarda el user[i].uname@ para la construccion
 * del promp si el usuario ingresado es correcto.
 * @return 1: si el usuario es correcto.
 * 		  -1: si el usuario es incorrecto.	
 * @date 05/04/2019.
 * @author Navarro, Matias Alejandro.
 */
int userLog(char promp[])
{
	char usuario[20], password[20];
	int error = 0;
	printf("Autenticacion de usuario\n");

	//Comprueba que el usuario sea correcto. Solo permite 3 errores
	while (error < 3)
	{
		printf("Usuario: ");
		//Ingreso del usuario
		fgets(usuario, 20, stdin);
		fflush(stdout);
		strtok(usuario, "\n");

		printf("Password: ");
		//Ingreso de la contraseña
		fgets(password, 20, stdin);
		fflush(stdout);
		strtok(password, "\n");

		//Comprobacion de Usuario y Contraseña
		for (int i = 0; i < CANT; i++)
		{
			if (strcmp(users[i].uname, usuario) == 0)
			{
				if (strcmp(users[i].pass, password) == 0)
				{
					strcpy(promp, users[i].uname);
					return 1;
					break;
				}
			}
		}

		error++;
	}
	return -1;
}

/**
 * @brief Funcion que arma el promp completo user[i].uname@hostname: .
 * @param promp: arreglo donde se arma el promp
 * @date 05/04/2019
 * @author Navarro, Matias Alejandro.
 */
void getpromp(char promp[])
{
	char hostname[TAM];

	//Concatena "@" al promp
	strcat(promp, "@");
	//Obtiene el nombre del host
	gethostname(hostname, TAM);
	strcat(promp, hostname);
}

/**
 * @brief Funcion que imprime los comandos validos que puede se pueden ingresar desde
 * el servidor.
 * @date 05/04/2019.
 * @author Navarro, Matias Alejandro
 */
void getComandosValidos()
{
	printf("\n");
	printf("- update firmware: actualiza el firmware del satelite\n");
	printf("- get telemetria: obtiene los datos del satelite\n");
	printf("- start scanning: comienza el escaneo de la tierra\n");
	printf("- exit: apagar el sistema\n");
	printf("\n");
	fflush(stdout);
}

/**
 * @brief Funcion que permite ingresar los distintos comandos disponibles. 
 * @param 	newsockfd: socket por donde se envia y reciben los datos.
 * 	 		promp: el prop del usuario del server (Ej: "Bianca@MatiasNavarro-Linux")..
 * @date 05/04/2019.
 * @author Navarro, Matias Alejandro.
 */
int setComando(int newsockfd, char promp[])
{
	char buffer[TAM];
	char infoSat[TAM];
	int v, flag=1;

	//Bucle que espera los comandos
	while (flag)
	{
		printf("%s: ", promp);
		memset(buffer, 0, sizeof(buffer));
		//Ingreso de comando
		fgets(buffer, sizeof(buffer) - 1, stdin);
		strtok(buffer, "\n");

		//Comprueba que tipo de comando se ingreso
		//Update
		if (strcmp(buffer, "update firmware") == 0)
		{
			printf("Actualizando Firmware\n");
			write(newsockfd, buffer, sizeof(buffer));
			sleep(2);
			updateFirmware(newsockfd);
		}
		//Telemetria
		else if (strcmp(buffer, "get telemetria") == 0)
		{
			printf("Obteniendo telemetria\n \n");
			write(newsockfd, buffer, sizeof(buffer));
			sleep(2);
			v = telemetria(newsockfd, infoSat);
			if (v == 0)
			{
				printf("Telemetria completada exitosamente\n");
			}
			else
			{
				printf("Error durante la telemetria\n");
			}
		}
		//Star Scanning
		else if (strcmp(buffer, "start scanning") == 0)
		{
			printf("Start Scannig\n");
			write(newsockfd,buffer,sizeof(buffer));
			v = startScanning(newsockfd);
			sleep(2);
			if(v==0){
				printf("Escaneo completo\n");
			}
			else
			{
				printf("Error durante el escaneo\n");
			}
			
		}
		//Help
		else if (strcmp(buffer, "help") == 0)
		{
			//Imprime los comandos disponibles
			getComandosValidos();
		}
		//Exit
		else if (strcmp(buffer, "exit") == 0)
		{
			printf("Apagando Sistema\n");
			return -1;
		}
		//Comando invalido
		else
		{
			printf("Comando invalido. Ingrese 'help' para mas informacion\n");
		}
	}
	return -1;
}

/**
 * @brief Funcion que actualiza el firmware del satelite. Lee un archivo binario y lo envio.
 * @param newsockfd: socket por donde se envia y reciben los datos.
 * @date 05/04/2019
 * @author Navarro, Matias Alejandro
 */
void updateFirmware(int newsockfd)
{
	FILE *firmware;
	char buffer[TAM], send[TAM];
	int size, read_size, num_packet = 1, n;
	//Limpia lo buffers
	memset(buffer, 0, sizeof(buffer));
	memset(send, 0, sizeof(send));

	n = read(newsockfd, buffer, sizeof(buffer));
	if (n < 0)
	{
		printf("Error al leer el socket");
		return;
	}
	//Compruebo que el satelite este listo para la actualizacion
	if (strcmp(buffer, "OK") == 0)
	{
		printf("Satelite Listo\n");
	}
	else
	{
		printf("Error en el update\n");
		return;
	}

	//Abre el binario
	firmware = fopen("../../bin/firmwareUpdate.bin", "r");
	if (firmware == NULL)
	{ //Comprueba que el archivo no este vacio
		printf("Error al cargar el binario :c\n");
		return;
	}

	fseek(firmware, 0, SEEK_END);
	size = ftell(firmware);
	fseek(firmware, 0, SEEK_SET);
	// printf("Size %i\n", size);

	n = write(newsockfd, &size, sizeof(size));
	if (n < 0)
	{
		printf("Error en el update\n");
		return;
	}

	n = read(newsockfd, &buffer, sizeof(buffer));
	if (n < 0)
	{
		printf("Error en el update\n");
		return;
	}

	while (!feof(firmware))
	{
		//Lee del archivo y lo coloca en el buffer
		read_size = fread(send, 1, sizeof(size) - 1, firmware);

		//Envia el dato
		write(newsockfd, send, read_size);
		num_packet++;

		//Limpia el buffer
		memset(send, 0, sizeof(send));
	}

	fclose(firmware);
	sleep(2);
	printf("Actualizacion exitosa\n");
}

/**
 * @brief Funcion que obtiene la informacion de los distintos campos del cliente (satelite),
 * como son el ID, Update, Version de Firmware y Consumo de CPU.
 * @param newsockfd: socket por el cual se realiza la comunicacion con el cliente.
 *        infoStat: buffer donde se va a guardar los datos recibidos desde el satelite.
 * @return 0 si la comunicaicon no tuvo errores.
 *        -1 si ocurrio algun error.
 * @date 05/04/2019
 * @author Navarro, Matias Alejandro
 */
int telemetria(int newsockfd, char infoSat[])
{
	char buffer[TAM];
	int n;
	memset(buffer,0,sizeof(buffer));

	n = write(newsockfd,"OK",sizeof("OK"));
	if(n<0){
		//Error al conectar con el satelite
		return -1;
	}

	n = read(newsockfd,buffer,sizeof(buffer));
	if(n<0){
		//Error en la lectura
		return -1;
	}
	
	strcpy(infoSat,buffer);
	printf("%s\n",infoSat);
	fflush(stdout);

	return 0;
}

/**
 * @brief Funcion 
 * @author Navarro, Matias Alejandro
 * @param 
 * @date 05/04/2019
 * @return 
 */
int startScanning(int newsockfd){

	FILE *picture;
	char buffer[TAM];
	char archivo[32000];
	int size=0, reciv_size=0 ,read_size, num_packet = 1, packet_size, n;
	//Limpia lo buffers
	memset(buffer, 0, sizeof(buffer));
	memset(archivo, 0, sizeof(archivo));

	n = write(newsockfd, "OK", sizeof("OK"));
	if (n < 0)
	{
		printf("Error al leer el socket");
		return -1;
	}


	packet_size = read(newsockfd, &size, sizeof(size));
	if (packet_size < 0)
	{
		printf("Error en el update\n");
		return -1;
	}

	printf("Tamañano del archivo: %i\n", packet_size);
	//Verificacion del tamaño
	write(newsockfd, &size, sizeof(size));

	//Abre el archivo a "escribir" 
	picture = fopen("./earth.jpg", "w");
	if (picture == NULL)
	{
		printf("Error al abrir el archivo\n");
		return -1;
	}

	while (reciv_size < size)
	{
		memset(archivo, 0, sizeof(archivo));
		//Lee el tamaño del paquete
		packet_size = read(newsockfd, archivo, sizeof(archivo));
		if (packet_size < 0)
		{
			printf("Error en el update");
			return -1;
		}

		printf("Paquete %i recibido correctamente\n", num_packet);
		printf("Tamaño del paquete: %i\n", packet_size);

		read_size = fwrite(archivo, 1, packet_size, picture);
		if (read_size != packet_size)
		{
			printf("Error de escritura\n");
			printf("Error en el update");
			return -1;
		}

		reciv_size += read_size;
		num_packet++;

		printf("Tamaño total del binario recibido: %i\n", reciv_size);
	}

	fclose(picture);
	printf("......\n");
	printf("......\n");
	printf("......\n");
	printf("......\n");
	printf("......\n");

	return 0;
}