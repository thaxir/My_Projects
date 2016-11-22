import socket
import time

# we want to bind on all possible IP addresses
host = "0.0.0.0"
port = 5004
buffer = 10240000
socket.SOCK_DCCP                = 6
socket.IPPROTO_DCCP             = 33
# Create socket and bind to address
server = socket.socket(socket.AF_INET, socket.SOCK_DCCP,socket.IPPROTO_DCCP)

addr = (host,port)
server.bind(addr)
server.listen(1)
s,a = server.accept()
print "\n"
print "-" * 40
print "\n"
print "Starting dccp receive server...  control-break to exit."
print "\nWaiting for data..."

# total bytes recieved since last 'reset'
totalbytes = 0

# -1 is a deliberately invalid timestamp
timestamp = -1

# the total number of bursts that have come in
totalrcvs = 0

while 1:
   data,addr = s.recvfrom(buffer)
   
   if not data:
      print "No data."
      break
   else:
           delay = time.time()
      
           data = len(data)
           totalbytes += data
           totalrcvs += 1

           rate = totalbytes/(delay - timestamp) * 8 / 1000
           average_rtt= delay/totalbytes
print "\nRcvd: %s bytes, %s total in %s sec at %s kbps \n Average rtt %s" % (data, totalbytes, delay - timestamp, rate,average_rtt)
outfile = open("dccp_results.csv", "a").write(str(data)+','+'total , '+ str(totalbytes) +' in ' + str(delay-timestamp) +' sec at '+ str(rate) +' kbps'+' average rtt :'+ str(average_rtt) + '\n')
                
if data == 1:
                    # this is the reset, send one byte to trigger
                    totalbytes = 0
                    timestamp = time.time()
                    totalrcvs = 0
                    print "Reset recieved, clearing statistics."

s.close()
