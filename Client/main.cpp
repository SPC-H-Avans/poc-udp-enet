#include <iostream>
#include <enet/enet.h>

const int PORT = 7777;
const char *const HOST = "127.0.0.1";

int main(int argc, char *args[]) {
    if (enet_initialize() != 0) {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetHost *client = enet_host_create(NULL, 1, 1, 0, 0);

    if (client == NULL) {
        fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
        return EXIT_FAILURE;
    }

    //adres van de server
    ENetAddress address;
    //mostly data die wordt ontvangen van de server
    ENetEvent event;
    //server waarmee we connecten peer = anybody who is connected
    ENetPeer *peer;

    enet_address_set_host(&address, HOST);
    address.port = PORT;

    //connect to host, amount of channels, 0 = data
    peer = enet_host_connect(client, &address, 1, 0);

    if (peer == NULL) {
        fprintf(stderr, "No available peers for initiating an ENet connection.\n");
        return EXIT_FAILURE;
    }

    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connection succeeded on host: " << HOST << " with port: " << PORT << std::endl;
    } else {
        enet_peer_reset(peer);
        std::cout << "Connection failed on host: " << HOST << " with port: " << PORT << std::endl;
        //wanneer connectie niet succesvol -> terug naar main screen
        return EXIT_SUCCESS;
    }

    //1000 = 1 sec delay
    while (true) {
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_RECEIVE: {
                    printf("A packet of length %u containing '%s' was received from %s on channel %u.\n",
                           event.packet->dataLength,
                           event.packet->data,
                           event.peer->data,
                           event.channelID);
                    enet_packet_destroy(event.packet);

                    //reply to server
                    ENetPacket *packet = enet_packet_create("Hello server", strlen("Hello server") + 1,
                                                            ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer, 0, packet);
                    enet_host_flush(client);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    std::cout << event.peer->data << " disconnected.\n";
                    event.peer->data = NULL;
                    return EXIT_FAILURE;
                }
                default: {
                    std::cout << "Something went wrong" << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
}