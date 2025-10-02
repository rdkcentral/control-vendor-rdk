/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <glib.h>
#include "ctrlm_private/ctrlm_voice_packet_analysis.h"

#define SEQUENCE_NUM_INVALID  (0xFF)

class ctrlm_voice_packet_analysis_rf4ce_t : public ctrlm_voice_packet_analysis {
   public:
      ctrlm_voice_packet_analysis_rf4ce_t();
      virtual void reset();
      virtual ctrlm_voice_packet_analysis_result_t packet_check(const void* header, unsigned long header_len, const void* data, unsigned long data_len);
      virtual void stats_get(ctrlm_voice_packet_analysis_stats_t& stats) const;
   private:
      guchar                           sequence_num_last;
      guint32                          total_packets;
      guint32                          duplicated_packets;
      guint32                          lost_packets;
      guint32                          sequence_error_count;
};

ctrlm_voice_packet_analysis_rf4ce_t::ctrlm_voice_packet_analysis_rf4ce_t() :
   sequence_num_last(SEQUENCE_NUM_INVALID),
   total_packets(0),
   duplicated_packets(0),
   lost_packets(0),
   sequence_error_count(0)
   {
   }

void ctrlm_voice_packet_analysis_rf4ce_t::reset() {
   sequence_num_last = 0x20;
   total_packets = 0;
   duplicated_packets = 0;
   lost_packets = 0;
   sequence_error_count = 0;
}

ctrlm_voice_packet_analysis_result_t ctrlm_voice_packet_analysis_rf4ce_t::packet_check(const void* header, unsigned long header_len, const void* data, unsigned long data_len) {
   ctrlm_voice_packet_analysis_result_t result = CTRLM_VOICE_PACKET_ANALYSIS_GOOD;
   return result;
}

void ctrlm_voice_packet_analysis_rf4ce_t::stats_get(ctrlm_voice_packet_analysis_stats_t& stats) const {
   stats.total_packets = total_packets;
   stats.bad_packets = 0;
   stats.duplicated_packets = duplicated_packets;
   stats.lost_packets = lost_packets;
   stats.sequence_error_count = sequence_error_count;
}

ctrlm_voice_packet_analysis* ctrlm_voice_packet_analysis_factory() {
   return new ctrlm_voice_packet_analysis_rf4ce_t;
}
