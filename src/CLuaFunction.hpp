//
//  CLuaFunction.hpp
//  integral
//
//  Copyright (C) 2014, 2016  André Pereira Henriques
//  aphenriques (at) outlook (dot) com
//
//  This file is part of integral.
//
//  integral is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  integral is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with integral.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef integral_CLuaFunction_hpp
#define integral_CLuaFunction_hpp

#include <functional>
#include "Adaptor.hpp"
#include "exchanger.hpp"
#include "LuaFunctionWrapper.hpp"

namespace integral {
    namespace detail {
        using CLuaFunction = Adaptor<std::function<int(lua_State *)>>;
        
        namespace exchanger {
            template<>
            class Exchanger<CLuaFunction> {
            public:
                inline static void push(lua_State *luaState, const CLuaFunction &function);
            };
        }
        
        //--
        
        namespace exchanger {
            inline void Exchanger<CLuaFunction>::push(lua_State *luaState, const CLuaFunction &function) {
                LuaFunctionWrapper::pushFunction(luaState, function, 0);
            }
        }
    }
}

#endif