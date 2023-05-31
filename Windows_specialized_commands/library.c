#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include <Winsock2.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")



#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif


void infoMACadaptersNetwork() {
    char buffer[1024];
    FILE* fp;

    // Execute the command 'getmac' and save the output to a temporary file
    system("getmac > temp_mac.txt");

    // Open the temporary file
    fopen_s(&fp, "temp_mac.txt", "r");
    if (fp == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    // Create or overwrite localinfo.txt file
    FILE* output;
    fopen_s(&output, "Create or overwrite localinfo.txt filet", "w");
    if (output == NULL) {
        printf("Error when opening the file localinfo.txt\n");
        fclose(fp);
        return;
    }

    // Read contents of temporary file and display MAC addresses
    printf("MAC addresses of network adapters:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, output);
        printf("%s", buffer);
    }

    // Close files
    fclose(fp);
    fclose(output);

    // Delete temporary file
    remove("temp_mac.txt");
}


void configAdapters() {
    FILE* fp;
    char buffer[1024];

    // Execute the command 'ipconfig /all' and save the output in a temporary file.
    system("ipconfig /all > temp_config.txt");

    // Open the temporary file
    fopen_s(&fp, "temp_config.txt", "r");
    if (fp == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    // Open the file localinfo.txt in append mode
    FILE* output;
    fopen_s(&output, "localinfo.txt", "a");
    if (output == NULL) {
        printf("Error opening the file localinfo.txt\n");
        fclose(fp);
        return;
    }

    // Read the contents of the temporary file, display network configuration and store it in localinfo.txt
    printf("Network configuration:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, output);
        printf("%s", buffer);
    }

    // Close files
    fclose(fp);
    fclose(output);

    // Delete temporary file
    remove("temp_config.txt");
}


void infoDevice() {
    char adapter[256];
    printf("Enter the name of the network adapter: ");
    fgets(adapter, sizeof(adapter), stdin);
    adapter[strcspn(adapter, "\n")] = '\0';

    FILE* fp;
    char buffer[1024];

    // Execute the command 'ipconfig' and save the output to a temporary file.
    system("ipconfig > temp_config.txt");

    // Open the temporary file
    fopen_s(&fp, "temp_config.txt", "r");
    if (fp == NULL) {
        printf("Error opening the temporary file.\n");
        return;
    }

    int found_adaptor = 0;
    printf("\nInformation on the selected network adapter:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, adapter)) {
            found_adaptor = 1;
        }
        if (found_adaptor && (strstr(buffer, "IPv4") || strstr(buffer, "Subnet mask") || strstr(buffer, "Gateway"))) {
            printf("%s", buffer);
        }
        if (found_adaptor && strstr(buffer, "Gateway")) {
            break;
        }
    }

    fclose(fp);
    remove("temp_config.txt");

    if (!found_adaptor) {
        printf("The specified network adapter was not found..\n");
    }
}


void showIP() {
    char file_path[256];
    printf("Enter the path and name of the file with web addresses: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = '\0';

    FILE* fp, * fp_ip;
    char buffer[1024];

    fopen_s(&fp, file_path, "r");
    if (fp == NULL) {
        printf("Error opening web address file.\n");
        return;
    }

    fopen_s(&fp_ip, "ip.txt", "w");
    if (fp_ip == NULL) {
        printf("Error opening the file ip.txt.\n");
        fclose(fp);
        return;
    }

    printf("\nContents of the web address file:\n");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error initializing Winsock.\n");
        fclose(fp);
        fclose(fp_ip);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("%s\n", buffer);

        struct addrinfo hints, * res, * p;
        int status;
        char ipstr[INET6_ADDRSTRLEN];

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if ((status = getaddrinfo(buffer, NULL, &hints, &res)) != 0) {
            printf("The IP could not be obtained for %s\n", buffer);
            continue;
        }

        for (p = res; p != NULL; p = p->ai_next) {
            void* addr;
            if (p->ai_family == AF_INET) {
                struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
                addr = &(ipv4->sin_addr);
            }
            else {
                struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
                addr = &(ipv6->sin6_addr);
            }

            inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
            printf("IP: %s\n", ipstr);
            fputs(ipstr, fp_ip);
            fputs("\n", fp_ip);
            break;
        }

        freeaddrinfo(res);
    }

    WSACleanup();

    fclose(fp);
    fclose(fp_ip);
}