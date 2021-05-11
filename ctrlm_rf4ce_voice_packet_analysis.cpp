
#include "../ctrlm_voice_packet_analysis.h"

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
