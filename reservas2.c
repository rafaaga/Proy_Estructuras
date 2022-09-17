#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ocupacion{
   int fechas[ 14 ];
   char cont;
}ocupacion;

typedef struct reservas{
   char nombre[ 20 ];
   char fecha[ 20 ];
}reservas;

void calendar(char* s)
{
   time_t t;
   struct tm *tm;
   char fecha[100];
   char hora[100];

   t=time(NULL);
   tm=localtime(&t);
   strftime(fecha, 100, "%d/%m/%Y ", tm);
   strftime(hora, 100, "%H:%M:%S", tm);
   const char* str1 = fecha;
   const char* str2 = hora;
   char buffer[100];
   strcat(strcpy(buffer, str1), str2);
	strcpy(s, buffer);
	return;
}


int menu(){
   printf( "Restaurante Pelagato\n" );
   printf( "====================\n\n" );
   printf( "1. Hacer Reserva\n" );
   printf( "2. Editar Reserva\n" );
   printf( "3. Consultar Reserva\n" );
   printf( "4. Deshacer Reserva\n" );
   printf( "5. Intercambiar Reservas\n" );
   printf( "6. Listar Reservas\n" );
   printf( "7. Generar Reporte\n" );
   printf( "8. Log\n" );
   printf( "0. Salir\n\n" );
   printf( "Seleccionar opción: " );
}

