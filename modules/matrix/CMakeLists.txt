cmake_minimum_required(VERSION 3.8)

project(matrix-console-app LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		libmatrix
)
target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/W3 /MP4
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
)