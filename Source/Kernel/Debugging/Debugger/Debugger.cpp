#include <System/System.h>

using namespace System;
using namespace Types;
using namespace Values;
using namespace System::Runtime;
using namespace System::Data;
using namespace System::IO;
using namespace System::Devices;
using namespace System::Graphics;
using namespace System::Interface;
using namespace System::Objects;

void DebuggerLoop()
{
    DataStream* debuggerStream = new DataStream(null);

    switch (debuggerStream->Read<u32>())
    {
        case 0x0CFBF3F4: // u32 RTTI_ClassHierarchyDescriptor::Signature::get()
        {
            RTTI_ClassHierarchyDescriptor* object = debuggerStream->Read<RTTI_ClassHierarchyDescriptor*>();
            u32 result = object->Signature;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8E482A5C: // void RTTI_ClassHierarchyDescriptor::Signature::set(u32 value)
        {
        }
        break;
        
        case 0x057B11F9: // u32 RTTI_ClassHierarchyDescriptor::Attributes::get()
        {
            RTTI_ClassHierarchyDescriptor* object = debuggerStream->Read<RTTI_ClassHierarchyDescriptor*>();
            u32 result = object->Attributes;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x11EB542D: // void RTTI_ClassHierarchyDescriptor::Attributes::set(u32 value)
        {
        }
        break;
        
        case 0x41A68EAD: // u32 RTTI_ClassHierarchyDescriptor::BaseClassesCount::get()
        {
            RTTI_ClassHierarchyDescriptor* object = debuggerStream->Read<RTTI_ClassHierarchyDescriptor*>();
            u32 result = object->BaseClassesCount;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x9628C8F5: // void RTTI_ClassHierarchyDescriptor::BaseClassesCount::set(u32 value)
        {
        }
        break;
        
        case 0xE7BA4C8E: // [RTTI_BaseClassDescriptor]** RTTI_ClassHierarchyDescriptor::BaseClasses::get()
        {
            RTTI_ClassHierarchyDescriptor* object = debuggerStream->Read<RTTI_ClassHierarchyDescriptor*>();
            [RTTI_BaseClassDescriptor]** result = object->BaseClasses;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x62FF5680: // void RTTI_ClassHierarchyDescriptor::BaseClasses::set([RTTI_BaseClassDescriptor]** value)
        {
        }
        break;
        
        case 0x5F40A8D6: // s32 RTTI_PMD::MemberOffset::get()
        {
            RTTI_PMD* object = debuggerStream->Read<RTTI_PMD*>();
            s32 result = object->MemberOffset;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8F757EAD: // void RTTI_PMD::MemberOffset::set(s32 value)
        {
        }
        break;
        
        case 0x9A57B3AB: // s32 RTTI_PMD::VTableOffset::get()
        {
            RTTI_PMD* object = debuggerStream->Read<RTTI_PMD*>();
            s32 result = object->VTableOffset;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4C145A15: // void RTTI_PMD::VTableOffset::set(s32 value)
        {
        }
        break;
        
        case 0x2BAE3BBC: // s32 RTTI_PMD::vdisp::get()
        {
            RTTI_PMD* object = debuggerStream->Read<RTTI_PMD*>();
            s32 result = object->vdisp;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x241B5418: // void RTTI_PMD::vdisp::set(s32 value)
        {
        }
        break;
        
        case 0x8EC606C0: // RTTI_TypeDescriptor* RTTI_BaseClassDescriptor::Type::get()
        {
            RTTI_BaseClassDescriptor* object = debuggerStream->Read<RTTI_BaseClassDescriptor*>();
            RTTI_TypeDescriptor* result = object->Type;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC58CC89D: // void RTTI_BaseClassDescriptor::Type::set(RTTI_TypeDescriptor* value)
        {
        }
        break;
        
        case 0xEA4DEB61: // u32 RTTI_BaseClassDescriptor::BaseClassesCount::get()
        {
            RTTI_BaseClassDescriptor* object = debuggerStream->Read<RTTI_BaseClassDescriptor*>();
            u32 result = object->BaseClassesCount;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x22AC85B6: // void RTTI_BaseClassDescriptor::BaseClassesCount::set(u32 value)
        {
        }
        break;
        
        case 0xD5BCF458: // [RTTI_PMD] RTTI_BaseClassDescriptor::Pmd::get()
        {
            RTTI_BaseClassDescriptor* object = debuggerStream->Read<RTTI_BaseClassDescriptor*>();
            [RTTI_PMD] result = object->Pmd;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5AD17F12: // void RTTI_BaseClassDescriptor::Pmd::set([RTTI_PMD] value)
        {
        }
        break;
        
        case 0x281008DE: // u32 RTTI_BaseClassDescriptor::Attributes::get()
        {
            RTTI_BaseClassDescriptor* object = debuggerStream->Read<RTTI_BaseClassDescriptor*>();
            u32 result = object->Attributes;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA60C9FB0: // void RTTI_BaseClassDescriptor::Attributes::set(u32 value)
        {
        }
        break;
        
        case 0xC6DD40C3: // [RTTI_ClassHierarchyDescriptor]* RTTI_BaseClassDescriptor::Hierarchy::get()
        {
            RTTI_BaseClassDescriptor* object = debuggerStream->Read<RTTI_BaseClassDescriptor*>();
            [RTTI_ClassHierarchyDescriptor]* result = object->Hierarchy;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3564BFCB: // void RTTI_BaseClassDescriptor::Hierarchy::set([RTTI_ClassHierarchyDescriptor]* value)
        {
        }
        break;
        
        case 0x28BA24B3: // u32 RTTI_CompleteObjectLocator::Signature::get()
        {
            RTTI_CompleteObjectLocator* object = debuggerStream->Read<RTTI_CompleteObjectLocator*>();
            u32 result = object->Signature;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4622027A: // void RTTI_CompleteObjectLocator::Signature::set(u32 value)
        {
        }
        break;
        
        case 0xEC0C43E2: // u32 RTTI_CompleteObjectLocator::Offset::get()
        {
            RTTI_CompleteObjectLocator* object = debuggerStream->Read<RTTI_CompleteObjectLocator*>();
            u32 result = object->Offset;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x30F9D8D5: // void RTTI_CompleteObjectLocator::Offset::set(u32 value)
        {
        }
        break;
        
        case 0xA85E2855: // u32 RTTI_CompleteObjectLocator::CdOffset::get()
        {
            RTTI_CompleteObjectLocator* object = debuggerStream->Read<RTTI_CompleteObjectLocator*>();
            u32 result = object->CdOffset;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB1FE7988: // void RTTI_CompleteObjectLocator::CdOffset::set(u32 value)
        {
        }
        break;
        
        case 0x5EEF7F2C: // RTTI_TypeDescriptor* RTTI_CompleteObjectLocator::Type::get()
        {
            RTTI_CompleteObjectLocator* object = debuggerStream->Read<RTTI_CompleteObjectLocator*>();
            RTTI_TypeDescriptor* result = object->Type;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xDBBD9767: // void RTTI_CompleteObjectLocator::Type::set(RTTI_TypeDescriptor* value)
        {
        }
        break;
        
        case 0x8B6A3D7B: // [RTTI_ClassHierarchyDescriptor]* RTTI_CompleteObjectLocator::Hierarchy::get()
        {
            RTTI_CompleteObjectLocator* object = debuggerStream->Read<RTTI_CompleteObjectLocator*>();
            [RTTI_ClassHierarchyDescriptor]* result = object->Hierarchy;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x47B6D982: // void RTTI_CompleteObjectLocator::Hierarchy::set([RTTI_ClassHierarchyDescriptor]* value)
        {
        }
        break;
        
        case 0x3574402C: // Unit::Unit()
        {
            Unit* result = new Unit();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x29B32F36: // Unit::Unit(float value)
        {
            float value = debuggerStream->Read<float>();
            Unit* result = new Unit(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3834E0DC: // Unit::Unit(double value)
        {
            double value = debuggerStream->Read<double>();
            Unit* result = new Unit(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x22CD845C: // Unit::Unit(bool value)
        {
            bool value = debuggerStream->Read<bool>();
            Unit* result = new Unit(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4458E491: // Unit::Unit(s32 value)
        {
            s32 value = debuggerStream->Read<s32>();
            Unit* result = new Unit(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x79932B73: // Unit Unit::operator+(Unit me, Unit other)
        {
            Unit* object = debuggerStream->Read<Unit*>();
            Unit* other = debuggerStream->Read<Unit*>();
            Unit result = object->operator+(other);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xD976F4AE: // Unit Unit::operator-(Unit me, Unit other)
        {
            Unit* object = debuggerStream->Read<Unit*>();
            Unit* other = debuggerStream->Read<Unit*>();
            Unit result = object->operator-(other);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xA405F2F6: // Unit Unit::operator*(Unit me, Unit other)
        {
            Unit* object = debuggerStream->Read<Unit*>();
            Unit* other = debuggerStream->Read<Unit*>();
            Unit result = object->operator*(other);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xFF5F3F21: // Unit Unit::operator!(Unit me)
        {
            Unit* object = debuggerStream->Read<Unit*>();
            Unit result = object->operator!();
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xECF00FF4: // [Matrix3] Matrix3::Identity::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            [Matrix3] result = object->Identity;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xAFE94C2C: // void Matrix3::Identity::set([Matrix3] value)
        {
        }
        break;
        
        case 0xAC8F1637: // float* Matrix3::components::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float* result = object->components;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6CD36279: // void Matrix3::components::set(float* value)
        {
        }
        break;
        
        case 0xCDE99418: // float Matrix3::c11::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c11;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6663BE83: // void Matrix3::c11::set(float value)
        {
        }
        break;
        
        case 0x436693FB: // float Matrix3::c12::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c12;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC535382A: // void Matrix3::c12::set(float value)
        {
        }
        break;
        
        case 0x8FCC9365: // float Matrix3::c13::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c13;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x12D7B872: // void Matrix3::c13::set(float value)
        {
        }
        break;
        
        case 0xF464A8DD: // float Matrix3::c21::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c21;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC9CAF349: // void Matrix3::c21::set(float value)
        {
        }
        break;
        
        case 0x7AEBAF3E: // float Matrix3::c22::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c22;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6A9C75E0: // void Matrix3::c22::set(float value)
        {
        }
        break;
        
        case 0xB641AFA0: // float Matrix3::c23::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c23;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xBD7EF5B8: // void Matrix3::c23::set(float value)
        {
        }
        break;
        
        case 0xE31FBC9E: // float Matrix3::c31::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c31;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xACADC80F: // void Matrix3::c31::set(float value)
        {
        }
        break;
        
        case 0x6D90BB7D: // float Matrix3::c32::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c32;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0FFB4EA6: // void Matrix3::c32::set(float value)
        {
        }
        break;
        
        case 0xA13ABBE3: // float Matrix3::c33::get()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->c33;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xD819CEFE: // void Matrix3::c33::set(float value)
        {
        }
        break;
        
        case 0x0516AEF2: // Matrix3::Matrix3()
        {
            Matrix3* result = new Matrix3();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0C7CFF2A: // Matrix3::Matrix3(Matrix3& matrix)
        {
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3* result = new Matrix3(*matrix);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xAE346FEC: // Matrix3::Matrix3(float c11, float c12, float c13, float c21, float c22, float c23, float c31, float c32, float c33)
        {
            float c11 = debuggerStream->Read<float>();
            float c12 = debuggerStream->Read<float>();
            float c13 = debuggerStream->Read<float>();
            float c21 = debuggerStream->Read<float>();
            float c22 = debuggerStream->Read<float>();
            float c23 = debuggerStream->Read<float>();
            float c31 = debuggerStream->Read<float>();
            float c32 = debuggerStream->Read<float>();
            float c33 = debuggerStream->Read<float>();
            Matrix3* result = new Matrix3(c11, c12, c13, c21, c22, c23, c31, c32, c33);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x48D9429D: // float Matrix3::Determinant()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            float result = object->Determinant();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x2A215020: // Matrix3& Matrix3::Transpose()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->Transpose();
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xD9F74A4D: // void Matrix3::Normalize()
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            object->Normalize();
        }
        break;
        
        case 0x6558E35A: // Matrix3& Matrix3::Normalize(Matrix3& matrix)
        {
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = Matrix3::Normalize(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xD87DEA3D: // Matrix3& Matrix3::CreateRotation(float pitch, float yaw, float roll)
        {
            float pitch = debuggerStream->Read<float>();
            float yaw = debuggerStream->Read<float>();
            float roll = debuggerStream->Read<float>();
            Matrix3& result = Matrix3::CreateRotation(pitch, yaw, roll);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x2726B52F: // Matrix3& Matrix3::CreateRotation(float x, float y, float z, float angle)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            float z = debuggerStream->Read<float>();
            float angle = debuggerStream->Read<float>();
            Matrix3& result = Matrix3::CreateRotation(x, y, z, angle);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC798744F: // Matrix3& Matrix3::CreateRotation([Vector3]& vector, float angle)
        {
            [Vector3]* vector = debuggerStream->Read<[Vector3]*>();
            float angle = debuggerStream->Read<float>();
            Matrix3& result = Matrix3::CreateRotation(*vector, angle);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xF0BB4161: // Matrix3& Matrix3::CreateRotation([Quaternion]& quaternion)
        {
            [Quaternion]* quaternion = debuggerStream->Read<[Quaternion]*>();
            Matrix3& result = Matrix3::CreateRotation(*quaternion);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x79668963: // Matrix3& Matrix3::CreateTranslation(float x, float y, float z)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            float z = debuggerStream->Read<float>();
            Matrix3& result = Matrix3::CreateTranslation(x, y, z);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC75B8629: // Matrix3& Matrix3::CreateTranslation([Vector3]& vector)
        {
            [Vector3]* vector = debuggerStream->Read<[Vector3]*>();
            Matrix3& result = Matrix3::CreateTranslation(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xCE1D7969: // Matrix3& Matrix3::CreateScale(float x, float y, float z)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            float z = debuggerStream->Read<float>();
            Matrix3& result = Matrix3::CreateScale(x, y, z);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x567ADD1B: // Matrix3& Matrix3::CreateScale([Vector3]& vector)
        {
            [Vector3]* vector = debuggerStream->Read<[Vector3]*>();
            Matrix3& result = Matrix3::CreateScale(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xE4DB3035: // Matrix3& Matrix3::operator+=(Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator+=(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x0BE695D5: // Matrix3& Matrix3::operator-=(Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator-=(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x7F7E7C5A: // Matrix3& Matrix3::operator*=(Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator*=(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xE7DD0B4A: // Matrix3& Matrix3::operator/=(Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator/=(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x611606DC: // Matrix3& Matrix3::operator+(Matrix3 me, Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator+(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xE5359B09: // Matrix3& Matrix3::operator-(Matrix3 me, Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator-(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x04713D9A: // Matrix3& Matrix3::operator*(Matrix3 me, Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator*(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x3CD359B0: // [Vector3]& Matrix3::operator*([Vector3]& vector)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            [Vector3]* vector = debuggerStream->Read<[Vector3]*>();
            [Vector3]& result = object->operator*(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x2FFBED85: // Matrix3& Matrix3::operator/(Matrix3 me, Matrix3& matrix)
        {
            Matrix3* object = debuggerStream->Read<Matrix3*>();
            Matrix3* matrix = debuggerStream->Read<Matrix3*>();
            Matrix3& result = object->operator/(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xF243F0A5: // s32 Point2::X::get()
        {
            Point2* object = debuggerStream->Read<Point2*>();
            s32 result = object->X;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x54F27163: // void Point2::X::set(s32 value)
        {
        }
        break;
        
        case 0x3EE9F03B: // s32 Point2::Y::get()
        {
            Point2* object = debuggerStream->Read<Point2*>();
            s32 result = object->Y;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xD354BA20: // void Point2::Y::set(s32 value)
        {
        }
        break;
        
        case 0xE2490815: // [Point2] Point2::Zero::get()
        {
            Point2* object = debuggerStream->Read<Point2*>();
            [Point2] result = object->Zero;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA83B5ABA: // void Point2::Zero::set([Point2] value)
        {
        }
        break;
        
        case 0xCDCDF3D7: // [Point2] Point2::One::get()
        {
            Point2* object = debuggerStream->Read<Point2*>();
            [Point2] result = object->One;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x006D4FBA: // void Point2::One::set([Point2] value)
        {
        }
        break;
        
        case 0x8A32DBA4: // Point2::Point2()
        {
            Point2* result = new Point2();
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA6741962: // Point2::Point2(s32 n)
        {
            s32 n = debuggerStream->Read<s32>();
            Point2* result = new Point2(n);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC20D36D7: // Point2::Point2(s32 x, s32 y)
        {
            s32 x = debuggerStream->Read<s32>();
            s32 y = debuggerStream->Read<s32>();
            Point2* result = new Point2(x, y);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x52DA452A: // bool Point2::operator==(Point2& point)
        {
            Point2* object = debuggerStream->Read<Point2*>();
            Point2* point = debuggerStream->Read<Point2*>();
            bool result = object->operator==(*point);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF6361326: // bool Point2::operator!=(Point2& point)
        {
            Point2* object = debuggerStream->Read<Point2*>();
            Point2* point = debuggerStream->Read<Point2*>();
            bool result = object->operator!=(*point);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x33CD2F65: // s32 Point3::X::get()
        {
            Point3* object = debuggerStream->Read<Point3*>();
            s32 result = object->X;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x31954A25: // void Point3::X::set(s32 value)
        {
        }
        break;
        
        case 0xFF672FFB: // s32 Point3::Y::get()
        {
            Point3* object = debuggerStream->Read<Point3*>();
            s32 result = object->Y;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB6338166: // void Point3::Y::set(s32 value)
        {
        }
        break;
        
        case 0x71E82818: // s32 Point3::Z::get()
        {
            Point3* object = debuggerStream->Read<Point3*>();
            s32 result = object->Z;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xE5A9DAE2: // void Point3::Z::set(s32 value)
        {
        }
        break;
        
        case 0x7F46E963: // [Point3] Point3::Zero::get()
        {
            Point3* object = debuggerStream->Read<Point3*>();
            [Point3] result = object->Zero;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xBEF5B3E4: // void Point3::Zero::set([Point3] value)
        {
        }
        break;
        
        case 0x105B2A52: // [Point3] Point3::One::get()
        {
            Point3* object = debuggerStream->Read<Point3*>();
            [Point3] result = object->One;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x799A40B8: // void Point3::One::set([Point3] value)
        {
        }
        break;
        
        case 0x4A7E6E53: // Point3::Point3()
        {
            Point3* result = new Point3();
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF0272BB1: // Point3::Point3(s32 n)
        {
            s32 n = debuggerStream->Read<s32>();
            Point3* result = new Point3(n);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x97870711: // Point3::Point3(s32 x, s32 y, s32 z)
        {
            s32 x = debuggerStream->Read<s32>();
            s32 y = debuggerStream->Read<s32>();
            s32 z = debuggerStream->Read<s32>();
            Point3* result = new Point3(x, y, z);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x44304BDD: // bool Point3::operator==(Point3& point)
        {
            Point3* object = debuggerStream->Read<Point3*>();
            Point3* point = debuggerStream->Read<Point3*>();
            bool result = object->operator==(*point);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xE0DC1DD1: // bool Point3::operator!=(Point3& point)
        {
            Point3* object = debuggerStream->Read<Point3*>();
            Point3* point = debuggerStream->Read<Point3*>();
            bool result = object->operator!=(*point);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x1763008F: // float Vector2::X::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float result = object->X;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3AA992C2: // void Vector2::X::set(float value)
        {
        }
        break;
        
        case 0xDBC90011: // float Vector2::Y::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float result = object->Y;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xED4B129A: // void Vector2::Y::set(float value)
        {
        }
        break;
        
        case 0xF8410AB3: // [Vector2] Vector2::Zero::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->Zero;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x42B46C19: // void Vector2::Zero::set([Vector2] value)
        {
        }
        break;
        
        case 0x1F1B28C3: // [Vector2] Vector2::One::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->One;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x673AB1F0: // void Vector2::One::set([Vector2] value)
        {
        }
        break;
        
        case 0x6EFF3A3B: // [Vector2] Vector2::Left::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->Left;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB67BF7E5: // void Vector2::Left::set([Vector2] value)
        {
        }
        break;
        
        case 0x3C170736: // [Vector2] Vector2::Up::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->Up;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x728359B1: // void Vector2::Up::set([Vector2] value)
        {
        }
        break;
        
        case 0xCF62734A: // [Vector2] Vector2::Right::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->Right;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5621E5D4: // void Vector2::Right::set([Vector2] value)
        {
        }
        break;
        
        case 0x95DE3066: // [Vector2] Vector2::Down::get()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            [Vector2] result = object->Down;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4D2C632A: // void Vector2::Down::set([Vector2] value)
        {
        }
        break;
        
        case 0xFAB63955: // Vector2::Vector2()
        {
            Vector2* result = new Vector2();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6A236397: // Vector2::Vector2(Vector2& vector)
        {
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2* result = new Vector2(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x150FCB31: // Vector2::Vector2(float n)
        {
            float n = debuggerStream->Read<float>();
            Vector2* result = new Vector2(n);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x2B438CBC: // Vector2::Vector2(float x, float y)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            Vector2* result = new Vector2(x, y);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA56F0972: // Vector2::Vector2([Point2]& point)
        {
            [Point2]* point = debuggerStream->Read<[Point2]*>();
            Vector2* result = new Vector2(*point);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x9148A90B: // float Vector2::Length()
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float result = object->Length();
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB7B8C389: // Vector2 Vector2::Lerp(Vector2& v1, Vector2& v2, float c)
        {
            Vector2* v1 = debuggerStream->Read<Vector2*>();
            Vector2* v2 = debuggerStream->Read<Vector2*>();
            float c = debuggerStream->Read<float>();
            Vector2 result = Vector2::Lerp(*v1, *v2, c);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xA4F587E6: // float Vector2::Dot(Vector2& v1, Vector2& v2)
        {
            Vector2* v1 = debuggerStream->Read<Vector2*>();
            Vector2* v2 = debuggerStream->Read<Vector2*>();
            float result = Vector2::Dot(*v1, *v2);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7C87B05F: // Vector2 Vector2::Normalize(Vector2& vector)
        {
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2 result = Vector2::Normalize(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x75AA9EB5: // float Vector2::Angle(Vector2& v1, Vector2& v2)
        {
            Vector2* v1 = debuggerStream->Read<Vector2*>();
            Vector2* v2 = debuggerStream->Read<Vector2*>();
            float result = Vector2::Angle(*v1, *v2);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x373B0C75: // float Vector2::Distance(Vector2& v1, Vector2& v2)
        {
            Vector2* v1 = debuggerStream->Read<Vector2*>();
            Vector2* v2 = debuggerStream->Read<Vector2*>();
            float result = Vector2::Distance(*v1, *v2);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xFB1405CF: // bool Vector2::operator==(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            bool result = object->operator==(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF206A5B2: // bool Vector2::operator!=(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            bool result = object->operator!=(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x18314DD3: // Vector2& Vector2::operator+=(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2& result = object->operator+=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xF70CE833: // Vector2& Vector2::operator-=(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2& result = object->operator-=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xE7041FFF: // Vector2& Vector2::operator*=(float factor)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float factor = debuggerStream->Read<float>();
            Vector2& result = object->operator*=(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x839401BC: // Vector2& Vector2::operator*=(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2& result = object->operator*=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xAD935AB0: // Vector2& Vector2::operator/=(float factor)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float factor = debuggerStream->Read<float>();
            Vector2& result = object->operator/=(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x1B3776AC: // Vector2& Vector2::operator/=(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2& result = object->operator/=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xB6BA7BB1: // Vector2 Vector2::operator+(Vector2 me, Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2 result = object->operator+(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x3299E664: // Vector2 Vector2::operator-(Vector2 me, Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2 result = object->operator-(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x33172983: // Vector2 Vector2::operator*(Vector2 me, float factor)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float factor = debuggerStream->Read<float>();
            Vector2 result = object->operator*(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xBC8164A1: // Vector2 Vector2::operator*(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2 result = object->operator*(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC7B9C50F: // Vector2 Vector2::operator/(Vector2 me, float factor)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            float factor = debuggerStream->Read<float>();
            Vector2 result = object->operator/(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xCDD6C8E3: // Vector2 Vector2::operator/(Vector2& vector)
        {
            Vector2* object = debuggerStream->Read<Vector2*>();
            Vector2* vector = debuggerStream->Read<Vector2*>();
            Vector2 result = object->operator/(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xD6EDDF4F: // float Vector3::X::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float result = object->X;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x2D81F602: // void Vector3::X::set(float value)
        {
        }
        break;
        
        case 0x1A47DFD1: // float Vector3::Y::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float result = object->Y;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xFA63765A: // void Vector3::Y::set(float value)
        {
        }
        break;
        
        case 0x94C8D832: // float Vector3::Z::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float result = object->Z;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5935F0F3: // void Vector3::Z::set(float value)
        {
        }
        break;
        
        case 0x654EEBC5: // [Vector3] Vector3::Zero::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Zero;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x36C8A17E: // void Vector3::Zero::set([Vector3] value)
        {
        }
        break;
        
        case 0xC28DF146: // [Vector3] Vector3::One::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->One;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x71F458AE: // void Vector3::One::set([Vector3] value)
        {
        }
        break;
        
        case 0xA671A871: // [Vector3] Vector3::Backward::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Backward;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x047F75A7: // void Vector3::Backward::set([Vector3] value)
        {
        }
        break;
        
        case 0x13D99F81: // [Vector3] Vector3::Forward::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Forward;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x27E522BF: // void Vector3::Forward::set([Vector3] value)
        {
        }
        break;
        
        case 0xF3F0DB4D: // [Vector3] Vector3::Left::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Left;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC2073A82: // void Vector3::Left::set([Vector3] value)
        {
        }
        break;
        
        case 0x7699A8A2: // [Vector3] Vector3::Right::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Right;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7D3A129F: // void Vector3::Right::set([Vector3] value)
        {
        }
        break;
        
        case 0x08D1D110: // [Vector3] Vector3::Down::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Down;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3950AE4D: // void Vector3::Down::set([Vector3] value)
        {
        }
        break;
        
        case 0xA7B24B59: // [Vector3] Vector3::Up::get()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            [Vector3] result = object->Up;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0B7456B3: // void Vector3::Up::set([Vector3] value)
        {
        }
        break;
        
        case 0x60D11F0D: // Vector3::Vector3()
        {
            Vector3* result = new Vector3();
            debuggerStream->Write(result);
        }
        break;
        
        case 0xCF08ED26: // Vector3::Vector3(Vector3& vector)
        {
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3* result = new Vector3(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5E0300EC: // Vector3::Vector3(float n)
        {
            float n = debuggerStream->Read<float>();
            Vector3* result = new Vector3(n);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x44E78B91: // Vector3::Vector3(float x, float y, float z)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            float z = debuggerStream->Read<float>();
            Vector3* result = new Vector3(x, y, z);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x68ECF202: // Vector3::Vector3([Vector2]& vector, float z)
        {
            [Vector2]* vector = debuggerStream->Read<[Vector2]*>();
            float z = debuggerStream->Read<float>();
            Vector3* result = new Vector3(*vector, z);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x50C676CB: // float Vector3::Length()
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float result = object->Length();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x199FC2C7: // Vector3 Vector3::Lerp(Vector3& v1, Vector3& v2, float c)
        {
            Vector3* v1 = debuggerStream->Read<Vector3*>();
            Vector3* v2 = debuggerStream->Read<Vector3*>();
            float c = debuggerStream->Read<float>();
            Vector3 result = Vector3::Lerp(*v1, *v2, c);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x34402D96: // Vector3 Vector3::Cross(Vector3& v1, Vector3& v2)
        {
            Vector3* v1 = debuggerStream->Read<Vector3*>();
            Vector3* v2 = debuggerStream->Read<Vector3*>();
            Vector3 result = Vector3::Cross(*v1, *v2);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x9FBC92C3: // float Vector3::Dot(Vector3& v1, Vector3& v2)
        {
            Vector3* v1 = debuggerStream->Read<Vector3*>();
            Vector3* v2 = debuggerStream->Read<Vector3*>();
            float result = Vector3::Dot(*v1, *v2);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6A6DBEA8: // Vector3 Vector3::Normalize(Vector3& vector)
        {
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3 result = Vector3::Normalize(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xE5885716: // float Vector3::Distance(Vector3& v1, Vector3& v2)
        {
            Vector3* v1 = debuggerStream->Read<Vector3*>();
            Vector3* v2 = debuggerStream->Read<Vector3*>();
            float result = Vector3::Distance(*v1, *v2);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x61A5852C: // bool Vector3::operator==(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            bool result = object->operator==(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x68B72551: // bool Vector3::operator!=(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            bool result = object->operator!=(*vector);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8280CD30: // Vector3& Vector3::operator+=(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3& result = object->operator+=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x6DBD68D0: // Vector3& Vector3::operator-=(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3& result = object->operator-=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x826324B9: // Vector3& Vector3::operator*=(float factor)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float factor = debuggerStream->Read<float>();
            Vector3& result = object->operator*=(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x1925815F: // Vector3& Vector3::operator*=(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3& result = object->operator*=(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC8F461F6: // Vector3& Vector3::operator/=(float factor)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float factor = debuggerStream->Read<float>();
            Vector3& result = object->operator/=(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x223AB538: // Vector3 Vector3::operator+(Vector3 me, Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3 result = object->operator+(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xA61928ED: // Vector3 Vector3::operator-(Vector3 me, Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3 result = object->operator-(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x25D9C0DD: // Vector3 Vector3::operator*(Vector3 me, float factor)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float factor = debuggerStream->Read<float>();
            Vector3 result = object->operator*(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xAA6B6A56: // Vector3 Vector3::operator*(Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3 result = object->operator*(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xD1772C51: // Vector3 Vector3::operator/(Vector3 me, float factor)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            float factor = debuggerStream->Read<float>();
            Vector3 result = object->operator/(factor);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC6723E1F: // Vector3 Vector3::operator^(Vector3 me, Vector3& vector)
        {
            Vector3* object = debuggerStream->Read<Vector3*>();
            Vector3* vector = debuggerStream->Read<Vector3*>();
            Vector3 result = object->operator^(*vector);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xDCA874B6: // float Quaternion::X::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            float result = object->X;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8B72044D: // void Quaternion::X::set(float value)
        {
        }
        break;
        
        case 0x10027428: // float Quaternion::Y::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            float result = object->Y;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5C908415: // void Quaternion::Y::set(float value)
        {
        }
        break;
        
        case 0x9E8D73CB: // float Quaternion::Z::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            float result = object->Z;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xFFC602BC: // void Quaternion::Z::set(float value)
        {
        }
        break;
        
        case 0xA7621AD0: // [Quaternion] Quaternion::Identity::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            [Quaternion] result = object->Identity;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xEB9E0123: // void Quaternion::Identity::set([Quaternion] value)
        {
        }
        break;
        
        case 0x0588661A: // float Quaternion::W::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            float result = object->W;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC8ED9283: // void Quaternion::W::set(float value)
        {
        }
        break;
        
        case 0x8A415B66: // float Quaternion::Angle::get()
        {
            Quaternion* object = debuggerStream->Read<Quaternion*>();
            float result = object->Angle;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3FA7795A: // void Quaternion::Angle::set(float value)
        {
        }
        break;
        
        case 0xF18E4363: // Quaternion::Quaternion()
        {
            Quaternion* result = new Quaternion();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x36E6239A: // Quaternion::Quaternion(float x, float y, float z, float angle)
        {
            float x = debuggerStream->Read<float>();
            float y = debuggerStream->Read<float>();
            float z = debuggerStream->Read<float>();
            float angle = debuggerStream->Read<float>();
            Quaternion* result = new Quaternion(x, y, z, angle);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x44B73CEF: // Quaternion::Quaternion([Vector3] vector, float angle)
        {
            [Vector3]* vector = debuggerStream->Read<[Vector3]*>();
            float angle = debuggerStream->Read<float>();
            Quaternion* result = new Quaternion(vector, angle);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x399D2141: // Quaternion& Quaternion::Lerp(Quaternion& q1, Quaternion& q2, float c)
        {
            Quaternion* q1 = debuggerStream->Read<Quaternion*>();
            Quaternion* q2 = debuggerStream->Read<Quaternion*>();
            float c = debuggerStream->Read<float>();
            Quaternion& result = Quaternion::Lerp(*q1, *q2, c);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x23BC9CB5: // s32 Units::Convert(s32 value, T from, T to)
        {
            s32 value = debuggerStream->Read<s32>();
            T* from = debuggerStream->Read<T*>();
            T* to = debuggerStream->Read<T*>();
            s32 result = Units::Convert(value, from, to);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x755CB8B3: // float Units::Convert(float value, T from, T to)
        {
            float value = debuggerStream->Read<float>();
            T* from = debuggerStream->Read<T*>();
            T* to = debuggerStream->Read<T*>();
            float result = Units::Convert(value, from, to);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6B8B523C: // u32 Color24::Value::get()
        {
            Color24* object = debuggerStream->Read<Color24*>();
            u32 result = object->Value;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x122983D7: // void Color24::Value::set(u32 value)
        {
        }
        break;
        
        case 0xBBBD083F: // u8 Color24::__Unused::get()
        {
            Color24* object = debuggerStream->Read<Color24*>();
            u8 result = object->__Unused;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB2F5B3A4: // void Color24::__Unused::set(u8 value)
        {
        }
        break;
        
        case 0x9FB72C7E: // u8 Color24::Red::get()
        {
            Color24* object = debuggerStream->Read<Color24*>();
            u8 result = object->Red;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF9EAC6FA: // void Color24::Red::set(u8 value)
        {
        }
        break;
        
        case 0xC69D2488: // u8 Color24::Green::get()
        {
            Color24* object = debuggerStream->Read<Color24*>();
            u8 result = object->Green;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x60351EBA: // void Color24::Green::set(u8 value)
        {
        }
        break;
        
        case 0xDA6970BB: // u8 Color24::Blue::get()
        {
            Color24* object = debuggerStream->Read<Color24*>();
            u8 result = object->Blue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x97FEA60C: // void Color24::Blue::set(u8 value)
        {
        }
        break;
        
        case 0x7A6013FF: // Color24::Color24()
        {
            Color24* result = new Color24();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x65B0EA81: // Color24::Color24(u32 value)
        {
            u32 value = debuggerStream->Read<u32>();
            Color24* result = new Color24(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6E2DE99D: // Color24::Color24(u8 red, u8 green, u8 blue)
        {
            u8 red = debuggerStream->Read<u8>();
            u8 green = debuggerStream->Read<u8>();
            u8 blue = debuggerStream->Read<u8>();
            Color24* result = new Color24(red, green, blue);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x541122C5: // bool Color24::operator==(Color24& other)
        {
            Color24* object = debuggerStream->Read<Color24*>();
            Color24* other = debuggerStream->Read<Color24*>();
            bool result = object->operator==(*other);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xE719175F: // u32 Color32::Value::get()
        {
            Color32* object = debuggerStream->Read<Color32*>();
            u32 result = object->Value;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x079F4189: // void Color32::Value::set(u32 value)
        {
        }
        break;
        
        case 0x9B50E0E5: // u8 Color32::Blue::get()
        {
            Color32* object = debuggerStream->Read<Color32*>();
            u8 result = object->Blue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7E7C1658: // void Color32::Blue::set(u8 value)
        {
        }
        break;
        
        case 0x4A0F61EB: // u8 Color32::Green::get()
        {
            Color32* object = debuggerStream->Read<Color32*>();
            u8 result = object->Green;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0CDA09E7: // void Color32::Green::set(u8 value)
        {
        }
        break;
        
        case 0xA25D12D5: // u8 Color32::Red::get()
        {
            Color32* object = debuggerStream->Read<Color32*>();
            u8 result = object->Red;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x18FFA7FC: // void Color32::Red::set(u8 value)
        {
        }
        break;
        
        case 0xB05A9491: // u8 Color32::Alpha::get()
        {
            Color32* object = debuggerStream->Read<Color32*>();
            u8 result = object->Alpha;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x59CB4079: // void Color32::Alpha::set(u8 value)
        {
        }
        break;
        
        case 0xF4FA744D: // Color32::Color32()
        {
            Color32* result = new Color32();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x990C474B: // Color32::Color32(u32 value)
        {
            u32 value = debuggerStream->Read<u32>();
            Color32* result = new Color32(value);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xBA456762: // Color32::Color32(u8 red, u8 green, u8 blue)
        {
            u8 red = debuggerStream->Read<u8>();
            u8 green = debuggerStream->Read<u8>();
            u8 blue = debuggerStream->Read<u8>();
            Color32* result = new Color32(red, green, blue);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x348C7281: // Color32::Color32(u8 alpha, u8 red, u8 green, u8 blue)
        {
            u8 alpha = debuggerStream->Read<u8>();
            u8 red = debuggerStream->Read<u8>();
            u8 green = debuggerStream->Read<u8>();
            u8 blue = debuggerStream->Read<u8>();
            Color32* result = new Color32(alpha, red, green, blue);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xDD65FA0D: // Color32::Color32([Color24] color, u8 alpha)
        {
            [Color24]* color = debuggerStream->Read<[Color24]*>();
            u8 alpha = debuggerStream->Read<u8>();
            Color32* result = new Color32(color, alpha);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x84CF2E4F: // bool Color32::operator==(Color32& other)
        {
            Color32* object = debuggerStream->Read<Color32*>();
            Color32* other = debuggerStream->Read<Color32*>();
            bool result = object->operator==(*other);
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB7DC45DC: // [Color32] Colors::Transparent::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color32] result = object->Transparent;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB9ABE098: // void Colors::Transparent::set([Color32] value)
        {
        }
        break;
        
        case 0xABF0740C: // [Color24] Colors::Black::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Black;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF3621114: // void Colors::Black::set([Color24] value)
        {
        }
        break;
        
        case 0x30F5D7AA: // [Color24] Colors::DeepGray::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DeepGray;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x25CE2C23: // void Colors::DeepGray::set([Color24] value)
        {
        }
        break;
        
        case 0x9DA7B1C1: // [Color24] Colors::DarkGray::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkGray;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x42943C6D: // void Colors::DarkGray::set([Color24] value)
        {
        }
        break;
        
        case 0x795E5F9B: // [Color24] Colors::Gray::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Gray;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB9AFFBEE: // void Colors::Gray::set([Color24] value)
        {
        }
        break;
        
        case 0x41B3E743: // [Color24] Colors::LightGray::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightGray;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5654494D: // void Colors::LightGray::set([Color24] value)
        {
        }
        break;
        
        case 0xC91A2209: // [Color24] Colors::BrightGray::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->BrightGray;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4F83444C: // void Colors::BrightGray::set([Color24] value)
        {
        }
        break;
        
        case 0x416EE01C: // [Color24] Colors::White::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->White;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0744B63A: // void Colors::White::set([Color24] value)
        {
        }
        break;
        
        case 0x62BC0576: // [Color24] Colors::RawRed::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawRed;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0F6B2E4C: // void Colors::RawRed::set([Color24] value)
        {
        }
        break;
        
        case 0x4CF6CBE7: // [Color24] Colors::RawGreen::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawGreen;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC3F628A8: // void Colors::RawGreen::set([Color24] value)
        {
        }
        break;
        
        case 0xD44FF3A0: // [Color24] Colors::RawBlue::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawBlue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x40D6307F: // void Colors::RawBlue::set([Color24] value)
        {
        }
        break;
        
        case 0x780069E7: // [Color24] Colors::RawCyan::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawCyan;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC1DBF00A: // void Colors::RawCyan::set([Color24] value)
        {
        }
        break;
        
        case 0xF19E5B55: // [Color24] Colors::RawMagenta::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawMagenta;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB2204AE4: // void Colors::RawMagenta::set([Color24] value)
        {
        }
        break;
        
        case 0x22ED3ACC: // [Color24] Colors::RawYellow::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->RawYellow;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF379AB76: // void Colors::RawYellow::set([Color24] value)
        {
        }
        break;
        
        case 0xCE3CE3D0: // [Color24] Colors::Red::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Red;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC129C368: // void Colors::Red::set([Color24] value)
        {
        }
        break;
        
        case 0xFB46FF72: // [Color24] Colors::LightRed::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightRed;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xEF8B4A2B: // void Colors::LightRed::set([Color24] value)
        {
        }
        break;
        
        case 0x391DB25C: // [Color24] Colors::DarkRed::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkRed;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x2EA22537: // void Colors::DarkRed::set([Color24] value)
        {
        }
        break;
        
        case 0xFDC23B45: // [Color24] Colors::Green::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Green;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xECA59989: // void Colors::Green::set([Color24] value)
        {
        }
        break;
        
        case 0x75F28C1B: // [Color24] Colors::LightGreen::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightGreen;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA3959069: // void Colors::LightGreen::set([Color24] value)
        {
        }
        break;
        
        case 0x76987A41: // [Color24] Colors::DarkGreen::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkGreen;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x98EF70D4: // void Colors::DarkGreen::set([Color24] value)
        {
        }
        break;
        
        case 0xEB56759B: // [Color24] Colors::Blue::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Blue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7C1B9643: // void Colors::Blue::set([Color24] value)
        {
        }
        break;
        
        case 0xD3BBCD43: // [Color24] Colors::LightBlue::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightBlue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x93E024E0: // void Colors::LightBlue::set([Color24] value)
        {
        }
        break;
        
        case 0x0FAF9BC1: // [Color24] Colors::DarkBlue::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkBlue;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x872051C0: // void Colors::DarkBlue::set([Color24] value)
        {
        }
        break;
        
        case 0x4719EFDC: // [Color24] Colors::Cyan::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Cyan;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xFD165636: // void Colors::Cyan::set([Color24] value)
        {
        }
        break;
        
        case 0x7FF45704: // [Color24] Colors::LightCyan::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightCyan;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x12EDE495: // void Colors::LightCyan::set([Color24] value)
        {
        }
        break;
        
        case 0xA3E00186: // [Color24] Colors::DarkCyan::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkCyan;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x062D91B5: // void Colors::DarkCyan::set([Color24] value)
        {
        }
        break;
        
        case 0xD012C616: // [Color24] Colors::Magenta::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Magenta;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x82D9F34E: // void Colors::Magenta::set([Color24] value)
        {
        }
        break;
        
        case 0xA12F18D3: // [Color24] Colors::LightMagenta::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightMagenta;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA57BF736: // void Colors::LightMagenta::set([Color24] value)
        {
        }
        break;
        
        case 0xB5A5F94E: // [Color24] Colors::DarkMagenta::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkMagenta;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x541AFEC1: // void Colors::DarkMagenta::set([Color24] value)
        {
        }
        break;
        
        case 0x1A84CCF8: // [Color24] Colors::Yellow::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Yellow;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xBF3FE899: // void Colors::Yellow::set([Color24] value)
        {
        }
        break;
        
        case 0x96DF80BC: // [Color24] Colors::LightYellow::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightYellow;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x1F7A3AE8: // void Colors::LightYellow::set([Color24] value)
        {
        }
        break;
        
        case 0x1D6252A0: // [Color24] Colors::DarkYellow::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkYellow;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xAA918F39: // void Colors::DarkYellow::set([Color24] value)
        {
        }
        break;
        
        case 0x3CC1B8F8: // [Color24] Colors::Orange::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Orange;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x1B528867: // void Colors::Orange::set([Color24] value)
        {
        }
        break;
        
        case 0xB09AF4BC: // [Color24] Colors::LightOrange::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightOrange;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xBB175A16: // void Colors::LightOrange::set([Color24] value)
        {
        }
        break;
        
        case 0x3B2726A0: // [Color24] Colors::DarkOrange::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkOrange;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x0EFCEFC7: // void Colors::DarkOrange::set([Color24] value)
        {
        }
        break;
        
        case 0x5708AFD4: // [Color24] Colors::Purple::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Purple;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x16AFFFE3: // void Colors::Purple::set([Color24] value)
        {
        }
        break;
        
        case 0xDB53E390: // [Color24] Colors::LightPurple::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightPurple;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB6EA2D92: // void Colors::LightPurple::set([Color24] value)
        {
        }
        break;
        
        case 0x50EE318C: // [Color24] Colors::DarkPurple::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkPurple;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x03019843: // void Colors::DarkPurple::set([Color24] value)
        {
        }
        break;
        
        case 0xF075B66B: // [Color24] Colors::Brown::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Brown;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF955EF55: // void Colors::Brown::set([Color24] value)
        {
        }
        break;
        
        case 0x78450135: // [Color24] Colors::LightBrown::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightBrown;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xB665E6B5: // void Colors::LightBrown::set([Color24] value)
        {
        }
        break;
        
        case 0x7B2FF76F: // [Color24] Colors::DarkBrown::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkBrown;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8D1F0608: // void Colors::DarkBrown::set([Color24] value)
        {
        }
        break;
        
        case 0xC0FA0D4B: // [Color24] Colors::Pink::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Pink;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x853E8756: // void Colors::Pink::set([Color24] value)
        {
        }
        break;
        
        case 0xF817B593: // [Color24] Colors::LightPink::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->LightPink;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x6AC535F5: // void Colors::LightPink::set([Color24] value)
        {
        }
        break;
        
        case 0x2403E311: // [Color24] Colors::DarkPink::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->DarkPink;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7E0540D5: // void Colors::DarkPink::set([Color24] value)
        {
        }
        break;
        
        case 0x0E827786: // [Color24] Colors::Sky::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Sky;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x9C76B3A5: // void Colors::Sky::set([Color24] value)
        {
        }
        break;
        
        case 0x44A7DB35: // [Color24] Colors::Brick::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Brick;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x1FCC29D6: // void Colors::Brick::set([Color24] value)
        {
        }
        break;
        
        case 0xAFEBD09F: // [Color24] Colors::Salmon::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Salmon;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xEF892EBE: // void Colors::Salmon::set([Color24] value)
        {
        }
        break;
        
        case 0xBDFF966E: // [Color24] Colors::Gold::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Gold;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x334FDC29: // void Colors::Gold::set([Color24] value)
        {
        }
        break;
        
        case 0xAEC2E0DB: // [Color24] Colors::Ice::get()
        {
            Colors* object = debuggerStream->Read<Colors*>();
            [Color24] result = object->Ice;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xAB967966: // void Colors::Ice::set([Color24] value)
        {
        }
        break;
        
        case 0x9B4D9FEC: // void Colors::Initialize([Color24] color)
        {
            [Color24]* color = debuggerStream->Read<[Color24]*>();
            Colors::Initialize(color);
        }
        break;
        
        case 0x0DDE0590: // [Matrix4] Matrix4::Identity::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            [Matrix4] result = object->Identity;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4B55D33C: // void Matrix4::Identity::set([Matrix4] value)
        {
        }
        break;
        
        case 0x4DCBB0A4: // float* Matrix4::components::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float* result = object->components;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xD44670EC: // void Matrix4::components::set(float* value)
        {
        }
        break;
        
        case 0xB09A9240: // float Matrix4::c11::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c11;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x577B89F4: // void Matrix4::c11::set(float value)
        {
        }
        break;
        
        case 0x3E1595A3: // float Matrix4::c12::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c12;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF42D0F5D: // void Matrix4::c12::set(float value)
        {
        }
        break;
        
        case 0xF2BF953D: // float Matrix4::c13::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c13;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x23CF8F05: // void Matrix4::c13::set(float value)
        {
        }
        break;
        
        case 0xF87A9C24: // float Matrix4::c14::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c14;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x69F1044E: // void Matrix4::c14::set(float value)
        {
        }
        break;
        
        case 0x8917AE85: // float Matrix4::c21::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c21;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xF8D2C43E: // void Matrix4::c21::set(float value)
        {
        }
        break;
        
        case 0x0798A966: // float Matrix4::c22::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c22;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x5B844297: // void Matrix4::c22::set(float value)
        {
        }
        break;
        
        case 0xCB32A9F8: // float Matrix4::c23::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c23;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x8C66C2CF: // void Matrix4::c23::set(float value)
        {
        }
        break;
        
        case 0xC1F7A0E1: // float Matrix4::c24::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c24;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xC6584984: // void Matrix4::c24::set(float value)
        {
        }
        break;
        
        case 0x9E6CBAC6: // float Matrix4::c31::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c31;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x9DB5FF78: // void Matrix4::c31::set(float value)
        {
        }
        break;
        
        case 0x10E3BD25: // float Matrix4::c32::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c32;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x3EE379D1: // void Matrix4::c32::set(float value)
        {
        }
        break;
        
        case 0xDC49BDBB: // float Matrix4::c33::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c33;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xE901F989: // void Matrix4::c33::set(float value)
        {
        }
        break;
        
        case 0xD68CB4A2: // float Matrix4::c34::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c34;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xA33F72C2: // void Matrix4::c34::set(float value)
        {
        }
        break;
        
        case 0xFA0DD70F: // float Matrix4::c41::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c41;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7CF159EB: // void Matrix4::c41::set(float value)
        {
        }
        break;
        
        case 0x7482D0EC: // float Matrix4::c42::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c42;
            debuggerStream->Write(result);
        }
        break;
        
        case 0xDFA7DF42: // void Matrix4::c42::set(float value)
        {
        }
        break;
        
        case 0xB828D072: // float Matrix4::c43::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c43;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x08455F1A: // void Matrix4::c43::set(float value)
        {
        }
        break;
        
        case 0xB2EDD96B: // float Matrix4::c44::get()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->c44;
            debuggerStream->Write(result);
        }
        break;
        
        case 0x427BD451: // void Matrix4::c44::set(float value)
        {
        }
        break;
        
        case 0x74C151F8: // Matrix4::Matrix4()
        {
            Matrix4* result = new Matrix4();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x9BD80403: // Matrix4::Matrix4(float c11, float c12, float c13, float c14, float c21, float c22, float c23, float c24, float c31, float c32, float c33, float c34, float c41, float c42, float c43, float c44)
        {
            float c11 = debuggerStream->Read<float>();
            float c12 = debuggerStream->Read<float>();
            float c13 = debuggerStream->Read<float>();
            float c14 = debuggerStream->Read<float>();
            float c21 = debuggerStream->Read<float>();
            float c22 = debuggerStream->Read<float>();
            float c23 = debuggerStream->Read<float>();
            float c24 = debuggerStream->Read<float>();
            float c31 = debuggerStream->Read<float>();
            float c32 = debuggerStream->Read<float>();
            float c33 = debuggerStream->Read<float>();
            float c34 = debuggerStream->Read<float>();
            float c41 = debuggerStream->Read<float>();
            float c42 = debuggerStream->Read<float>();
            float c43 = debuggerStream->Read<float>();
            float c44 = debuggerStream->Read<float>();
            Matrix4* result = new Matrix4(c11, c12, c13, c14, c21, c22, c23, c24, c31, c32, c33, c34, c41, c42, c43, c44);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x1F23EA6A: // Matrix4::Matrix4([Matrix3]& matrix)
        {
            [Matrix3]* matrix = debuggerStream->Read<[Matrix3]*>();
            Matrix4* result = new Matrix4(*matrix);
            debuggerStream->Write(result);
        }
        break;
        
        case 0x4FECFAE0: // Matrix4& Matrix4::Transpose()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            Matrix4& result = object->Transpose();
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xB520BAE8: // float Matrix4::Determinant()
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            float result = object->Determinant();
            debuggerStream->Write(result);
        }
        break;
        
        case 0x7E824078: // Matrix4& Matrix4::CreateTransformation([Vector3]& translation, [Matrix3]& rotation, [Vector3]& scale)
        {
            [Vector3]* translation = debuggerStream->Read<[Vector3]*>();
            [Matrix3]* rotation = debuggerStream->Read<[Matrix3]*>();
            [Vector3]* scale = debuggerStream->Read<[Vector3]*>();
            Matrix4& result = Matrix4::CreateTransformation(*translation, *rotation, *scale);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xA456E95C: // Matrix4& Matrix4::CreateView([Vector3]& position, [Vector3]& target, [Vector3]& up)
        {
            [Vector3]* position = debuggerStream->Read<[Vector3]*>();
            [Vector3]* target = debuggerStream->Read<[Vector3]*>();
            [Vector3]* up = debuggerStream->Read<[Vector3]*>();
            Matrix4& result = Matrix4::CreateView(*position, *target, *up);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0xC0638A55: // Matrix4& Matrix4::CreateProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
        {
            float fov = debuggerStream->Read<float>();
            float aspectRatio = debuggerStream->Read<float>();
            float nearPlane = debuggerStream->Read<float>();
            float farPlane = debuggerStream->Read<float>();
            Matrix4& result = Matrix4::CreateProjection(fov, aspectRatio, nearPlane, farPlane);
            debuggerStream->Write(&result);
        }
        break;
        
        case 0x5D1158A7: // Matrix4& Matrix4::operator*(Matrix4 me, Matrix4& matrix)
        {
            Matrix4* object = debuggerStream->Read<Matrix4*>();
            Matrix4* matrix = debuggerStream->Read<Matrix4*>();
            Matrix4& result = object->operator*(*matrix);
            debuggerStream->Write(&result);
        }
        break;
        
    }
}