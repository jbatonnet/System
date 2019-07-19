// Cpp

type_info::type_info(const type_info& arg) : _name(arg._name)
{
}
type_info::type_info(const char* pname) : _name(pname)
{
}
type_info::~type_info()
{
}

const char* type_info::name() const
{
    return _name;
}

bool type_info::operator==(const type_info& arg) const
{
    return _name == arg._name;
}
bool type_info::operator!=(const type_info& arg) const
{
    return _name != arg._name;
}

namespace __cxxabiv1
{
    #define ADD_CXX_TYPEINFO_SOURCE(t) t::t(const char* n) : type_info(n) { } \
                                       t::~t() { }

    ADD_CXX_TYPEINFO_SOURCE(__fundamental_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__array_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__function_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__enum_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__pbase_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__pointer_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__pointer_to_member_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__class_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__si_class_type_info)
    ADD_CXX_TYPEINFO_SOURCE(__vmi_class_type_info)

    #undef ADD_CXX_TYPEINFO_SOURCE
}

// H

class type_info
{
public:
    void* _tmp;
    const char* _name;

public:
    type_info(const type_info&);
    explicit type_info(const char*);
    virtual ~type_info();

    const char* name() const;

    bool operator==(const type_info&) const;
    bool operator!=(const type_info&) const;
};

namespace __cxxabiv1
{
    #define ADD_CXX_TYPEINFO_HEADER(t) class t : public type_info \
                                       { \
                                       public: \
                                           explicit t(const char*); \
                                           virtual ~t(); \
                                       } \

    ADD_CXX_TYPEINFO_HEADER(__fundamental_type_info);
    ADD_CXX_TYPEINFO_HEADER(__array_type_info);
    ADD_CXX_TYPEINFO_HEADER(__function_type_info);
    ADD_CXX_TYPEINFO_HEADER(__enum_type_info);
    ADD_CXX_TYPEINFO_HEADER(__pbase_type_info);
    ADD_CXX_TYPEINFO_HEADER(__pointer_type_info);
    ADD_CXX_TYPEINFO_HEADER(__pointer_to_member_type_info);
    ADD_CXX_TYPEINFO_HEADER(__class_type_info);
    ADD_CXX_TYPEINFO_HEADER(__si_class_type_info);
    ADD_CXX_TYPEINFO_HEADER(__vmi_class_type_info);

    #undef ADD_CXX_TYPEINFO_HEADER
}

/*
struct __type_info_node
{
    void *_MemPtr;
    __type_info_node* _Next;
};

extern __type_info_node __type_info_root_node;

class type_info
{
public:
    virtual ~type_info() _NOEXCEPT;
    bool __CLR_OR_THIS_CALL operator==(const type_info& _Rhs) const;
    bool __CLR_OR_THIS_CALL operator!=(const type_info& _Rhs) const;
    bool __CLR_OR_THIS_CALL before(const type_info& _Rhs) const;
    const char* __CLR_OR_THIS_CALL name(__type_info_node* __ptype_info_node = &__type_info_root_node) const;
    const char* __CLR_OR_THIS_CALL raw_name() const;

private:
    void *_M_data;
    char _M_d_name[1];
    __CLR_OR_THIS_CALL type_info(const type_info& _Rhs);
    type_info& __CLR_OR_THIS_CALL operator=(const type_info& _Rhs);
    static const char *__CLRCALL_OR_CDECL _Name_base(const type_info *,__type_info_node* __ptype_info_node);
    static void __CLRCALL_OR_CDECL _Type_info_dtor(type_info *);
};
*/
