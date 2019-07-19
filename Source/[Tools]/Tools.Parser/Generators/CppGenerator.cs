using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tools.Parser.Units;

namespace Tools.Parser.Generators
{
    using Type = Units.Type;

    public class CppGenerator : BasicGenerator
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
                return GetNamespaceIdentifier(ns.Parent as Namespace) + "::" + ns.Name;
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
            else if (type == Types.Object)  return "void*";
            else if (type == Types.Pointer) return "void*";
            else if (type == Types.Bool)    return "bool";
            else if (type == Types.S8)      return "signed char";
            else if (type == Types.U8)      return "char";
            else if (type == Types.S16)     return "short";
            else if (type == Types.U16)     return "unsigned short";
            else if (type == Types.S32)     return "int";
            else if (type == Types.U32)     return "unsigned int";
            else if (type == Types.S64)     return "long long";
            else if (type == Types.U64)     return "unsigned long long";
            else if (type == Types.Single)  return "float";
            else if (type == Types.Double)  return "double";
            else if (type == Types.Char)    return "char";
            else if (type == Types.String)  return "char*";

            return null;
        }

        public override string GetTypeIdentifier(Type type)
        {
            if (type is Type.Pointer)
                return GetTypeIdentifier((type as Type.Pointer).Type) + "*";
            if (type is Type.Reference)
                return GetTypeIdentifier((type as Type.Reference).Type) + "&";
            if (type is Type.Alias)
                return GetTypeIdentifier((type as Type.Alias).Type);

            if (type == null)
                return "";
            else if (type.Parent == null || type.Parent is File)
                return type.Name;
            else
                return GetIdentifier(type.Parent) + "::" + (type.Name == "" ? UnknownIdentifier : type.Name);
        }
        public override string GetTypeDisplay(Type type)
        {
            //throw new NotImplementedException();
            return type.Style.ToString().ToLower() + " " + type.Name;
        }

        public override string GetMethodIdentifier(Method method)
        {
            if (method.Parent is File)
                return method.Name;
            else
                return GetIdentifier(method.Parent) + "::" + method.Name;
        }
        public override string GetMethodDisplay(Method method)
        {
            throw new NotImplementedException();
        }

        public override string GetFieldIdentifier(Field field)
        {
            if (field.Parent is File)
                return field.Name;
            else
                return GetIdentifier(field.Parent) + "::" + field.Name;
        }
        public override string GetFieldDisplay(Field field)
        {
            return GetTypeIdentifier(field.Type) + " " + GetFieldIdentifier(field);
        }
    }
}