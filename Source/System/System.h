#ifndef _SYSTEM_SYSTEM_H_
#define _SYSTEM_SYSTEM_H_

extern "C" void AppMain();

#include <System/Common.h>

// Base
#include <System/Base/Default.h>
#include <System/Base/Events.h>
#include <System/Base/Exception.h>
#include <System/Base/Flags.h>
#include <System/Base/Functions.h>
#include <System/Base/Macros.h>
#include <System/Base/Object.h>
#include <System/Base/Parameters.h>
#include <System/Base/Reference.h>
#include <System/Base/String.h>
#include <System/Base/Templates.h>
#include <System/Base/Types.h>
#include <System/Base/Unit.h>
#include <System/Base/Exceptions/AssertException.h>

// Data
#include <System/Data/Database.h>
#include <System/Data/Record.h>
#include <System/Data/Table.h>

// Debugging
#include <System/Debugging/Console.h>
#include <System/Debugging/Log.h>
#include <System/Debugging/Serial.h>

// Devices
#include <System/Devices/Device.h>
#include <System/Devices/DeviceEnumerator.h>
#include <System/Devices/Communication/CommunicationDevice.h>
#include <System/Devices/Communication/NetworkDevice.h>
#include <System/Devices/Display/DisplayDevice.h>
#include <System/Devices/Input/ButtonsDevice.h>
#include <System/Devices/Input/InputDevice.h>
#include <System/Devices/Input/InputManager.h>
#include <System/Devices/Input/PointerDevice.h>
#include <System/Devices/Storage/FileSystem.h>
#include <System/Devices/Storage/StorageDevice.h>

// Graphics
#include <System/Graphics/Bitmap.h>
#include <System/Graphics/Colors.h>
#include <System/Graphics/Font.h>
#include <System/Graphics/FontFamily.h>
#include <System/Graphics/Point.h>
#include <System/Graphics/Surface.h>

// Interface
#include <System/Interface/Element.h>
#include <System/Interface/Window.h>
#include <System/Interface/WindowsManager.h>
#include <System/Interface/Containers/Container.h>
#include <System/Interface/Containers/Grid.h>
#include <System/Interface/Containers/Mover.h>
#include <System/Interface/Containers/ScrollContainer.h>
#include <System/Interface/Containers/SideMenu.h>
#include <System/Interface/Containers/StackContainer.h>
#include <System/Interface/Containers/Tab.h>
#include <System/Interface/Containers/TabContainer.h>
#include <System/Interface/Containers/Table.h>
#include <System/Interface/Controls/Button.h>
#include <System/Interface/Controls/Control.h>
#include <System/Interface/Controls/Graph.h>
#include <System/Interface/Controls/Image.h>
#include <System/Interface/Controls/Label.h>
#include <System/Interface/Controls/ListView.h>
#include <System/Interface/Controls/Menu.h>
#include <System/Interface/Controls/TextBox.h>

// IO
#include <System/IO/Directory.h>
#include <System/IO/DirectoryLink.h>
#include <System/IO/File.h>
#include <System/IO/ResourceLoader.h>
#include <System/IO/Streams/AsyncStream.h>
#include <System/IO/Streams/BufferStream.h>
#include <System/IO/Streams/DataStream.h>
#include <System/IO/Streams/Stream.h>
#include <System/IO/Streams/TeeStream.h>
#include <System/IO/Streams/TextStream.h>

// Maths
#include <System/Maths/Maths.h>
#include <System/Maths/Matrixes.h>
#include <System/Maths/Vectors.h>

// Objects
#include <System/Objects/Entity.h>
#include <System/Objects/User.h>
#include <System/Objects/Applications/Application.h>
#include <System/Objects/Applications/Game.h>

// Runtime
#include <System/Runtime/Cryptography/CRC32.h>
#include <System/Runtime/Cryptography/MD5.h>
#include <System/Runtime/Cryptography/SHA1.h>
#include <System/Runtime/Debugging/Debugger.h>
#include <System/Runtime/Debugging/Profiler.h>
#include <System/Runtime/Reflection/Constructor.h>
#include <System/Runtime/Reflection/Method.h>
#include <System/Runtime/Reflection/Namespace.h>
#include <System/Runtime/Reflection/Property.h>
#include <System/Runtime/Reflection/Symbol.h>
#include <System/Runtime/Reflection/Type.h>
#include <System/Runtime/Serialization/JSON.h>
#include <System/Runtime/Serialization/Serializer.h>
#include <System/Runtime/Serialization/XML.h>
#include <System/Runtime/Threading/Dispatcher.h>
#include <System/Runtime/Threading/Executable.h>
#include <System/Runtime/Threading/Lockable.h>
#include <System/Runtime/Threading/Mutex.h>
#include <System/Runtime/Threading/Process.h>
#include <System/Runtime/Threading/Signal.h>
#include <System/Runtime/Threading/Spinlock.h>
#include <System/Runtime/Threading/Thread.h>

// Structures
#include <System/Structures/Tuple.h>
#include <System/Structures/Collections/Array.h>
#include <System/Structures/Collections/Collection.h>
#include <System/Structures/Collections/ConcatenedCollection.h>
#include <System/Structures/Collections/Dictionary.h>
#include <System/Structures/Collections/FilteredCollection.h>
#include <System/Structures/Collections/InitializerCollection.h>
#include <System/Structures/Collections/LinkedList.h>
#include <System/Structures/Collections/List.h>
#include <System/Structures/Collections/ObservableCollection.h>
#include <System/Structures/Collections/ObservableList.h>
#include <System/Structures/Collections/OrderedCollection.h>
#include <System/Structures/Collections/ProjectedCollection.h>
#include <System/Structures/Collections/Queue.h>
#include <System/Structures/Collections/Stack.h>
#include <System/Structures/Graphs/GraphNode.h>
#include <System/Structures/Trees/Tree.h>
#include <System/Structures/Trees/TreeNode.h>

// Utilities
#include <System/Utilities/Random.h>
#include <System/Utilities/Units.h>
#include <System/Utilities/Time/DateTime.h>
#include <System/Utilities/Time/Enums.h>
#include <System/Utilities/Time/Timer.h>
#include <System/Utilities/Time/TimeSpan.h>

#endif
