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

int main() try {
  putln(romaji("genkidesuka"));
} catch (...) {
  return 1;
}
