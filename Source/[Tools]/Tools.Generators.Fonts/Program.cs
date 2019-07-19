using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.IO.Compression;

using SharpFont;

namespace System.Generator
{
    enum FontType : byte
    {
        None = 0x00,
        Serif = 0x01,
        Monospace = 0x02,
    }
    enum FontAttribute : byte
    {
        Unknown = 0xFF,
        Thin = 1,
        Light = 3,
        Regular = 4,
        Medium = 5,
        SemiBold = 6,
        Bold = 7,
        ExtraBold = 8,
        UltraBold = 9
    }

    class FontDefinition
    {
        public int Size { get; set; }
        public FontAttribute Attribute { get; set; }
        public bool Italic { get; set; }

        public int CacheWidth { get; set; } = 0;
        public int CacheHeight { get; set; } = 0;
        public int CacheBaseline { get; set; } = 0;
        public byte[] CacheData { get; set; }
        public int[] CachePositions { get; set; }
    }
    class FontFamilyDefinition
    {
        public string Name { get; set; }
        public FontType Type { get; set; }

        public List<FontDefinition> Fonts { get; } = new List<FontDefinition>();
    }

    class Program
    {
        static bool GeneratePngs { get; } = true;
        static byte[] FontSizes = { 8, 9, 10, 11, 12, 14, 16 }; //, 18, 20, 22, 24, 26 }; //, 28, 36, 48, 72 };
        static List<FontFamilyDefinition> FontFamilies { get; } = new List<FontFamilyDefinition>();

        static int Div64(Fixed26Dot6 value)
        {
            return (int)Math.Ceiling(value.Value / 64.0);
        }

