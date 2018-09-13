/* main.cpp - magic number checker
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

#include <iostream>
#include <image>
#include <magic>

#define PROGRAM_NAME "magician"
/* Official program name */

#define EXIT_OK 0
/* Correct exit */

#define EXIT_ERROR_USAGE 7
/* Exit error on bad usage */

int
main(int argc, char *argv[]) {
  image img;
  std::string fname;

  if (argc != 2) {
    std::cerr << PROGRAM_NAME << ": error: bad usage" << std::endl;
    std::cerr << "usage: " << PROGRAM_NAME << " FILE" << std::endl;
    return EXIT_ERROR_USAGE;
  }
  fname = argv[1];
  /* TODO : parse arguments */

  img.open(fname);
  /* TODO : check for errors */

  if (magic::elf32(img))
    std::cout << fname << " is a ELF-32 file" << std::endl;
  else if (magic::elf64(img))
    std::cout << fname << " is a ELF-64 file" << std::endl;
  else if (magic::flac(img))
    std::cout << fname << " is a FLAC file" << std::endl;
  else if (magic::gzip(img))
    std::cout << fname << " is a GZIP file" << std::endl;
  else if (magic::iso9660(img))
    std::cout << fname << " is a ISO9660 file" << std::endl;
  else if (magic::midi(img))
    std::cout << fname << " is a MIDI file" << std::endl;
  else if (magic::nes(img))
    std::cout << fname << " is a NES file" << std::endl;
  else if (magic::ogg(img))
    std::cout << fname << " is a OGG file" << std::endl;
  else if (magic::zip(img))
    std::cout << fname << " is a ZIP file" << std::endl;
  else
    std::cout << "unknown file type" << std::endl;

  return EXIT_OK;
}