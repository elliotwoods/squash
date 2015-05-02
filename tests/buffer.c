#include "test-codecs.h"

void
check_codec (SquashCodec* codec) {
  size_t compressed_length = squash_codec_get_max_compressed_size (codec, LOREM_IPSUM_LENGTH);
  size_t uncompressed_length = LOREM_IPSUM_LENGTH;
  uint8_t* compressed = (uint8_t*) malloc (compressed_length);
  uint8_t* uncompressed = (uint8_t*) malloc (LOREM_IPSUM_LENGTH);
  SquashStatus res;
  size_t pos = 0;

  res = squash_codec_compress_with_options (codec, &compressed_length, compressed, LOREM_IPSUM_LENGTH, (uint8_t*) LOREM_IPSUM, NULL);
  SQUASH_ASSERT_OK(res);

  res = squash_codec_decompress_with_options (codec, &uncompressed_length, uncompressed, compressed_length, compressed, NULL);
  SQUASH_ASSERT_OK(res);

  if (uncompressed_length != LOREM_IPSUM_LENGTH) {
    g_critical ("Decompressed data is %zu bytes, expected %zu", uncompressed_length, LOREM_IPSUM_LENGTH);
  }

  for (pos = 0 ; pos < uncompressed_length && pos < LOREM_IPSUM_LENGTH ; pos++) {
    if (uncompressed[pos] != LOREM_IPSUM[pos]) {
      g_error ("Decompressed data differs from the original at offset %zu", pos);
    }
  }
  g_assert (pos == uncompressed_length && pos == LOREM_IPSUM_LENGTH);

  free (compressed);
  free (uncompressed);
}
