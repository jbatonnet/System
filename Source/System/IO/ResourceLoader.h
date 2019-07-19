#ifndef _SYSTEM_RESOURCELOADER_H_
#define _SYSTEM_RESOURCELOADER_H_

#include <System/Structures/Collections/Dictionary.h>
#include <System/IO/File.h>

namespace System
{
    namespace IO
    {
        template<typename TResource> struct ResourceLoaderBase
        {
        private:
            static Dictionary<string, ResourceLoaderBase<TResource>*>* loaders;

        public:
            virtual Reference<TResource> LoadInternal(File* file) = 0;

            template<typename T> static void Register(const string& extension, ResourceLoaderBase<TResource>* loader)
            {
                if (!loaders)
                    loaders = new Dictionary<string, ResourceLoaderBase<TResource>*>();

                loaders->Add(extension, loader);
            }
            static Reference<TResource> Load(File* file)
            {
                if (!loaders)
                    return Reference<TResource>::Invalid;

                for (u32 i = 0; i < loaders->Count; i++)
                    if (file->Extension == loaders->At(i)->Key)
                        return loaders->At(i)->Value->LoadInternal(file);

                return Reference<TResource>::Invalid;
            }
        };

        template<typename TResource, typename TLoader> struct ResourceLoader : public ResourceLoaderBase<TResource>
        {
            ResourceLoader(const string& extension)
            {
                ResourceLoaderBase<TResource>::Register<TLoader>(extension, this);
            }

            virtual Reference<TResource> LoadInternal(File* file) override
            {
                return TLoader::Load(file->GetStream());
            }
        };

        template<typename TResource> Dictionary<string, ResourceLoaderBase<TResource>*>* ResourceLoaderBase<TResource>::loaders = null;
    }
}

#endif