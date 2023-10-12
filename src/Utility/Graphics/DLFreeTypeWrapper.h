#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H

class DLGlyph {

	FT_UInt glyphIndex;
	FT_Face face;

public:
	DLGlyph()
	{
		//need this for dynamic array :(
	}

	DLGlyph(uint32_t code, FT_Library lib, std::string fontpath)
	{
		FT_Error error = FT_New_Face(lib, fontpath.c_str(), 0, &(this->face));

		if (error == FT_Err_Unknown_File_Format)
		{
			throw std::runtime_error("Failed to init font face! Unknown file.");
		}
		else if (error)
		{
			throw std::runtime_error("Failed to init font face!");
		}

		error = FT_Set_Char_Size(this->face, 0, 16 * 64, 300, 300);
		//can set pixel sizes with FT_Set_Pixel_Sizes(face, 0, 16);

		if (error)
		{
			throw std::runtime_error("Failed to set character size!?");
		}


		this->glyphIndex = FT_Get_Char_Index(this->face, code);

		error = FT_Load_Glyph(this->face, this->glyphIndex, FT_LOAD_DEFAULT);

		if (error)
		{
			throw std::runtime_error("Failed to load glyph.");
		}

		if (this->face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		{
			error = FT_Render_Glyph(this->face->glyph, FT_RENDER_MODE_NORMAL);

			if (error)
			{
				throw std::runtime_error("Failed to render glyph.");
			}
		}

	}

	FT_Bitmap* getBitmapPointer()
	{
		return &(this->face->glyph->bitmap);
	}
};

class DLFreeTypeWrapper {


	FT_Library library;
	DLGlyph* glyphArray;


	const std::string path_to_font = "/resources/fonts/bitwise.ttf";

public:
	DLFreeTypeWrapper()
	{
		init();
	}

	~DLFreeTypeWrapper()
	{
		cleanup();
	}
	
	void init()
	{
		if (FT_Init_FreeType(&library))
		{
			throw std::runtime_error("Failed to init FreeType Library");
		}

		this->glyphArray = new DLGlyph[128];

		for (int i = 0; i < 128; i++)
		{
			this->glyphArray[i] = DLGlyph(i, library, path_to_font);
		}

	}

	void cleanup()
	{
		delete[] this->glyphArray;
	}

	FT_Bitmap* getCharBitmapPointer(char character)
	{
		return this->glyphArray[character].getBitmapPointer();
	}
};