        static void Main(string[] args)
        {
            // Load SharpFont
            Library library = new Library();

            // Load and cache everything
            string[] fontDirectories = Directory.GetDirectories(Path.Combine(Bootstrap.Root, @"Documents\Design\Fonts"));
            foreach (string fontDirectory in fontDirectories)
            {
                string fontName = Path.GetFileName(fontDirectory);
                FontFamilyDefinition fontFamily = new FontFamilyDefinition() { Name = fontName, Type = FontType.None };

                Console.WriteLine("Processing font family " + fontFamily.Name);

                string[] fontFiles = Directory.GetFiles(fontDirectory, "*.ttf");
                foreach (string fontFile in fontFiles)
                {
                    string fontFileName = Path.GetFileNameWithoutExtension(fontFile);
                    bool italic = fontFileName.EndsWith("Italic");
                    FontAttribute attribute;
                    if (!Enum.TryParse(fontFileName.Replace(fontName, "").Trim('-').Replace("Italic", ""), out attribute))
                        continue;

                    using (Face face = library.NewFace(fontFile, 0))
                    {
                        foreach (byte fontSize in FontSizes)
                        {
                            //face.SetPixelSizes(fontSize, 0);
                            face.SetCharSize(fontSize, 0, 96, 0);

                            FontDefinition font = new FontDefinition() { Size = fontSize, Attribute = attribute, Italic = italic };

                            Console.Write("\r- " + font.Attribute + (font.Italic ? "Italic" : "") + ", " + font.Size);

                            int yMin = 0,
                                yMax = 0;

                            font.CachePositions = new int[0x101];
                            for (char c = char.MinValue; c <= 0xFF; c++)
                            {
                                face.LoadChar(c, LoadFlags.ForceAutohint, LoadTarget.Normal);

                                yMax = Math.Max(yMax, Div64(face.Glyph.Metrics.HorizontalBearingY));
                                yMin = Math.Min(yMin, Div64(face.Glyph.Metrics.HorizontalBearingY) - Div64(face.Glyph.Metrics.Height));

                                font.CacheWidth += Math.Max(Div64(face.Glyph.Metrics.Width), Div64(face.Glyph.Metrics.HorizontalAdvance));
                                font.CachePositions[c + 1] = font.CachePositions[c] + Math.Max(Div64(face.Glyph.Metrics.Width), Div64(face.Glyph.Metrics.HorizontalAdvance));
                            }

                            font.CacheHeight = yMax - yMin;
                            font.CacheBaseline = yMax;

                            // Align sizes
                            font.CacheWidth += 4 - font.CacheWidth % 4;
                            font.CacheHeight += 4 - font.CacheHeight % 4;

                            // Data
                            font.CacheData = new byte[font.CacheWidth * font.CacheHeight];
                            for (char c = char.MinValue; c <= 0xFF; c++)
                            {
                                face.LoadChar(c, LoadFlags.ForceAutohint, LoadTarget.Normal);
                                face.Glyph.RenderGlyph(RenderMode.Normal);

                                for (int y = 0; y < face.Glyph.Bitmap.Rows; y++)
                                    for (int x = 0; x < face.Glyph.Bitmap.Width; x++)
                                    {
                                        int cacheX = font.CachePositions[c] + Div64(face.Glyph.Metrics.HorizontalBearingX) + x;
                                        int cacheY = font.CacheBaseline - Div64(face.Glyph.Metrics.HorizontalBearingY) + y;

                                        int cacheIndex = cacheY * font.CacheWidth + cacheX;
                                        int bufferIndex = y * face.Glyph.Bitmap.Pitch + x;

                                        double value = face.Glyph.Bitmap.BufferData[bufferIndex] / 255.0;
                                        value = Math.Pow(value, 1.4);
                                        byte gray = (byte)(value * 255);

                                        font.CacheData[cacheIndex] = gray;
                                    }
                            }

                            fontFamily.Fonts.Add(font);
                        }
                    }

                    Console.WriteLine();
                }

                FontFamilies.Add(fontFamily);
            }

            // Write bitmaps
            if (GeneratePngs)
            {
                foreach (FontFamilyDefinition fontFamily in FontFamilies)
                {
                    string directoryPath = Path.Combine(Bootstrap.Root, @"Documents\Design\Fonts", fontFamily.Name, "Bitmaps");
                    if (!Directory.Exists(directoryPath))
                        Directory.CreateDirectory(directoryPath);

                    foreach (FontDefinition font in fontFamily.Fonts)
                    {
                        Bitmap bitmap = new Bitmap(font.CacheWidth, font.CacheHeight);

                        for (int y = 0; y < font.CacheHeight; y++)
                            for (int x = 0; x < font.CacheWidth; x++)
                                bitmap.SetPixel(x, y, Color.FromArgb(font.CacheData[y * font.CacheWidth + x], 0, 0, 0));

                        bitmap.Save(Path.Combine(directoryPath, font.Attribute + (font.Italic ? "Italic" : "") + "-" + font.Size + ".png"));
                    }
                }
            }

            // Write fonts
            foreach (FontFamilyDefinition fontFamily in FontFamilies)
            {
                if (fontFamily.Fonts.Count == 0)
                    continue;

                using (FileStream fileStream = new FileStream(Path.Combine(Bootstrap.Root, @"Root\System\Fonts", fontFamily.Name + ".font.raw"), FileMode.Create))
                {
                    using (BinaryWriter fileWriter = new BinaryWriter(fileStream))
                    {
                        // Tag
                        fileWriter.Write(new[] { 'F', 'o', 'n', 't' });

                        // Version
                        fileWriter.Write((byte)0x00);
                        fileWriter.Write((byte)0x01);

                        // Name
                        fileWriter.Write(System.Text.Encoding.ASCII.GetBytes(fontFamily.Name));
                        fileWriter.Write((byte)0x00);

                        // Type
                        fileWriter.Write((byte)FontType.None);

                        // Count
                        ushort fontCount = (ushort)(fontFamily.Fonts.Count);
                        fileWriter.Write((byte)(fontCount & 0xFF));
                        fileWriter.Write((byte)((fontCount >> 8) & 0xFF));

                        // Index
                        long indexPosition = fileWriter.BaseStream.Position;
                        foreach (FontDefinition font in fontFamily.Fonts)
                        {
                            fileWriter.Write((byte)0x00);
                            fileWriter.Write((byte)0x00);
                            fileWriter.Write((uint)0x00);
                        }

                        // Fonts
                        foreach (FontDefinition font in fontFamily.Fonts)
                        {
                            long fontPosition = fileWriter.BaseStream.Position;
                            int fontIndex = (font.Italic ? 32 : 0) | (byte)font.Attribute;

                            // Index
                            fileWriter.Seek((int)indexPosition, SeekOrigin.Begin);
                            fileWriter.Write((byte)fontIndex);
                            fileWriter.Write((byte)font.Size);
                            fileWriter.Write((uint)fontPosition);
                            indexPosition += 6;
                            fileWriter.Seek((int)fontPosition, SeekOrigin.Begin);

                            // Width
                            fileWriter.Write((ushort)font.CacheWidth);

                            // Height
                            fileWriter.Write((ushort)font.CacheHeight);

                            // Baseline
                            fileWriter.Write((ushort)font.CacheBaseline);

                            // Positions
                            for (char c = char.MinValue; c <= 0xFF; c++)
                                fileWriter.Write((ushort)font.CachePositions[c + 1]);

                            // Data
                            fileWriter.Write(font.CacheData);
                        }

                        // Create a compressed copy
                        using (FileStream copyStream = new FileStream(Path.Combine(Bootstrap.Root, @"Root\System\Fonts", fontFamily.Name + ".font"), FileMode.Create))
                        using (DeflateStream deflateStream = new DeflateStream(copyStream, CompressionLevel.Optimal))
                        {
                            fileStream.Seek(0, SeekOrigin.Begin);
                            fileStream.CopyTo(deflateStream);
                        }
                    }
                }
            }
        }
    }
}