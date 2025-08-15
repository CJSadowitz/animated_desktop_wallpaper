#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

char* get_shader_source(const char* file_path)
{
	int char_count = 0;
	FILE* file;

	file = fopen(file_path, "r");

	if (!file)
	{
		return NULL;
	}
	while (fgetc(file) != EOF)
	{
		char_count++;
	}
	rewind(file);

	char* source_buffer = malloc((char_count + 1) * sizeof(char));
	fread(source_buffer, sizeof(char), char_count, file);
	source_buffer[char_count] = '\0';

	fclose(file);

	return source_buffer;
}

unsigned int create_shader(const char* shader_source, unsigned int shader_type)
{
	unsigned int shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	int success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		printf("%s", info_log);
	}

	return shader;
}

unsigned int compile_program(
		unsigned int vertex_shader,
		unsigned int fragment_shader)
{
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	int success;
	char info_log[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		printf("%s", info_log);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

unsigned int get_program(const char* vertex_source, const char* fragment_source)
{
	unsigned int vertex_shader   = create_shader(
			vertex_source, GL_VERTEX_SHADER); 
	unsigned int fragment_shader = create_shader(
			fragment_source, GL_FRAGMENT_SHADER);
	unsigned int program = compile_program(vertex_shader, fragment_shader);
	return program;
}

#endif

