module DATAMEM(MemWrite,MemRead,Addr,Wdata,Rdata); 
    input [31:0] Addr,Wdata; 
    input MemWrite,MemRead; 
    output [31:0] Rdata; 
     
    reg [31:0] Rdata; 
    reg [31:0] regfile[511:0];
   
 
    always@(Addr,Wdata,MemWrite,MemRead) 
    if(MemWrite) 
    begin 
      $display("Writing %d -> Addr: %d",Wdata,Addr); 
      regfile[Addr]<=Wdata; //memory write 
    end 
 
    always@(Addr,Wdata,MemWrite,MemRead) 
    if(MemRead) 
      Rdata <= regfile[Addr];//memory read 
 
endmodule 