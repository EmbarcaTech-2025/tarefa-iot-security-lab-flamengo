// Bibliotecas necessárias
#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR

int main() {
    // Inicializa interfaces padrão
    stdio_init_all();

    // Conecta ao WiFi com credenciais originais
    connect_to_wifi("LACERDA 2.4G", "7223480CBD");

    // Configura o cliente MQTT com credenciais originais
    mqtt_setup("bitdog1", "192.168.1.3", "jplacerda", "embarcatech12345");

    const char *mensagem = "26.5";
    uint8_t criptografada[16];
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);

    while (true) {
        // Publica a mensagem original periodicamente
        mqtt_comm_publish("C:/Users/komba/OneDrive/Documentos/mosquitto", mensagem, strlen(mensagem));
        
        // Alternativa: Publica a mensagem criptografada
        // mqtt_comm_publish("C:/Users/komba/OneDrive/Documentos/mosquitto", criptografada, strlen(mensagem));
        
        // Aguarda 5 segundos antes da próxima publicação
        sleep_ms(5000);
    }

    return 0;
}

/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "26.6"
 */