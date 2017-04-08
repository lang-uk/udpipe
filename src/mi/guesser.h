//
// Created by Москалевський on 4/6/17.
//

#ifndef SRC_GUESSER_H
#define SRC_GUESSER_H

#include "utils/string_piece.h"
#include "morphodita/morpho/morpho_dictionary.h"
#include "morphodita/morpho/generic_lemma_addinfo.h"
#include <codecvt>
#include <string>
#include <locale>
#include <iostream>
#include <boost/locale/generator.hpp>


using ufal::udpipe::morphodita::generic_lemma_addinfo;
using ufal::udpipe::morphodita::morpho_dictionary;
using ufal::udpipe::morphodita::tagged_lemma;
using namespace ufal::udpipe::utils;


typedef morpho_dictionary<generic_lemma_addinfo> Dictionary;


namespace mi
{
  class Guesser
  {
  private:
    const Dictionary *dictionary;

    std::locale unicode_locale{"en_US.UTF-8"};
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  public:
    void setDictionary(const Dictionary *dictionary);

    void analyze(vector<tagged_lemma>& o_lemmas, const char *i_form_bytes);

  private:
    void lookup(const wstring& form, vector<tagged_lemma, allocator<tagged_lemma>>& o_lemmas);
    void lookup_cases(vector<tagged_lemma>& o_lemmas, const wstring& form);
  };
}


#endif //SRC_GUESSER_H
