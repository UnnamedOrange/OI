#pragma once

/*===========================================
Project: datagen						   ==
										   ==
Author: Orange Software					   ==
										   ==
Description: Data generator for OI.		   ==
										   ==
Date: 2018-5-4							   ==
										   ==
Remark: This header need C++ 11.		   ==
										   ==
------									   ==
										   ==
Version: Build 2						   ==
										   ==
Update time: 2018-5-5 19:45:12			   ==
===========================================*/

// include necessary headers
#include <random>
#include <ctime>
#include <climits>

// define macro for convenience
#define verify(expression) ((expression) ? true : (throw, false))

// define macro for environment
#define _DATAGEN_BEGIN namespace datagen {
#define _DATAGEN_END }
#define _PUBLIC_BEGIN namespace Public {
#define _PUBLIC_END }

#ifndef DATAGEN
#define DATAGEN
_DATAGEN_BEGIN

namespace Random
{
	typedef short				sint16;
	typedef long				sint32;
	typedef long long			sint64;
	typedef unsigned short		uint16;
	typedef unsigned long		uint32;
	typedef unsigned long long	uint64;
	typedef float				real32;
	typedef double				real64;

	// engine: give out unsigned int
	static std::default_random_engine engine;

	// distribution: use uint stream to make random value
	typedef std::uniform_int_distribution	<sint64> ud_sint;
	typedef std::uniform_int_distribution	<uint64> ud_uint;
	typedef std::uniform_real_distribution	<real32> ud_real32;
	typedef std::uniform_real_distribution	<real64> ud_real64;
	typedef std::normal_distribution		<real64> nd_real;

	// use a uint as the seed
	void srand(uint32 seed) { engine.seed(seed); }

	_PUBLIC_BEGIN

	sint16 rand_int16() { return (sint16)ud_sint(SHRT_MIN, SHRT_MAX)(engine); }
	sint32 rand_int32() { return (sint32)ud_sint(INT_MIN, INT_MAX)(engine); }
	sint64 rand_int() { return (sint64)ud_sint(LLONG_MIN, LLONG_MAX)(engine); }
	uint16 rand_uint16() { return (uint16)ud_uint(0, USHRT_MAX)(engine); }
	uint32 rand_uint32() { return (uint32)ud_uint(0, UINT_MAX)(engine); }
	uint64 rand_uint() { return (uint64)ud_uint(0, ULLONG_MAX)(engine); }

	sint64 rand_int(sint64 l, sint64 r) { return ud_sint(l, r)(engine); }
	sint64 rand_uint(uint64 l, uint64 r) { return ud_uint(l, r)(engine); }

	real32 rand_real32() { return ud_real32()(engine); }
	real64 rand_real() { return ud_real64()(engine); }

	real32 rand_real32(real32 l, real32 r) { return ud_real32(l, r)(engine); }
	real64 rand_real(real64 l, real64 r) { return ud_real64(l, r)(engine); }

	// 3 sigma principle
	sint64 rand_int_n(real64 mean, real64 sigma) { return (sint64)nd_real(mean, sigma)(engine); }
	real64 rand_real_n(real64 mean, real64 sigma) { return nd_real(mean, sigma)(engine); }

	_PUBLIC_END
}

namespace Task
{
	// variable
	bool		bInitialized;
	std::string	strProblemName;
	bool		bEnableSubtask;
	int			idSubtask;
	int			idPoint;

	// buffer
	const int	buffer_size = 8192;
	char		buffer[buffer_size];

	_PUBLIC_BEGIN

	void Initialize(
			const char*		lpcProblemName = "data",
			bool			bEnableSt = false,
			Random::uint32	seed = (Random::uint32)std::time(NULL))
	{
		verify(!bInitialized);
		bInitialized = true;

		FILE* backup = fopen("seed.backup", "w");
		fprintf(backup, "%u", seed);
		fclose(backup);

		Random::srand(seed);
		strProblemName = lpcProblemName;
		bEnableSubtask = bEnableSt;

		idSubtask = (int)bEnableSt;
		idPoint = 0;
	}

	void NextSubtask() {
		verify(bEnableSubtask);
		idSubtask++;
		idPoint = 0;
	}

	class CaseBase
	{
		int stamp;

	protected:
		FILE * file_output;

	public:
		CaseBase() : stamp(std::clock())
		{
			verify(bInitialized);

			idPoint++;

			// get file name
			if (idSubtask)
				sprintf(buffer, "%s%d-%d.in",
					strProblemName.c_str(),
					idSubtask, idPoint);
			else
				sprintf(buffer, "%s%d.in",
					strProblemName.c_str(),
					idPoint);
			file_output = fopen(buffer, "w");
		}
		~CaseBase()
		{
			fclose(file_output);

			if (idSubtask)
				sprintf(buffer, "%s.exe < %s%d-%d.in > %s%d-%d.ans",
					strProblemName.c_str(),
					strProblemName.c_str(), idSubtask, idPoint,
					strProblemName.c_str(), idSubtask, idPoint);
			else
				sprintf(buffer, "%s.exe < %s%d.in > %s%d.ans",
					strProblemName.c_str(),
					strProblemName.c_str(), idPoint,
					strProblemName.c_str(), idPoint);

			verify(!system(buffer));

			if (idSubtask)
				printf("%s%d-%d has been generated in %d ms\n",
					strProblemName.c_str(),
					idSubtask, idPoint,
					std::clock() - stamp);
			else
				printf("%s%d has been generated in %d ms\n",
					strProblemName.c_str(),
					idPoint,
					std::clock() - stamp);
		}
	};

#define cprintf(...) fprintf(file_output, __VA_ARGS__)
#define GoCase(Case, times, ...)\
	for (int counter = 1; counter <= times; counter++)\
		delete new Case(__VA_ARGS__)

	_PUBLIC_END
}

_DATAGEN_END
#endif /* DATAGEN */

using namespace datagen::Random::Public;
using namespace datagen::Task::Public;