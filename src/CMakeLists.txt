cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 14)



set(SOURCE_FILES
        model/evaluator.cpp
        model/evaluator.h
        model/model.cpp
        model/model.h
        model/model_morphodita_parsito.cpp
        model/model_morphodita_parsito.h
        model/pipeline.cpp
        model/pipeline.h
        morphodita/derivator/derivation_formatter.cpp
        morphodita/derivator/derivation_formatter.h
        morphodita/derivator/derivator.h
        morphodita/derivator/derivator_dictionary.cpp
        morphodita/derivator/derivator_dictionary.h
        morphodita/derivator/derivator_dictionary_encoder.cpp
        morphodita/derivator/derivator_dictionary_encoder.h
        morphodita/morpho/casing_variants.h
        morphodita/morpho/czech_lemma_addinfo.h
        morphodita/morpho/czech_morpho.cpp
        morphodita/morpho/czech_morpho.h
        morphodita/morpho/czech_morpho_encoder.cpp
        morphodita/morpho/czech_morpho_encoder.h
        morphodita/morpho/english_lemma_addinfo.h
        morphodita/morpho/english_morpho.cpp
        morphodita/morpho/english_morpho.h
        morphodita/morpho/english_morpho_encoder.cpp
        morphodita/morpho/english_morpho_encoder.h
        morphodita/morpho/english_morpho_guesser.cpp
        morphodita/morpho/english_morpho_guesser.h
        morphodita/morpho/english_morpho_guesser_encoder.cpp
        morphodita/morpho/english_morpho_guesser_encoder.h
        morphodita/morpho/external_morpho.cpp
        morphodita/morpho/external_morpho.h
        morphodita/morpho/external_morpho_encoder.cpp
        morphodita/morpho/external_morpho_encoder.h
        morphodita/morpho/generic_lemma_addinfo.h
        morphodita/morpho/generic_morpho.cpp
        morphodita/morpho/generic_morpho.h
        morphodita/morpho/generic_morpho_encoder.cpp
        morphodita/morpho/generic_morpho_encoder.h
        morphodita/morpho/morpho.cpp
        morphodita/morpho/morpho.h
        morphodita/morpho/morpho_dictionary.h
        morphodita/morpho/morpho_dictionary_encoder.h
        morphodita/morpho/morpho_ids.h
        morphodita/morpho/morpho_prefix_guesser.h
        morphodita/morpho/morpho_prefix_guesser_encoder.cpp
        morphodita/morpho/morpho_prefix_guesser_encoder.h
        morphodita/morpho/morpho_statistical_guesser.cpp
        morphodita/morpho/morpho_statistical_guesser.h
        morphodita/morpho/morpho_statistical_guesser_encoder.cpp
        morphodita/morpho/morpho_statistical_guesser_encoder.h
        morphodita/morpho/morpho_statistical_guesser_trainer.cpp
        morphodita/morpho/morpho_statistical_guesser_trainer.h
        morphodita/morpho/persistent_unordered_map.h
        morphodita/morpho/persistent_unordered_map_encoder.h
        morphodita/morpho/raw_morpho_dictionary_reader.cpp
        morphodita/morpho/raw_morpho_dictionary_reader.h
        morphodita/morpho/small_stringops.h
        morphodita/morpho/tag_filter.cpp
        morphodita/morpho/tag_filter.h
        morphodita/tagger/conllu_elementary_features.h
        morphodita/tagger/czech_elementary_features.h
        morphodita/tagger/elementary_features.h
        morphodita/tagger/elementary_features_encoder.h
        morphodita/tagger/feature_sequences.h
        morphodita/tagger/feature_sequences_encoder.h
        morphodita/tagger/feature_sequences_optimizer.h
        morphodita/tagger/generic_elementary_features.h
        morphodita/tagger/perceptron_tagger.h
        morphodita/tagger/perceptron_tagger_trainer.h
        morphodita/tagger/tagger.cpp
        morphodita/tagger/tagger.h
        morphodita/tagger/tagger_ids.h
        morphodita/tagger/tagger_trainer.h
        morphodita/tagger/training_maps.h
        morphodita/tagger/viterbi.h
        morphodita/tagger/vli.h
        morphodita/tagset_converter/identity_tagset_converter.cpp
        morphodita/tagset_converter/identity_tagset_converter.h
        morphodita/tagset_converter/pdt_to_conll2009_tagset_converter.cpp
        morphodita/tagset_converter/pdt_to_conll2009_tagset_converter.h
        morphodita/tagset_converter/strip_lemma_comment_tagset_converter.cpp
        morphodita/tagset_converter/strip_lemma_comment_tagset_converter.h
        morphodita/tagset_converter/strip_lemma_id_tagset_converter.cpp
        morphodita/tagset_converter/strip_lemma_id_tagset_converter.h
        morphodita/tagset_converter/tagset_converter.cpp
        morphodita/tagset_converter/tagset_converter.h
        morphodita/tokenizer/czech_tokenizer.cpp
        morphodita/tokenizer/czech_tokenizer.h
        morphodita/tokenizer/english_tokenizer.cpp
        morphodita/tokenizer/english_tokenizer.h
        morphodita/tokenizer/generic_tokenizer.cpp
        morphodita/tokenizer/generic_tokenizer.h
        morphodita/tokenizer/generic_tokenizer_factory.cpp
        morphodita/tokenizer/generic_tokenizer_factory.h
        morphodita/tokenizer/generic_tokenizer_factory_encoder.cpp
        morphodita/tokenizer/generic_tokenizer_factory_encoder.h
        morphodita/tokenizer/gru_tokenizer.cpp
        morphodita/tokenizer/gru_tokenizer.h
        morphodita/tokenizer/gru_tokenizer_factory.cpp
        morphodita/tokenizer/gru_tokenizer_factory.h
        morphodita/tokenizer/gru_tokenizer_network.cpp
        morphodita/tokenizer/gru_tokenizer_network.h
        morphodita/tokenizer/gru_tokenizer_network_trainer.h
        morphodita/tokenizer/gru_tokenizer_trainer.cpp
        morphodita/tokenizer/gru_tokenizer_trainer.h
        morphodita/tokenizer/ragel_tokenizer.cpp
        morphodita/tokenizer/ragel_tokenizer.h
        morphodita/tokenizer/tokenizer.cpp
        morphodita/tokenizer/tokenizer.h
        morphodita/tokenizer/tokenizer_factory.cpp
        morphodita/tokenizer/tokenizer_factory.h
        morphodita/tokenizer/tokenizer_ids.h
        morphodita/tokenizer/unicode_tokenizer.cpp
        morphodita/tokenizer/unicode_tokenizer.h
        morphodita/tokenizer/vertical_tokenizer.cpp
        morphodita/tokenizer/vertical_tokenizer.h
        morphodita/version/version.cpp
        morphodita/version/version.h
        parsito/configuration/configuration.cpp
        parsito/configuration/configuration.h
        parsito/configuration/node_extractor.cpp
        parsito/configuration/node_extractor.h
        parsito/configuration/value_extractor.cpp
        parsito/configuration/value_extractor.h
        parsito/embedding/embedding.cpp
        parsito/embedding/embedding.h
        parsito/embedding/embedding_encode.cpp
        parsito/network/activation_function.h
        parsito/network/network_parameters.h
        parsito/network/neural_network.cpp
        parsito/network/neural_network.h
        parsito/network/neural_network_trainer.cpp
        parsito/network/neural_network_trainer.h
        parsito/parser/parser.cpp
        parsito/parser/parser.h
        parsito/parser/parser_nn.cpp
        parsito/parser/parser_nn.h
        parsito/parser/parser_nn_trainer.cpp
        parsito/parser/parser_nn_trainer.h
        parsito/transition/transition.cpp
        parsito/transition/transition.h
        parsito/transition/transition_oracle.h
        parsito/transition/transition_system.cpp
        parsito/transition/transition_system.h
        parsito/transition/transition_system_link2.cpp
        parsito/transition/transition_system_link2.h
        parsito/transition/transition_system_projective.cpp
        parsito/transition/transition_system_projective.h
        parsito/transition/transition_system_swap.cpp
        parsito/transition/transition_system_swap.h
        parsito/tree/node.h
        parsito/tree/tree.cpp
        parsito/tree/tree.h
        parsito/tree/tree_format.cpp
        parsito/tree/tree_format.h
        parsito/tree/tree_format_conllu.cpp
        parsito/tree/tree_format_conllu.h
        parsito/version/version.cpp
        parsito/version/version.h
#        rest_server/microrestd/libmicrohttpd/autoinit_funcs.h
#        rest_server/microrestd/libmicrohttpd/connection.cpp
#        rest_server/microrestd/libmicrohttpd/connection.h
#        rest_server/microrestd/libmicrohttpd/daemon.cpp
#        rest_server/microrestd/libmicrohttpd/internal.cpp
#        rest_server/microrestd/libmicrohttpd/internal.h
#        rest_server/microrestd/libmicrohttpd/memorypool.cpp
#        rest_server/microrestd/libmicrohttpd/memorypool.h
#        rest_server/microrestd/libmicrohttpd/MHD_config.h
#        rest_server/microrestd/libmicrohttpd/microhttpd.h
#        rest_server/microrestd/libmicrohttpd/platform.h
#        rest_server/microrestd/libmicrohttpd/platform_interface.h
#        rest_server/microrestd/libmicrohttpd/postprocessor.cpp
#        rest_server/microrestd/libmicrohttpd/reason_phrase.cpp
#        rest_server/microrestd/libmicrohttpd/reason_phrase.h
#        rest_server/microrestd/libmicrohttpd/response.cpp
#        rest_server/microrestd/libmicrohttpd/response.h
#        rest_server/microrestd/libmicrohttpd/tsearch.h
#        rest_server/microrestd/libmicrohttpd/w32functions.cpp
#        rest_server/microrestd/libmicrohttpd/w32functions.h
#        rest_server/microrestd/pugixml/pugiconfig.h
#        rest_server/microrestd/pugixml/pugixml.cpp
#        rest_server/microrestd/pugixml/pugixml.h
#        rest_server/microrestd/rest_server/json_builder.cpp
#        rest_server/microrestd/rest_server/json_builder.h
#        rest_server/microrestd/rest_server/json_response_generator.cpp
#        rest_server/microrestd/rest_server/json_response_generator.h
#        rest_server/microrestd/rest_server/response_generator.h
#        rest_server/microrestd/rest_server/rest_request.h
#        rest_server/microrestd/rest_server/rest_server.cpp
#        rest_server/microrestd/rest_server/rest_server.h
#        rest_server/microrestd/rest_server/rest_service.h
#        rest_server/microrestd/rest_server/string_piece.h
#        rest_server/microrestd/rest_server/version.cpp
#        rest_server/microrestd/rest_server/version.h
#        rest_server/microrestd/rest_server/xml_builder.cpp
#        rest_server/microrestd/rest_server/xml_builder.h
#        rest_server/microrestd/rest_server/xml_response_generator.cpp
#        rest_server/microrestd/rest_server/xml_response_generator.h
#        rest_server/microrestd/microrestd.h
#        rest_server/microrestd/pugixml.h
#        rest_server/udpipe_server.cpp
#        rest_server/udpipe_service.cpp
#        rest_server/udpipe_service.h
        sentence/empty_node.h
        sentence/input_format.cpp
        sentence/input_format.h
        sentence/multiword_token.h
        sentence/output_format.cpp
        sentence/output_format.h
        sentence/sentence.cpp
        sentence/sentence.h
        sentence/token.cpp
        sentence/token.h
        sentence/word.h
        tokenizer/detokenizer.cpp
        tokenizer/detokenizer.h
        tokenizer/morphodita_tokenizer_wrapper.cpp
        tokenizer/morphodita_tokenizer_wrapper.h
        tokenizer/multiword_splitter.cpp
        tokenizer/multiword_splitter.h
        tokenizer/multiword_splitter_trainer.cpp
        tokenizer/multiword_splitter_trainer.h
        trainer/trainer.cpp
        trainer/trainer.h
        trainer/trainer_morphodita_parsito.cpp
        trainer/trainer_morphodita_parsito.h
        trainer/training_failure.cpp
        trainer/training_failure.h
        unilib/unicode.cpp
        unilib/unicode.h
        unilib/uninorms.cpp
        unilib/uninorms.h
        unilib/unistrip.cpp
        unilib/unistrip.h
        unilib/utf16.cpp
        unilib/utf16.h
        unilib/utf8.cpp
        unilib/utf8.h
        unilib/version.cpp
        unilib/version.h
        utils/binary_decoder.h
        utils/binary_encoder.h
        utils/common.h
        utils/compressor.h
        utils/compressor_load.cpp
        utils/compressor_save.cpp
        utils/getpara.h
        utils/getwhole.h
        utils/iostreams.h
        utils/named_values.h
        utils/new_unique_ptr.h
        utils/options.cpp
        utils/options.h
        utils/parse_double.h
        utils/parse_int.h
        utils/pointer_decoder.h
        utils/process_args.h
        utils/split.h
        utils/string_piece.h
        utils/threadsafe_stack.h
        utils/url_detector.cpp
        utils/url_detector.h
        utils/xml_encoded.h
        version/version.cpp
        version/version.h
        common.h
        udpipe.cpp mi/guesser.cpp mi/guesser.h mi/guesser.cpp mi/guesser.h mi/static.cpp mi/static.h mi/nodejs.cpp mi/nodejs.h)

add_executable(src ${SOURCE_FILES})
include_directories(.)

find_package(Boost 1.63 COMPONENTS locale)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(src ${Boost_LIBRARIES})
endif()