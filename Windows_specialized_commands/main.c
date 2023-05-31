#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"


int main() {
    char option;

    while (1) {
        printf("-------MENU-------\n");
        printf("1. Report MACs of network adapter devices installed in the system\n");
        printf("2. Show the complete network configuration of the local machine\n");
        printf("3. Display the information related to a stored network adapter\n");
        printf("4. Show IP's from webs.txt file\n");
        printf("5. EXIT\n");
        printf("Choose the option you want: ");
        scanf_s(" %c", &option, 1);
        getchar(); // To capture the newline character remaining in the buffer

        switch (option) {
        case '1':
            printf("You have chosen:\nReport the MACs of the network adapter devices installed in the system and store them in LocalInfo.txt.\n\n");
            infoMACadaptersNetwork();
            break;
        case '2':
            printf("You have chosen: \nDisplay the complete network configuration of the local machine for the different adapters and store them in LocalInfo.txt\n");
            configAdapters();
            break;
        case '3':
            printf("You have chosen: \nDisplay the information related to a network adapter of the ones stored in localinfo.txt chosen by the user..\n");
            infoDevice();
            break;
        case '4':
            printf("You have chosen: \nShow IP's from the ips.txt file\n");
            showIP();
            break;
        case '5':
            return 0;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    return 0;
}
