`include "constants.h"
`timescale 1ns/1ps


// Operations: and (op = 0)
//             or  (op = 1)
//             add (op = 2)
//             sub(op = 6)
//             slt  (op = 7)
module ALU(ALUCon,DataA,DataB,Result); 
    input [3:0] ALUCon; 
    input [31:0] DataA,DataB; 
    output [31:0] Result; 
     
    reg [31:0] Result; 
    reg Zero; 
     
    initial begin 
        Result = 32'd0; 
    end 
 
    always@(ALUCon,DataA,DataB) 
    begin  
      case(ALUCon) 
          4'b0000://and 
             Result <= DataA&DataB; 
           
          4'b0001://or 
             Result <= DataA|DataB; 
         
          4'b0010://add 
              Result <= DataA+DataB;        
          
          4'b0110://sub 
             Result <= DataA-DataB; 
 
          4'b0111://slt 
             Result = DataA<DataB ? 1:0; 
          
          default: //error 
          begin 
              $display("ALUERROR"); 
              Result = 0; 
          end 
           
      endcase 
    end 
 
endmodule 

// Memory (active 1024 words, from 10 address lsbs).
// Read : enable ren, address addr, data dout
// Write: enable wen, address addr, data din.
module InstructMem(PC,Inst); 
    input [31:0] PC; 
    output [31:0] Inst; 
     
    reg [31:0] regfile[511:0];//32 32-bit register 
     
    assign Inst = regfile[PC]; //assigns output to instruction 
     
endmodule 


// Register File. Read ports: address raA, data rdA
//                            address raB, data rdB
//                Write port: address wa, data wd, enable wen.
module Registers(clock,WE,InData,WrReg,ReadA,ReadB,OutA,OutB); 
    input [4:0] WrReg, ReadA, ReadB; 
    input WE,clock; 
    input [31:0] InData; 
    output [31:0] OutA,OutB; 
     
    reg [31:0] OutA, OutB;//2 32-bit output reg 
    reg [31:0] regfile[31:0];//32 32-bit registers 
     
    initial begin 
        OutA = -20572; //random values for initial 
        OutB = -398567; 
    end 
     
    always@(clock,InData,WrReg,WE) 
    begin 
      if(WE && clock) 
        begin 
         regfile[WrReg]<=InData;//write to register 
         $display("Grafei to WrReg: %d Data: %d",WrReg,InData); 
        end 
        end 
     
    always @ (clock,ReadA,ReadB,WrReg) 
    begin 
        if(~clock) 
        begin 
      OutA <= regfile[ReadA];//read values from registers 
      OutB <= regfile[ReadB]; 
      
      end 
    end 
 
 
endmodule 