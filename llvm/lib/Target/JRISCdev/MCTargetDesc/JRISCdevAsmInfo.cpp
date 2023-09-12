#include "JRISCdevAsmInfo.h"

using namespace llvm;

//void JRISCdevMCAsmInfo::anchor(){}

JRISCdevMCAsmInfo::JRISCdevMCAsmInfo(const Triple &TT){
    LabelSuffix = "";
    CommentString = "# ";
    AsciiDirective = "B ";
    ZeroDirective = "ZERO ";
    IsLittleEndian = false;
    PrivateLabelPrefix = ".";
    Data8bitsDirective = "B ";
    Data16bitsDirective = "H ";
    Data32bitsDirective = "W ";
    HasDotTypeDotSizeDirective = false;
    HasFunctionAlignment = false; 
    AllowAtInName = true;
}