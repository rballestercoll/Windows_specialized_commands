# Windows_specialized_commands
> C application that allows us to edit text files and control several simple Windows console commands.

## Objectives
Initially display a menu that allows to select which of the different functionalities implemented in the application will be accessed and which will be the following:

1. Inform about which is/are the MAC of the network adapter devices installed in the system and store it in a file localinfo.txt.
2. Display the complete network configuration of the local machine for the different adapters and store it in the above .txt file.
3. Display the information related to a network adapter from those stored in the above file chosen by the user.
4. Display the IP of a set of web pages found in a .txt file.

## Route

- I have created a function that shows the MAC address of the device's network adapters and displays it on the screen, in addition to storing it.
- I have created another function whose functionality is to display for a network adapter which will be asked previously to the user, both the IP, mask, and gateway. The rest of the network configurations are not to be displayed. To perform the above the function will launch a command of two that will provide the information it needs along with other information that is not considered relevant, and will be able to extract and display the one that has been detailed.
- And finally I have designed a function that reads the content of a text file consisting of a series of web addresses each of which occupies one line of the text file. The path and name of the text file will be asked to the user and initially the contents of the file will be displayed on the screen. Finally it will launch a ping for each of the webs and it will determine and inform about their IPs which will be stored in an ip.txt file.

