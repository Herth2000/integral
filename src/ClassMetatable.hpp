//
//  ClassMetatable.hpp
//  integral
//
//  Copyright (C) 2017  André Pereira Henriques
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

#ifndef integral_ClassMetatable_hpp
#define integral_ClassMetatable_hpp

#include <type_traits>
#include <utility>
#include <lua.hpp>
#include "Composite.hpp"
#include "exchanger.hpp"
#include "generic.hpp"
#include "type_manager.hpp"

namespace integral {
    // T: class type
    // B...: base classes types
    template<typename T, typename ...B>
    class ClassMetatable {
    public:
        // non-copyable
        ClassMetatable(const ClassMetatable &) = delete;
        ClassMetatable & operator=(const ClassMetatable &) = delete;

        ClassMetatable(ClassMetatable &&) = default;
        ClassMetatable() = default;

        template<typename K, typename V>
        inline detail::Composite<ClassMetatable<T, B...>, typename std::decay<K>::type, typename std::decay<V>::type> set(K&& key, V &&value) &&;
    };

    namespace detail {
        namespace exchanger {
            template<typename T, typename ...B>
            class Exchanger<ClassMetatable<T, B...>> {
            public:
                inline static void push(lua_State *luaState);
                inline static void push(lua_State *luaState, const ClassMetatable<T, B...> &);
            };
        }
    }

    //--

    template<typename T, typename ...B>
    template<typename K, typename V>
    inline detail::Composite<ClassMetatable<T, B...>, typename std::decay<K>::type, typename std::decay<V>::type> ClassMetatable<T, B...>::set(K&& key, V &&value) && {
        return detail::Composite<ClassMetatable<T, B...>, typename std::decay<K>::type, typename std::decay<V>::type>(std::move(*this), std::forward<K>(key), std::forward<V>(value));
    }

    namespace detail {
        namespace exchanger {
            template<typename T, typename ...B>
            inline void Exchanger<ClassMetatable<T, B...>>::push(lua_State *luaState) {
                type_manager::pushClassMetatable<T>(luaState);
                generic::expandDummyTemplatePack((type_manager::defineInheritance<T, B>(luaState), 0)...);
            }

            template<typename T, typename ...B>
            inline void Exchanger<ClassMetatable<T, B...>>::push(lua_State *luaState, const ClassMetatable<T, B...> &) {
                push(luaState);
            }
        }
    }
}

#endif