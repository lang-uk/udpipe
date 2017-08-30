cmake_minimum_required(VERSION 3.5)

project(udpipe)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)


set(MICRORESTD_FILES
        rest_server/microrestd/libmicrohttpd/connection.cpp
        rest_server/microrestd/libmicrohttpd/daemon.cpp
        rest_server/microrestd/libmicrohttpd/internal.cpp
        rest_server/microrestd/libmicrohttpd/memorypool.cpp
        rest_server/microrestd/libmicrohttpd/postprocessor.cpp
        rest_server/microrestd/libmicrohttpd/reason_phrase.cpp
        rest_server/microrestd/libmicrohttpd/response.cpp
        rest_server/microrestd/libmicrohttpd/w32functions.cpp
        rest_server/microrestd/pugixml/pugixml.cpp
        rest_server/microrestd/rest_server/json_builder.cpp
        rest_server/microrestd/rest_server/json_response_generator.cpp
        rest_server/microrestd/rest_server/rest_server.cpp
        rest_server/microrestd/rest_server/version.cpp
        rest_server/microrestd/rest_server/xml_builder.cpp
        rest_server/microrestd/rest_server/xml_response_generator.cpp
        )

set(UDPIPE_SERVER_FILES
        rest_server/udpipe_server.cpp
        rest_server/udpipe_service.cpp
        )

set(UDPIPE_CLI_FILES
        model/evaluator.cpp
        morphodita/morpho/morpho_statistical_guesser_trainer.cpp
        trainer/trainer_morphodita_parsito.cpp
        trainer/trainer.cpp
        unilib/uninorms.cpp
        unilib/unistrip.cpp
        unilib/utf16.cpp
        )

set(COMMON_FILES
        parsito/network/neural_network_trainer.cpp
        model/model.cpp
        model/model_morphodita_parsito.cpp
        model/pipeline.cpp
        morphodita/derivator/derivation_formatter.cpp
        morphodita/derivator/derivator_dictionary.cpp
        morphodita/morpho/czech_morpho.cpp
        morphodita/morpho/english_morpho.cpp
        morphodita/morpho/english_morpho_guesser.cpp
        morphodita/morpho/external_morpho.cpp
        morphodita/morpho/generic_morpho.cpp
        morphodita/morpho/generic_morpho_encoder.cpp
        morphodita/morpho/morpho.cpp
        morphodita/morpho/morpho_statistical_guesser.cpp
        morphodita/morpho/morpho_statistical_guesser_encoder.cpp
        morphodita/morpho/raw_morpho_dictionary_reader.cpp
        morphodita/morpho/tag_filter.cpp
        morphodita/tagger/tagger.cpp
        morphodita/tokenizer/czech_tokenizer.cpp
        morphodita/tokenizer/english_tokenizer.cpp
        morphodita/tokenizer/generic_tokenizer.cpp
        morphodita/tokenizer/generic_tokenizer_factory.cpp
        morphodita/tokenizer/generic_tokenizer_factory_encoder.cpp
        morphodita/tokenizer/gru_tokenizer.cpp
        morphodita/tokenizer/gru_tokenizer_factory.cpp
        morphodita/tokenizer/gru_tokenizer_network.cpp
        morphodita/tokenizer/gru_tokenizer_trainer.cpp
        morphodita/tokenizer/ragel_tokenizer.cpp
        morphodita/tokenizer/tokenizer.cpp
        morphodita/tokenizer/tokenizer_factory.cpp
        morphodita/tokenizer/unicode_tokenizer.cpp
        morphodita/tokenizer/vertical_tokenizer.cpp
        morphodita/version/version.cpp
        parsito/configuration/configuration.cpp
        parsito/configuration/node_extractor.cpp
        parsito/configuration/value_extractor.cpp
        parsito/embedding/embedding.cpp
        parsito/embedding/embedding_encode.cpp
        parsito/network/neural_network.cpp
        parsito/parser/parser.cpp
        parsito/parser/parser_nn.cpp
        parsito/parser/parser_nn_trainer.cpp
        parsito/transition/transition.cpp
        parsito/transition/transition_system.cpp
        parsito/transition/transition_system_link2.cpp
        parsito/transition/transition_system_projective.cpp
        parsito/transition/transition_system_swap.cpp
        parsito/tree/tree.cpp
        parsito/tree/tree_format.cpp
        parsito/tree/tree_format_conllu.cpp
        parsito/version/version.cpp
        sentence/input_format.cpp
        sentence/output_format.cpp
        sentence/sentence.cpp
        sentence/token.cpp
        tokenizer/detokenizer.cpp
        tokenizer/morphodita_tokenizer_wrapper.cpp
        tokenizer/multiword_splitter.cpp
        tokenizer/multiword_splitter_trainer.cpp
        trainer/training_failure.cpp
        unilib/unicode.cpp
        unilib/utf8.cpp
        unilib/version.cpp
        utils/compressor_load.cpp
        utils/compressor_save.cpp
        utils/options.cpp
        version/version.cpp
        mi/guesser.cpp
        mi/static.cpp
        )


include_directories(.)


set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Threads)

add_executable(udpipe ${COMMON_FILES} ${UDPIPE_CLI_FILES} udpipe.cpp)
add_executable(udpipe_server ${COMMON_FILES} ${MICRORESTD_FILES} ${UDPIPE_SERVER_FILES})
target_link_libraries(udpipe_server ${CMAKE_THREAD_LIBS_INIT})

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()


if (CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")

    set_property(TARGET udpipe PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    set_property(TARGET udpipe PROPERTY CXX_VISIBILITY_PRESET hidden)

    set_property(TARGET udpipe_server PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
    set_property(TARGET udpipe_server PROPERTY CXX_VISIBILITY_PRESET hidden)
endif ()

