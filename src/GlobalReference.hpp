//
//  GlobalReference.hpp
//  integral
//
//  Copyright (C) 2016  André Pereira Henriques
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

#ifndef integral_GlobalReference_hpp
#define integral_GlobalReference_hpp

#include <memory>
#include <string>
#include <lua.hpp>

namespace integral {
    namespace detail {
        class GlobalReference {
        public:
            inline GlobalReference(const std::shared_ptr<lua_State> &luaState);
            
            inline lua_State * getLuaState() const;
            inline void push() const;
            inline std::string getReferenceString() const;
            
        private:
            std::shared_ptr<lua_State> luaState_;
        };
        
        //--
        
        inline GlobalReference::GlobalReference(const std::shared_ptr<lua_State> &luaState) : luaState_(luaState) {}
        
        inline lua_State * GlobalReference::getLuaState() const {
            return luaState_.get();
        }
        
        inline void GlobalReference::push() const {
            lua_pushglobaltable(getLuaState());
        }
        
        inline std::string GlobalReference::getReferenceString() const {
            return std::string("_G");
        }
    }
}

#endif
