// Server program
 #include <arpa/inet.h>
 #include <errno.h>
 #include <netinet/in.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
// #include <strings.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <unistd.h>
 #define PORT 5000
 #define MAXLINE 1024
 #include <string.h>
//#include "chat.h"
class Communication{
    public:
          //int PORT= 5000;
          //    //int MAXLINE= 1024;
               char* message;
                      int sockfd;
                          struct sockaddr_in cliaddr, servaddr;
                              virtual void run(){}



                              };


class Client: public Communication{
    public:
    Client(){
    message = "Hello Server";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    }
    void run()
    {
    char buffer[MAXLINE];
    //struct sockaddr_in servaddr;

    int n, len;
    // Creating socket file descriptor
    //if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    //printf("socket creation failed");
    //exit(0);
    //}

    //memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    //servaddr.sin_family = AF_INET;
    //servaddr.sin_port = htons(PORT);
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&servaddr,
    sizeof(servaddr)) < 0) {
    printf("\n Error : Connect Failed \n");
    }
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, "Hello Server");
    write(sockfd, buffer, sizeof(buffer));
    printf("Message from server: ");
    read(sockfd, buffer, sizeof(buffer));
    puts(buffer);
    close(sockfd);
    }
};


class Server : public  Communication{
  public:
int max(int x, int y)
 {
  if (x > y)
   return x;
   else
   return y;
  }
    Server(){
    message = "Hello Client";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
bzero(&servaddr, sizeof(servaddr));
        // Filling server information
         servaddr.sin_family = AF_INET;
         servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         servaddr.sin_port = htons(PORT);


    }
 void run()
  {
  int listenfd, connfd, udpfd, nready, maxfdp1;
  char buffer[MAXLINE];
  pid_t childpid;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  //struct sockaddr_in cliaddr, servaddr;
  void sig_chld(int);

   /* create listening TCP socket */
  // sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // bzero(&servaddr, sizeof(servaddr));
   //servaddr.sin_family = AF_INET;
   //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   //servaddr.sin_port = htons(PORT);

  // binding server addr structure to listenfd
   bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
   listen(sockfd, 10);

   /* create UDP socket */
   udpfd = socket(AF_INET, SOCK_DGRAM, 0);
   // binding server addr structure to udp sockfd
   bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  // clear the descriptor set
  FD_ZERO(&rset);

  // get maxfd
  maxfdp1 = max(sockfd, udpfd) + 1;
  for (;;) {

  // set listenfd and udpfd in readset
  FD_SET(sockfd, &rset);
  FD_SET(udpfd, &rset);

   // select the ready descriptor
   nready = select(maxfdp1, &rset, NULL, NULL, NULL);

   // if tcp socket is readable then handle
   // it by accepting the connection
   if (FD_ISSET(sockfd, &rset)) {
   len = sizeof(cliaddr);
   connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
   if ((childpid = fork()) == 0) {
   close(sockfd);
   bzero(buffer, sizeof(buffer));
   printf("Message From TCP client: ");
   read(connfd, buffer, sizeof(buffer));
   puts(buffer);
   write(connfd, (const char*)message, sizeof(buffer));
   close(connfd);
   exit(0);
   }
   close(connfd);
   }
   // if udp socket is readable receive the message.
   if (FD_ISSET(udpfd, &rset)) {
   len = sizeof(cliaddr);
   bzero(buffer, sizeof(buffer));
   printf("\nMessage from UDP client: ");
   n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
   (struct sockaddr*)&cliaddr, &len);
   puts(buffer);
   sendto(udpfd, (const char*)message, sizeof(buffer), 0,
   (struct sockaddr*)&cliaddr, sizeof(cliaddr));
   }
  }
 }
};


int main(){



Communication *comm;

 int sockfd;
  char buffer[MAXLINE];
  char* message = "Hello Server";
  struct sockaddr_in servaddr;

  int n, len;
  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  printf("socket creation failed");
  exit(0);
  }
  memset(&servaddr, 0, sizeof(servaddr));
  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(sockfd, (struct sockaddr*)&servaddr,
  sizeof(servaddr)) < 0) {
  comm=new Server();
  }else {comm=new Client();}

    comm->run();



}
