class Communication{
  public:
    char* message;
    int sockfd;
    struct sockaddr_in cliaddr, servaddr;
    virtual void run(){}



};
