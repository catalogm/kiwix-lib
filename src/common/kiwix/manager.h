/*
 * Copyright 2011 Emmanuel Engelhart <kelson@kiwix.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef KIWIX_MANAGER_H
#define KIWIX_MANAGER_H

#include <kiwix/library.h>
#include <kiwix/reader.h>
#include <string>
#include <sstream>
#include "time.h"

using namespace std;

namespace kiwix {

  class Manager {
    
  public:
    Manager();
    ~Manager();

    bool readFile(const string path);
    bool writeFile(const string path);
    bool removeBookByIndex(const unsigned int bookIndex);
    bool removeBookById(const string id);
    bool addBookFromPath(const string path, const string url = "");
    Library cloneLibrary();
    
  protected:
    kiwix::Library library;
    
    bool readBookFromPath(const string path, kiwix::Book &book);
  };

}

#endif
