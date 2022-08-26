#include <GUIUtil.hpp>
#include <raylib.h>


GlobalFonts& GlobalFonts::GlobalFontInstance()
{
  static GlobalFonts* globalFonts = new GlobalFonts;
  return *globalFonts;
}

// Draw text using font inside rectangle limits with support for text selection
void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        textOffsetX += glyphWidth;
    }
}


// Draw text using font inside rectangle limits
void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}



GlobalFonts::GlobalFonts()
{
  char *telText = "1234567890 భూమి భూమి సూర్యుని నుండి 3వ గ్రహం మరియు దానిని మనం ఇల్లు అని పిలుస్తాము.జీవాన్ని కలిగి ఉన్న ఏకైక ఖగోళ వస్తువు ఇది.దాదాపు 71% భూమి యొక్క ఉపరితలం సముద్రాలచే కప్పబడి ఉంటుంది.29% భూమి.భూమి యొక్క వాతావరణంలో ఎక్కువగా నైట్రోజన్ మరియు ఆక్సిజన్ ఉంటాయి.మిగిలినవి నీటి ఆవిరి మరియు వివిధ గ్రీన్హౌస్ వాయువులు.";
  char *engText = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *hinText = "123456789 धरती धरती सूर्य से तीसरा ग्रह है और जिस ग्रह को हम घर कहते हैं।यह एकमात्र खगोलीय पिंड है जिसे जीवन को आश्रय देने के लिए जाना जाता है।पृथ्वी की सतह महासागरों से आच्छादित है29% भूमि।पृथ्वी के वायुमंडल में ज्यादातर नाइट्रोजन और ऑक्सीजन हैं। शेष जल वाष्प और विभिन्न ग्रीनहाउस गैसें हैं।";

  // TODO: some sort of loop for this?

  // Get codepoints from text
  int codepointCount = 0;
  int *codepoints = LoadCodepoints(hinText, &codepointCount);

  // Removed duplicate codepoints to generate smaller font atlas
  int codepointsNoDupsCount = 0;
  int *codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
  UnloadCodepoints(codepoints);

  // Load font containing all the provided codepoint glyphs
  // A texture font atlas is automatically generated
  hi = LoadFontEx("res/fonts/Anek-Devanagari-Regular.ttf", 47, codepointsNoDups, codepointsNoDupsCount);


    // Get codepoints from text
  codepointCount = 0;
  codepoints = LoadCodepoints(telText, &codepointCount);

  // Removed duplicate codepoints to generate smaller font atlas
  codepointsNoDupsCount = 0;
  codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
  UnloadCodepoints(codepoints);

  // Load font containing all the provided codepoint glyphs
  // A texture font atlas is automatically generated
  tel = LoadFontEx("res/fonts/NotoSerifTelugu-Regular.ttf", 47, codepointsNoDups, codepointsNoDupsCount);


    // Get codepoints from text
  codepointCount = 0;
  codepoints = LoadCodepoints(engText, &codepointCount);

  // Removed duplicate codepoints to generate smaller font atlas
  codepointsNoDupsCount = 0;
  codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
  UnloadCodepoints(codepoints);

  // Load font containing all the provided codepoint glyphs
  // A texture font atlas is automatically generated
  // TODO: Load the font right here!
  //eng = LoadFontEx(".ttf", 47, codepointsNoDups, codepointsNoDupsCount);

  

   // Set bilinear scale filter for better font scaling
  SetTextureFilter(hi.texture, TEXTURE_FILTER_BILINEAR);
  SetTextureFilter(eng.texture, TEXTURE_FILTER_BILINEAR);
  SetTextureFilter(tel.texture, TEXTURE_FILTER_BILINEAR);

  // Free codepoints, atlas has already been generated
  free(codepointsNoDups);


  //currentLang = Lang::ENGLISH;
  currentLang = Lang::ENGLISH;
  switch(currentLang)
     {
     case Lang::ENGLISH:
       {
	 size = 50;
	 fontSize = 20;
	 fontSpacing = 3;
	 break;
       }

    case Lang::HINDI:
      {
	size = 100;
	fontSize = 22;
	fontSpacing = 0;
	break;
      }
     case Lang::TELUGU:
       {
	 size = 100;
	 fontSize = 22;
	 fontSpacing = 0;
	 break;
       }

       
     }

}



// Remove codepoint duplicates if requested
// WARNING: This process could be a bit slow if there text to process is very long
static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount)
{
    int codepointsNoDupsCount = codepointCount;
    int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
    memcpy(codepointsNoDups, codepoints, codepointCount*sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++)
    {
        for (int j = i + 1; j < codepointsNoDupsCount; j++)
        {
            if (codepointsNoDups[i] == codepointsNoDups[j])
            {
                for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    *codepointsResultCount = codepointsNoDupsCount;
    return codepointsNoDups;
}
