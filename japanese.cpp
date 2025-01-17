#pragma leco tool

import jute;
import print;

struct pair {
  jute::view key;
  jute::view value;
};

jute::heap romaji(jute::view txt) {
  jute::heap res {};

  constexpr const pair pairs[] {
    { "i",  "い" },
    { "u",  "う" },
    { "o",  "お" },
    { "ka", "か" },
    { "ki", "き" },
    { "ku", "く" },
    { "se", "せ" },
    { "su", "す" },
    { "ha", "は" },
    { "ho", "ほ" },
    { "ma", "ま" },
    { "na", "な" },
    { "ni", "に" },
    { "yo", "よ" },
    { "n",  "ん" },

    { "ga", "が" },
    { "ge", "げ" },
    { "da", "だ" },
    { "de", "で" },
    { "bu", "ぶ" },

    { "jo", "じょ" },
  };

  while (txt.size()) {
    int sz = res.size();
    for (auto [k, v] : pairs) {
      auto [l, r] = txt.subview(k.size());
      if (k != l) continue;

      txt = r;
      res = res + v;
      break;
    }
    if (sz == res.size()) die("unknown character after: ", txt);
  }
  return res;
}

jute::heap kanji(jute::view txt) {
  constexpr const pair pairs[] {
    { "げんき",       "元気"   }, 
    { "だいじょうぶ", "大丈夫" },
    { "にほん",       "日本"   },
    { "せんせい",     "先生"   },
    { "がくせい",     "学生"   },
    { "なに",         "何"     },
  };

  jute::heap res {};
  while (txt.size()) {
    int sz = res.size();
    for (auto [k, v] : pairs) {
      auto [l, r] = txt.subview(k.size());
      if (k != l) continue;

      txt = r;
      res = res + v;
      break;
    }
    if (sz == res.size()) {
      auto [l, r] = txt.subview(1);
      res = res + l;
      txt = r;
    }
  }
  return res;
}

int main() try {
  putln(kanji(*romaji("ohayou")));
  putln(kanji(*romaji("genkidesuka")));
  putln(kanji(*romaji("genkida")));
  putln(kanji(*romaji("daijoubuka")));
  putln(kanji(*romaji("nihon")));
  putln(kanji(*romaji("sensei")));
  putln(kanji(*romaji("gakusei")));
  putln(kanji(*romaji("nani")));
} catch (...) {
  return 1;
}
