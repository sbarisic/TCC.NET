// This is the main DLL file.

#include "stdafx.h"

#include "TCC_NET.h"

const char my_program[] =
	"int foo(int n) {\n"
	//"    printf(\"Hello World!\\n\");\n"
	"    return n + n;\n"
	"}\n";

namespace TCC {
	static void TCCError(IntPtr Opaque, String^ Msg) {
		throw gcnew Exception(Msg);
	}

	C::C() {
		State = tcc_new();
		SetErrorFunc(IntPtr::Zero, gcnew ErrorFunc(TCCError));
	}

	C::~C() {
		tcc_delete(TCCSTAT);
	}

	void C::SetLibPath(String^ Path) {
		auto P = CreateStr(Path);
		tcc_set_lib_path(TCCSTAT, P);
		FreeStr(P);
	}

	int C::SetOutputType(OutputType OutType) {
		return tcc_set_output_type(TCCSTAT, (int)OutType);
	}

	void C::SetErrorFunc(IntPtr ErrorOpaque, ErrorFunc^ Func) {
		tcc_set_error_func(TCCSTAT, ErrorOpaque.ToPointer(), (void(*)(void*,const char*))GetFuncPointer(Func));
	}

	int C::SetOptions(String^ Str) {
		auto O = CreateStr(Str);
		int Ret = tcc_set_options(TCCSTAT, O);
		FreeStr(O);
		return Ret;
	}

	void C::Define(String^ Symbol, String^ Val) {
		auto S = CreateStr(Symbol);
		auto V = CreateStr(Val);
		tcc_define_symbol(TCCSTAT, S, V);
		FreeStr(S);
		FreeStr(V);
	}

	void C::Undef(String^ Symbol) {
		auto S = CreateStr(Symbol);
		tcc_undefine_symbol(TCCSTAT, S);
		FreeStr(S);
	}

	int C::AddIncludePath(String^ Path, bool SysInclude) {
		int Ret = 0;
		auto P = CreateStr(Path);
		if (SysInclude)
			Ret = tcc_add_sysinclude_path(TCCSTAT, P);
		else
			Ret = tcc_add_include_path(TCCSTAT, P);
		FreeStr(P);
		return Ret;
	}

	int C::AddLibraryPath(String^ Path) {
		auto P = CreateStr(Path);
		int Ret = tcc_add_library_path(TCCSTAT, P);
		FreeStr(P);
		return Ret;
	}

	int C::OutputFile(String^ File) {
		auto F = CreateStr(File);
		int Ret = tcc_output_file(TCCSTAT, F);
		FreeStr(F);
		return Ret;
	}

	int C::CompileString(String^ Str) {
		auto S = CreateStr(Str);
		int Ret = tcc_compile_string(TCCSTAT, S);
		FreeStr(S);
		return Ret;
	}

	int C::Relocate(IntPtr Mem) {
		return tcc_relocate(TCCSTAT, Mem.ToPointer());
	}

	int C::RelocateTo(Func<int, IntPtr>^ AllocFunc) {
		return tcc_relocate(TCCSTAT, AllocFunc(tcc_relocate(TCCSTAT, 0)).ToPointer());
	}

	IntPtr C::GetSymbol(String^ Name) {
		auto N = CreateStr(Name);
		IntPtr Ret = IntPtr(tcc_get_symbol(TCCSTAT, N));
		FreeStr(N);
		return Ret;
	}

	generic <typename T> T C::GetFunc(String^ Name) {
		IntPtr Sym = GetSymbol(Name);
		if (Sym == IntPtr::Zero)
			throw gcnew Exception("Function not found " + Name);
		return (T)Marshal::GetDelegateForFunctionPointer(Sym, T::typeid);
	}

	int C::AddSymbol(String^ Name, Delegate^ Del) {
		return C::AddSymbol(Name, GetFuncPointerA(Del));
	}

	int C::AddSymbol(String^ Name, IntPtr Ptr) {
		auto N = CreateStr(Name);
		int Ret = tcc_add_symbol(TCCSTAT, N, Ptr.ToPointer());
		FreeStr(N);
		return Ret;
	}

	int C::AddFile(String^ Name) {
		auto N = CreateStr(Name);
		int Ret = tcc_add_file(TCCSTAT, N);
		FreeStr(N);
		return Ret;
	}
}