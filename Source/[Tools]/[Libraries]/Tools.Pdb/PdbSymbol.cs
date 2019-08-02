using System;
using System.Collections.Generic;

using Dia2Lib;

namespace Tools.Pdb
{
    public class PdbSymbol
    {
        private const int nsNone = 0x00;
        private const int nsfCaseInsensitive = 0x02;
        private const int nsfUndecoratedName = 0x10;

        public uint SymIndexId => diaSymbol.symIndexId;
        public uint SymTag => diaSymbol.symTag;
        public string Name => diaSymbol.name;
        public PdbSymbol LexicalParent => PdbSymbol.From(diaSymbol.lexicalParent);
        public PdbSymbol ClassParent => PdbSymbol.From(diaSymbol.classParent);
        public PdbSymbol Type => PdbSymbol.From(diaSymbol.type);
        public uint DataKind => diaSymbol.dataKind;
        public uint LocationType => diaSymbol.locationType;
        public uint AddressSection => diaSymbol.addressSection;
        public uint AddressOffset => diaSymbol.addressOffset;
        public uint RelativeVirtualAddress => diaSymbol.relativeVirtualAddress;
        public ulong VirtualAddress => diaSymbol.virtualAddress;
        public uint RegisterId => diaSymbol.registerId;
        public int Offset => diaSymbol.offset;
        public ulong Length => diaSymbol.length;
        public uint Slot => diaSymbol.slot;
        public int VolatileType => diaSymbol.volatileType;
        public int ConstType => diaSymbol.constType;
        public int UnalignedType => diaSymbol.unalignedType;
        public uint Access => diaSymbol.access;
        public string LibraryName => diaSymbol.libraryName;
        public uint Platform => diaSymbol.platform;
        public uint Language => diaSymbol.language;
        public int EditAndContinueEnabled => diaSymbol.editAndContinueEnabled;
        public uint FrontEndMajor => diaSymbol.frontEndMajor;
        public uint FrontEndMinor => diaSymbol.frontEndMinor;
        public uint FrontEndBuild => diaSymbol.frontEndBuild;
        public uint BackEndMajor => diaSymbol.backEndMajor;
        public uint BackEndMinor => diaSymbol.backEndMinor;
        public uint BackEndBuild => diaSymbol.backEndBuild;
        public string SourceFileName => diaSymbol.sourceFileName;
        public string Unused => diaSymbol.unused;
        public uint ThunkOrdinal => diaSymbol.thunkOrdinal;
        public int ThisAdjust => diaSymbol.thisAdjust;
        public uint VirtualBaseOffset => diaSymbol.virtualBaseOffset;
        public int Virtual => diaSymbol.@virtual;
        public int Intro => diaSymbol.intro;
        public int Pure => diaSymbol.pure;
        public uint CallingConvention => diaSymbol.callingConvention;
        public dynamic Value => diaSymbol.value;
        public uint BaseType => diaSymbol.baseType;
        public uint Token => diaSymbol.token;
        public uint TimeStamp => diaSymbol.timeStamp;
        public Guid Guid => diaSymbol.guid;
        public string SymbolsFileName => diaSymbol.symbolsFileName;
        public int Reference => diaSymbol.reference;
        public uint Count => diaSymbol.count;
        public uint BitPosition => diaSymbol.bitPosition;
        public PdbSymbol ArrayIndexType => PdbSymbol.From(diaSymbol.arrayIndexType);
        public int Packed => diaSymbol.packed;
        public int Constructor => diaSymbol.constructor;
        public int OverloadedOperator => diaSymbol.overloadedOperator;
        public int Nested => diaSymbol.nested;
        public int HasNestedTypes => diaSymbol.hasNestedTypes;
        public int HasAssignmentOperator => diaSymbol.hasAssignmentOperator;
        public int HasCastOperator => diaSymbol.hasCastOperator;
        public int Scoped => diaSymbol.scoped;
        public int VirtualBaseClass => diaSymbol.virtualBaseClass;
        public int IndirectVirtualBaseClass => diaSymbol.indirectVirtualBaseClass;
        public int VirtualBasePointerOffset => diaSymbol.virtualBasePointerOffset;
        public PdbSymbol VirtualTableShape => PdbSymbol.From(diaSymbol.virtualTableShape);
        public uint LexicalParentId => diaSymbol.lexicalParentId;
        public uint ClassParentId => diaSymbol.classParentId;
        public uint TypeId => diaSymbol.typeId;
        public uint ArrayIndexTypeId => diaSymbol.arrayIndexTypeId;
        public uint VirtualTableShapeId => diaSymbol.virtualTableShapeId;
        public int Code => diaSymbol.code;
        public int Function => diaSymbol.function;
        public int Managed => diaSymbol.managed;
        public int Msil => diaSymbol.msil;
        public uint VirtualBaseDispIndex => diaSymbol.virtualBaseDispIndex;
        public string UndecoratedName => diaSymbol.undecoratedName;
        public uint Age => diaSymbol.age;
        public uint Signature => diaSymbol.signature;
        public int CompilerGenerated => diaSymbol.compilerGenerated;
        public int AddressTaken => diaSymbol.addressTaken;
        public uint Rank => diaSymbol.rank;
        public PdbSymbol LowerBound => PdbSymbol.From(diaSymbol.lowerBound);
        public PdbSymbol UpperBound => PdbSymbol.From(diaSymbol.upperBound);
        public uint LowerBoundId => diaSymbol.lowerBoundId;
        public uint UpperBoundId => diaSymbol.upperBoundId;
        public uint TargetSection => diaSymbol.targetSection;
        public uint TargetOffset => diaSymbol.targetOffset;
        public uint TargetRelativeVirtualAddress => diaSymbol.targetRelativeVirtualAddress;
        public ulong TargetVirtualAddress => diaSymbol.targetVirtualAddress;
        public uint MachineType => diaSymbol.machineType;
        public uint OemId => diaSymbol.oemId;
        public uint OemSymbolId => diaSymbol.oemSymbolId;
        public PdbSymbol ObjectPointerType => PdbSymbol.From(diaSymbol.objectPointerType);
        public uint UdtKind => diaSymbol.udtKind;
        public int NoReturn => diaSymbol.noReturn;
        public int CustomCallingConvention => diaSymbol.customCallingConvention;
        public int NoInline => diaSymbol.noInline;
        public int OptimizedCodeDebugInfo => diaSymbol.optimizedCodeDebugInfo;
        public int NotReached => diaSymbol.notReached;
        public int InterruptReturn => diaSymbol.interruptReturn;
        public int FarReturn => diaSymbol.farReturn;
        public int IsStatic => diaSymbol.isStatic;
        public int HasDebugInfo => diaSymbol.hasDebugInfo;
        public int IsLTCG => diaSymbol.isLTCG;
        public int IsDataAligned => diaSymbol.isDataAligned;
        public int HasSecurityChecks => diaSymbol.hasSecurityChecks;
        public string CompilerName => diaSymbol.compilerName;
        public int HasAlloca => diaSymbol.hasAlloca;
        public int HasSetJump => diaSymbol.hasSetJump;
        public int HasLongJump => diaSymbol.hasLongJump;
        public int HasInlAsm => diaSymbol.hasInlAsm;
        public int HasEH => diaSymbol.hasEH;
        public int HasSEH => diaSymbol.hasSEH;
        public int HasEHa => diaSymbol.hasEHa;
        public int IsNaked => diaSymbol.isNaked;
        public int IsAggregated => diaSymbol.isAggregated;
        public int IsSplitted => diaSymbol.isSplitted;
        public PdbSymbol Container => PdbSymbol.From(diaSymbol.container);
        public int InlSpec => diaSymbol.inlSpec;
        public int NoStackOrdering => diaSymbol.noStackOrdering;
        public PdbSymbol VirtualBaseTableType => PdbSymbol.From(diaSymbol.virtualBaseTableType);
        public int HasManagedCode => diaSymbol.hasManagedCode;
        public int IsHotpatchable => diaSymbol.isHotpatchable;
        public int IsCVTCIL => diaSymbol.isCVTCIL;
        public int IsMSILNetmodule => diaSymbol.isMSILNetmodule;
        public int IsCTypes => diaSymbol.isCTypes;
        public int IsStripped => diaSymbol.isStripped;
        public uint FrontEndQFE => diaSymbol.frontEndQFE;
        public uint BackEndQFE => diaSymbol.backEndQFE;
        public int WasInlined => diaSymbol.wasInlined;
        public int StrictGSCheck => diaSymbol.strictGSCheck;
        public int IsCxxReturnUdt => diaSymbol.isCxxReturnUdt;
        public int IsConstructorVirtualBase => diaSymbol.isConstructorVirtualBase;
        public int RValueReference => diaSymbol.RValueReference;
        public PdbSymbol UnmodifiedType => PdbSymbol.From(diaSymbol.unmodifiedType);
        public int FramePointerPresent => diaSymbol.framePointerPresent;
        public int IsSafeBuffers => diaSymbol.isSafeBuffers;
        public int Intrinsic => diaSymbol.intrinsic;
        public int @Sealed => diaSymbol.@sealed;
        public int HfaFloat => diaSymbol.hfaFloat;
        public int HfaDouble => diaSymbol.hfaDouble;
        public uint LiveRangeStartAddressSection => diaSymbol.liveRangeStartAddressSection;
        public uint LiveRangeStartAddressOffset => diaSymbol.liveRangeStartAddressOffset;
        public uint LiveRangeStartRelativeVirtualAddress => diaSymbol.liveRangeStartRelativeVirtualAddress;
        public uint CountLiveRanges => diaSymbol.countLiveRanges;
        public ulong LiveRangeLength => diaSymbol.liveRangeLength;
        public uint OffsetInUdt => diaSymbol.offsetInUdt;
        public uint ParamBasePointerRegisterId => diaSymbol.paramBasePointerRegisterId;
        public uint LocalBasePointerRegisterId => diaSymbol.localBasePointerRegisterId;
        public int IsLocationControlFlowDependent => diaSymbol.isLocationControlFlowDependent;
        public uint Stride => diaSymbol.stride;
        public uint NumberOfRows => diaSymbol.numberOfRows;
        public uint NumberOfColumns => diaSymbol.numberOfColumns;
        public int IsMatrixRowMajor => diaSymbol.isMatrixRowMajor;
        public int IsReturnValue => diaSymbol.isReturnValue;
        public int IsOptimizedAway => diaSymbol.isOptimizedAway;
        public uint BuiltInKind => diaSymbol.builtInKind;
        public uint RegisterType => diaSymbol.registerType;
        public uint BaseDataSlot => diaSymbol.baseDataSlot;
        public uint BaseDataOffset => diaSymbol.baseDataOffset;
        public uint TextureSlot => diaSymbol.textureSlot;
        public uint SamplerSlot => diaSymbol.samplerSlot;
        public uint UavSlot => diaSymbol.uavSlot;
        public uint SizeInUdt => diaSymbol.sizeInUdt;
        public uint MemorySpaceKind => diaSymbol.memorySpaceKind;
        public uint UnmodifiedTypeId => diaSymbol.unmodifiedTypeId;
        public uint SubTypeId => diaSymbol.subTypeId;
        public PdbSymbol SubType => PdbSymbol.From(diaSymbol.subType);
        public uint NumberOfModifiers => diaSymbol.numberOfModifiers;
        public uint NumberOfRegisterIndices => diaSymbol.numberOfRegisterIndices;
        public int IsHLSLData => diaSymbol.isHLSLData;
        public int IsPointerToDataMember => diaSymbol.isPointerToDataMember;
        public int IsPointerToMemberFunction => diaSymbol.isPointerToMemberFunction;
        public int IsSingleInheritance => diaSymbol.isSingleInheritance;
        public int IsMultipleInheritance => diaSymbol.isMultipleInheritance;
        public int IsVirtualInheritance => diaSymbol.isVirtualInheritance;
        public int RestrictedType => diaSymbol.restrictedType;
        public int IsPointerBasedOnSymbolValue => diaSymbol.isPointerBasedOnSymbolValue;
        public PdbSymbol BaseSymbol => PdbSymbol.From(diaSymbol.baseSymbol);
        public uint BaseSymbolId => diaSymbol.baseSymbolId;
        public string ObjectFileName => diaSymbol.objectFileName;
        public int IsAcceleratorGroupSharedLocal => diaSymbol.isAcceleratorGroupSharedLocal;
        public int IsAcceleratorPointerTagLiveRange => diaSymbol.isAcceleratorPointerTagLiveRange;
        public int IsAcceleratorStubFunction => diaSymbol.isAcceleratorStubFunction;
        public uint NumberOfAcceleratorPointerTags => diaSymbol.numberOfAcceleratorPointerTags;
        public int IsSdl => diaSymbol.isSdl;
        public int IsWinRTPointer => diaSymbol.isWinRTPointer;
        public int IsRefUdt => diaSymbol.isRefUdt;
        public int IsValueUdt => diaSymbol.isValueUdt;
        public int IsInterfaceUdt => diaSymbol.isInterfaceUdt;
        public int IsPGO => diaSymbol.isPGO;
        public int HasValidPGOCounts => diaSymbol.hasValidPGOCounts;
        public int IsOptimizedForSpeed => diaSymbol.isOptimizedForSpeed;
        public uint PGOEntryCount => diaSymbol.PGOEntryCount;
        public uint PGOEdgeCount => diaSymbol.PGOEdgeCount;
        public ulong PGODynamicInstructionCount => diaSymbol.PGODynamicInstructionCount;
        public uint StaticSize => diaSymbol.staticSize;
        public uint FinalLiveStaticSize => diaSymbol.finalLiveStaticSize;
        public string PhaseName => diaSymbol.phaseName;
        public int HasControlFlowCheck => diaSymbol.hasControlFlowCheck;
        public int ConstantExport => diaSymbol.constantExport;
        public int DataExport => diaSymbol.dataExport;
        public int PrivateExport => diaSymbol.privateExport;
        public int NoNameExport => diaSymbol.noNameExport;
        public int ExportHasExplicitlyAssignedOrdinal => diaSymbol.exportHasExplicitlyAssignedOrdinal;
        public int ExportIsForwarder => diaSymbol.exportIsForwarder;
        public uint Ordinal => diaSymbol.ordinal;
        public uint FrameSize => diaSymbol.frameSize;
        public uint ExceptionHandlerAddressSection => diaSymbol.exceptionHandlerAddressSection;
        public uint ExceptionHandlerAddressOffset => diaSymbol.exceptionHandlerAddressOffset;
        public uint ExceptionHandlerRelativeVirtualAddress => diaSymbol.exceptionHandlerRelativeVirtualAddress;
        public ulong ExceptionHandlerVirtualAddress => diaSymbol.exceptionHandlerVirtualAddress;
        public uint Characteristics => diaSymbol.characteristics;
        public PdbSymbol CoffGroup => PdbSymbol.From(diaSymbol.coffGroup);


