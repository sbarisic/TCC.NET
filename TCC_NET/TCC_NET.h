// TCC_NET.h

#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#define TCCSTAT ((TCCState*)State)

namespace TCC {
	public enum class OutputType : int {
		Memory = TCC_OUTPUT_MEMORY,
		Exe = TCC_OUTPUT_EXE,
		DLL = TCC_OUTPUT_DLL,
		OBJ = TCC_OUTPUT_OBJ,
		Preprocess = TCC_OUTPUT_PREPROCESS,
	};

	public delegate void ErrorFunc(IntPtr Opaque, String^ Msg);

	public ref class C {
	public:
		static IntPtr RELOCATE_AUTO = IntPtr(TCC_RELOCATE_AUTO);
		void* State;

		C();
		~C();

		int CompileString(String^ Str);
		int Relocate(IntPtr Mem);
		int RelocateTo(Func<int, IntPtr>^ AllocFunc);

		void SetLibPath(String^ Path);
		int SetOutputType(OutputType OutType);
		void SetErrorFunc(IntPtr ErrorOpaque, ErrorFunc^ Func);
		int SetOptions(String^ Options);

		int AddIncludePath(String^ Path, bool SysInclude);
		int AddLibraryPath(String^ Path);

		int OutputFile(String^ File);

		void Define(String^ Symbol, String^ Val);
		void Undef(String^ Symbol);

		IntPtr GetSymbol(String^ Name);
		generic <typename T> T GetFunc(String^ Name);

		int AddSymbol(String^ Name, Delegate^ Del);
		int AddSymbol(String^ Name, IntPtr Ptr);

		int AddFile(String^ Path);
	};

}
