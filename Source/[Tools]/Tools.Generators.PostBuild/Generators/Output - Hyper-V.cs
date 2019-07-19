using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DiscUtils;
using DiscUtils.Fat;
using DiscUtils.Partitions;

namespace Tools.Generator
{
    public class HyperVOutput
    {
        public static void Generate()
        {
            string rootPath = Path.Combine(Bootstrap.Root, @"Root");
            string vhdxPath = Path.Combine(Bootstrap.Root, @"Hyper-V\Virtual Hard Disks\Disk.vhdx");

            using (VirtualDisk virtualDisk = VirtualDisk.OpenDisk(vhdxPath, FileAccess.ReadWrite))
            {
                // Get system partition
                PartitionInfo partition = virtualDisk.Partitions.Partitions.FirstOrDefault();

                // Open FAT partition
                using (SparseStream partitionStream = partition.Open())
                using (FatFileSystem fatFileSystem = new FatFileSystem(partitionStream))
                {
                    // Clean partition
                    string[] fileSystemEntries = fatFileSystem.GetFileSystemEntries("");
                }
            }
        }
    }
}