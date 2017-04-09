//
// Created by Москалевський on 4/6/17.
//

#include "guesser.h"
#include <boost/algorithm/string.hpp>
#include <boost/locale/conversion.hpp>
#include <regex>


namespace institute
{
  namespace mova
  {
//  static const auto ORDINAL_PARADIGM_BASE = {
//      "Case=Nom|Gender=Masc|NumType=Ord",
//      "Case=Gen|Gender=Masc|NumType=Ord",
//      "Case=Dat|Gender=Masc|NumType=Ord",
//      "Case=Acc|Gender=Masc|NumType=Ord",
//      "Case=Ins|Gender=Masc|NumType=Ord",
//      "Case=Loc|Gender=Masc|NumType=Ord",
//      "Case=Voc|Gender=Masc|NumType=Ord",
//      "Case=Nom|Gender=Fem|NumType=Ord",
//      "Case=Gen|Gender=Fem|NumType=Ord",
//      "Case=Dat|Gender=Fem|NumType=Ord",
//      "Case=Acc|Gender=Fem|NumType=Ord",
//      "Case=Ins|Gender=Fem|NumType=Ord",
//      "Case=Loc|Gender=Fem|NumType=Ord",
//      "Case=Voc|Gender=Fem|NumType=Ord",
//      "Case=Nom|Gender=Neut|NumType=Ord",
//      "Case=Gen|Gender=Neut|NumType=Ord",
//      "Case=Dat|Gender=Neut|NumType=Ord",
//      "Case=Acc|Gender=Neut|NumType=Ord",
//      "Case=Ins|Gender=Neut|NumType=Ord",
//      "Case=Loc|Gender=Neut|NumType=Ord",
//      "Case=Voc|Gender=Neut|NumType=Ord",
//      "Case=Nom|Number=Plur|NumType=Ord",
//      "Case=Gen|Number=Plur|NumType=Ord",
//      "Case=Dat|Number=Plur|NumType=Ord",
//      "Case=Acc|Number=Plur|NumType=Ord",
//      "Case=Ins|Number=Plur|NumType=Ord",
//      "Case=Loc|Number=Plur|NumType=Ord",
//      "Case=Voc|Number=Plur|NumType=Ord",
//  };

    static const auto CARDINAL_1_2_PARADIGM = {
        "Case=Nom|Gender=Masc|NumType=Card",
        "Case=Gen|Gender=Masc|NumType=Card",
        "Case=Dat|Gender=Masc|NumType=Card",
        "Case=Acc|Gender=Masc|NumType=Card",
        "Case=Ins|Gender=Masc|NumType=Card",
        "Case=Loc|Gender=Masc|NumType=Card",
        "Case=Voc|Gender=Masc|NumType=Card",
        "Case=Nom|Gender=Fem|NumType=Card",
        "Case=Gen|Gender=Fem|NumType=Card",
        "Case=Dat|Gender=Fem|NumType=Card",
        "Case=Acc|Gender=Fem|NumType=Card",
        "Case=Ins|Gender=Fem|NumType=Card",
        "Case=Loc|Gender=Fem|NumType=Card",
        "Case=Voc|Gender=Fem|NumType=Card",
        "Case=Nom|Gender=Neut|NumType=Card",
        "Case=Gen|Gender=Neut|NumType=Card",
        "Case=Dat|Gender=Neut|NumType=Card",
        "Case=Acc|Gender=Neut|NumType=Card",
        "Case=Ins|Gender=Neut|NumType=Card",
        "Case=Loc|Gender=Neut|NumType=Card",
        "Case=Voc|Gender=Neut|NumType=Card",
    };

    static const auto CARDINAL_GENERAL_PARADIGM = {
        "~NUM~~Case=Nom|Number=Plur|NumType=Card",
        "~NUM~~Case=Gen|Number=Plur|NumType=Card",
        "~NUM~~Case=Dat|Number=Plur|NumType=Card",
        "~NUM~~Case=Acc|Number=Plur|NumType=Card",
        "~NUM~~Case=Ins|Number=Plur|NumType=Card",
        "~NUM~~Case=Loc|Number=Plur|NumType=Card",
        "~NUM~~Case=Voc|Number=Plur|NumType=Card",
//    };
//
//    static const auto ORDINAL_PARADIGM = {
        "~ADJ~~Case=Nom|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Gen|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Dat|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Acc|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Ins|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Loc|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Voc|Gender=Masc|NumType=Ord",
        "~ADJ~~Case=Nom|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Gen|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Dat|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Acc|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Ins|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Loc|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Voc|Gender=Fem|NumType=Ord",
        "~ADJ~~Case=Nom|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Gen|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Dat|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Acc|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Ins|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Loc|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Voc|Gender=Neut|NumType=Ord",
        "~ADJ~~Case=Nom|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Gen|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Dat|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Acc|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Ins|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Loc|Number=Plur|NumType=Ord",
        "~ADJ~~Case=Voc|Number=Plur|NumType=Ord",
//    };
//
//    static const auto ORDINAL_ASNOUN_PARADIGM = {
        "~NOUN~~Animacy=Inan|Case=Nom|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Gen|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Dat|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Acc|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Ins|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Loc|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Voc|Gender=Masc|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Nom|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Gen|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Dat|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Acc|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Ins|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Loc|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Voc|Gender=Fem|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Nom|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Gen|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Dat|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Acc|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Ins|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Loc|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Voc|Gender=Neut|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Nom|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Gen|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Dat|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Acc|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Ins|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Loc|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Voc|Number=Plur|NumType=Ord",
        "~NOUN~~Animacy=Inan|Case=Nom|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Gen|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Dat|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Acc|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Ins|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Loc|Number=Ptan",
        "~NOUN~~Animacy=Inan|Case=Voc|Number=Ptan",
    };
//  static const std::vector<std::string> ORDINAL_PARADIGM_VECTOR(ORDINAL_PARADIGM);
    static std::vector<const char*> vec;


