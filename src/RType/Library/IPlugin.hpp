#ifndef RTYPE_LIBRARY_IPLUGIN_HPP_
#define RTYPE_LIBRARY_IPLUGIN_HPP_

# ifdef RTYPE_IS_WIN32
#  define DLL_EXPORT_KEYWORD __declspec(dllexport)
# else
#  define DLL_EXPORT_KEYWORD
# endif

# define RTYPE_PLUGIN														\
	extern "C"																\
	{																		\
		DLL_EXPORT_KEYWORD rtype::library::IPlugin* plugin_instantiate();	\
	}

namespace rtype
{
	namespace library
	{
		class IPlugin
		{
		public:
			virtual ~IPlugin() {}
		};
	} // namespace library
} // namespace rtype

#endif // RTYPE_LIBRARY_IPLUGIN_HPP_
