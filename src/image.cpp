/* image.cpp - handler for image files
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

#include <image>

image::image() {
  this->openned = false;
}
/* Constructor */

image::image(std::string fname) {
  this->openned = false;

  this->open(fname);
}
/* Constructor */

image::~image() {
  this->close();
}
/* Destructor */

int
image::set_pos(std::streampos offset) {
  if (!this->openned)
    return -1;

  this->fs.seekg(offset, this->fs.beg);
  if (this->fs.bad() || this->fs.fail())
    return -2;

  this->pos = offset;

  return 0;
}
/* Sets stream position */

void
image::open(std::string fname) {
  if (this->openned)
    return;

  this->fn = fname;

  this->fs.open(fn, std::ios::in | std::ios::binary);
  if (this->fs.bad() || this->fs.fail())
    throw std::ios_base::failure("canno't open file");

  this->pos = 0;

  this->openned = true;
}
/* Opens file */

void
image::close() {
  if (!this->openned)
    return;

  this->fs.close();

  this->pos = 0;

  this->openned = false;
}
/* Closes file */

std::streamsize
image::read(char *dest, int n, std::streampos offset) {
  std::streamsize size;

  if (!this->openned)
    return -1;

  if (offset != this->pos)
    if (this->set_pos(offset) != 0)
      return -2;

  this->fs.read(dest, n);
  size = this->fs.gcount();

  this->pos += size;

  return size;
}
/* Reads bytes from image */

#ifdef TEST

#include <cstring>

int
main(void) {
  image img;
  char buff[35];
  std::streamsize n;
  int err;

  err = 0;

  img.open("src/image.cpp");

  n = img.read(buff, 35, 3);
  if (n < 35)
    err++;

  if (strncmp(buff, "image.cpp - handler for image files", 35) != 0)
    err++;

  img.close();

  return err;
}

#endif