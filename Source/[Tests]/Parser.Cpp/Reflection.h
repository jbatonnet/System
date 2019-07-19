enum class IdentifierType : unsigned char
{
    None,
    Namespace,
    Type,
    Method,
    Constructor,
    Property
};

struct Namespace
{
    const short parent;
    const char* name;
};

struct Type
{
    const struct
    {
        IdentifierType type;
        short index;
    } parent;
    
    const char* name;
    const type_info* typeId;
};

struct Method
{
    const struct
    {
        IdentifierType type;
        short index;
    } parent;

    const char* name;
    const void* pointer;
};

struct Field
{
    const struct
    {
        IdentifierType type;
        short index;
    } parent;

    const char* name;
    const short type;
};

extern const Namespace _reflection_namespaces[];
extern const Type _reflection_types[];
extern const Method _reflection_methods[];
extern const Field _reflection_fields[];