--
--  function_on_stack.lua
--  integral
--
--  Copyright (C) 2014, 2015  André Pereira Henriques
--  aphenriques (at) outlook (dot) com
--
--  This file is part of integral.
--
--  integral is free software: you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation, either version 3 of the License, or
--  (at your option) any later version.
--
--  integral is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with integral.  If not, see <http://www.gnu.org/licenses/>.
--

-- MacOX specific shared library extension
package.cpath = package.cpath .. ";?.dylib"

local library = require("liblibrary")

local getPrefixed = library.getPrefixFunction("prefix-")
print(getPrefixed("word"))

local getSuffixed1 = library.getSuffixFunction1("-suffix1")
print(getSuffixed1("palavra"))

-- getSuffixFunction2 does the same as getSuffixFunction
local getSuffixed2 = library.getSuffixFunction2("-suffix2")
print(getSuffixed2("palavra"))

local object = library.newObject("object")
print(object)