    static const auto SYM_TAG = "~SYM~";

    static const std::wregex SMILE_RE(LR"(:\(+|:\)+)");
    static const std::wregex ARABIC_1_2_NUMERAL_RE(LR"((\d+?[^1])?[12])");
    static const std::wregex ARABIC_GENERAL_NUMERAL_RE(LR"(\d+?1\d|\d+?[03-9])");
    static const std::wregex ARABIC_NUMERAL_RE(LR"(\d+)");
    // see "B. Parsing a URI Reference with a Regular Expression" http://www.ietf.org/rfc/rfc2396.txt
//  static const std::wregex URL_RE(LR"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)");
    static const std::wregex URL_LOSE_RE(LR"(https?://.*|www\..*)");

    void Guesser::analyze(vector<tagged_lemma>& o_lemmas, const char* i_form_bytes)
    {

//    std::vector<std::string> v;
//    v.insert(v.end(), {{""}});
      auto init_num_lemmas = o_lemmas.size();
      auto form = converter.from_bytes(i_form_bytes);

      lookup_cases(o_lemmas, form);

      if (init_num_lemmas == o_lemmas.size()) {
        boost::replace_all(form, L"\'", L"’");
        boost::replace_all(form, L"\"", L"’");
        boost::replace_all(form, L"*", L"’");
        boost::replace_all(form, L"`", L"’");
        lookup_cases(o_lemmas, form);
      }

      if (std::regex_match(form, ARABIC_NUMERAL_RE)) {
        for (auto tag : CARDINAL_GENERAL_PARADIGM) {
          o_lemmas.emplace_back(i_form_bytes, tag);
        }
        if (std::regex_match(form, ARABIC_1_2_NUMERAL_RE)) {
          for (auto tag : CARDINAL_1_2_PARADIGM) {
            o_lemmas.emplace_back(i_form_bytes, tag);
          }
        }
      }

      if (init_num_lemmas == o_lemmas.size()) {
        bool is_symbol = std::regex_match(form, SMILE_RE)
                         || std::regex_match(form, URL_LOSE_RE);
        if (is_symbol) {
          o_lemmas.emplace_back(i_form_bytes, SYM_TAG);
        }
      }

      if (init_num_lemmas == o_lemmas.size()) {
        lookup_fricativized(o_lemmas, form);
      }
    }

    void Guesser::lookup_cases(vector<tagged_lemma>& o_lemmas, const wstring& form)
    {
      auto lowercase = boost::to_lower_copy(form, unicode_locale);
      auto uppercase = boost::to_upper_copy(form, unicode_locale);

      auto titlecase = lowercase.substr(0, 1);
      boost::to_upper(titlecase, unicode_locale);
      titlecase += lowercase.substr(1);

      lookup(form, o_lemmas);

      if (form == titlecase || form == uppercase) {
        lookup(lowercase, o_lemmas);
      }
      if (form == uppercase && form.length() > 1) {
        lookup(titlecase, o_lemmas);
      }
    }

    void Guesser::lookup_fricativized(vector<tagged_lemma>& o_lemmas, const wstring& form)
    {
      wstring fricative;
      std::vector<size_t> lowcase_idx;
      std::vector<size_t> upcase_idx;
      for (size_t i = 0; i < form.size(); ++i) {
        const wchar_t& c = form[i];
        if (c == L'ґ') {
          fricative.push_back(L'г');
          lowcase_idx.push_back(i);
        } else if (c == L'Ґ') {
          fricative.push_back(L'Ґ');
          upcase_idx.push_back(i);
        } else {
          fricative.push_back(c);
        }
      }

      if (lowcase_idx.size() || upcase_idx.size()) {
        auto init_num_lemmas = o_lemmas.size();
        lookup_cases(o_lemmas, fricative);
        for (auto i = init_num_lemmas; i < o_lemmas.size(); ++i) {
          auto lemma = converter.from_bytes(o_lemmas[i].lemma);
          for (auto j: lowcase_idx) {
            lemma[j] = L'ґ';
          }
          for (auto j: upcase_idx) {
            lemma[j] = L'Ґ';
          }
          o_lemmas[i].lemma = converter.to_bytes(lemma);
        }
      }
    }

    void Guesser::lookup(const wstring& form, vector<tagged_lemma>& o_lemmas)
    {
      string bytes{converter.to_bytes(form)};
      dictionary->analyze(bytes, o_lemmas);
    }

    void Guesser::setDictionary(const Dictionary* dictionary)
    {
      this->dictionary = dictionary;
    }
  }
}