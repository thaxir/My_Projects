module cpu(clock); 
    input clock; 
    reg [31:0] cycle; 
     
    //IF vars 
    wire [31:0] nextpc,IFpc_plus_4,IFinst; 
    reg [31:0] pc; 
     
    //ID vars 
    wire PCSrc; 
    wire [4:0] IDRegRs,IDRegRt,IDRegRd; 
    wire [31:0] IDpc_plus_4,IDinst; 
    wire [31:0] IDRegAout, IDRegBout; 
    wire [31:0] IDimm_value,BranchAddr,PCMuxOut,JumpTarget; 
     
    //control vars sto stadio ID 
    wire PCWrite,IFIDWrite,HazMuxCon,jump,bne,imm; //HazMuxCon to shma p kanei control to mux tou hazard unit
    wire [8:0] IDcontrol,ConOut; 
         
    //EX vars 
    wire [1:0] EXWB,ForwardA,ForwardB,aluop; 
    wire [2:0] EXM; 
    wire [3:0] EXEX,ALUCon; 
    wire [4:0] EXRegRs,EXRegRt,EXRegRd,regtopass; 
    wire [31:0] EXRegAout,EXRegBout,EXimm_value, b_value; 
    wire [31:0] EXALUOut,ALUSrcA,ALUSrcB; 
     
    //MEM vars 
    wire [1:0] MEMWB; 
    wire [2:0] MEMM; 
    wire [4:0] MEMRegRd; 
    wire [31:0] MEMALUOut,MEMWriteData,MEMReadData; 
     
    //WB vars 
    wire [1:0] WBWB; 
    wire [4:0] WBRegRd; 
    wire [31:0] datatowrite,WBReadData,WBALUOut; 
     
    
    //initial conditions 
    initial begin 
       pc = 0; 
       cycle = 0; 
    end 
   
     
     
      //Instruction Fetch (IF) 
    
    assign PCSrc = ((IDRegAout==IDRegBout)&IDcontrol[6])|((IDRegAout!=IDRegBout)&bne); 
    assign IFFlush = PCSrc|jump; 
    assign IFpc_plus_4 = pc + 4; 
 
    assign nextpc = PCSrc ? BranchAddr : PCMuxOut; 
    always @ (posedge clock) begin 
       if(PCWrite) 
       begin 
          pc = nextpc; //update pc 
          $display("PC: %d",pc); 
       end 
      
    end     
     
    InstructMem cpu_IMem(pc,IFinst); 
    IFID IFIDreg(IFFlush,clock,IFIDWrite,IFpc_plus_4,IFinst,IDinst,IDpc_plus_4); 
     
      //Instruction Decode (ID) 
   
   assign IDRegRs[4:0]=IDinst[25:21]; 
   assign IDRegRt[4:0]=IDinst[20:16]; 
   assign IDRegRd[4:0]=IDinst[15:11]; 
   assign IDimm_value = {IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15],IDinst[15:0]}; 
   assign BranchAddr = (IDimm_value << 2) + IDpc_plus_4; 
   assign JumpTarget[31:28] = IFpc_plus_4[31:28]; 
   assign JumpTarget[27:2] = IDinst[25:0]; 
   assign JumpTarget[1:0] = 0; 
    
   assign IDcontrol = HazMuxCon ? ConOut : 0;  
   assign PCMuxOut = jump ? JumpTarget : IFpc_plus_4; 
    
   HazardUnit HU(IDRegRs,IDRegRt,EXRegRt,EXM[1],PCWrite,IFIDWrite,HazMuxCon); 
   Control thecontrol(IDinst[31:26],ConOut,jump,bne); 
   Registers regs(clock,WBWB[0],datatowrite,WBRegRd,IDRegRs,IDRegRt,IDRegAout,IDRegBout); 
   IDEX IDEXreg(clock,IDcontrol[8:7],IDcontrol[6:4],IDcontrol[3:0],IDRegAout,IDRegBout,IDimm_value,IDRegRs,IDRegRt,IDRegRd,EXWB,EXM,EXEX,EXRegAout,EXRegBout,EXimm_value,EXRegRs,EXRegRt,EXRegRd);                                                         
    
     //Execution (EX) 
    
    assign regtopass = EXEX[3] ? EXRegRd : EXRegRt; 
    assign b_value = EXEX[2] ? EXimm_value : EXRegBout; 
     
    BIGMUX2 MUX0(ForwardA,EXRegAout,datatowrite,MEMALUOut,0,ALUSrcA); 
    BIGMUX2 MUX1(ForwardB,b_value,datatowrite,MEMALUOut,0,ALUSrcB); 
    ForwardUnit FU(MEMRegRd,WBRegRd,EXRegRs, EXRegRt, MEMWB[0], WBWB[0], ForwardA, ForwardB); 
    //ALU control 
   assign aluop[0] = (~IDinst[31]&~IDinst[30]&~IDinst[29]&IDinst[28]&~IDinst[27]&~IDinst[26])|(imm); 
   assign aluop[1] = (~IDinst[31]&~IDinst[30]&~IDinst[29]&~IDinst[28]&~IDinst[27]&~IDinst[26])|(imm); 
   ALUControl ALUcontrol(EXEX[1:0],EXimm_value[5:0],ALUCon); 
   ALU theALU(ALUCon,ALUSrcA,ALUSrcB,EXALUOut); 
   EXMEM EXMEMreg(clock,EXWB,EXM,EXALUOut,regtopass,EXRegBout,MEMM,MEMWB,MEMALUOut,MEMRegRd,MEMWriteData); 

  
    //Memory (Mem) 
     
    DATAMEM DM(MEMM[0],MEMM[1],MEMALUOut,MEMWriteData,MEMReadData); 
    MEMWB MEMWBreg(clock,MEMWB,MEMReadData,MEMALUOut,MEMRegRd,WBWB,WBReadData,WBALUOut,WBRegRd); 
    
     //Write Back (WB) 
      
    assign datatowrite = WBWB[1] ? WBReadData : WBALUOut; 
     
     
endmodule 