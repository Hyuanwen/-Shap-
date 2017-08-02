#ifndef DEUDEBUG_H
#define DEUDEBUG_H

#define DEBUG
#ifdef  DEBUG

	extern long _debug_getline ;
	template<class _Elem,
	class _Traits,
	class _Alloc> inline
	basic_istream<_Elem, _Traits>& __CLRCALL_OR_CDECL GETLINE(
		basic_istream<_Elem, _Traits>& _Istr,
		basic_string<_Elem, _Traits, _Alloc>& _Str)
	{	
		_debug_getline++;		
		return (getline(_Istr, _Str));
	}

#endif

#endif