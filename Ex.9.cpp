#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct Message {
    long messageType;
    char text[50];
};


int createMessageQueue() {
    key_t key = ftok("message_queue_example", 65);  

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    return msgid;
}


void sendMessageToQueue(int msgid, struct Message *message) {
    printf("Sending message to the queue...\n");
    message->messageType = 1;
    sprintf(message->text, "Hello from process %d", getpid());

   
    if (msgsnd(msgid, message, sizeof(struct Message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message->text);
}


void receiveMessageFromQueue(int msgid, struct Message *message) {
    printf("Receiving message from the queue...\n");

 
    if (msgrcv(msgid, message, sizeof(struct Message), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Message received: %s\n", message->text);
}

int main() {
    int msgid = createMessageQueue();

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        
        struct Message receivedMessage;
        receiveMessageFromQueue(msgid, &receivedMessage);
    } else {
    
        struct Message sentMessage;
        sendMessageToQueue(msgid, &sentMessage);

        
        wait(NULL);

        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