int main(){
   FILE *memoria;
   FILE *log = fopen( "log.txt", "a" );
   reservas cliente[ 100 ];
   ocupacion disponible[ 100 ];
   int opc, n = 0, mes, dia, hour, i, j, res = 0, sim = 0, lotto;
   char horalog[100];
   calendar(horalog);
   char fecha[ 20 ];
   char nombre[14];
   memoria = fopen( "reservas.dat", "rb" );
   fread( &n, sizeof( int ), 1, memoria );
   fread( &res, sizeof( disponible ), 1, memoria );
   fread( cliente, sizeof( cliente ), 1, memoria );
   fread( disponible, sizeof( disponible ), 1, memoria );
   fclose( memoria );
   do{
   menu();
   scanf( "%d", &opc );
   switch ( opc ){
      case 1:
         printf( "Nombre = " );
         scanf( "%s", nombre );
         strcpy(fecha, "");
         printf( "Mes a hacer la reserva (1 - 12) = " );
         scanf( "%d", &mes );
         while ( mes < 0 || mes > 12){
            printf( "Seleccione una opción valida = " );
            scanf( "%d", &mes );
         }
         if( mes < 10 ){
            strcat(fecha, "0");
         }
         char *num;
         if( asprintf( &num, "%d", mes ) == -1 ) {
            perror( "asprintf" );
         }
         else{
            strcat( fecha, num );
            free( num );
         }
         strcat(fecha, '/');
         // Se asume que todos los meses tienen 30 días :)
         printf( "Día a hacer la reserva (1 - 30) = " );
         scanf( "%d", &dia );
         while ( dia < 0 || dia > 30){
            printf( "Seleccione una opción valida = " );
            scanf( "%d", &dia );
         }
         if( dia < 10 ){
            strcat(fecha, "0");
         }
         char *num2;
         if ( asprintf( &num2, "%d", dia ) == -1 ) {
            perror( "asprintf" );
         }
         else{
            strcat( fecha, num2 );
            free( num2 );
         }
         strcat( fecha, "/21 " );
         printf( "Hora: (1.16:00  2.18:00  3.20:00  4.22:00) = " );
         scanf( "%d", &hour );
          while ( hour < 0 || hour > 4){
            printf( "Seleccione una opción valida = " );
            scanf( "%d", &hour );
         }
         if ( hour == 1){
            strcat( fecha, "16:00\0" );
         }
         else if ( hour == 2){
            strcat( fecha, "18:00\0" );
         }
         else if ( hour == 3){
            strcat( fecha, "20:00\0" );
         }
         else if ( hour == 4){
            strcat( fecha, "22:00\0" );
         }
         if (res == 0){
            strcpy( cliente[ n ].nombre, nombre );
            strcpy( cliente[ n++ ].fecha, fecha );
            strcpy( disponible[ res ].fechas, fecha );
            disponible[ res++ ].cont = 1;
            fprintf( log, "%s  Se ha generado una reserva a nombre de %s para la fecha de %s\n", horalog, cliente[ n - 1 ].nombre, cliente[ n - 1 ].fecha );
         }
         else{
            for ( i = 0; i < res; i++ ){
               if( strcmp( fecha, disponible[ i ].fechas ) == 0 ){
                  sim = 1;
                  if ( disponible[i].cont < 5 ){
                     strcpy( cliente[ n ].nombre, nombre );
                     strcpy( cliente[ n++ ].fecha, fecha );
                     disponible[ i ].cont++;
                     fprintf( log, "%s  Se ha generado una reserva a nombre de %s para la fecha de %s\n", horalog, cliente[ n - 1 ].nombre, cliente[ n - 1 ].fecha );                     
                     break;
                  }
                  else{
                     printf( "Lo sentimos, todas las mesas están ocupadas para esa hora ese día.\n" );
                  }
               }
            }
            if ( sim = 0 ){
               strcpy( cliente[ n ].nombre, nombre );
               strcpy( cliente[ n++ ].fecha, fecha );
               printf( "*%s*%s*\n", fecha, cliente[ n-1 ].fecha );
               strcpy( disponible[ res ].fechas, fecha );
               disponible[ res++ ].cont = 1;
               fprintf( log, "%s  Se ha generado una reserva a nombre de %s para la fecha de %s\n", horalog, cliente[ n - 1 ].nombre, cliente[ n - 1 ].fecha );
            }
         }
         break;
      case 2:
         printf( "Nombre = " );
         scanf( "%s", nombre );
         for( i = 0; i < n; i++ ){
            if( strcmp( nombre, cliente[ i ].nombre ) == 0 ){
               strcpy(fecha, "");
               printf( "Mes a hacer la reserva (1 - 12) = " );
               scanf( "%d", &mes );
               while ( mes < 0 || mes > 12){
                  printf( "Seleccione una opción valida = " );
                  scanf( "%d", &mes );
               }
               if( mes < 10 ){
                  strcat(fecha, "0");
               }
               char *num;
               if( asprintf( &num, "%d", mes ) == -1 ) {
                  perror( "asprintf" );
               }
               else{
                  strcat( fecha, num );
                  free( num );
               }
               strcat(fecha, "/");
               // Se asume que todos los meses tienen 30 días :)
               printf( "Día a hacer la reserva (1 - 30) = " );
               scanf( "%d", &dia );
               while ( dia < 0 || dia > 30){
                  printf( "Seleccione una opción valida = " );
                  scanf( "%d", &dia );
               }
               if( dia < 10 ){
                  strcat(fecha, "0");
               }
               char *num2;
               if ( asprintf( &num2, "%d", dia ) == -1 ) {
                  perror( "asprintf" );
               }
               else{
                  strcat( fecha, num2 );
                  free( num2 );
               }
               strcat( fecha, "/21 " );
               printf( "Hora: (1.16:00  2.18:00  3.20:00  4.22:00) = " );
               scanf( "%d", &hour );
               while ( hour < 0 || hour > 4){
                  printf( "Seleccione una opción valida = " );
                  scanf( "%d", &hour );
               }
               if ( hour == 1){
                  strcat( fecha, "16:00\0" );
               }
               else if ( hour == 2){
                  strcat( fecha, "18:00\0" );
               }
               else if ( hour == 3){
                  strcat( fecha, "20:00\0" );
               }
               else if ( hour == 4){
                  strcat( fecha, "22:00\0" );
               }
               for ( j = 0; j < res; j++ ){
                  if( strcmp( fecha, disponible[ j ].fechas ) == 0 ){
                     sim = 1;
                     if ( disponible[ j ].cont < 5 ){
                        strcpy( cliente[ i ].fecha, fecha );
                        disponible[ j ].cont++;
                        fprintf( log, "%s  Se ha reagendado la reserva de %s para la fecha de %s\n", horalog, cliente[ i ].nombre, cliente[ j ].fecha );                     
                        break;
                     }
                     else{
                        printf( "Lo sentimos, todas las mesas están ocupadas para esa hora ese día.\n" );
                     }
                  }
               }
            }
         }
         break;
      case 3:
         printf( "Nombre = " );
         scanf( "%s", nombre );
         for( i = 0; i < n; i++ ){
            if( strcmp( nombre, cliente[ i ].nombre ) == 0 ){
               printf( "Fecha = %s\n", cliente[ i ].fecha );
               sim++;
            }
         }
         if ( sim == 0 ){
            printf( "La persona %s no tiene una reserva con nosotros\n", nombre );
         }
         sim = 0;
         break;
      case 4:
         printf( "Nombre = " );
         scanf( "%s", nombre );
         for( i = 0; i < n; i++ ){
            if( strcmp( nombre, cliente[ i ].nombre ) == 0 ){
               fprintf( log, "%s  Se ha cancelado la reserva de %s\n", horalog, cliente[ i ].nombre);
               sim++;
               for( j = i; j < n - 1; j++ ){
                  cliente[ j ] = cliente[ j + 1];
               }
            }
         }
         if ( sim == 0 ){
            printf( "La persona %s no tiene una reserva con nosotros\n", nombre );
         }
         sim = 0;
         n--;
         break;
      case 5:
         printf( "Nombre = " );
         scanf( "%s", nombre );
         for( i = 0; i < n; i++ ){
            if( strcmp( nombre, cliente[ i ].nombre ) == 0 ){
               printf( "Nombre = " );
               sim++;
               for( i = 0; i < n; i++ ){
                  if( strcmp( nombre, cliente[ i ].nombre ) == 0 ){
                     sim++;
                     char aux[ 100 ];
                     strcpy( aux, cliente[ i ].fecha );
                     strcpy( cliente[ i ].fecha, cliente[ j ].fecha );
                     strcpy( cliente[ j ].fecha, aux );
                     fprintf( log, "%s   Se intercambió la reserva de %s con la de %s \n", horalog, cliente[ i ].nombre, cliente[ j ].nombre );
                  }
               }
            }
         }
         if (sim < 2 ){
            printf( "Persona(s) no encontrada(s)\n" );
         }
         break;
      case 6:
         printf( "    NOMBRE      FECHA Y HORA\n");
         printf( "============== ==============\n" );
         for( i = 0; i < n; i++ ){
            printf( "%-14s %s\n", cliente[ i ].nombre, cliente[ i ].fecha);
         }
         break;
      case 7:
         memoria = fopen( "report.txt", "w" );
         fprintf( memoria, "    NOMBRE      FECHA Y HORA\n");
         fprintf( memoria, "============== ==============\n" );
         for( i = 0; i < n; i++ ){
            fprintf( memoria, "%-14s %-14s\n", cliente[ i ].nombre, cliente[ i ].fecha );
         }
         fclose( memoria );
         system( "notepad report.txt" );
         break;
      case 8:
         fclose( log );
         system( "log.txt" );
         log = fopen( "log.txt", "a" );
         break;
      case 777:
         srand(time(NULL));
         lotto = rand() % n;
         printf("¡%s lleva su cena gratis!\n", cliente[lotto].nombre);
         fprintf( log, "%s  Se ha concedido una cena gratis a %s\n", horalog, cliente[ lotto ].nombre);
         break;
      default:
         break;
      }
      printf("\n");
   }while( opc != 0 && opc < 8 || opc == 777);
   memoria = fopen( "reservas.dat", "wb" );
   fwrite( &n, sizeof( int ), 1, memoria );
   fwrite( &res, sizeof( disponible ), 1, memoria );
   fwrite( cliente, sizeof( cliente ), 1, memoria );
   fwrite( disponible, sizeof( disponible ), 1, memoria );
   fclose( memoria );
   return 0;
}