#include <GUIUtil.hpp>
#include <raylib.h>


GlobalFonts& GlobalFonts::GlobalFontInstance()
{
  static GlobalFonts* globalFonts = new GlobalFonts;
  return *globalFonts;
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
  codepoints = LoadCodepoints(engText, &codepointCount);

  // Removed duplicate codepoints to generate smaller font atlas
  codepointsNoDupsCount = 0;
  codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
  UnloadCodepoints(codepoints);

  // Load font containing all the provided codepoint glyphs
  // A texture font atlas is automatically generated
  tel = LoadFontEx("res/fonts/NotoSerifTelugu-Regular.ttf", 47, codepointsNoDups, codepointsNoDupsCount);


    // Get codepoints from text
  codepointCount = 0;
  codepoints = LoadCodepoints(hinText, &codepointCount);

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


  currentLang = 1;
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
