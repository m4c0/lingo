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
    { "ka", "か" },
    { "ki", "き" },
    { "ge", "げ" },
    { "su", "す" },
    { "da", "だ" },
    { "de", "で" },
    { "n",  "ん" },
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
    { "げんき", "元気" }, 
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
  putln(kanji(*romaji("genkidesuka")));
  putln(kanji(*romaji("genkida")));
} catch (...) {
  return 1;
}
