--
--  showcase.lua
--  integral
--
--  Copyright (C) 2013, 2014, 2015  André Pereira Henriques
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

-- This sample does NOT show all integral features (only part of its capability)
local showcase = require("libshowcase")
-- no problem loading multiple integral libraries (no problem loading _any_ other library)

package.cpath = package.cpath .. ";otherlib/?.so;otherlib/?.dylib"
local otherlib = require("libotherlib")
print("-> libotherlib:")
print("otherlib.getMessage()", otherlib.getMessage())

print("\n-> Base class:")
baseObject = showcase.Base.new(42.1)
print("baseObject:getNumber():", baseObject:getNumber())
baseObject:setNumber(84.2)
print("baseObject:getNumber():", baseObject:getNumber())
-- number error due to float c type argument in c function (to avoid it, use double c type)
print("baseObject:getSum(21.1):", baseObject:getSum(21.1))

print("\n-> Derived class:")

derivedObject = showcase.Derived.new(-0.1, "string of Derived")
print("derivedObject:getNumber():", derivedObject:getNumber())
-- alternative way of calling method
print("showcase.Derived.getNumber(derivedObject):", showcase.Derived.getNumber(derivedObject))
print("derivedObject:getString():", derivedObject:getString())
print("derivedObject:getConcatenated(\" + extra string\"):", derivedObject:getConcatenated(" + extra string"))
print("derivedObject:__tostring():", derivedObject)
print("derivedObject:getNumberAndString():", derivedObject:getNumberAndString())

print("\n-> Inheritance and functions:")

-- number error due to float c type argument in c function (to avoid it, use double c type)
-- calling Base metatable class with a Derived object
print("showcase.Base.getSum(derivedObject, 21.1):", showcase.Base.getSum(derivedObject, 21.1))
-- or using inheritance:
 print("derivedObject:getSum(21.1)", derivedObject:getSum(21.1))
print("showcase.getSumBase(derivedObject, showcase.Base.new(-2)):getNumber():", showcase.getSumBase(derivedObject, showcase.Base.new(-2)):getNumber());
print("showcase.getSumBase(showcase.Base.new(-2), derivedObject):getNumber():", showcase.getSumBase(showcase.Base.new(-2), derivedObject):getNumber());

print("\n-> Error handling:")
local _, message = pcall(function() showcase.throwCppException("c++ exception test message") end)
print("Expected C++ exception error:", message)
local _, message = pcall(function() showcase.getSumBase(42) end)
print("Expected wrong function parameter error:", message)
local _, message = pcall(function() showcase.Derived.getString(baseObject) end)
print("Expected incompatible userdata (class) function parameter error:", message)
local _, message = pcall(function() showcase.Derived.getNumberAndString(nil) end)
print("Expected integral::get<T> error:", message)
local _, message = pcall(function() showcase.Derived.getNumberAndString(otherlib.getDummyObject()) end)
print("Expected incompatible usedata from other library error:", message)

print("\nEnd of showcase")
