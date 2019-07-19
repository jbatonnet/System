#ifndef _SYSTEM_MACROS_H_
#define _SYSTEM_MACROS_H_

// String
#define concat1(x, y) x##y
#define concat(x, y) concat1(x, y)
#define stringify(x) #x

// Blocks
//#ifndef WINDOWS
#define using(declaration) for (bool concat(_using_flag, __LINE__) = true; concat(_using_flag, __LINE__); ) for (declaration; concat(_using_flag, __LINE__); concat(_using_flag, __LINE__) = false)
//#endif

#define foreach(type, variable, collection) for (bool concat(_using_flag, __LINE__) = true; concat(_using_flag, __LINE__); ) for (Reference<Collection<type>> concat(_foreach_collection, __LINE__) = (collection); concat(_using_flag, __LINE__); concat(_using_flag, __LINE__) = false) for (Reference<Iterator<type>> concat(_foreach_iterator, __LINE__) = concat(_foreach_collection, __LINE__)->GetIterator(); concat(_foreach_iterator, __LINE__)->Next(); ) for (bool concat(_foreach_flag, __LINE__) = true; concat(_foreach_flag, __LINE__); ) for (type variable = concat(_foreach_iterator, __LINE__)->GetCurrent(); concat(_foreach_flag, __LINE__); concat(_foreach_flag, __LINE__) = false)
#define lock(lockable) for (bool concat(_lock_flag, __LINE__) = true; concat(_lock_flag, __LINE__); ) for (LockableLocker concat(_lock_lockable, __LINE__)(lockable); concat(_lock_flag, __LINE__); concat(_lock_flag, __LINE__) = false)



// Assert

#define COUNT_ASSERT_ARGS_IMPL2(_1, _2, count, ...) count
#define COUNT_ASSERT_ARGS_IMPL(args) COUNT_ASSERT_ARGS_IMPL2 args
#define COUNT_ASSERT_ARGS(...) COUNT_ASSERT_ARGS_IMPL((__VA_ARGS__, 2, 1, 0))

#define assert_chooser2(count) assert##count
#define assert_chooser1(count) assert_chooser2(count)
#define assert_chooser(count) assert_chooser1(count)
#define assert_glue(x, y) x y

#define assert(...) assert_glue(assert_chooser(COUNT_ASSERT_ARGS(__VA_ARGS__)), (__VA_ARGS__))
#define assert1(condition) Debug::Assert(condition, #condition)
#define assert2(condition, message) Debug::Assert(condition, message)





#ifndef WINDOWS
#define try()
#define catch()
#define finally
#endif

/*
#define Property(type, name, field) protected: \
type field; \
public: \
Event<type> name##Changed; \
type& Get##name() { return field; } \
type Set##name(type value) { if (field == value) return value; field = value; return value; } \
_declspec(property(get = Get##name, put = Set##name)) type name;
*/

#endif