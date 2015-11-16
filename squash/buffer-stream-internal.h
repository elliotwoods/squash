/* Copyright (c) 2013 The Squash Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *   Evan Nemerson <evan@nemerson.com>
 */
/* IWYU pragma: private, include <squash/internal.h> */

#ifndef SQUASH_BUFFER_STREAM_INTERNAL_H
#define SQUASH_BUFFER_STREAM_INTERNAL_H

#if !defined (SQUASH_COMPILATION)
#error "This is internal API; you cannot use it."
#endif

SQUASH_BEGIN_DECLS

#ifndef SQUASH_BUFFER_STREAM_BUFFER_SIZE
#  define SQUASH_BUFFER_STREAM_BUFFER_SIZE (4096 - sizeof (SquashSList))
#endif

typedef struct SquashBufferStreamSList_ {
  SquashSList base;
  uint8_t data[SQUASH_BUFFER_STREAM_BUFFER_SIZE];
} SquashBufferStreamSList;

typedef struct SquashBufferStream_ {
  SquashStream base_object;

  SquashBuffer* input;
  SquashBuffer* output;
  size_t output_pos;
} SquashBufferStream;

SQUASH_NONNULL(1)
SquashBufferStream* squash_buffer_stream_new     (SquashCodec* codec, SquashStreamType stream_type, SquashOptions* options);
SQUASH_NONNULL(1)
SquashStatus        squash_buffer_stream_process (SquashBufferStream* stream);
SQUASH_NONNULL(1)
SquashStatus        squash_buffer_stream_finish  (SquashBufferStream* stream);
SQUASH_NONNULL(1)
SquashStatus        squash_buffer_stream_reset   (SquashBufferStream* stream);

SQUASH_END_DECLS

#endif /* SQUASH_BUFFER_STREAM_INTERNAL_H */
