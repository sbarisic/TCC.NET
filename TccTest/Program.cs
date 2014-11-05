using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Reflection;

using Language.NET;
using TCC;

namespace TccTest {
	class Program {
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		delegate int TestFunc(int A, int B);
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		delegate void WriteLineFunc(string Str);

		static void Main(string[] args) {
			Console.Title = "TCC.NET";

			C Tiny = new C();

			Tiny.SetLibPath("tcc");
			Tiny.SetOutputType(OutputType.Memory);

			Tiny.Define("FUNC_NAME", "Test");
			Tiny.AddSymbol("WriteLine", new WriteLineFunc(Console.WriteLine));

			Tiny.CompileString("int FUNC_NAME(int A, int B) { WriteLine(\"Hello World!\"); return A + B; }");
			Tiny.Relocate(C.RELOCATE_AUTO);


			Console.WriteLine(Tiny.GetFunc<TestFunc>("Test")(2, 3));
			Console.ReadLine();
		}
	}
}