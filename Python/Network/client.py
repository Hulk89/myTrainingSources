from socket import *

sClientSock = socket( AF_INET, SOCK_STREAM )
sClientSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

sClientSock.connect( ('localhost', 8000) )
sClientSock.send( 'HelloPython'.encode() )
print('send HelloPython')
sClientSock.close()
