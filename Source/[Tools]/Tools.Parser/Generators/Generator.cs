using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Tools.Parser.Generators;
using Tools.Parser.Units;

namespace Tools.Parser
{
    public abstract class Generator
    {
        public abstract string GetIdentifier(Unit unit);
        public abstract string GetDisplay(Unit unit);
    }

    public abstract class BasicGenerator : Generator
    {
        protected const string UnknownIdentifier = "??";

        public override string GetIdentifier(Unit unit)
        {
            if (unit is File)
                return GetFileIdentifier(unit as File);
            else if (unit is Namespace)
                return GetNamespaceIdentifier(unit as Namespace);
            else if (unit is Units.Type.BuiltIn)
                return GetBuiltInTypeIdentifier(unit as Units.Type.BuiltIn);
            else if (unit is Units.Type)
                return GetTypeIdentifier(unit as Units.Type);
            else if (unit is Method)
                return GetMethodIdentifier(unit as Method);
            else if (unit is Field)
                return GetFieldIdentifier(unit as Field);

            return null;
        }
        public override string GetDisplay(Unit unit)
        {
            if (unit is File)
                return GetFileDisplay(unit as File);
            else if (unit is Namespace)
                return GetNamespaceDisplay(unit as Namespace);
            else if (unit is Units.Type.BuiltIn)
                return GetBuiltInTypeDisplay(unit as Units.Type.BuiltIn);
            else if (unit is Units.Type)
                return GetTypeDisplay(unit as Units.Type);
            else if (unit is Method)
                return GetMethodDisplay(unit as Method);
            else if (unit is Field)
                return GetFieldDisplay(unit as Field);

            return null;
        }

        public abstract string GetFileIdentifier(File file);
        public abstract string GetFileDisplay(File file);

        public abstract string GetNamespaceIdentifier(Namespace ns);
        public abstract string GetNamespaceDisplay(Namespace ns);

        public abstract string GetBuiltInTypeIdentifier(Units.Type.BuiltIn type);
        public virtual string GetBuiltInTypeDisplay(Units.Type.BuiltIn type)
        {
            return GetBuiltInTypeIdentifier(type);
        }

        public abstract string GetTypeIdentifier(Units.Type type);
        public abstract string GetTypeDisplay(Units.Type type);

        public abstract string GetMethodIdentifier(Method method);
        public abstract string GetMethodDisplay(Method method);

        public abstract string GetFieldIdentifier(Field field);
        public abstract string GetFieldDisplay(Field field);
    }

    public class DefaultGenerator : CppGenerator { }
}