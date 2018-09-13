/* magic.cpp - magic number checks
 * Copyright (C) 2018  Bruno Mondelo

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <magic>

bool imagencmp(image& img, unsigned char *s, int n, std::streampos offset);
/* Data comparer */

bool
imagencmp(image& img, unsigned char *s, int n, std::streampos offset) {
  bool val;
  char *buff;
  std::streamsize size;

  val = true;

  buff = new char[n];

  size = img.read(buff, n, offset);
  if (size != n)
    val = false;
  else
    if (memcmp(buff, s, static_cast<size_t>(n) != 0))
      val = false;

  delete[] buff;

  return val;
}
/* Data comparer */

bool
magic::elf32(image& img) {
  unsigned char signature[4] = {0x7f, 0x45, 0x4c, 0x46};
  unsigned char bit32[1] = {0x01};

  if (!imagencmp(img, signature, 4, 0x0))
    return false;

  if (!imagencmp(img, bit32, 1, 0x04))
    return false;

  return true;
}
/* Executable and Linkable Format 32 bits */

bool
magic::elf64(image& img) {
  unsigned char signature[4] = {0x7f, 0x45, 0x4c, 0x46};
  unsigned char bit64[1] = {0x02};

  if (!imagencmp(img, signature, 4, 0x0))
    return false;

  if (!imagencmp(img, bit64, 1, 0x04))
    return false;

  return true;
}
/* Executable and Linkable Format 32 bits */

bool
magic::flac(image& img) {
  unsigned char signature[4] = {0x66, 0x4c, 0x61, 0x43};

  if (!imagencmp(img, signature, 4, 0x00))
    return false;

  return true;
}
/* Free Lossless Audio Codec */

bool
magic::gzip(image& img) {
  unsigned char signature[2] = {0x1f, 0x8b};

  if (!imagencmp(img, signature, 2, 0x00))
    return false;

  return true;
}
/* GNU Zip */

bool
magic::iso9660(image& img) {
  unsigned char signature[5] = {0x43, 0x44, 0x30, 0x30, 0x31};

  if (!imagencmp(img, signature, 5, 0x8001) &&
  !imagencmp(img, signature, 5, 0x8801) &&
  !imagencmp(img, signature, 5, 0x9001))
    return false;

  return true;
}
/* ISO9660 */

bool
magic::midi(image& img) {
  unsigned char signature[4] = {0x4d, 0x54, 0x68, 0x64};

  if (!imagencmp(img, signature, 4, 0x00))
    return false;

  return true;
}
/* Musical Instrument Digital Interface */

bool
magic::nes(image& img) {
  unsigned char signature[4] = {0x4e, 0x45, 0x53, 0x1};

  if (!imagencmp(img, signature, 4, 0x00))
    return false;

  return true;
}
/* Nintendo Entertainment System */

bool
magic::ogg(image& img) {
  unsigned char signature[4] = {0x4f, 0x67, 0x67, 0x53};

  if (!imagencmp(img, signature, 4, 0x00))
    return false;

  return true;
}
/* Ogg */

bool
magic::zip(image& img) {
  unsigned char signature[4] = {0x50, 0x4b, 0x03, 0x04};
  unsigned char signature_empty[4] = {0x50, 0x4b, 0x05, 0x06};
  unsigned char signature_spanned[4] = {0x50, 0x4b, 0x07, 0x08};

  if (!imagencmp(img, signature, 4, 0x00) &&
    !imagencmp(img, signature_empty, 4, 0x00) &&
    !imagencmp(img, signature_spanned, 4, 0x00))
    return false;

  return true;
}
/* Zip */
/* TODO : split ZIP into subtypes */
