#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <OneWire.h>//Se importan las librerías
#include <DallasTemperature.h>

//-------wifi---------
const char* ssid = "Speedy-94F29D";
const char* password = "4761007483";
WiFiServer server(80);

//-------EEPROM-------
float sensorValue;
int eeAddress = 0;
boolean safe;

//--------Sensor-----
#define Pin 2
int LED_aparpadear = 5;                 // Definimos la variable y el número del GPIO a conectar el LED a parpadear. 
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature
float temp=0;

void setup() 
{
  delay(1000);
  Serial.begin(9600);
  //--------- WIFI-------------
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //Conexión a la red

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  server.begin(); //Iniciamos el servidor
  Serial.println("Servidor Iniciado");
  Serial.println("Ingrese desde un navegador web usando la siguiente IP:");
  Serial.println(WiFi.localIP()); //Obtenemos la IP 

  //----------EEPROM----------
  
  //EEPROM[ index ] = 0;
  

  //-----------Sensor----------
  sensors.begin(); //Se inician los sensores
  pinMode(LED_aparpadear, OUTPUT);      // Inicializa el LED_aparpadear como una salida.
}

void loop() 
{
  //---------- WIFI-------------
/*  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  {
    Serial.println("Nuevo Cliente");

    //esperamos hasta que hayan datos disponibles
    while (!client.available() && client.connected())
    {
      delay(1);
    }
  }*/
  //----------------------------
  sensors.requestTemperatures(); //Prepara el sensor para la lectura
  temp=sensors.getTempCByIndex(0);
  
  /*if(temp > 20)
  {
   // if(safe == false)
   // {
      EEPROM.put( eeAddress, sensorValue );  //Grabamos el valor
      eeAddress += sizeof(float);  //Obtener la siguiente posicion para escribir
      //if(eeAddress >= EEPROM.length())eeAddress = 0;  //Comprobar que no hay desbordamiento
        
       //safe=true;
    //}
    // Funciones para variables completas (tiene en cuenta el tamaño de la variable)
    
    
   //-------------- Leo lo que se guardo ------------//
   float f;
   int eeAddress = 0; //EEPROM address to start reading from    
   EEPROM.get( eeAddress, f );
   Serial.print( "Float leido: " );
   Serial.println( f, 3 ); 


    //digitalWrite(LED_aparpadear, HIGH);
    Serial.print(temp); //Se lee e imprime la temperatura en grados Celsius
    Serial.print(" Temperatura actual: "); Serial.print(temp);Serial.println(" Centigrados");
  }
  else
  {
    Serial.print("ATENCION !! ");Serial.print(temp);Serial.println(" grados Centigrados"); //Se lee e imprime la temperatura en grados Celsius
    digitalWrite(LED_aparpadear, HIGH);   // Enciende el LED.
    delay(1000);                          // Espera un segundo.
    digitalWrite(LED_aparpadear, LOW);    // Apaga el LED.
    delay(2000);                          // Espera dos segundos.
  }*/
  delay(1000); //Se provoca un lapso de 1 segundo antes de la próxima lectura
  Serial.print(temp); //Se lee e imprime la temperatura en grados Celsius
  Serial.print(" Temperatura actual: "); Serial.print(temp);Serial.println(" Centigrados");
}


