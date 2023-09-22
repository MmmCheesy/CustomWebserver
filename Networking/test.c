//
// ==================================
// Game 1
// ==================================
//
// test.c
//
// Alex Eckert
// 2/11/2023
//
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "Server.h"


void launch(struct Server *server) {
    
    char username[30000];
    char password[30000];
    FILE *filePointer;
    long fileSize;
    
    while (1) {
        char buffer[30000];
        int address_length = sizeof(server->address);
        int new_socket;
        //printf("===== WAITING FOR CONNECTION =====\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s", buffer);
        
        int underscore = 0;
        
        for (int i = 5; buffer[i] != '_' && buffer[i] != ' '; i++) {
            username[i-5] = buffer[i];
            if (buffer[i+1] == '_')
                username[i+1-5] = '\0';
                underscore = i + 1;
        }
        if (underscore != 0) {
            for (int i = underscore; !(buffer[i] == ' ' && buffer[i+1] == 'H' && buffer[i+2] == 'T' && buffer[i+3] == 'T' && buffer[i+4] == 'P' && buffer[i+5] == '/'); i++) {
                password[i - underscore] = buffer[i + 1];
            }
        }
        
        if (((strcmp(username, "end0?") == 0) || (strcmp(username, "end1?") == 0) || (strcmp(username, "end2?") == 0) || (strcmp(username, "end3?") == 0) || (strcmp(username, "end4?") == 0) || (strcmp(username, "end5?") == 0)) && (strcmp(password, "") != 0)) {
            if (strcmp(username, "end0?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "300......%s\n", password);
                fclose(filePointer);
            } else if (strcmp(username, "end1?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "200......%s\n", password);
                fclose(filePointer);
            } else if (strcmp(username, "end2?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "400......%s\n", password);
                fclose(filePointer);
            } else if (strcmp(username, "end3?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "300......%s\n", password);
                fclose(filePointer);
            } else if (strcmp(username, "end4?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "250......%s\n", password);
                fclose(filePointer);
            } else if (strcmp(username, "end5?") == 0) {
                filePointer = fopen("names.txt", "a");
                fprintf(filePointer, "150......%s\n", password);
                fclose(filePointer);
            }
            filePointer = fopen("html files/level4.html", "r");
            fseek(filePointer, 0L, SEEK_END);
            fileSize = ftell(filePointer);
            rewind(filePointer);
            char *page = (char*)malloc ((fileSize+1)*sizeof(char));
            if (page){
                fread (page, sizeof(char), fileSize, filePointer);
            }
            fclose(filePointer);
            write(new_socket, page, fileSize);
            close(new_socket);
            free(page);
        } else if (strcmp(username, "Level2") == 0) {
            filePointer = fopen("html files/level2.html", "r");
            fseek(filePointer, 0L, SEEK_END);
            fileSize = ftell(filePointer);
            rewind(filePointer);
            char *page = (char*)malloc ((fileSize+1)*sizeof(char));
            if (page){
                fread (page, sizeof(char), fileSize, filePointer);
            }
            fclose(filePointer);
            write(new_socket, page, fileSize);
            close(new_socket);
            free(page);
        } else if (strcmp(username, "Level3") == 0) {
            if (strcmp(password, "a ") == 0) {
                filePointer = fopen("html files/level3a.html", "r");
            } else if (strcmp(password, "b ") == 0) {
                filePointer = fopen("html files/level3b.html", "r");
            } else {
                filePointer = fopen("html files/level3.html", "r");
            }
            fseek(filePointer, 0L, SEEK_END);
            fileSize = ftell(filePointer);
            rewind(filePointer);
            char *page = (char*)malloc ((fileSize+1)*sizeof(char));
            if (page){
                fread (page, sizeof(char), fileSize, filePointer);
            }
            fclose(filePointer);
            write(new_socket, page, fileSize);
            close(new_socket);
            free(page);
        } else {
            filePointer = fopen("html files/level1.html", "r");
            fseek(filePointer, 0L, SEEK_END);
            fileSize = ftell(filePointer);
            rewind(filePointer);
            char *page = (char*)malloc ((fileSize+1)*sizeof(char));
            if (page){
                fread (page, sizeof(char), fileSize, filePointer);
            }
            fclose(filePointer);
            write(new_socket, page, fileSize);
            close(new_socket);
            free(page);
        }
        
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        
    }
}

int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);
}
