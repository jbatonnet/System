#include <System/System.h>
#include "Reflection.h"

#pragma const_seg(push, reflection, ".reflection")

#define ______ -1
#define _ -1

#define N IdentifierType::Namespace
#define T IdentifierType::Type

static const Namespace _reflection_namespaces[] =
{
    // Parent, Name
    { ______, "System" }, // System
    { ______, "Types" }, // Types
    { ______, "Values" }, // Values
    { ______, "Colors" }, // Colors
    { 0x0000, "Runtime" }, // System::Runtime
    { 0x0000, "Data" }, // System::Data
    { 0x0000, "IO" }, // System::IO
    { 0x0000, "Devices" }, // System::Devices
    { 0x0000, "Graphics" }, // System::Graphics
    { 0x0000, "Interface" }, // System::Interface
    { 0x0000, "Objects" }, // System::Objects
};

static const Type _reflection_types[] =
{
    // Parent, Name, TypeId
    { { N, ______ }, "void", &typeid(void) },
    { { N, ______ }, "object", &typeid(void*) },
    { { N, ______ }, "void*", &typeid(void*) },
    { { N, ______ }, "bool", &typeid(bool) },
    { { N, ______ }, "s8", &typeid(signed char) },
    { { N, ______ }, "u8", &typeid(char) },
    { { N, ______ }, "s16", &typeid(short) },
    { { N, ______ }, "u16", &typeid(unsigned short) },
    { { N, ______ }, "s32", &typeid(int) },
    { { N, ______ }, "u32", &typeid(unsigned int) },
    { { N, ______ }, "s64", &typeid(long long) },
    { { N, ______ }, "u64", &typeid(unsigned long long) },
    { { N, ______ }, "float", &typeid(float) },
    { { N, ______ }, "double", &typeid(double) },
    { { N, ______ }, "char", &typeid(char) },
    { { N, ______ }, "string", &typeid(char*) },
    { { N, ______ }, "Flag", &typeid(Flag) },
    { { N, ______ }, "String", &typeid(String) },
    { { N, ______ }, "Object", &typeid(Object) },
    { { N, ______ }, "Month", &typeid(Month) },
    { { N, ______ }, "Day", &typeid(Day) },
    { { N, ______ }, "Casing", &typeid(Casing) },
    { { N, ______ }, "MemoryType", &typeid(MemoryType) },
    { { N, ______ }, "Memory", &typeid(Memory) },
    { { N, ______ }, "Unit", &typeid(Unit) },
    { { N, ______ }, "ILockable", &typeid(ILockable) },
    { { N, ______ }, "LockableLocker", &typeid(LockableLocker) },
    { { N, ______ }, "Exception", &typeid(Exception) },
    { { N, ______ }, "AssertException", &typeid(AssertException) },
    { { N, ______ }, "ConsoleStream", &typeid(ConsoleStream) },
    { { N, ______ }, "Maths", &typeid(Maths) },
    { { N, ______ }, "Matrix3", &typeid(Matrix3) },
    { { N, ______ }, "Point2", &typeid(Point2) },
    { { N, ______ }, "Point3", &typeid(Point3) },
    { { N, ______ }, "Vector2", &typeid(Vector2) },
    { { N, ______ }, "Vector3", &typeid(Vector3) },
    { { N, ______ }, "Quaternion", &typeid(Quaternion) },
    { { N, ______ }, "UnitGroup", &typeid(UnitGroup) },
    { { N, ______ }, "Units", &typeid(Units) },
    { { N, ______ }, "ConsoleColor", &typeid(ConsoleColor) },
    { { N, ______ }, "Console", &typeid(Console) },
    { { N, ______ }, "Log", &typeid(Log) },
    { { N, ______ }, "Serial", &typeid(Serial) },
    { { N, ______ }, "Color24", &typeid(Color24) },
    { { N, ______ }, "Color32", &typeid(Color32) },
    { { N, ______ }, "Matrix4", &typeid(Matrix4) },
    { { N, ______ }, "Application", &typeid(Application) },
    { { N, ______ }, "Game", &typeid(Game) },
    { { N, ______ }, "Timer", &typeid(Timer) },
    { { N, ______ }, "RandomStream", &typeid(RandomStream) },
    { { N, ______ }, "Random", &typeid(Random) },
    { { N, ______ }, "TimeSpan", &typeid(TimeSpan) },
    { { N, ______ }, "DateTime", &typeid(DateTime) },
    { { N, 0x0003 }, "System", &typeid(Colors::System) },
    { { N, 0x0004 }, "Type", &typeid(System::Runtime::Type) },
    { { N, 0x0004 }, "Mutex", &typeid(System::Runtime::Mutex) },
    { { N, 0x0004 }, "Process", &typeid(System::Runtime::Process) },
    { { N, 0x0004 }, "Dispatcher", &typeid(System::Runtime::Dispatcher) },
    { { N, 0x0004 }, "Thread", &typeid(System::Runtime::Thread) },
    { { N, 0x0004 }, "Spinlock", &typeid(System::Runtime::Spinlock) },
    { { N, 0x0004 }, "Signal", &typeid(System::Runtime::Signal) },
    { { N, 0x0004 }, "Debugger", &typeid(System::Runtime::Debugger) },
    { { N, 0x0004 }, "Profiler", &typeid(System::Runtime::Profiler) },
    { { N, 0x0004 }, "AccessibilityModifier", &typeid(System::Runtime::AccessibilityModifier) },
    { { N, 0x0004 }, "Symbol", &typeid(System::Runtime::Symbol) },
    { { N, 0x0004 }, "Constructor", &typeid(System::Runtime::Constructor) },
    { { N, 0x0004 }, "VirtualizationModifier", &typeid(System::Runtime::VirtualizationModifier) },
    { { N, 0x0004 }, "Method", &typeid(System::Runtime::Method) },
    { { N, 0x0004 }, "Reflection", &typeid(System::Runtime::Reflection) },
    { { N, 0x0004 }, "Namespace", &typeid(System::Runtime::Namespace) },
    { { N, 0x0004 }, "Property", &typeid(System::Runtime::Property) },
    { { N, 0x0004 }, "Serializer", &typeid(System::Runtime::Serializer) },
    { { N, 0x0004 }, "Executable", &typeid(System::Runtime::Executable) },
    { { N, 0x0005 }, "Record", &typeid(System::Data::Record) },
    { { N, 0x0005 }, "Table", &typeid(System::Data::Table) },
    { { N, 0x0005 }, "Database", &typeid(System::Data::Database) },
    { { N, 0x0006 }, "SeekOrigin", &typeid(System::IO::SeekOrigin) },
    { { N, 0x0006 }, "Stream", &typeid(System::IO::Stream) },
    { { N, 0x0006 }, "TextStream", &typeid(System::IO::TextStream) },
    { { N, 0x0006 }, "BufferStream", &typeid(System::IO::BufferStream) },
    { { N, 0x0006 }, "FileAttributes", &typeid(System::IO::FileAttributes) },
    { { N, 0x0006 }, "File", &typeid(System::IO::File) },
    { { N, 0x0006 }, "Directory", &typeid(System::IO::Directory) },
    { { N, 0x0006 }, "FileStream", &typeid(System::IO::FileStream) },
    { { N, 0x0006 }, "DirectoryLink", &typeid(System::IO::DirectoryLink) },
    { { N, 0x0006 }, "AsyncStream", &typeid(System::IO::AsyncStream) },
    { { N, 0x0006 }, "DataStream", &typeid(System::IO::DataStream) },
    { { N, 0x0006 }, "TeeStream", &typeid(System::IO::TeeStream) },
    { { N, 0x0007 }, "Device", &typeid(System::Devices::Device) },
    { { N, 0x0007 }, "PointerEvent", &typeid(System::Devices::PointerEvent) },
    { { N, 0x0007 }, "PointerPositionEvent", &typeid(System::Devices::PointerPositionEvent) },
    { { N, 0x0007 }, "PointerMoveEvent", &typeid(System::Devices::PointerMoveEvent) },
    { { N, 0x0007 }, "PointerScrollEvent", &typeid(System::Devices::PointerScrollEvent) },
    { { N, 0x0007 }, "PointerDevice", &typeid(System::Devices::PointerDevice) },
    { { N, 0x0007 }, "Buttons", &typeid(System::Devices::Buttons) },
    { { N, 0x0007 }, "RawButtonEvent", &typeid(System::Devices::RawButtonEvent) },
    { { N, 0x0007 }, "ButtonEvent", &typeid(System::Devices::ButtonEvent) },
    { { N, 0x0007 }, "ButtonsMapping", &typeid(System::Devices::ButtonsMapping) },
    { { N, 0x0007 }, "CharactersMapping", &typeid(System::Devices::CharactersMapping) },
    { { N, 0x0007 }, "ButtonsState", &typeid(System::Devices::ButtonsState) },
    { { N, 0x0007 }, "ButtonsDevice", &typeid(System::Devices::ButtonsDevice) },
    { { N, 0x0007 }, "Jauges", &typeid(System::Devices::Jauges) },
    { { N, 0x0007 }, "JaugeEvent", &typeid(System::Devices::JaugeEvent) },
    { { N, 0x0007 }, "InputManager", &typeid(System::Devices::InputManager) },
    { { N, 0x0007 }, "DeviceEnumerator", &typeid(System::Devices::DeviceEnumerator) },
    { { N, 0x0007 }, "CommunicationDevice", &typeid(System::Devices::CommunicationDevice) },
    { { N, 0x0007 }, "NetworkDevice", &typeid(System::Devices::NetworkDevice) },
    { { N, 0x0007 }, "DisplayMode", &typeid(System::Devices::DisplayMode) },
    { { N, 0x0007 }, "DisplayOverlay", &typeid(System::Devices::DisplayOverlay) },
    { { N, 0x0007 }, "DisplayDevice", &typeid(System::Devices::DisplayDevice) },
    { { N, 0x0007 }, "InputType", &typeid(System::Devices::InputType) },
    { { N, 0x0007 }, "InputDeviceType", &typeid(System::Devices::InputDeviceType) },
    { { N, 0x0007 }, "InputDevice", &typeid(System::Devices::InputDevice) },
    { { N, 0x0007 }, "StorageDevice", &typeid(System::Devices::StorageDevice) },
    { { N, 0x0007 }, "FileSystem", &typeid(System::Devices::FileSystem) },
    { { N, 0x0007 }, "FileSystemConstructorBase", &typeid(System::Devices::FileSystemConstructorBase) },
    { { N, 0x0007 }, "FileSystemType", &typeid(System::Devices::FileSystemType) },
    { { N, 0x0008 }, "Point", &typeid(System::Graphics::Point) },
    { { N, 0x0008 }, "Rectangle", &typeid(System::Graphics::Rectangle) },
    { { N, 0x0008 }, "Outline", &typeid(System::Graphics::Outline) },
    { { N, 0x0008 }, "Alignment", &typeid(System::Graphics::Alignment) },
    { { N, 0x0008 }, "Orientation", &typeid(System::Graphics::Orientation) },
    { { N, 0x0008 }, "Direction", &typeid(System::Graphics::Direction) },
    { { N, 0x0008 }, "BitmapLoaderBase", &typeid(System::Graphics::BitmapLoaderBase) },
    { { N, 0x0008 }, "Bitmap", &typeid(System::Graphics::Bitmap) },
    { { N, 0x0008 }, "Bitmaps", &typeid(System::Graphics::Bitmaps) },
    { { N, 0x0008 }, "Font", &typeid(System::Graphics::Font) },
    { { N, 0x0008 }, "FontType", &typeid(System::Graphics::FontType) },
    { { N, 0x0008 }, "FontAttribute", &typeid(System::Graphics::FontAttribute) },
    { { N, 0x0008 }, "FontFamily", &typeid(System::Graphics::FontFamily) },
    { { N, 0x0008 }, "Surface", &typeid(System::Graphics::Surface) },
    { { N, 0x0008 }, "SubSurface", &typeid(System::Graphics::SubSurface) },
    { { N, 0x0008 }, "ShiftedSurface", &typeid(System::Graphics::ShiftedSurface) },
    { { N, 0x0009 }, "DockStyle", &typeid(System::Interface::DockStyle) },
    { { N, 0x0009 }, "Element", &typeid(System::Interface::Element) },
    { { N, 0x0009 }, "Control", &typeid(System::Interface::Control) },
    { { N, 0x0009 }, "Container", &typeid(System::Interface::Container) },
    { { N, 0x0009 }, "Window", &typeid(System::Interface::Window) },
    { { N, 0x0009 }, "Mover", &typeid(System::Interface::Mover) },
    { { N, 0x0009 }, "Tab", &typeid(System::Interface::Tab) },
    { { N, 0x0009 }, "ButtonStyle", &typeid(System::Interface::ButtonStyle) },
    { { N, 0x0009 }, "ButtonState", &typeid(System::Interface::ButtonState) },
    { { N, 0x0009 }, "Button", &typeid(System::Interface::Button) },
    { { N, 0x0009 }, "WindowState", &typeid(System::Interface::WindowState) },
    { { N, 0x0009 }, "WindowLayer", &typeid(System::Interface::WindowLayer) },
    { { N, 0x0009 }, "WindowsManager", &typeid(System::Interface::WindowsManager) },
    { { N, 0x0009 }, "ScrollContainer", &typeid(System::Interface::ScrollContainer) },
    { { N, 0x0009 }, "Label", &typeid(System::Interface::Label) },
    { { N, 0x0009 }, "ColumnWidthType", &typeid(System::Interface::ColumnWidthType) },
    { { N, 0x0009 }, "Grid", &typeid(System::Interface::Grid) },
    { { N, 0x0009 }, "StackContainer", &typeid(System::Interface::StackContainer) },
    { { N, 0x0009 }, "TabContainer", &typeid(System::Interface::TabContainer) },
    { { N, 0x0009 }, "Table", &typeid(System::Interface::Table) },
    { { N, 0x0009 }, "Graph", &typeid(System::Interface::Graph) },
    { { N, 0x0009 }, "Image", &typeid(System::Interface::Image) },
    { { N, 0x0009 }, "ListViewItem", &typeid(System::Interface::ListViewItem) },
    { { N, 0x0009 }, "ListView", &typeid(System::Interface::ListView) },
    { { N, 0x0009 }, "Menu", &typeid(System::Interface::Menu) },
    { { N, 0x0009 }, "TextStyle", &typeid(System::Interface::TextStyle) },
    { { N, 0x0009 }, "TextBox", &typeid(System::Interface::TextBox) },
    { { N, 0x000A }, "Entity", &typeid(System::Objects::Entity) },
    { { N, 0x000A }, "User", &typeid(System::Objects::User) },
};

