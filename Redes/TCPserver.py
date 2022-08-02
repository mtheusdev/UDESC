from socket import *

serverPort = 12001
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)

print "The server is ready to receive"

while True:
	connectionSocket, addr = serverSocket.accept()
	print 'Conectado por', addr
	sentence = connectionSocket.recv(1024)
	if(sentence != ''):
		print "Something came from a client - " + sentence
	capitalizedSentence = sentence.upper()
	connectionSocket.send(capitalizedSentence)
	connectionSocket.close()
	sentence = ''
	
