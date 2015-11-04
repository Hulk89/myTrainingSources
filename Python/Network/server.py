from socket import *

sServerSock = socket( AF_INET, SOCK_STREAM )

sServerSock.bind( ('localhost', 8000) )
sServerSock.listen(1)

while 1 :
        print('waiting accept...')
        sClientSock, sAddr = sServerSock.accept()
        sAddr
        sClientSock.setsockopt( SOL_SOCKET, SO_REUSEADDR, 1 )
        sMsg = sClientSock.recv(1024)
        print(sMsg);
        sClientSock.close()