static const Field _reflection_fields[] =
{
    // Parent, Name, Type
    { { T, 0x0011 }, "Length", 0x0009 }, // String::Length
    { { T, 0x0011 }, "Buffer", 0xffffffff }, // String::Buffer
    { { T, 0x0011 }, "Null", 0xffffffff }, // String::Null
    { { T, 0x0011 }, "Empty", 0xffffffff }, // String::Empty
    { { T, 0x0011 }, "NewLine", 0xffffffff }, // String::NewLine
    { { T, 0x0011 }, "Separator", 0xffffffff }, // String::Separator
    { { T, 0x001A }, "lockable", 0xffffffff }, // LockableLocker::lockable
    { { T, 0x001B }, "Message", 0xffffffff }, // Exception::Message
    { { T, 0x001B }, "Frames", 0xffffffff }, // Exception::Frames
    { { T, 0x001F }, "Identity", 0xffffffff }, // Matrix3::Identity
    { { T, 0x0020 }, "X", 0x0008 }, // Point2::X
    { { T, 0x0020 }, "Y", 0x0008 }, // Point2::Y
    { { T, 0x0020 }, "Zero", 0xffffffff }, // Point2::Zero
    { { T, 0x0020 }, "One", 0xffffffff }, // Point2::One
    { { T, 0x0021 }, "X", 0x0008 }, // Point3::X
    { { T, 0x0021 }, "Y", 0x0008 }, // Point3::Y
    { { T, 0x0021 }, "Z", 0x0008 }, // Point3::Z
    { { T, 0x0021 }, "Zero", 0xffffffff }, // Point3::Zero
    { { T, 0x0021 }, "One", 0xffffffff }, // Point3::One
    { { T, 0x0022 }, "X", 0x000c }, // Vector2::X
    { { T, 0x0022 }, "Y", 0x000c }, // Vector2::Y
    { { T, 0x0022 }, "Zero", 0xffffffff }, // Vector2::Zero
    { { T, 0x0022 }, "One", 0xffffffff }, // Vector2::One
    { { T, 0x0022 }, "Left", 0xffffffff }, // Vector2::Left
    { { T, 0x0022 }, "Up", 0xffffffff }, // Vector2::Up
    { { T, 0x0022 }, "Right", 0xffffffff }, // Vector2::Right
    { { T, 0x0022 }, "Down", 0xffffffff }, // Vector2::Down
    { { T, 0x0023 }, "X", 0x000c }, // Vector3::X
    { { T, 0x0023 }, "Y", 0x000c }, // Vector3::Y
    { { T, 0x0023 }, "Z", 0x000c }, // Vector3::Z
    { { T, 0x0023 }, "Zero", 0xffffffff }, // Vector3::Zero
    { { T, 0x0023 }, "One", 0xffffffff }, // Vector3::One
    { { T, 0x0023 }, "Backward", 0xffffffff }, // Vector3::Backward
    { { T, 0x0023 }, "Forward", 0xffffffff }, // Vector3::Forward
    { { T, 0x0023 }, "Left", 0xffffffff }, // Vector3::Left
    { { T, 0x0023 }, "Right", 0xffffffff }, // Vector3::Right
    { { T, 0x0023 }, "Down", 0xffffffff }, // Vector3::Down
    { { T, 0x0023 }, "Up", 0xffffffff }, // Vector3::Up
    { { T, 0x0024 }, "X", 0x000c }, // Quaternion::X
    { { T, 0x0024 }, "Y", 0x000c }, // Quaternion::Y
    { { T, 0x0024 }, "Z", 0x000c }, // Quaternion::Z
    { { T, 0x0024 }, "Identity", 0xffffffff }, // Quaternion::Identity
    { { T, 0x0028 }, "BaseConsoleStream", 0xffffffff }, // Console::BaseConsoleStream
    { { T, 0x0028 }, "BaseStream", 0xffffffff }, // Console::BaseStream
    { { T, 0x0028 }, "Color", 0x0027 }, // Console::Color
    { { T, 0x0028 }, "BackColor", 0x0027 }, // Console::BackColor
    { { T, 0x0029 }, "Trace", 0xffffffff }, // Log::Trace
    { { T, 0x0029 }, "Debug", 0xffffffff }, // Log::Debug
    { { T, 0x0029 }, "Info", 0xffffffff }, // Log::Info
    { { T, 0x0029 }, "Warning", 0xffffffff }, // Log::Warning
    { { T, 0x0029 }, "Error", 0xffffffff }, // Log::Error
    { { T, 0x002A }, "BaseStream", 0xffffffff }, // Serial::BaseStream
    { { T, 0x002D }, "Identity", 0xffffffff }, // Matrix4::Identity
    { { T, 0x0030 }, "Ticks", 0x000b }, // Timer::Ticks
    { { T, 0x0033 }, "sign", 0x0003 }, // TimeSpan::sign
    { { T, 0x0033 }, "days", 0x0009 }, // TimeSpan::days
    { { T, 0x0033 }, "milliseconds", 0x0009 }, // TimeSpan::milliseconds
    { { T, 0x0033 }, "Days", 0x0007 }, // TimeSpan::Days
    { { T, 0x0033 }, "Hours", 0x0005 }, // TimeSpan::Hours
    { { T, 0x0033 }, "Minutes", 0x0005 }, // TimeSpan::Minutes
    { { T, 0x0033 }, "Seconds", 0x0005 }, // TimeSpan::Seconds
    { { T, 0x0033 }, "Milliseconds", 0x0007 }, // TimeSpan::Milliseconds
    { { T, 0x0034 }, "Year", 0x0007 }, // DateTime::Year
    { { T, 0x0034 }, "Month", 0x0013 }, // DateTime::Month
    { { T, 0x0034 }, "Day", 0x0005 }, // DateTime::Day
    { { T, 0x0034 }, "Hours", 0x0005 }, // DateTime::Hours
    { { T, 0x0034 }, "Minutes", 0x0005 }, // DateTime::Minutes
    { { T, 0x0034 }, "Seconds", 0x0005 }, // DateTime::Seconds
    { { T, 0x0034 }, "Milliseconds", 0x0007 }, // DateTime::Milliseconds
    { { T, 0x0034 }, "DayOfWeek", 0xffffffff }, // DateTime::DayOfWeek
    { { T, 0x0034 }, "Date", 0xffffffff }, // DateTime::Date
    { { T, 0x0034 }, "Time", 0xffffffff }, // DateTime::Time
    { { T, 0x0034 }, "DateFormat", 0xffffffff }, // DateTime::DateFormat
    { { T, 0x0034 }, "TimeFormat", 0xffffffff }, // DateTime::TimeFormat
    { { T, 0x0034 }, "DateTimeFormat", 0xffffffff }, // DateTime::DateTimeFormat
    { { T, 0x0034 }, "LongDateFormat", 0xffffffff }, // DateTime::LongDateFormat
    { { T, 0x0034 }, "LongTimeFormat", 0xffffffff }, // DateTime::LongTimeFormat
    { { T, 0x0034 }, "LongDateTimeFormat", 0xffffffff }, // DateTime::LongDateTimeFormat
    { { T, 0x0034 }, "Now", 0xffffffff }, // DateTime::Now
    { { T, 0x0035 }, "Color", 0xffffffff }, // Colors::System::Color
    { { T, 0x0035 }, "ActiveBackground", 0xffffffff }, // Colors::System::ActiveBackground
    { { T, 0x0035 }, "InactiveBackground", 0xffffffff }, // Colors::System::InactiveBackground
    { { T, 0x0035 }, "Border", 0xffffffff }, // Colors::System::Border
    { { T, 0x0035 }, "Menu", 0xffffffff }, // Colors::System::Menu
    { { T, 0x0035 }, "ActiveTab", 0xffffffff }, // Colors::System::ActiveTab
    { { T, 0x0035 }, "InactiveTab", 0xffffffff }, // Colors::System::InactiveTab
    { { T, 0x0035 }, "ActiveSubtab", 0xffffffff }, // Colors::System::ActiveSubtab
    { { T, 0x0035 }, "InactiveSubtab", 0xffffffff }, // Colors::System::InactiveSubtab
    { { T, 0x0036 }, "RawName", 0xffffffff }, // System::Runtime::Type::RawName
    { { T, 0x0036 }, "Name", 0xffffffff }, // System::Runtime::Type::Name
    { { T, 0x0036 }, "FullName", 0xffffffff }, // System::Runtime::Type::FullName
    { { T, 0x0036 }, "BaseTypes", 0xffffffff }, // System::Runtime::Type::BaseTypes
    { { T, 0x0038 }, "Threads", 0xffffffff }, // System::Runtime::Process::Threads
    { { T, 0x0039 }, "bufferIndex", 0x0003 }, // System::Runtime::Dispatcher::bufferIndex
    { { T, 0x0039 }, "frameBuffer1", 0xffffffff }, // System::Runtime::Dispatcher::frameBuffer1
    { { T, 0x0039 }, "frameBuffer2", 0xffffffff }, // System::Runtime::Dispatcher::frameBuffer2
    { { T, 0x0039 }, "invokeLock", 0xffffffff }, // System::Runtime::Dispatcher::invokeLock
    { { T, 0x0039 }, "flushLock", 0xffffffff }, // System::Runtime::Dispatcher::flushLock
    { { T, 0x003A }, "Id", 0x0009 }, // System::Runtime::Thread::Id
    { { T, 0x003A }, "Name", 0xffffffff }, // System::Runtime::Thread::Name
    { { T, 0x003A }, "Process", 0xffffffff }, // System::Runtime::Thread::Process
    { { T, 0x003A }, "Dispatcher", 0xffffffff }, // System::Runtime::Thread::Dispatcher
    { { T, 0x0040 }, "Name", 0xffffffff }, // System::Runtime::Symbol::Name
    { { T, 0x004B }, "Default", 0xffffffff }, // System::Data::Database::Default
    { { T, 0x004D }, "Position", 0x000b }, // System::IO::Stream::Position
    { { T, 0x004D }, "Length", 0x000b }, // System::IO::Stream::Length
    { { T, 0x004D }, "EndOfStream", 0x0003 }, // System::IO::Stream::EndOfStream
    { { T, 0x004D }, "Null", 0xffffffff }, // System::IO::Stream::Null
    { { T, 0x0051 }, "Path", 0xffffffff }, // System::IO::File::Path
    { { T, 0x0051 }, "Name", 0xffffffff }, // System::IO::File::Name
    { { T, 0x0051 }, "Extension", 0xffffffff }, // System::IO::File::Extension
    { { T, 0x0051 }, "Size", 0x000b }, // System::IO::File::Size
    { { T, 0x0052 }, "Name", 0xffffffff }, // System::IO::Directory::Name
    { { T, 0x0052 }, "Parent", 0xffffffff }, // System::IO::Directory::Parent
    { { T, 0x0052 }, "Directories", 0xffffffff }, // System::IO::Directory::Directories
    { { T, 0x0052 }, "Files", 0xffffffff }, // System::IO::Directory::Files
    { { T, 0x0052 }, "FullPath", 0xffffffff }, // System::IO::Directory::FullPath
    { { T, 0x0052 }, "Root", 0xffffffff }, // System::IO::Directory::Root
    { { T, 0x0052 }, "Current", 0xffffffff }, // System::IO::Directory::Current
    { { T, 0x0054 }, "Target", 0xffffffff }, // System::IO::DirectoryLink::Target
    { { T, 0x0058 }, "Loaded", 0x0003 }, // System::Devices::Device::Loaded
    { { T, 0x0059 }, "Index", 0x0005 }, // System::Devices::PointerEvent::Index
    { { T, 0x005A }, "X", 0x0007 }, // System::Devices::PointerPositionEvent::X
    { { T, 0x005A }, "Y", 0x0007 }, // System::Devices::PointerPositionEvent::Y
    { { T, 0x005B }, "X", 0x0004 }, // System::Devices::PointerMoveEvent::X
    { { T, 0x005B }, "Y", 0x0004 }, // System::Devices::PointerMoveEvent::Y
    { { T, 0x005C }, "Delta", 0x0006 }, // System::Devices::PointerScrollEvent::Delta
    { { T, 0x005D }, "PointerMove", 0xffffffff }, // System::Devices::PointerDevice::PointerMove
    { { T, 0x005D }, "PointerDown", 0xffffffff }, // System::Devices::PointerDevice::PointerDown
    { { T, 0x005D }, "PointerUp", 0xffffffff }, // System::Devices::PointerDevice::PointerUp
    { { T, 0x005D }, "PointerScroll", 0xffffffff }, // System::Devices::PointerDevice::PointerScroll
    { { T, 0x005F }, "Button", 0x005e }, // System::Devices::RawButtonEvent::Button
    { { T, 0x0060 }, "Button", 0x005e }, // System::Devices::ButtonEvent::Button
    { { T, 0x0060 }, "Character", 0x0004 }, // System::Devices::ButtonEvent::Character
    { { T, 0x0064 }, "ButtonDown", 0xffffffff }, // System::Devices::ButtonsDevice::ButtonDown
    { { T, 0x0064 }, "ButtonUp", 0xffffffff }, // System::Devices::ButtonsDevice::ButtonUp
    { { T, 0x0066 }, "Jauge", 0x0065 }, // System::Devices::JaugeEvent::Jauge
    { { T, 0x0066 }, "Value", 0x000c }, // System::Devices::JaugeEvent::Value
    { { T, 0x0067 }, "PointerMove", 0xffffffff }, // System::Devices::InputManager::PointerMove
    { { T, 0x0067 }, "PointerDown", 0xffffffff }, // System::Devices::InputManager::PointerDown
    { { T, 0x0067 }, "PointerUp", 0xffffffff }, // System::Devices::InputManager::PointerUp
    { { T, 0x0067 }, "PointerPosition", 0xffffffff }, // System::Devices::InputManager::PointerPosition
    { { T, 0x0067 }, "ButtonDown", 0xffffffff }, // System::Devices::InputManager::ButtonDown
    { { T, 0x0067 }, "ButtonUp", 0xffffffff }, // System::Devices::InputManager::ButtonUp
    { { T, 0x0067 }, "JaugeChange", 0xffffffff }, // System::Devices::InputManager::JaugeChange
    { { T, 0x0069 }, "Streams", 0xffffffff }, // System::Devices::CommunicationDevice::Streams
    { { T, 0x006B }, "Id", 0x0007 }, // System::Devices::DisplayMode::Id
    { { T, 0x006B }, "Width", 0x0007 }, // System::Devices::DisplayMode::Width
    { { T, 0x006B }, "Height", 0x0007 }, // System::Devices::DisplayMode::Height
    { { T, 0x006B }, "Bpp", 0x0005 }, // System::Devices::DisplayMode::Bpp
    { { T, 0x006C }, "Visible", 0x0003 }, // System::Devices::DisplayOverlay::Visible
    { { T, 0x006C }, "Position", 0xffffffff }, // System::Devices::DisplayOverlay::Position
    { { T, 0x006C }, "Bitmap", 0xffffffff }, // System::Devices::DisplayOverlay::Bitmap
    { { T, 0x006D }, "Surface", 0xffffffff }, // System::Devices::DisplayDevice::Surface
    { { T, 0x006D }, "VSync", 0xffffffff }, // System::Devices::DisplayDevice::VSync
    { { T, 0x006D }, "Overlay", 0xffffffff }, // System::Devices::DisplayDevice::Overlay
    { { T, 0x006D }, "DisplayMode", 0xffffffff }, // System::Devices::DisplayDevice::DisplayMode
    { { T, 0x0071 }, "FileSystems", 0xffffffff }, // System::Devices::StorageDevice::FileSystems
    { { T, 0x0072 }, "Root", 0xffffffff }, // System::Devices::FileSystem::Root
    { { T, 0x0072 }, "Name", 0xffffffff }, // System::Devices::FileSystem::Name
    { { T, 0x0075 }, "Unit", 0xffffffff }, // System::Graphics::Point::Unit
    { { T, 0x0076 }, "Position", 0xffffffff }, // System::Graphics::Rectangle::Position
    { { T, 0x0076 }, "Size", 0xffffffff }, // System::Graphics::Rectangle::Size
    { { T, 0x0077 }, "Top", 0x0009 }, // System::Graphics::Outline::Top
    { { T, 0x0077 }, "Right", 0x0009 }, // System::Graphics::Outline::Right
    { { T, 0x0077 }, "Bottom", 0x0009 }, // System::Graphics::Outline::Bottom
    { { T, 0x0077 }, "Left", 0x0009 }, // System::Graphics::Outline::Left
    { { T, 0x007C }, "Data", 0xffffffff }, // System::Graphics::Bitmap::Data
    { { T, 0x007C }, "Size", 0xffffffff }, // System::Graphics::Bitmap::Size
    { { T, 0x007E }, "Family", 0xffffffff }, // System::Graphics::Font::Family
    { { T, 0x007E }, "Size", 0x0005 }, // System::Graphics::Font::Size
    { { T, 0x007E }, "Attributes", 0x0080 }, // System::Graphics::Font::Attributes
    { { T, 0x0081 }, "Name", 0xffffffff }, // System::Graphics::FontFamily::Name
    { { T, 0x0081 }, "Type", 0x007f }, // System::Graphics::FontFamily::Type
    { { T, 0x0086 }, "pointed", 0x0003 }, // System::Interface::Element::pointed
    { { T, 0x0086 }, "PositionChanged", 0xffffffff }, // System::Interface::Element::PositionChanged
    { { T, 0x0086 }, "Position", 0xffffffff }, // System::Interface::Element::Position
    { { T, 0x0086 }, "SizeChanged", 0xffffffff }, // System::Interface::Element::SizeChanged
    { { T, 0x0086 }, "Size", 0xffffffff }, // System::Interface::Element::Size
    { { T, 0x0086 }, "EnabledChanged", 0xffffffff }, // System::Interface::Element::EnabledChanged
    { { T, 0x0086 }, "Enabled", 0x0003 }, // System::Interface::Element::Enabled
    { { T, 0x0086 }, "VisibleChanged", 0xffffffff }, // System::Interface::Element::VisibleChanged
    { { T, 0x0086 }, "Visible", 0x0003 }, // System::Interface::Element::Visible
    { { T, 0x0086 }, "BackColorChanged", 0xffffffff }, // System::Interface::Element::BackColorChanged
    { { T, 0x0086 }, "BackColor", 0xffffffff }, // System::Interface::Element::BackColor
    { { T, 0x0086 }, "DockChanged", 0xffffffff }, // System::Interface::Element::DockChanged
    { { T, 0x0086 }, "Dock", 0x0085 }, // System::Interface::Element::Dock
    { { T, 0x0086 }, "MarginChanged", 0xffffffff }, // System::Interface::Element::MarginChanged
    { { T, 0x0086 }, "Margin", 0xffffffff }, // System::Interface::Element::Margin
    { { T, 0x0086 }, "Tag", 0xffffffff }, // System::Interface::Element::Tag
    { { T, 0x0086 }, "PointerMove", 0xffffffff }, // System::Interface::Element::PointerMove
    { { T, 0x0086 }, "PointerScroll", 0xffffffff }, // System::Interface::Element::PointerScroll
    { { T, 0x0086 }, "PointerIn", 0xffffffff }, // System::Interface::Element::PointerIn
    { { T, 0x0086 }, "PointerOut", 0xffffffff }, // System::Interface::Element::PointerOut
    { { T, 0x0086 }, "PointerDown", 0xffffffff }, // System::Interface::Element::PointerDown
    { { T, 0x0086 }, "PointerUp", 0xffffffff }, // System::Interface::Element::PointerUp
    { { T, 0x0086 }, "ButtonDown", 0xffffffff }, // System::Interface::Element::ButtonDown
    { { T, 0x0086 }, "ButtonUp", 0xffffffff }, // System::Interface::Element::ButtonUp
    { { T, 0x0087 }, "Surface", 0xffffffff }, // System::Interface::Control::Surface
    { { T, 0x0087 }, "Redrawn", 0xffffffff }, // System::Interface::Control::Redrawn
    { { T, 0x0088 }, "BorderChanged", 0xffffffff }, // System::Interface::Container::BorderChanged
    { { T, 0x0088 }, "Border", 0xffffffff }, // System::Interface::Container::Border
    { { T, 0x0088 }, "BorderColor", 0xffffffff }, // System::Interface::Container::BorderColor
    { { T, 0x0088 }, "Containers", 0xffffffff }, // System::Interface::Container::Containers
    { { T, 0x0088 }, "Controls", 0xffffffff }, // System::Interface::Container::Controls
    { { T, 0x0088 }, "Refreshed", 0xffffffff }, // System::Interface::Container::Refreshed
    { { T, 0x0089 }, "cachedSurface", 0xffffffff }, // System::Interface::Window::cachedSurface
    { { T, 0x0089 }, "Title", 0xffffffff }, // System::Interface::Window::Title
    { { T, 0x0089 }, "State", 0x008f }, // System::Interface::Window::State
    { { T, 0x0089 }, "Layer", 0x0090 }, // System::Interface::Window::Layer
    { { T, 0x0089 }, "StateChanged", 0xffffffff }, // System::Interface::Window::StateChanged
    { { T, 0x0089 }, "LayerChanged", 0xffffffff }, // System::Interface::Window::LayerChanged
    { { T, 0x0089 }, "Closed", 0xffffffff }, // System::Interface::Window::Closed
    { { T, 0x008B }, "Title", 0xffffffff }, // System::Interface::Tab::Title
    { { T, 0x008E }, "ImageChanged", 0xffffffff }, // System::Interface::Button::ImageChanged
    { { T, 0x008E }, "Image", 0xffffffff }, // System::Interface::Button::Image
    { { T, 0x008E }, "TextChanged", 0xffffffff }, // System::Interface::Button::TextChanged
    { { T, 0x008E }, "Text", 0xffffffff }, // System::Interface::Button::Text
    { { T, 0x008E }, "FontChanged", 0xffffffff }, // System::Interface::Button::FontChanged
    { { T, 0x008E }, "Font", 0xffffffff }, // System::Interface::Button::Font
    { { T, 0x008E }, "StyleChanged", 0xffffffff }, // System::Interface::Button::StyleChanged
    { { T, 0x008E }, "Style", 0x008c }, // System::Interface::Button::Style
    { { T, 0x008E }, "BorderChanged", 0xffffffff }, // System::Interface::Button::BorderChanged
    { { T, 0x008E }, "Border", 0xffffffff }, // System::Interface::Button::Border
    { { T, 0x008E }, "Alignment", 0xffffffff }, // System::Interface::Button::Alignment
    { { T, 0x008E }, "Padding", 0xffffffff }, // System::Interface::Button::Padding
    { { T, 0x008E }, "Color", 0xffffffff }, // System::Interface::Button::Color
    { { T, 0x008E }, "BorderColor", 0xffffffff }, // System::Interface::Button::BorderColor
    { { T, 0x008E }, "OverColor", 0xffffffff }, // System::Interface::Button::OverColor
    { { T, 0x008E }, "DownColor", 0xffffffff }, // System::Interface::Button::DownColor
    { { T, 0x0093 }, "Color", 0xffffffff }, // System::Interface::Label::Color
    { { T, 0x0093 }, "Text", 0xffffffff }, // System::Interface::Label::Text
    { { T, 0x0093 }, "Font", 0xffffffff }, // System::Interface::Label::Font
    { { T, 0x0093 }, "AutoSize", 0x0003 }, // System::Interface::Label::AutoSize
    { { T, 0x0093 }, "Alignment", 0xffffffff }, // System::Interface::Label::Alignment
    { { T, 0x0095 }, "Columns", 0xffffffff }, // System::Interface::Grid::Columns
    { { T, 0x0095 }, "ShowHeaders", 0x0003 }, // System::Interface::Grid::ShowHeaders
    { { T, 0x0095 }, "Font", 0xffffffff }, // System::Interface::Grid::Font
    { { T, 0x0095 }, "AlternateBackColor", 0xffffffff }, // System::Interface::Grid::AlternateBackColor
    { { T, 0x0095 }, "AutoSize", 0x0003 }, // System::Interface::Grid::AutoSize
    { { T, 0x0096 }, "Orientation", 0xffffffff }, // System::Interface::StackContainer::Orientation
    { { T, 0x0096 }, "AutoSize", 0x0003 }, // System::Interface::StackContainer::AutoSize
    { { T, 0x0096 }, "Padding", 0xffffffff }, // System::Interface::StackContainer::Padding
    { { T, 0x0096 }, "Elements", 0xffffffff }, // System::Interface::StackContainer::Elements
    { { T, 0x0097 }, "CurrentTab", 0xffffffff }, // System::Interface::TabContainer::CurrentTab
    { { T, 0x0097 }, "Orientation", 0xffffffff }, // System::Interface::TabContainer::Orientation
    { { T, 0x0099 }, "SegmentSize", 0x0007 }, // System::Interface::Graph::SegmentSize
    { { T, 0x0099 }, "GridSize", 0xffffffff }, // System::Interface::Graph::GridSize
    { { T, 0x0099 }, "GridShift", 0x0007 }, // System::Interface::Graph::GridShift
    { { T, 0x0099 }, "FillBelow", 0x0003 }, // System::Interface::Graph::FillBelow
    { { T, 0x009A }, "Color", 0xffffffff }, // System::Interface::Image::Color
    { { T, 0x009F }, "Text", 0xffffffff }, // System::Interface::TextBox::Text
    { { T, 0x009F }, "TextChanged", 0xffffffff }, // System::Interface::TextBox::TextChanged
    { { T, 0x009F }, "Font", 0xffffffff }, // System::Interface::TextBox::Font
    { { T, 0x009F }, "FontChanged", 0xffffffff }, // System::Interface::TextBox::FontChanged
    { { T, 0x009F }, "ReadOnly", 0x0003 }, // System::Interface::TextBox::ReadOnly
    { { T, 0x009F }, "MultiLine", 0x0003 }, // System::Interface::TextBox::MultiLine
    { { T, 0x009F }, "BackColor", 0xffffffff }, // System::Interface::TextBox::BackColor
    { { T, 0x009F }, "SelectionColor", 0xffffffff }, // System::Interface::TextBox::SelectionColor
    { { T, 0x009F }, "Selections", 0xffffffff }, // System::Interface::TextBox::Selections
    { { T, 0x00A0 }, "Id", 0x0009 }, // System::Objects::Entity::Id
    { { T, 0x00A1 }, "Name", 0xffffffff }, // System::Objects::User::Name
};

#pragma const_seg(pop, reflection)
