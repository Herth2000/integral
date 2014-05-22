//
//  type_counter.h
//  integral
//
//  Copyright (C) 2013, 2014  André Pereira Henriques
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

#ifndef integral_type_counter_h
#define integral_type_counter_h

#include "basic.h"
#include "exchanger.h"

namespace integral {
    namespace detail {
        namespace type_counter {
            template<typename T>
            class TypeCounter {
            public:
                static constexpr unsigned getCount();
            };
            
            template<typename ...T>
            class TypeCounter<exchanger::LuaPack<T...>> {
            public:
                static constexpr unsigned getCount();
            };
            
            template<typename ...T>
            constexpr unsigned getCount();
            
            constexpr unsigned sum();
            
            template<typename ...J>
            constexpr unsigned sum(unsigned i, J... j);
            
            //--
            
            template<typename T>
            constexpr unsigned TypeCounter<T>::getCount() {
                return 1;
            }
            
            template<typename ...T>
            constexpr unsigned TypeCounter<exchanger::LuaPack<T...>>::getCount() {
                return sizeof...(T);
            }
            
            template<typename ...T>
            constexpr unsigned getCount() {
                return sum(TypeCounter<basic::BasicType<T>>::getCount()...);
            }
            
            constexpr unsigned sum() {
                return 0;
            }
            
            template<typename ...J>
            constexpr unsigned sum(unsigned i, J... j) {
                return i + sum(j...);
            }
        }
    }
}

#endif