        internal IDiaSymbol diaSymbol;

        private PdbSymbol(IDiaSymbol diaSymbol)
        {
            this.diaSymbol = diaSymbol;
        }

        public IEnumerable<PdbSymbol> FindChildren(string name)
        {
            diaSymbol.findChildrenEx(SymTagEnum.SymTagNull, name, nsfCaseInsensitive | nsfUndecoratedName, out IDiaEnumSymbols diaEnumSymbols);
            return PdbSymbol.EnumerateFrom(diaEnumSymbols);
        }
        public IEnumerable<PdbSymbol> FindChildren(PdbSymbolTag tag)
        {
            diaSymbol.findChildrenEx((SymTagEnum)tag, null, nsNone, out IDiaEnumSymbols diaEnumSymbols);
            return PdbSymbol.EnumerateFrom(diaEnumSymbols);
        }
        public IEnumerable<PdbSymbol> FindChildren(PdbSymbolTag tag, string name)
        {
            diaSymbol.findChildrenEx((SymTagEnum)tag, name, nsfCaseInsensitive | nsfUndecoratedName, out IDiaEnumSymbols diaEnumSymbols);
            return PdbSymbol.EnumerateFrom(diaEnumSymbols);
        }

        internal static PdbSymbol From(IDiaSymbol diaSymbol)
        {
            if (diaSymbol == null)
                return null;

            return new PdbSymbol(diaSymbol);
        }
        internal static IEnumerable<PdbSymbol> EnumerateFrom(IDiaEnumSymbols diaEnumSymbols)
        {
            if (diaEnumSymbols == null)
                yield break;

            diaEnumSymbols.Reset();

            while (true)
            {
                diaEnumSymbols.Next(1, out IDiaSymbol diaSymbol, out uint read);
                if (read == 0)
                    break;

                yield return new PdbSymbol(diaSymbol);
            }
        }
    }
}
