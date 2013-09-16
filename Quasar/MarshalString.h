//------------------------------------------------------------
//  Filename:  MarshalString.h
//
// Convert System::String to Standard String
//
//  Descrip:  text entered in the UI textBoxes is 
//            System::String data type.  Use
//            MarshalString to convert to Standard string
//
// 
// void functions made inline to avoid multiple definitions
//------------------------------------------------------------


#ifndef MARSHALSTRING_H
#define MARSHALSTRING_H

#include <string>
#include <iostream>
using namespace std;
using namespace System;

inline void MarshalString ( String ^ s, string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

inline void MarshalString ( String ^ s, wstring& os ) {
   using namespace Runtime::InteropServices;
   const wchar_t* chars = 
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

#endif