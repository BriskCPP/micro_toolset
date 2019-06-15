#pragma once
#ifndef MICRO_UNITS__HEADER_ONLY_LIBRARY__POINTER_UTIL_H
#include<memory>

namespace micro_toolset
{
	namespace header_only_library
	{
		namespace pointer_util
		{
			template<typename Callable, unsigned int id>
			class CallableObjectHolder
			{
			private:
				static std::unique_ptr<Callable> callableObject;
			public:
				template<typename ReturnType, typename ... Arguments >
				static inline ReturnType callback(Arguments... args)
				{
					return (*callableObject)(std::forward<Arguments>(args)...);
				}

				template<typename ReturnType, typename ... Arguments >
				using c_style_function_pointer = ReturnType(*)(Arguments ... args);

				template<typename ReturnType, typename ... Arguments>
				static inline c_style_function_pointer<ReturnType, Arguments...> getPointer(
					Callable *callable
				)
				{
					callableObject = std::unique_ptr<Callable>(callable);
					return &callback<ReturnType, Arguments...>;
				}
			};
			//define static member out of the class
			template<typename Callable, unsigned int id>
			std::unique_ptr<Callable> CallableObjectHolder<Callable, id>::callableObject;
		}
	}
}
#endif // !MICRO_UNITS__HEADER_ONLY_LIBRARY__POINTER_UTIL_H
