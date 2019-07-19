using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Tools.Parser.Units
{
    public static class Types
    {
        public static IEnumerable<Type> All
        {
            get
            {
                yield return Void; yield return Object; yield return Pointer;
                yield return Bool;
                yield return S8; yield return U8; yield return S16; yield return U16; yield return S32; yield return U32; yield return S64; yield return U64;
                yield return Single; yield return Double;
                yield return Char; yield return String;
            }
        }

        public static Type Void = new Type.BuiltIn("void");
        public static Type Object = new Type.BuiltIn("object");
        public static Type Pointer = new Type.BuiltIn("void*");

        public static Type Bool = new Type.BuiltIn("bool");

        public static Type S8 = new Type.BuiltIn("s8");
        public static Type U8 = new Type.BuiltIn("u8");
        public static Type S16 = new Type.BuiltIn("s16");
        public static Type U16 = new Type.BuiltIn("u16");
        public static Type S32 = new Type.BuiltIn("s32");
        public static Type U32 = new Type.BuiltIn("u32");
        public static Type S64 = new Type.BuiltIn("s64");
        public static Type U64 = new Type.BuiltIn("u64");

        public static Type Single = new Type.BuiltIn("float");
        public static Type Double = new Type.BuiltIn("double");

        public static Type Char = new Type.BuiltIn("char");
        public static Type String = new Type.BuiltIn("string");
    }
}