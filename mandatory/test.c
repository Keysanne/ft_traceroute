#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip_icmp.h>
#include <errno.h>

#define PACKET_SIZE     4096
#define DEST_PORT       33434  // Destination port for UDP traceroute
#define MAX_HOPS        30     // Maximum number of hops

void traceroute_udp(const char *destination_ip) {
    struct sockaddr_in addr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, destination_ip, &(addr.sin_addr));

    char ip_str[INET_ADDRSTRLEN];

    for (int ttl = 1; ttl <= MAX_HOPS; ++ttl) {
        // Set TTL option for the socket
        setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        // Craft UDP packet
        char packet[PACKET_SIZE];
        memset(packet, 0, PACKET_SIZE);

        // UDP header
        struct udphdr *udp_header = (struct udphdr *)packet;
        udp_header->source = htons(12345);  // Source port (arbitrary)
        udp_header->dest = htons(DEST_PORT);
        udp_header->len = htons(sizeof(struct udphdr)); // Length of UDP header + payload

        // Send UDP packet
        if (sendto(sockfd, packet, sizeof(struct udphdr), 0,
                   (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("sendto");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // Receive ICMP Time Exceeded messages
        struct sockaddr_in sender_addr;
        socklen_t sender_addr_len = sizeof(sender_addr);
        char recv_buffer[PACKET_SIZE];
        ssize_t bytes_received = recvfrom(sockfd, recv_buffer, PACKET_SIZE, 0,
                                           (struct sockaddr *)&sender_addr, &sender_addr_len);
        if (bytes_received < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("%d: * * *\n", ttl);
            } else {
                perror("recvfrom");
            }
            continue;
        }

        // Extract and print IP address from ICMP message
        struct iphdr *ip_header = (struct iphdr *)recv_buffer;
        inet_ntop(AF_INET, &(ip_header->saddr), ip_str, INET_ADDRSTRLEN);
        printf("%d: %s\n", ttl, ip_str);

        // Check if destination reached
        if (ip_header->saddr == addr.sin_addr.s_addr) {
            printf("Destination reached.\n");
            break;
        }
    }

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <destination_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    traceroute_udp(argv[1]);

    return 0;
}