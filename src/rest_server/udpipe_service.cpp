// This file is part of UDPipe <http://github.com/ufal/udpipe/>.
//
// Copyright 2016 Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <sstream>

#include "udpipe_service.h"

namespace ufal {
namespace udpipe {

// Init the UDPipe service -- load the models
bool udpipe_service::init(const vector<model_description>& model_descriptions) {
  if (model_descriptions.empty()) return false;

  // Load models
  models.clear();
  rest_models_map.clear();
  for (auto& model_description : model_descriptions) {
    Model* model = Model::load(model_description.file.c_str());
    if (!model) return false;

    // Store the model
    models.emplace_back(model_description.rest_id, model_description.acknowledgements, model);
  }

  // Fill rest_models_map with model name and aliases
  for (auto& model : models) {
    // Fail if this model id is aready in use.
    if (!rest_models_map.emplace(model.rest_id, &model).second) return false;

    // Create (but not overwrite) id without version.
    for (unsigned i = 0; i+1+6 < model.rest_id.size(); i++)
      if (model.rest_id[i] == '-') {
        bool is_version = true;
        for (unsigned j = i+1; j < i+1+6; j++)
          is_version = is_version && model.rest_id[j] >= '0' && model.rest_id[j] <= '9';
        if (is_version)
          rest_models_map.emplace(model.rest_id.substr(0, i) + model.rest_id.substr(i+1+6), &model);
      }

    // Create (but not overwrite) hyphen-separated prefixes.
    for (unsigned i = 0; i < model.rest_id.size(); i++)
      if (model.rest_id[i] == '-')
        rest_models_map.emplace(model.rest_id.substr(0, i), &model);
  }
  // Default model
  rest_models_map.emplace(string(), &models.front());

  // Init REST service
  json_models.clear().object().indent().key("models").indent().object();
  for (auto& model : models) {
    json_models.indent().key(model.rest_id).indent().array();
    if (model.can_tokenize) json_models.value("tokenizer");
    if (model.can_tag) json_models.value("tagger");
    if (model.can_parse) json_models.value("parser");
    json_models.close();
  }
  json_models.indent().close().indent().key("default_model").indent().value(model_descriptions.front().rest_id).finish(true);

  return true;
}

// Handlers with their URLs
unordered_map<string, bool (udpipe_service::*)(microrestd::rest_request&)> udpipe_service::handlers = {
  // REST service
  {"/models", &udpipe_service::handle_rest_models},
  {"/process", &udpipe_service::handle_rest_process},
};

// Handle a request using the specified URL/handler map
bool udpipe_service::handle(microrestd::rest_request& req) {
  auto handler_it = handlers.find(req.url);
  return handler_it == handlers.end() ? req.respond_not_found() : (this->*handler_it->second)(req);
}

// Load selected model
const udpipe_service::model_info* udpipe_service::load_rest_model(const string& rest_id, string& error) {
  auto model_it = rest_models_map.find(rest_id);
  if (model_it == rest_models_map.end())
    return error.assign("Requested model '").append(rest_id).append("' does not exist.\n"), nullptr;

  return model_it->second;
}

// REST service
inline microrestd::string_piece sp(string_piece str) { return microrestd::string_piece(str.str, str.len); }
inline microrestd::string_piece sp(const char* str, size_t len) { return microrestd::string_piece(str, len); }

udpipe_service::rest_response_generator::rest_response_generator(const model_info* model) : model(model) {
  json.object();
  json.indent().key("model").indent().value(model->rest_id);
  json.indent().key("acknowledgements").indent().array();
  json.indent().value("http://ufal.mff.cuni.cz/udpipe#udpipe_acknowledgements");
  if (!model->acknowledgements.empty()) json.indent().value(model->acknowledgements);
  json.indent().close().indent().key("result").indent().value("");
}

// REST service handlers

bool udpipe_service::handle_rest_models(microrestd::rest_request& req) {
  return req.respond(rest_response_generator::mime, json_models);
}

bool udpipe_service::handle_rest_process(microrestd::rest_request& req) {
  string error;
  auto rest_id = get_rest_model_id(req);
  auto model = load_rest_model(rest_id, error);
  if (!model) return req.respond_error(error);

  auto& data = get_data(req, error); if (!error.empty()) return req.respond_error(error);
  bool tokenizer = false;
  unique_ptr<input_format> input(get_input_format(req, model, tokenizer, error)); if (!input) return req.respond_error(error);
  auto& tagger = get_tagger(req, model, error); if (!error.empty()) return req.respond_error(error);
  auto& parser = get_parser(req, model, error); if (!error.empty()) return req.respond_error(error);
  unique_ptr<output_format> output(get_output_format(req, error)); if (!output) return req.respond_error(error);

  // Try loading the input if tokenizer is not used
  if (!tokenizer) {
    input->set_text(data);
    sentence s;
    while (input->next_sentence(s, error)) {}
    if (!error.empty())
      return req.respond_error(error.insert(0, "Cannot read input data: ").append("\n"));
  }

  input->set_text(data);
  class generator : public rest_response_generator {
   public:
    generator(const model_info* model, input_format* input, const string& tagger, const string& parser, output_format* output)
        : rest_response_generator(model), input(input), tagger(tagger), parser(parser), output(output) {}

    bool generate() {
      if (!input->next_sentence(s, error)) {
        output->finish_document(os);
        json.value(os.str(), true);
        os.str(string());

        json.finish(true);

        return false;
      }

      if (tagger != "none")
        model->model->tag(s, tagger, error);
      if (parser != "none")
        model->model->parse(s, parser, error);

      output->write_sentence(s, os);
      json.value(os.str(), true);
      os.str(string());

      return true;
    }

   private:
    sentence s;
    string error;
    ostringstream os;
    unique_ptr<input_format> input;
    const string& tagger;
    const string& parser;
    unique_ptr<output_format> output;
  };
//  if (req.params.find("json") == "no") {
////    req.respond("text/plain; charset=utf-8");
//  }
  return req.respond(generator::mime, new generator(model, input.release(), tagger, parser, output.release()));
}

// REST service helpers

const string& udpipe_service::get_rest_model_id(microrestd::rest_request& req) {
  static string empty;

  auto model_it = req.params.find("model");
  return model_it == req.params.end() ? empty : model_it->second;
}

const string& udpipe_service::get_data(microrestd::rest_request& req, string& error) {
  auto data_it = req.params.find("data");
  if (data_it == req.params.end()) return error.assign("Required argument 'data' is missing.\n"), empty;

  return data_it->second;
}

input_format* udpipe_service::get_input_format(microrestd::rest_request& req, const model_info* model, bool& is_tokenizer, string& error) {
  auto tokenizer_it = req.params.find("tokenizer");
  if (tokenizer_it != req.params.end()) {
    if (!model->can_tokenize) return error.assign("The required model does not contain a tokenizer!"), nullptr;
    input_format* tokenizer = model->model->new_tokenizer(Model::DEFAULT);
    if (!tokenizer) return error.assign("Cannot construct a tokenizer instance!"), nullptr;
    return is_tokenizer = true, tokenizer;
  }

  auto& input = req.params.emplace("input", "conllu").first->second;
  auto input_format = input_format::new_input_format(input);
  if (!input_format) return error.assign("Unknown input format '").append(input).append("'.\n"), nullptr;
  return is_tokenizer = false, input_format;
}

const string& udpipe_service::get_tagger(microrestd::rest_request& req, const model_info* model, string& error) {
  auto& tagger = req.params.emplace("tagger", "none").first->second;
  if (tagger != "none" && !model->can_tag) return error.assign("The required model does not contain a tagger!"), empty;
  return tagger;
}

const string& udpipe_service::get_parser(microrestd::rest_request& req, const model_info* model, string& error) {
  auto& parser = req.params.emplace("parser", "none").first->second;
  if (parser != "none" && !model->can_parse) return error.assign("The required model does not contain a parser!"), empty;
  return parser;
}

output_format* udpipe_service::get_output_format(microrestd::rest_request& req, string& error) {
  auto& output = req.params.emplace("output", "conllu").first->second;
  auto output_format = output_format::new_output_format(output);
  if (!output_format) return error.assign("Unknown output format '").append(output).append("'.\n"), nullptr;
  return output_format;
}

const string udpipe_service::empty;

} // namespace udpipe
} // namespace ufal
