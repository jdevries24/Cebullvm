#include "JRISCdevTargetMachine.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/KnownBits.h"
#include "llvm/Support/Debug.h"
using namespace llvm;

#define DEBUG_TYPE "JRISCdev-isel"
#define PASS_NAME "JRISCdev DAG->DAG Pattern Instruction Selection"

namespace llvm {
class JRISCdevDAGToDAGISel : public SelectionDAGISel {

public:
    static char ID;


 #define GET_DAGISEL_DECL
 #include "JRISCGenDAGISel.inc"

  explicit JRISCdevDAGToDAGISel(JRISCdevTargetMachine &TargetMachine,
                             CodeGenOptLevel OptLevel)
      : SelectionDAGISel(ID, TargetMachine, OptLevel) {
      }
      StringRef getPassName() const override{
        return "JRISCdev DAG->DAG instruction selection";
      }
      bool SelectAddr(SDValue Addr,SDValue &Base,SDValue &Offset);
      void SelectConst(SDNode *Node);
      void SelectLargeConst(ConstantSDNode *Node);
      void SelectFrameIndex(SDNode *Node);
      void Select(SDNode *Node) override;
};

char JRISCdevDAGToDAGISel::ID;


#define GET_DAGISEL_BODY JRISCdevDAGToDAGISel
#include "JRISCGenDAGISel.inc"

bool JRISCdevDAGToDAGISel::SelectAddr(SDValue Addr,SDValue &Base,SDValue &Offset){
  SDLoc dl(Addr);
  if(FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)){
    EVT PtrVT = getTargetLowering()->getPointerTy(CurDAG->getDataLayout());
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(),PtrVT);
    Offset = CurDAG->getTargetConstant(0,dl,MVT::i32);
    return true;
  }
  if((Addr.getOpcode() == ISD::ADD) && (Addr.getOperand(1).getOpcode() == ISD::Constant)){
    ConstantSDNode *CNode = cast<ConstantSDNode>(Addr.getOperand(1));
    if((CNode->getSExtValue() < 0xffff) && (CNode->getSExtValue() > -65500)){
      Base = Addr.getOperand(0);
      Offset = CurDAG->getTargetConstant(CNode->getSExtValue(),dl,MVT::i32);
      //CurDAG->UpdateNodeOperands(Addr.getNode(),Addr.getOperand(0),CurDAG->getTargetConstant(0,dl,MVT::i32));
      return true;
    }
  }
  //Base = Addr;
  //Offset = CurDAG->getTargetConstant(0,dl,MVT::i32);
  return false;
}

void JRISCdevDAGToDAGISel::SelectLargeConst(ConstantSDNode *node){
  SDLoc dl(node);
  CurDAG->SelectNodeTo(node,JRISCdev::LARGEMOVE,MVT::i32,CurDAG->getTargetConstant(node->getSExtValue(),dl,MVT::i32));
}

void JRISCdevDAGToDAGISel::SelectConst(SDNode *node){
  ConstantSDNode *CNode = cast<ConstantSDNode>(node);
  int64_t cvalue = CNode->getSExtValue();
  if((cvalue >= 0x10000) || (cvalue <= -0x10000)){
    SelectLargeConst(CNode);
  }
  else{
    auto ZR = CurDAG->getRegister(JRISCdev::R0,MVT::i32);
    SDLoc dl(node);
    if(cvalue == 0){
      CurDAG->SelectNodeTo(node,JRISCdev::MOV,MVT::i32,ZR);
    }
    else if(cvalue > 0){
      CurDAG->SelectNodeTo(node,JRISCdev::ADDI,MVT::i32,ZR,CurDAG->getTargetConstant(cvalue,dl,MVT::i32));
    }
    else if(cvalue < 0){
      CurDAG->SelectNodeTo(node,JRISCdev::SUBI,MVT::i32,ZR,CurDAG->getTargetConstant(cvalue * -1,dl,MVT::i32));
    }
  }
}

void JRISCdevDAGToDAGISel::SelectFrameIndex(SDNode *node){
  if(FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(node)){
    SDLoc dl(node);
    EVT PtrVT = getTargetLowering()->getPointerTy(CurDAG->getDataLayout());
    CurDAG->SelectNodeTo(node,JRISCdev::ADDI,MVT::i32,CurDAG->getTargetFrameIndex(FIN->getIndex(),PtrVT),CurDAG->getTargetConstant(0,dl,MVT::i32));
  }
}

void JRISCdevDAGToDAGISel::Select(SDNode *node){
  switch(node->getOpcode()){
    case ISD::Constant:
      SelectConst(node);
      break;
    case ISD::FrameIndex:
      SelectFrameIndex(node);
      break;
    default:
      SelectCode(node);
      break;
  }
}

FunctionPass *createJRISCdevISelDag(JRISCdevTargetMachine &TM,CodeGenOptLevel lev){
    return new JRISCdevDAGToDAGISel(TM,lev);
}

}
//INITIALIZE_PASS(JRISCdevDAGToDAGISel, DEBUG_TYPE, PASS_NAME, false, false)
