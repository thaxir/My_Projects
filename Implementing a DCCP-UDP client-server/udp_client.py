from socket import *
import string
import time

host = "89.210.168.254"
port = 5004

UDPSock = socket(AF_INET,SOCK_DGRAM)

print "\n"
print "-" * 40

print "\nStarting client end.  Control-C to quit."

print "\nOur target:"
print "udp_server.py running on %s port %s" % (host, port)

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
                UDPSock.sendto("X", (host,port))
                
                for x in range(numtimes):
        		if(UDPSock.sendto(data,(host,port))):
                            print "*",
                        else:
                            print "."
                            
                     
                        time.sleep(0.0001)
                print "Done."

            except:
                print "Send failed"


UDPSock.close()
