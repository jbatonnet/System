using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tools.Parser.Units;

namespace Tools.Parser.Generators
{
    public class CsGenerator : BasicGenerator
    {
        public override string GetFileIdentifier(File file)
        {
            return file.Path;
        }
        public override string GetFileDisplay(File file)
        {
            return System.IO.Path.GetFileName(file.Path);
        }

        public override string GetNamespaceIdentifier(Namespace ns)
        {
            if (ns.Parent is Namespace)
                return GetNamespaceIdentifier(ns.Parent as Namespace) + "." + ns.Name;
            else
                return ns.Name;
        }
        public override string GetNamespaceDisplay(Namespace ns)
        {
            return "namespace " + ns.Name;
        }

        public override string GetBuiltInTypeIdentifier(Units.Type.BuiltIn type)
        {
            if (type == Types.Void)         return "void";
            else if (type == Types.Pointer) return "IntPtr";
            else if (type == Types.Bool)    return "bool";
            else if (type == Types.S8)      return "sbyte";
            else if (type == Types.U8)      return "byte";
            else if (type == Types.S16)     return "short";
            else if (type == Types.U16)     return "ushort";
            else if (type == Types.S32)     return "int";
            else if (type == Types.U32)     return "uint";
            else if (type == Types.S64)     return "long";
            else if (type == Types.U64)     return "ulong";
            else if (type == Types.Single)  return "float";
            else if (type == Types.Double)  return "double";
            else if (type == Types.Char)    return "char";
            else if (type == Types.String)  return "string";

            return null;
        }

        public override string GetTypeIdentifier(Units.Type type)
        {
            if (type.Parent == null || type.Parent is File)
                return type.Name;
            else
                return GetIdentifier(type.Parent) + "." + (type.Name == "" ? UnknownIdentifier : type.Name);
        }
        public override string GetTypeDisplay(Units.Type type)
        {
            throw new NotImplementedException();
        }

        public override string GetMethodIdentifier(Method method)
        {
            throw new NotImplementedException();
        }
        public override string GetMethodDisplay(Method method)
        {
            throw new NotImplementedException();
        }

        public override string GetFieldIdentifier(Field field)
        {
            throw new NotImplementedException();
        }
        public override string GetFieldDisplay(Field field)
        {
            throw new NotImplementedException();
        }
    }
}