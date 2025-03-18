#include <iostream>
#include <cstring>
#include "mqtt/async_client.h"

#define QOS 1
#define TimeOut 1000

const std::string SERVEUR_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("publisher");
const std::string TOPIC("test");

class PublisherCallback : public virtual mqtt::callback {
    // virtual permet d'héviter la duplication de mqtt::callback et cas d'héritage mutltiple
    public:
        void connection_lost(const std::string& cause) override {
            // override permet de garantire la redéfinition de la méthode de la class de base
            std::cout << "Connection lost: " << cause << std::endl;
        }

        void delivery_complete(mqtt::delivery_token_ptr token) override {
            std::cout << "Message delivered" << std::endl;
        }
};

int main(int argc, char **argv){
    mqtt::async_client client(SERVEUR_ADDRESS, CLIENT_ID);
    
    mqtt::connect_options connectOpt;
    connectOpt.set_keep_alive_interval(20);
    connectOpt.set_clean_session(true);
    try{
        // definir le callback pour la fonction : celui-ci permet de suivre en cas de pb ou de  confirmation d'envoi
        PublisherCallback callback_c;

        client.set_callback(callback_c);

        // créer un token qui représente l'action de connexion
        mqtt::token_ptr token_c = client.connect(connectOpt);
        token_c->wait(); // on attend que la connexion soit bien effectué
        
        while(true){
            std::string message;
            std::cout << "Entrez le message ou q pour quitter : " << std::endl;
            std::getline(std::cin, message);

            if(message == "q"){
                std::cout << "Vous allez quitter" << std::endl;
                break;
            }

            mqtt::message_ptr pubMessage = mqtt::make_message(TOPIC, message, QOS, false); // false signifie que le message n'est pas "retenue"
            client.publish(pubMessage)->wait();
                                                                                    
        }
    }
    catch (const mqtt::exception& ex)
    {
        std::cerr << "MQTT Exception: " << ex.what() << std::endl;
        return 1;
    }
    // on deconnecte quand la connexion est rompue
    mqtt::token_ptr disconnectionToken = client.disconnect();
    disconnectionToken->wait();
    return 0;
}
