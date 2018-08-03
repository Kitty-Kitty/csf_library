#include "stdafx.h"
#include "CppUnitTest.h"
#include "csf_buffer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test_libcsf
{		
	TEST_CLASS(csf_buffer_test)
	{
	public:
		
		TEST_METHOD(csf_buffer_create)
		{
			// TODO: Your test code here
			csf::core::base::csf_buffer			*tmp_buf = new csf::core::base::csf_buffer(1024);
		}

	};
}