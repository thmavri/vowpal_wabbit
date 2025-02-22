// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#pragma once

#include "../../vw.h"
VW_WARNING_STATE_PUSH
VW_WARNING_DISABLE_BADLY_FORMED_XML
#include "generated/example_generated.h"
VW_WARNING_STATE_POP

namespace VW
{
namespace parsers
{
namespace flatbuffer
{
int flatbuffer_to_examples(vw* all, io_buf& buf, v_array<example*>& examples);

class parser
{
public:
  parser() = default;
  const VW::parsers::flatbuffer::ExampleRoot* data();
  bool parse_examples(vw* all, io_buf& buf, v_array<example*>& examples, uint8_t* buffer_pointer = nullptr);

private:
  const VW::parsers::flatbuffer::ExampleRoot* _data;
  uint8_t* _flatbuffer_pointer;
  flatbuffers::uoffset_t _object_size = 0;
  bool _active_collection = false;
  uint32_t _example_index = 0;
  uint32_t _multi_ex_index = 0;
  bool _active_multi_ex = false;
  const VW::parsers::flatbuffer::MultiExample* _multi_example_object = nullptr;
  uint32_t _labeled_action = 0;
  uint64_t _c_hash = 0;

  bool parse(io_buf& buf, uint8_t* buffer_pointer = nullptr);
  void process_collection_item(vw* all, v_array<example*>& examples);
  void parse_example(vw* all, example* ae, const Example* eg);
  void parse_multi_example(vw* all, example* ae, const MultiExample* eg);
  void parse_namespaces(vw* all, example* ae, const Namespace* ns);
  void parse_features(vw* all, features& fs, const Feature* feature, const flatbuffers::String* ns);
  void parse_flat_label(shared_data* sd, example* ae, const Example* eg);

  void parse_simple_label(shared_data* sd, polylabel* l, reduction_features* red_features, const SimpleLabel* label);
  void parse_cb_label(polylabel* l, const CBLabel* label);
  void parse_ccb_label(polylabel* l, const CCBLabel* label);
  void parse_cs_label(polylabel* l, const CS_Label* label);
  void parse_cb_eval_label(polylabel* l, const CB_EVAL_Label* label);
  void parse_mc_label(shared_data* sd, polylabel* l, const MultiClass* label);
  void parse_multi_label(polylabel* l, const MultiLabel* label);
  void parse_slates_label(polylabel* l, const Slates_Label* label);
  void parse_continuous_action_label(polylabel* l, const ContinuousLabel* label);
};
}  // namespace flatbuffer
}  // namespace parsers
}  // namespace VW
