cmake_minimum_required(VERSION 3.8)

project(tests LANGUAGES CXX)

function(create_test name library)
	add_executable(${name} ${name}.cpp)
	target_include_directories(${name}
		PUBLIC
			${CONAN_LIBS}
	)
	target_link_libraries(${name}
		PUBLIC
			${CONAN_LIBS}
			${library}
	)
	target_compile_options(${name}
		PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:
				/W3 /MP4
				$<$<CONFIG:Debug>:/MTd>
				$<$<CONFIG:Release>:/MT>>
	)
	add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

create_test(MatrixTests libmatrix)
