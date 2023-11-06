#include "JRISCdevMClower.h"

#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

MCOperand JRISCdevMCInstLower::lowerOperand(const MachineOperand &MO) const{
    auto MOT = MO.getType();
    switch(MOT){
        case MachineOperand::MO_Register:
            return MCOperand::createReg(MO.getReg());
        case MachineOperand::MO_Immediate:
            return MCOperand::createImm(MO.getImm());
        case MachineOperand::MO_MachineBasicBlock:
        {
            MCSymbol *sy = MO.getMBB()->getSymbol();
            const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(sy,*ctx);
            return MCOperand::createExpr(MCSym);
        }
        case MachineOperand::MO_GlobalAddress:
        {
            const GlobalValue *GV = MO.getGlobal();
            MCSymbol *sy = ctx->getOrCreateSymbol(GV->getName());
            const MCSymbolRefExpr *MCSym = MCSymbolRefExpr::create(sy,*ctx);
            return MCOperand::createExpr(MCSym);
        }
        case MachineOperand::MO_RegisterMask:
            return MCOperand();
        default:
            MO.dump();
            llvm_unreachable("Machine OP not implemented");
    }
    return MCOperand();
}


void JRISCdevMCInstLower::init(MCContext *ct){
    ctx = ct;
}
void JRISCdevMCInstLower::lower(const MachineInstr *MI, MCInst &OutMI) const {
    OutMI.setOpcode(MI->getOpcode());
    for(auto &MO: MI->operands()){
        OutMI.addOperand(lowerOperand(MO));
    }
}