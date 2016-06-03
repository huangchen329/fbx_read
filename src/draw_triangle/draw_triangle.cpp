//画三角形
//#include <sb7.h>
//#include <shader.h>
//
//class simpleclear_app : public sb7::application
//{
//    void init()
//    {
//        static const char title[] = "OpenGL SuperBible - Simple Clear";
//
//        sb7::application::init();
//
//        memcpy(info.title, title, sizeof(title));
//    }
//
//	virtual void render(double currentTime)
//	{
//		static const GLfloat red[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		glClearBufferfv(GL_COLOR, 0, red);
//		glUseProgram(draw_triangle_program);
//		//glPointSize(20.0f);
//		//GLfloat attrib[] = {(float)sin(currentTime) * 0.5f,
//		//					(float)cos(currentTime) * 0.6f,
//		//					0.0f, 0.0f };
//		//// Update the value of input attribute 0
//		//glVertexAttrib4fv(0, attrib);
//		GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
//		glVertexAttrib4fv(1, color);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//    }
//
//	virtual void startup()
//	{
//		load_shader();
//		glGenVertexArrays(1, &vertex_array_object);
//		glBindVertexArray(vertex_array_object);
//	}
//
//	void load_shader();
//
//private:
//	 GLuint				draw_triangle_program;
//	 GLuint				vertex_array_object;
//};
//
//DECLARE_MAIN(simpleclear_app)
//
//
//void simpleclear_app::load_shader()
//	{
//		GLuint vs;
//		GLuint fs;
//
//		vs = sb7::shader::load("media/shaders/draw_triangle/draw_triangle.vs.glsl", GL_VERTEX_SHADER);
//		fs = sb7::shader::load("media/shaders/draw_triangle/draw_triangle.fs.glsl", GL_FRAGMENT_SHADER);
//
//		draw_triangle_program = glCreateProgram();
//		glAttachShader(draw_triangle_program, vs);
//		glAttachShader(draw_triangle_program, fs);
//		glLinkProgram(draw_triangle_program);
//
//		glDeleteShader(vs);
//		glDeleteShader(fs);
//	}

//使用贴图
//#include <sb7.h>
//#include <shader.h>
//#include <sb7ktx.h>
//
//class simpleclear_app : public sb7::application
//{
//    void init()
//    {
//        static const char title[] = "OpenGL SuperBible - Simple Clear";
//
//        sb7::application::init();
//
//        memcpy(info.title, title, sizeof(title));
//    }
//
//	virtual void render(double currentTime)
//	{
//		static const GLfloat red[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		glClearBufferfv(GL_COLOR, 0, red);
//		glBindVertexArray(vao);
//		// Now bind it to the context using the GL_TEXTURE_2D binding point
//        glBindTexture(GL_TEXTURE_2D, texture);
//		glUseProgram(program);
//		glViewport(0, 0, info.windowWidth, info.windowHeight);
//		GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
//		glVertexAttrib4fv(1, color);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//    }
//
//	virtual void startup()
//	{
//		GLfloat vertices[] = {
//
//			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // 右上角
//			1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 右下角
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,// 左下角
//			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f // 左上角
//		};
//
//		GLuint indices[] = { // 起始于0!
//
//			0, 1, 3, // 第一个三角形
//			1, 2, 3  // 第二个三角形
//		};
//		GLuint vbo;
//		GLuint ebo;
//
//
//		load_shader();
//		glGenTextures(1, &texture);
//        // Load texture from file
//        sb7::ktx::file::load("media/textures/brick.ktx", texture);
//
//		glGenVertexArrays(1, &vao);
//		glBindVertexArray(vao);
//		glGenBuffers(1, &vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, vao);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), NULL);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
//		glEnableVertexAttribArray(1);
//		glGenBuffers(1, &ebo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//		glBindVertexArray(0);
//	}
//
//	void load_shader();
//
//private:
//	 GLuint				program;
//	 GLuint				vao;
//	 GLuint				texture;
//
//};
//
//DECLARE_MAIN(simpleclear_app)
//
//
//void simpleclear_app::load_shader()
//	{
//		GLuint vs;
//		GLuint fs;
//
//		vs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.vs.glsl", GL_VERTEX_SHADER);
//		fs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.fs.glsl", GL_FRAGMENT_SHADER);
//
//		program = glCreateProgram();
//		glAttachShader(program, vs);
//		glAttachShader(program, fs);
//		glLinkProgram(program);
//
//		glDeleteShader(vs);
//		glDeleteShader(fs);
//	}

//两个贴图融合

