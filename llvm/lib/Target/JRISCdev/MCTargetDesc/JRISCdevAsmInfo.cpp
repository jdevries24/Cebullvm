#include "JRISCdevAsmInfo.h"

using namespace llvm;

void JRISCdevMCAsmInfo::anchor(){}

JRISCdevMCAsmInfo::JRISCdevMCAsmInfo(const Triple &TT){
    LabelSuffix = "";
    CommentString = "#";
    AsciiDirective = "B";
    ZeroDirective = "ZERO";
    IsLittleEndian = false;
    GlobalDirective = "@";
    Data8bitsDirective = "B";
    Data16bitsDirective = "H";
    Data32bitsDirective = "W";
}