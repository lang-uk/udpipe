//
// Created by Москалевський on 4/6/17.
//

#include "guesser.h"
#include <boost/algorithm/string.hpp>
#include <boost/locale/conversion.hpp>
#include <regex>

//using namespace std;
//using namespace boost;

namespace mi
{
  static const std::wregex SMILE_RE(LR"(:\(+|:\)+)");

  void Guesser::analyze(vector<tagged_lemma>& o_lemmas, const char *i_form_bytes)
  {
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

    if (init_num_lemmas == o_lemmas.size()) {
      bool is_smile = std::regex_match(form, SMILE_RE);
      if (is_smile) {
        o_lemmas.emplace_back(converter.to_bytes(form), "~SYM~");
      }
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

  void Guesser::lookup(const wstring& form, vector<tagged_lemma>& o_lemmas)
  {
    string bytes{converter.to_bytes(form)};
    dictionary->analyze(bytes, o_lemmas);
  }

  void Guesser::setDictionary(const Dictionary *dictionary)
  {
    this->dictionary = dictionary;
  }
}

