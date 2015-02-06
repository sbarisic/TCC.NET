using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
using System.Reflection;

using Language.NET;
using TCC;

namespace TccTest {
	class Program {
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		delegate void MainFunc();

		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		delegate void StringFunc(string Arg);

		static void WriteLine(string Str) {
			Console.WriteLine(Str);
		}

		static void Main(string[] args) {
			Console.Title = "TCC.NET";
			C Tiny = new C();

			Tiny.SetLibPath("tcc");
			Tiny.SetOutputType(OutputType.Memory);

			Tiny.AddSymbol("WriteLine", new StringFunc(WriteLine));
			Tiny.AddFile("test.c");
			Tiny.Relocate(C.RELOCATE_AUTO);

			MainFunc CMain = Tiny.GetFunc<MainFunc>("Main");
			CMain();

			Console.WriteLine("Complete");
			Console.ReadLine();
		}
	}
}