#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0x71, 0x03, 0x58, 0x9B, 0xB5, 0xE7}; // MAC Address del dispositivo.

EthernetServer server(80); // Puerto de escucha de el servidor Web.

void setup(){
    
    Serial.begin(9600);
    
    Ethernet.begin(mac); // Inicia la red DHCP
    server.begin();      // Inicia el Servidor
    
    // Debug: Para ver que IP fue asignado al dispositivo.
    Serial.print("El servidor esta corriendo en: ");
    Serial.println(Ethernet.localIP());
  
}

void loop(){
    
    EthernetClient client = server.available();
    
    if (client) {
        
        Serial.println("Cliente Nuevo");
        
        boolean currentLineIsBlank = true;
                       
        while(client.connected()){
            
            // Debug: La cantidad de Bytes disponibles en la peticion
            // Serial.print("Cantidad de Bytes en la peticion: ");
            // Serial.println(client.available());
            
            
            if(client.available()){
                
                // Si existen Bytes disponibles en la peticion
                // se asignan a la variable c por medio del metodo read()
                // y se resta de la cantidad de bytes disponibles en la
                // peticion.
                
                char c = client.read();
                Serial.print(c);
                
                if(c == '\n' && currentLineIsBlank){
                    
                    Serial.println("Fin de la peticion...");
                    Serial.println("Se inicia la respuesta...");
                    Serial.println();
                    
                    // Inicia la Respuesta
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("<h1>Hola Mundo!</h1>");
                    break;
                    
                }
                
                // Comprueba si la ultima linea esta en blanco y asigna
                // true o false a currentLineIsBlanl
                if(c == '\n'){
                    
                    currentLineIsBlank = true;
                    
                } else if(c != '\r'){
                    
                    currentLineIsBlank = false;
                    
                }
                
            }
        } // Fin de loop while que se ejecuta mientras el cliente este conectado
        
        delay(1); // Hay que darle tiempo al servidor de recibir los datos.
        client.stop();
        
    }
}
