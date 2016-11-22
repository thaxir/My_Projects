module IFID(flush,clock,IFIDWrite,PC_Plus4,Inst,InstReg,PC_Plus4Reg); 
    input [31:0] PC_Plus4,Inst; 
    input clock,IFIDWrite,flush; 
    output [31:0] InstReg, PC_Plus4Reg; 
     
    reg [31:0] InstReg, PC_Plus4Reg; 
     
    initial begin 
        InstReg = 0; 
        PC_Plus4Reg = 0; 
    end 
     
    always@(posedge clock) 
    begin 
        if(flush) 
        begin 
           InstReg <= 0; 
           PC_Plus4Reg <=0; 
        end 
        else if(IFIDWrite) 
        begin 
           InstReg <= Inst; 
           PC_Plus4Reg <= PC_Plus4; 
        end 
    end 
 
endmodule 


module IDEX(clock,WB,M,EX,DataA,DataB,imm_value,RegRs,RegRt,RegRd,WBreg,Mreg,EXreg,DataAreg, 
DataBreg,imm_valuereg,RegRsreg,RegRtreg,RegRdreg); 
    input clock; 
    input [1:0] WB; 
    input [2:0] M; 
    input [3:0] EX; 
    input [4:0] RegRs,RegRt,RegRd; 
    input [31:0] DataA,DataB,imm_value; 
    output [1:0] WBreg; 
    output [2:0] Mreg; 
    output [3:0] EXreg; 
    output [4:0] RegRsreg,RegRtreg,RegRdreg; 
    output [31:0] DataAreg,DataBreg,imm_valuereg; 
     
 
    reg [1:0] WBreg; 
    reg [2:0] Mreg; 
    reg [3:0] EXreg; 
    reg [31:0] DataAreg,DataBreg,imm_valuereg; 
    reg [4:0] RegRsreg,RegRtreg,RegRdreg; 
     
    initial begin 
        WBreg = 0;
        
        Mreg = 0; 
        EXreg = 0; 
        DataAreg = 0; 
        DataBreg = 0; 
        imm_valuereg = 0; 
        RegRsreg = 0; 
        RegRtreg = 0; 
        RegRdreg = 0; 
    end 
     
    always@(posedge clock) 
    begin 
        WBreg <= WB; 
        Mreg <= M; 
        EXreg <= EX; 
        DataAreg <= DataA; 
        DataBreg <= DataB; 
        imm_valuereg <= imm_value; 
        RegRsreg <= RegRs; 
        RegRtreg <= RegRt; 
        RegRdreg <= RegRd; 
            end 
     
endmodule 


module EXMEM(clock,WB,M,ALUOut,RegRD,WriteDataIn,Mreg,WBreg,ALUreg,RegRDreg,WriteDataOut); 
   input clock; 
   input [1:0] WB; 
   input [2:0] M; 
   input [4:0] RegRD; 
   input [31:0] ALUOut,WriteDataIn; 
   output [1:0] WBreg; 
   output [2:0] Mreg; 
   output [31:0] ALUreg,WriteDataOut; 
   output [4:0] RegRDreg; 
 
   reg [1:0] WBreg; 
   reg [2:0] Mreg; 
   reg [31:0] ALUreg,WriteDataOut; 
   reg [4:0] RegRDreg; 
    
   initial begin 
      WBreg=0; 
      Mreg=0; 
      ALUreg=0; 
      WriteDataOut=0; 
      RegRDreg=0; 
   end 
   
       always@(posedge clock) 
    begin 
        WBreg <= WB; 
        Mreg <= M; 
        ALUreg <= ALUOut; 
        RegRDreg <= RegRD; 
        WriteDataOut <= WriteDataIn; 
    end 
 
endmodule


module MEMWB(clock,WB,Memout,ALUOut,RegRD,WBreg,Memreg,ALUreg,RegRDreg); 
   input clock; 
   input [1:0] WB; 
   input [4:0] RegRD; 
   input [31:0] Memout,ALUOut; 
   output [1:0] WBreg; 
   output [31:0] Memreg,ALUreg; 
   output [4:0] RegRDreg; 
 
   reg [1:0] WBreg; 
   reg [31:0] Memreg,ALUreg; 
   reg [4:0] RegRDreg; 
    
   initial begin 
      WBreg = 0; 
      Memreg = 0; 
      ALUreg = 0; 
      RegRDreg = 0; 
        
   end 
    
    always@(posedge clock) 
    begin 
        WBreg <= WB; 
        Memreg <= Memout; 
        ALUreg <= ALUOut; 
        RegRDreg <= RegRD; 
    end 
    
endmodule  


 



