using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Tools.Generator
{
    using Parser.Units;
    using Parser.Generators;

    public class Kernel
    {
        private static CppGenerator cppGenerator = new CppGenerator();

        public static void Generate()
        {
            string kernelPath = Path.Combine(Bootstrap.Source, @"Kernel\API\API.cpp");
            string systemPath = Path.Combine(Bootstrap.Source, @"System\API\API.Kernel.cpp");

            #region Kernel API

            using (StreamWriter output = System.IO.File.CreateText(kernelPath))
            {
                List<Type> types = Program.Parser.Types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared)).ToList();
                List<Method> methods = types.SelectMany(t => t.Methods).ToList();

                output.WriteLine("#include <HAL/Interrupts.h>");
                output.WriteLine("#include <Kernel/Runtime/Threading/Task.h>");
                output.WriteLine("#include <Kernel/Memory/Memory.h>");
                output.WriteLine();

                foreach (var file in Program.Parser.Files)
                    output.WriteLine("#include <{0}>", file.Path.Replace(Bootstrap.Source + "\\", "").Replace("\\", "/"));
                output.WriteLine();

                foreach (Namespace ns in Program.Parser.Namespaces)
                    output.WriteLine("using namespace {0};", ns.ToIdentifier(cppGenerator));
                output.WriteLine();

                output.WriteLine("struct API_Interrupt");
                output.WriteLine("{");
                output.WriteLine("    u64 Id;");
                output.WriteLine("    u64 Time;");
                output.WriteLine();
                output.WriteLine("    Task* Task;");
                output.WriteLine("    u32 Function;");
                output.WriteLine("    u32 ObjectId;");
                output.WriteLine("    void* Parameters;");
                output.WriteLine("    void* Result;");
                output.WriteLine();
                output.WriteLine("    API_Interrupt* Next;");
                output.WriteLine("};");
                output.WriteLine();

                output.WriteLine("API_Interrupt *firstInterrupt = null, *lastInterrupt = null;");
                output.WriteLine("u32 interruptIds = 0;");
                output.WriteLine();
                output.WriteLine("u32 sharedIds = 1;");
                output.WriteLine("void* sharedObjects[256] = { null };");
                output.WriteLine();
                output.WriteLine("Signal* signal = null;");
                output.WriteLine();

                #region API_InterruptHandler

                output.WriteLine("void API_InterruptHandler(InterruptHandlerParameters parameters, u32 irq, InterruptHandlerRegisters registers)");
                output.WriteLine("{");
                output.WriteLine("    API_Interrupt* newInterrupt = new API_Interrupt();");
                output.WriteLine();
                output.WriteLine("    newInterrupt->Id = interruptIds++;");
                output.WriteLine("    newInterrupt->Time = Timer::Time();");
                output.WriteLine("    newInterrupt->Task = Task::Current;");
                output.WriteLine("    newInterrupt->Function = registers.eax;");
                output.WriteLine("    newInterrupt->ObjectId = registers.ebx;");
                output.WriteLine("    newInterrupt->Parameters = (void*)registers.esi;");
                output.WriteLine("    newInterrupt->Result = (void*)registers.edi;");
                output.WriteLine("    newInterrupt->Next = null;");
                output.WriteLine();
                output.WriteLine("    if (firstInterrupt)");
                output.WriteLine("    {");
                output.WriteLine("        lastInterrupt->Next = newInterrupt;");
                output.WriteLine("        lastInterrupt = newInterrupt;");
                output.WriteLine("    }");
                output.WriteLine("    else");
                output.WriteLine("        firstInterrupt = lastInterrupt = newInterrupt;");
                output.WriteLine();
                output.WriteLine("    Task::Current->mode = TaskMode::WaitAPI;");
                output.WriteLine();
                output.WriteLine("    //signal->Send();");
                output.WriteLine("}");
                output.WriteLine();

                #endregion
                #region API_HandleInterrupts

                output.WriteLine("void API_HandleInterrupts()");
                output.WriteLine("{");
                output.WriteLine("    signal = new Signal();");
                output.WriteLine();
                output.WriteLine("    for (;;)");
                output.WriteLine("    {");
                output.WriteLine("        //signal->Wait();");
                output.WriteLine();
                output.WriteLine("        if (!firstInterrupt)");
                output.WriteLine("        {");
                output.WriteLine("            _asm hlt");
                output.WriteLine("            continue;");
                output.WriteLine("        }");
                output.WriteLine();
                output.WriteLine("        switch (firstInterrupt->Function)");
                output.WriteLine("        {");

                foreach (Method method in methods.Where(m => m.Result != null && !m.Modifiers.HasFlag(Modifiers.Static)))
                {
                    Type type = method.Parent as Type;

                    output.WriteLine("            #pragma region {0}", method);
                    output.WriteLine();
                    output.WriteLine("            case 0x{0:X8}:", method.GetHashCode());
                    output.WriteLine("            {");

                    if (!method.Modifiers.HasFlag(Modifiers.Static))
                        output.WriteLine("                {0}* object = ({0}*)sharedObjects[firstInterrupt->ObjectId];", type.Name);

                    for (int i = 0; i < method.Parameters.Count(); i++)
                    {
                        var kvp = method.Parameters.ElementAt(i);

                        if (kvp.Value is Type.Pointer)
                        {
                            output.WriteLine("                {0}* {1}Ptr = ({0}*)Memory_Translate((void*)((u32)firstInterrupt->Parameters{2}), firstInterrupt->Task, Task::Kernel);", kvp.Value.ToIdentifier(cppGenerator), kvp.Key, method.Parameters.Take(i).Select(p => " + sizeof(" + p.Value.ToIdentifier(cppGenerator) + ")").Join());
                            output.WriteLine("                {0} {1} = ({0})Memory_Translate((void*)*{1}Ptr, firstInterrupt->Task, Task::Kernel);", kvp.Value.ToIdentifier(cppGenerator), kvp.Key, method.Parameters.Take(i).Select(p => " + sizeof(" + p.Value.ToIdentifier(cppGenerator) + ")").Join());
                        }
                        else if (kvp.Value.Name.ToLower() == "string")
                        {
                            output.WriteLine("                string* {1}String = ({0}*)Memory_Translate((void*)((u32)firstInterrupt->Parameters{2}), firstInterrupt->Task, Task::Kernel);", kvp.Value.ToIdentifier(cppGenerator), kvp.Key, method.Parameters.Take(i).Select(p => " + sizeof(" + p.Value.ToIdentifier(cppGenerator) + ")").Join());
                            output.WriteLine("                char* {0}Chars = new char[{0}String->Length];", kvp.Key);
                            output.WriteLine("                Memory::Copy(Memory_Translate((void*){0}String->Buffer, firstInterrupt->Task, Task::Kernel), {0}Chars, {0}String->Length);", kvp.Key);
                            output.WriteLine("                string {0}({0}Chars, {0}String->Length);", kvp.Key);
                        }
                        else
                            output.WriteLine("                {0}* {1} = ({0}*)Memory_Translate((void*)((u32)firstInterrupt->Parameters{2}), firstInterrupt->Task, Task::Kernel);", kvp.Value.ToIdentifier(cppGenerator), kvp.Key, method.Parameters.Take(i).Select(p => " + sizeof(" + p.Value.ToIdentifier(cppGenerator) + ")").Join());
                    }
                    if (!method.Modifiers.HasFlag(Modifiers.Static) || method.Parameters.Any())
                        output.WriteLine();

                    if (type.Name != "ConsoleStream")
                    {
                        output.WriteLine("#if {0}", type.Name == "Memory" ? "DEBUG_MEMORY" : "DEBUG_API");
                        output.WriteLine("                Console::Write{5}(\"[API] {0} {1}::{2}({3})\", {4});", method.Result, type, method.Name, Enumerable.Range(0, method.Parameters.Count()).Select(i => method.Parameters.ElementAt(i).Value.ToIdentifier(cppGenerator).ToLower() == "string" ? "\\\"{" + i + "}\\\"" : "{" + i + "}").Join(", "), !method.Parameters.Any() ? "null" : method.Parameters.Select(p => (p.Value.Style == TypeStyle.Enum ? "(u32)" : "") + p.Key).Join(", "), method.Result.Name == "void" || method.Result.Name == "Point2" ? "Line" : "");
                        output.WriteLine("#endif");
                    }

                    output.Write("                ");
                    if (method.Result.Name != "void")
                        output.Write("{0} result = ", method.Result.ToIdentifier(cppGenerator));
                    if (method.Modifiers.HasFlag(Modifiers.Static))
                        output.Write("{0}::", type.Name);
                    else
                        output.Write("object->");
                    output.WriteLine("{0}({1});", method.Name, method.Parameters.Select(p => p.Value is Type.Pointer || p.Value.ToIdentifier(cppGenerator).ToLower() == "string" ? p.Key : "*" + p.Key).Join(", "));

                    bool returnVoid = method.Result.Name == "void";
                    bool returnSharedObject = types.Any(d => d.Name == method.Result.ToIdentifier(cppGenerator).Replace("*", ""));
                    bool returnList = method.Result.ToIdentifier(cppGenerator).Replace("const ", "").StartsWith("List<");

                    if (!returnVoid)
                    {
                        if (method.Result.ToIdentifier(cppGenerator).Replace("const ", "").ToLower() == "string")
                        {
                            output.WriteLine("                char* sharedString = (char*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);");
                            output.WriteLine("                Memory::Copy(result.Buffer, sharedString, result.Length);");
                            output.WriteLine("                sharedString[result.Length] = 0;");
                        }
                        else if (returnSharedObject)
                        {
                            output.WriteLine("                u32 id = result ? sharedIds++ : 0;");
                            output.WriteLine("                if (id)");
                            output.WriteLine("                    sharedObjects[id] = result;");
                            output.WriteLine("                Memory::Copy<u32>(&id, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));");
                        }
                        else if (returnList)
                        {
                            string listType = method.Result.ToIdentifier(cppGenerator).Replace("const ", "").Replace("List<", "").Trim().TrimEnd('>').Trim();
                            bool returnListOfSharedObjects = types.Any(d => d.Name == listType.Replace("*", ""));

                            output.WriteLine("                List<{0}>* sharedList = (List<{0}>*)Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel);", returnListOfSharedObjects ? "u32" : listType);
                            output.WriteLine("                for (u32 i = 0; i < result.Count; i++)");
                            output.WriteLine("                {");

                            if (returnListOfSharedObjects)
                            {
                                output.WriteLine("                    u32 id = result[i] ? sharedIds++ : 0;");
                                output.WriteLine("                    if (id)");
                                output.WriteLine("                        sharedObjects[id] = result[i];");
                            }

                            output.WriteLine("                    // FIXME: using (new Heap(firstInterrupt->Task))");
                            output.WriteLine("                    sharedList->Add({0});", returnListOfSharedObjects ? "id" : "result[i]");
                            output.WriteLine("                }");
                        }
                        else
                            output.WriteLine("                Memory::Copy<{0}>(&result, Memory_Translate(firstInterrupt->Result, firstInterrupt->Task, Task::Kernel));", method.Result.ToIdentifier(cppGenerator).Replace("const ", ""));
                    }

                    if (method.Result.Name != "void" && type.Name != "ConsoleStream")
                    {
                        output.WriteLine("#if {0}", type.Name == "Memory" ? "DEBUG_MEMORY" : "DEBUG_API");

                        if (method.Result.Name != "Point2" && !method.Result.ToIdentifier(cppGenerator).Contains("List"))
                            output.WriteLine("                Console::WriteLine(\" > {1}{{0}}{1}\", {0});", (method.Result.Name == "u64" ? "(u32)" : "") + (returnSharedObject ? "id" : "result"), method.Result.ToIdentifier(cppGenerator).Contains("string") ? "\\\"" : "");
                        else
                            output.WriteLine("                Console::WriteLine();");

                        output.WriteLine("#endif");
                    }

                    output.WriteLine("            }");
                    output.WriteLine("            break;");
                    output.WriteLine();
                    output.WriteLine("            #pragma endregion");
                }

                output.WriteLine("        }");
                output.WriteLine();
                output.WriteLine("        _asm cli");
                output.WriteLine();
                output.WriteLine("        firstInterrupt->Task->mode = TaskMode::Normal;");
                output.WriteLine("        delete firstInterrupt;");
                output.WriteLine("        firstInterrupt = firstInterrupt->Next;");
                output.WriteLine();
                output.WriteLine("        _asm sti");
                output.WriteLine();
                output.WriteLine("        Timer::Sleep(0);");
                output.WriteLine("    }");
                output.WriteLine("}");

                #endregion
            }

            #endregion
            #region System API

            using (StreamWriter output = System.IO.File.CreateText(systemPath))
            {
                output.WriteLine("#ifdef KERNEL");
                output.WriteLine();

                output.WriteLine("#include <HAL/Interrupts.h>");
                output.WriteLine();

                foreach (File f in Program.Parser.Files)
                    output.WriteLine("#include <{0}>", f.Path.Replace(Bootstrap.Source + "\\", "").Replace("\\", "/"));
                output.WriteLine();

                foreach (Namespace n in Program.Parser.Namespaces)
                    output.WriteLine("using namespace {0};", n.ToIdentifier(cppGenerator));
                output.WriteLine();

                List<Type> types = Program.Parser.Types/*.Where(t => t.Modifiers.HasFlag(Modifiers.Shared))*/.ToList();

                // Static fields
                /*foreach (Type type in types)
                {
                    List<Field> fields = type.Fields.Where(f => f.Modifiers.HasFlag(Modifiers.Public) && f.Modifiers.HasFlag(Modifiers.Static)).ToList();

                    if (fields.Count > 0)
                    {
                        foreach (Field field in fields)
                            output.WriteLine("{0} {1}::{2};", field.Type.ToIdentifier(), type.ToIdentifier(), field.Name);

                        output.WriteLine();
                    }
                }*/

                // Shared classes
                foreach (Type type in types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared)))
                {
                    List<Method> methods = type.Methods.Where(m => m.Parent == type && !m.Modifiers.HasFlag(Modifiers.Static)).ToList();

                    if (methods.Count > 0)
                    {
                        output.WriteLine("class Kernel{0} : public {0}", type.Name);
                        output.WriteLine("{");
                        output.WriteLine("private:");
                        output.WriteLine("    u32 objectId;");
                        output.WriteLine();
                        output.WriteLine("public:");
                        output.WriteLine("    Kernel{0}(u32 id) : objectId(id) {{ }}", type.Name);
                        output.WriteLine();

                        foreach (Method m in methods.Where(m => m.Result != null))
                            output.WriteLine("    {0} {1}({2}){3};", m.Result.ToIdentifier(cppGenerator), m.Name, string.Join(", ", m.Parameters.Select(p => p.Value.ToIdentifier(cppGenerator) + " " + p.Key).ToArray()), /*m.Const ? " const" : */"");

                        output.WriteLine("};");
                    }
                }

                output.WriteLine();

                foreach (Type type in types)
                {
                    List<Method> methods = new List<Method>();

                    if (type.Modifiers.HasFlag(Modifiers.Shared))
                    {
                        methods = type.Methods.Where(m => !m.Modifiers.HasFlag(Modifiers.Static)).ToList();
                        foreach (Method m in methods.Where(m => m.Result != null))
                        {
                            bool returnsKernelObject = types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared)).Any(d => d.Name == m.Result.ToIdentifier(cppGenerator).Replace("*", ""));
                            bool returnsList = m.Result.ToIdentifier(cppGenerator).Replace("const ", "").StartsWith("List<");
                            string listType = m.Result.ToIdentifier(cppGenerator).Replace("const ", "").Replace("List<", "").Trim().TrimEnd('>').Trim();
                            bool returnListOfSharedObjects = types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared)).Any(d => d.Name == listType.Replace("*", ""));

                            output.WriteLine("{0} Kernel{3}::{1}({2}){4}", m.Result.ToIdentifier(cppGenerator), m.Name, string.Join(", ", m.Parameters.Select(p => p.Value.ToIdentifier(cppGenerator) + " " + p.Key).ToArray()), type.Name, /*m.Const ? " const" : */"");
                            output.WriteLine("{");

                            output.WriteLine("    u32 id = objectId;");
                            if (m.Result.ToIdentifier(cppGenerator) != "void")
                            {
                                if (returnsKernelObject)
                                    output.WriteLine("    u32 result;");
                                else if (returnsList)
                                    output.WriteLine("    List<{0}> result;", returnListOfSharedObjects ? "u32" : m.Result.ToIdentifier(cppGenerator));
                                else if (m.Result.ToIdentifier(cppGenerator) == "string")
                                    output.WriteLine("    char result[0x100];");
                                else
                                    output.WriteLine("    {0} result;", m.Result.ToIdentifier(cppGenerator));
                            }
                            output.WriteLine();

                            output.WriteLine("    _asm");
                            output.WriteLine("    {");
                            output.WriteLine("        mov eax, 0x{0:X8}", m.GetHashCode());
                            output.WriteLine("        mov ebx, [id]");

                            if (m.Parameters.Any())
                                output.WriteLine("        lea esi, {0}", m.Parameters.First().Key);
                            if (m.Result.ToIdentifier(cppGenerator) != "void")
                                output.WriteLine("        lea edi, result");

                            output.WriteLine();
                            output.WriteLine("        int INTERRUPT_SYSTEM");
                            output.WriteLine("    }");

                            if (m.Result.ToIdentifier(cppGenerator) != "void")
                            {

                                output.WriteLine();

                                if (returnsKernelObject)
                                    output.WriteLine("    return result ? new Kernel{0}(result) : null;", m.Result.ToIdentifier(cppGenerator).Replace("*", ""));
                                else
                                {
                                    output.Write("    return result");
                                    if (returnsList && returnListOfSharedObjects)
                                        output.Write(".Select<{0}*>([](u32 i) -> {0}* {{ return new Kernel{0}(i); }})", listType.Replace("*", ""));
                                    output.WriteLine(";");
                                }
                            }

                            output.WriteLine("}");
                        }
                    }

                    List<Method> staticMethods = type.Methods.Where(m => m.Modifiers.HasFlag(Modifiers.Static) && m.Modifiers.HasFlag(Modifiers.Shared)).ToList();
                    foreach (Method m in staticMethods)
                    {
                        bool returnsKernelObject = types.Where(t => t.Modifiers.HasFlag(Modifiers.Shared)).Any(d => d.Name == m.Result.ToIdentifier(cppGenerator).Replace("*", ""));

                        output.WriteLine("{0} {1}::{2}({3})", m.Result.ToIdentifier(cppGenerator), type.Name, m.Name, string.Join(", ", m.Parameters.Select(p => p.Value.ToIdentifier(cppGenerator) + " " + p.Key).ToArray()));
                        output.WriteLine("{");

                        if (m.Result.ToIdentifier(cppGenerator) != "void")
                        {
                            if (returnsKernelObject)
                                output.WriteLine("    u32 result;");
                            else
                                output.WriteLine("    {0} result;", m.Result.ToIdentifier(cppGenerator));
                            output.WriteLine();
                        }

                        output.WriteLine("    _asm");
                        output.WriteLine("    {");
                        output.WriteLine("        mov eax, 0x{0:X8}", m.GetHashCode());

                        if (m.Parameters.Any())
                            output.WriteLine("        lea esi, {0}", m.Parameters.First().Key);
                        if (m.Result.ToIdentifier(cppGenerator) != "void")
                            output.WriteLine("        lea edi, result");

                        output.WriteLine();
                        output.WriteLine("        int INTERRUPT_SYSTEM");
                        output.WriteLine("    }");

                        if (m.Result.ToIdentifier(cppGenerator) != "void")
                        {
                            output.WriteLine();

                            if (returnsKernelObject)
                                output.WriteLine("    return new Kernel{0}(result);", m.Result.ToIdentifier(cppGenerator).Replace("*", ""));
                            else
                                output.WriteLine("    return result;");
                        }

                        output.WriteLine("}");
                    }

                    if (methods.Count + staticMethods.Count > 0)
                        output.WriteLine();
                }

                output.WriteLine("#endif");
            }

            #endregion
        }
    }
}
