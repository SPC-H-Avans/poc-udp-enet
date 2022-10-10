#include <iostream>
#include <enet/enet.h>

const int PORT = 7777;

int main(int argc, char* args[]){
    if(enet_initialize() != 0){
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetEvent event;
    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = 7777;

    //address, player limit, channels, incoming bandwidth, outgoing bandwidth
    ENetHost* server = enet_host_create(&address, 3, 1, 0, 0);

    if(server == nullptr){
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        return EXIT_FAILURE;
    }

    std::cout << "Server running..";

    while(true){
        while(enet_host_service(server, &event, 0) > 0){
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    std::cout << "A new client connected from " << event.peer->address.host << ":" <<event.peer->address.port << std::endl;

                    //store client information
                    event.peer -> data = (void *) "Client";

                    //send message to client
                    ENetPacket *packet = enet_packet_create("Hello client", strlen("Hello client") + 1,
                                                            ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer, 0, packet);
                    enet_host_flush(server);
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE: {
                    printf("A packet of length %u containing '%s' was received from %s on channel %u.\n",
                           event.packet->dataLength,
                           event.packet->data,
                           event.peer->data,
                           event.channelID);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: {
                    printf("%s disconnected.\n", event.peer->data);
                    //reset client's information
                    event.peer->data = NULL;
                    break;
                }
            }
        }
    }

    enet_host_destroy(server);
    return EXIT_SUCCESS;
}