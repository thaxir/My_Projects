import socket
import string
import time

host = "0.0.0.0"
port = 5004
socket.SOCK_DCCP                = 6
socket.IPPROTO_DCCP             = 33
client = socket.socket(socket.AF_INET, socket.SOCK_DCCP,socket.IPPROTO_DCCP)
addr = (host,port)

client.connect(addr)
print "\n"
print "-" * 40
print "dccp_client.py"
print "-" * 40

print "\nStarting client end.  Control-C to quit."

print "\nOur target:"
print "dccp_server.py running on %s port %s" % (host, port)

print "\n\nEnter number of bytes to send and the number of times to send them:\n(for instance '100 10' to send 10 bursts of 100 bytes each)";

while (1):
	data = raw_input('% ')
	args = string.split(data)

	try:
                if args[0] == "reset":
                    data = "X"
                    numtimes = 1
                else:            
                    data = "X" * int(args[0])
                    numtimes = int(args[1])
        except:
                data = None
                numtimes = None
                print "Error, you need to specify two numbers.  First the number of bytes to send, second the number of times to send them."
                
	if not data:
		pass
	else:
            try:
                #the resetter...
                client.sendto("X", (host,port))
                
                for x in range(numtimes):
        		if(client.sendto(data,(host,port))):
                            print "*",
                        else:
                            print "."
                            
                     
                        time.sleep(0.0001)
                print "Done."

            except:
                print "Send failed"


client.close()