//#include <sb7.h>
//#include <shader.h>
//#include <sb7ktx.h>
//
//class simpleclear_app : public sb7::application
//{
//    void init()
//    {
//        static const char title[] = "OpenGL SuperBible - Simple Clear";
//
//        sb7::application::init();
//
//        memcpy(info.title, title, sizeof(title));
//    }
//
//	virtual void render(double currentTime)
//	{
//		static const GLfloat red[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		glClearBufferfv(GL_COLOR, 0, red);
//		glUseProgram(program);
//		glBindVertexArray(vao);
//		// Now bind it to the context using the GL_TEXTURE_2D binding point
//		glActiveTexture(GL_TEXTURE0); 
//        glBindTexture(GL_TEXTURE_2D, texture);
//		glUniform1i(glGetUniformLocation(program, "ourTexture1"), 0);
//		glActiveTexture(GL_TEXTURE1); 
//        glBindTexture(GL_TEXTURE_2D, texture1);
//		glUniform1i(glGetUniformLocation(program, "ourTexture2"), 1);
//		glViewport(0, 0, info.windowWidth, info.windowHeight);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//    }
//
//	virtual void startup()
//	{
//		GLfloat vertices[] = {
//
//			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // 右上角
//			1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 右下角
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,// 左下角
//			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f // 左上角
//		};
//
//		GLuint indices[] = { // 起始于0!
//
//			0, 1, 3, // 第一个三角形
//			1, 2, 3  // 第二个三角形
//		};
//		GLuint vbo;
//		GLuint ebo;
//
//
//		load_shader();
//		glActiveTexture(GL_TEXTURE0); 
//		glGenTextures(1, &texture);
//        // Load texture from file
//        sb7::ktx::file::load("media/textures/brick.ktx", texture);
//		glActiveTexture(GL_TEXTURE1); 
//		glGenTextures(1, &texture1);
//        // Load texture from file
//        sb7::ktx::file::load("media/textures/floor.ktx", texture1);
//
//		glGenVertexArrays(1, &vao);
//		glBindVertexArray(vao);
//		glGenBuffers(1, &vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, vao);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), NULL);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
//		glEnableVertexAttribArray(1);
//		glGenBuffers(1, &ebo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//		glBindVertexArray(0);
//	}
//
//	void load_shader();
//
//private:
//	 GLuint				program;
//	 GLuint				vao;
//	 GLuint				texture;
//	 GLuint				texture1;
//
//};
//
//DECLARE_MAIN(simpleclear_app)
//
//
//void simpleclear_app::load_shader()
//	{
//		GLuint vs;
//		GLuint fs;
//
//		vs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.vs.glsl", GL_VERTEX_SHADER);
//		fs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.fs.glsl", GL_FRAGMENT_SHADER);
//
//		program = glCreateProgram();
//		glAttachShader(program, vs);
//		glAttachShader(program, fs);
//		glLinkProgram(program);
//
//		glDeleteShader(vs);
//		glDeleteShader(fs);
//	}

//旋转物体k
#include <sb7.h>
#include <shader.h>
#include <sb7ktx.h>
#include <vmath.h>

class simpleclear_app : public sb7::application
{
    void init()
    {
        static const char title[] = "OpenGL SuperBible - Simple Clear";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

	virtual void render(double currentTime)
	{
		glViewport(0, 0, info.windowWidth, info.windowHeight);
		static const GLfloat red[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);
		glUseProgram(program);
		glBindVertexArray(vao);
		// Now bind it to the context using the GL_TEXTURE_2D binding point
		glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1); 
        glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(program, "ourTexture2"), 1);
		glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, vmath::translate((float)1, (float)1, (float)0));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
    }

	virtual void startup()
	{
		GLfloat vertices[] = {

			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // 右上角
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 右下角
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,// 左下角
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f // 左上角
		};

		GLuint indices[] = { // 起始于0!

			0, 1, 3, // 第一个三角形
			1, 2, 3  // 第二个三角形
		};
		GLuint vbo;
		GLuint ebo;


		load_shader();
		glActiveTexture(GL_TEXTURE0); 
		glGenTextures(1, &texture);
        // Load texture from file
        sb7::ktx::file::load("media/textures/brick.ktx", texture);
		glActiveTexture(GL_TEXTURE1); 
		glGenTextures(1, &texture1);
        // Load texture from file
        sb7::ktx::file::load("media/textures/floor.ktx", texture1);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), NULL);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	void load_shader();

private:
	 GLuint				program;
	 GLuint				vao;
	 GLuint				texture;
	 GLuint				texture1;

};

DECLARE_MAIN(simpleclear_app)


void simpleclear_app::load_shader()
	{
		GLuint vs;
		GLuint fs;

		vs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.vs.glsl", GL_VERTEX_SHADER);
		fs = sb7::shader::load("media/shaders/draw_triangle/draw_texture.fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}