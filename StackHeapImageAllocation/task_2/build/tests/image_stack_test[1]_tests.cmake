add_test( TestImageFromPng.InitFromFileSize /home/bruno/Learning/ModernCppCV/StackHeapImageAllocation/task_2/build/tests/image_stack_test [==[--gtest_filter=TestImageFromPng.InitFromFileSize]==] --gtest_also_run_disabled_tests)
set_tests_properties( TestImageFromPng.InitFromFileSize PROPERTIES WORKING_DIRECTORY /home/bruno/Learning/ModernCppCV/StackHeapImageAllocation/task_2/tests)
add_test( TestImageFromPng.InitFromFileContents /home/bruno/Learning/ModernCppCV/StackHeapImageAllocation/task_2/build/tests/image_stack_test [==[--gtest_filter=TestImageFromPng.InitFromFileContents]==] --gtest_also_run_disabled_tests)
set_tests_properties( TestImageFromPng.InitFromFileContents PROPERTIES WORKING_DIRECTORY /home/bruno/Learning/ModernCppCV/StackHeapImageAllocation/task_2/tests)
set( image_stack_test_TESTS TestImageFromPng.InitFromFileSize TestImageFromPng.InitFromFileContents)
