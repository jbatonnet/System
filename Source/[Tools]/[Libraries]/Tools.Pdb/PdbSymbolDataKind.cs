namespace Tools.Pdb
{
    public enum PdbSymbolDataKind
    {
        Unknown,
        Local,
        StaticLocal,
        Param,
        ObjectPtr,
        FileStatic,
        Global,
        Member,
        StaticMember,
        Constant
    }
}
