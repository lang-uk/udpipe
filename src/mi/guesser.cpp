//
// Created by Москалевський on 4/6/17.
//

#include "guesser.h"
#include "static.h"
#include <boost/algorithm/string.hpp>
#include <boost/locale/conversion.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <algorithm>
#include <iostream>


namespace institute
{
  namespace mova
  {
    ///////////////////////////////////////////////////////////////////////////
    void Guesser::analyze(vector<tagged_lemma>& o_lemmas, const char* i_form_bytes)
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

      if (init_num_lemmas == o_lemmas.size() && std::regex_match(form, FOREIGN_RE)) {
        o_lemmas.emplace_back(i_form_bytes, FOREIGN_TAG);
      }

      if (init_num_lemmas == o_lemmas.size()) {
        std::wsmatch m;
        if (std::regex_match(form, m, ABBR_NUMERAL_RE)) {
          wchar_t last_digit_char = *(m[1].second - 1);
          wstring ending(m[2].first, m[2].second);

          std::for_each(std::begin(NUMERAL_MAP), std::end(NUMERAL_MAP), [&](const NumMapRow& row) {
            if (row.digit == last_digit_char && boost::ends_with(row.form, ending)) {
              wstring lemma(m[1].first, m[1].second);
              lemma += L'-';
              lemma.insert(lemma.end(), row.lemma.end() - ending.length(), row.lemma.end());  // todo: safe
//              wcerr << lemma << endl;

              o_lemmas.emplace_back(converter.to_bytes(lemma), row.tag);
            }
          });
        }
      }
    }

    ///////////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////////
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

    ///////////////////////////////////////////////////////////////////////////
    void Guesser::lookup(const wstring& form, vector<tagged_lemma>& o_lemmas)
    {
      string bytes{converter.to_bytes(form)};
      dictionary->analyze(bytes, o_lemmas);
    }

    ///////////////////////////////////////////////////////////////////////////
    void Guesser::init_with_dict(const Dictionary* dictionary)
    {
      this->dictionary = dictionary;
    }

    ///////////////////////////////////////////////////////////////////////////
    void Guesser::build_numeral_map()
    {

    }
  }
}